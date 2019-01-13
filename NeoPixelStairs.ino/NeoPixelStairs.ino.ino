// NeoPixel Stair Led-strips
//  
// 06-01-2019 Vinz68  Initial release     
// 11-01-2019 Vinz68  LDR sensor added    
// 13-01-2019 Vinz68  Beathe function more configurable (number of used leds, BREATHELEDS)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Configuration of the NeoPixel output
#define PIN             5         // Pin used for the NeoPixels

// How many NeoPixels are attached to the Arduino ?
#define LEDSPERSTRIP    36        // Number of leds per strip
#define LEDSTRIPS       16        // Number of stair steps (led strips)
#define NUMPIXELS       LEDSTRIPS*LEDSPERSTRIP 
#define BREATHELEDS     1         // Number of leds used in breathe function. 
                                  // NOTE:  The number indicates the number of Begin Leds and Last leds per strip 
                                  //        so with setting = "1", the first and last led of the ledstrip would be used  for the breathe function.
                                  // NOTE:  Minimal value = 0       (= no breathe function)
                                  //        Maximum value = LEDSPERSTRIP / 2  (= all leds used in the breathe function)

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// Configuration of the Passive Infrared (PIR)
int alarmPinTop = 10;             // PIR at the top of the stairs
int alarmPinBottom = 11;          // PIR at the bottom of the stairs
int alarmValueTop = LOW;          // Variable to hold the PIR status
int alarmValueBottom = LOW;       // Variable to hold the PIR status

// Configuration of the Light dependent resistor (LDR)
bool useLDR = true;               // flag, when true the program uses the LDR, set to "false" if you don't have a LDR sensor.
int LDRSensor = A0;               // Light dependent resistor, Analog Input line 
int LDRValue = 0;                 // Variable to hold the measured LDR value
int LDRThreshold = 600;           // Only switch on LED's at night when LDR senses low light conditions - you may have to change this value for your circumstances!

// Other Input/output
int ledPin = 13;                  // LED on the arduino board flashes when PIR activated

// Set up Variables for the needed program logic (DO NOT TOUCH THESE!)
unsigned long timeOut = 0;        // timestamp to remember when the PIR was triggered.
unsigned long timeLoopStart = 0;  // timestamp to remember when loop has started. used to determine the end-delay (keeps loop running in same intervals)
unsigned long timeTemp = 0;       // temp. var used in time calculations
unsigned long timeDiff = 0;       // temp. var used in time calculations
bool readPIRInputs = true;        // flag, when true, reads the PIR sensors. Disabled (false) by the program when LDR indicated that there is enough light.
int downUp = 0;                   // main program mode, The possible values are:
                                  //  0   =   Idle mode, waiting for PIR trigger to turn stairs on.
                                  //  1   =   Going down, Turning stairs on (direction up to down)
                                  //  2   =   Going up, Turnurning stairs on (direction down to up)
                                  //  3   =   Turning leds off, from top to down
                                  //  4   =   Turninf leds off, from bottom to up
                                  //  5   =   All leds just turned off. After short time, automatically mode will be set to "0".


//-------------------------------------------------------------------------------------------------------
// TUNING PART: for the Breathe effect, turn-on and turn-off speed and LDR sesonr usage
//-------------------------------------------------------------------------------------------------------
int change = 2;                 // used in 'breathing' the LED's , make value smalle to make it smoother, or higher to make it faster
int breathe = 25;               // used in 'breathing' the LED's.
int turnOnSpeed = 300;          // speed to turn on next led-strip, in msec between next strip
int turnOffSpeed = 200;         // speed to turn off next led-strip, in msec between next strip
int keepLedsOnTime = 18000;     // keep leds on for at least .. msec.
int keepLedsOffTime = 1500;     // keep leds off for at least .. msec.


void setup() {

  strip.begin();            // This initializes the NeoPixel library.
  
  strip.setBrightness(35);  // Adjust brightness here
  clearStrip();             // Initialize all pixels to 'off', and do strip.show()
  
  Serial.begin (9600);      // only required for debugging. Output some settings in the Serial Monitor Window 
  Serial.print("NeoPixel used on outout-pin [");  
  Serial.print(PIN); 
  Serial.print("] with ");  
  Serial.print(NUMPIXELS ); 
  Serial.println(" Pixels"); 
  if (useLDR) {
    Serial.print("LDR used on analog input pin [");
    Serial.print(LDRSensor);
    Serial.println("]");
    Serial.print("LDR current value =");
    LDRValue = analogRead(LDRSensor);
    Serial.println( LDRValue );
  }

  // Configure the used digital input & output
  pinMode(ledPin, OUTPUT); // initilise the onboard pin 13 LED as an indicator
  pinMode(alarmPinTop, INPUT_PULLUP); // for PIR at top of stairs initialise the input pin and use the internal restistor
  pinMode(alarmPinBottom, INPUT_PULLUP); // for PIR at bottom of stairs initialise the input pin and use the internal restistor

  delay (2000); // it takes the sensor 2 seconds to scan the area around it before it can detect infrared presence.
}

void loop() {

  // register the current time (in msec, for later use to optimize the execution loop)
  timeLoopStart=millis();

  // By default read the PIR inputs (unless LDR sensors are used and it is light enough...)
  readPIRInputs = true;
  if (useLDR) {
    // Read the value of the Light Sensor
    LDRValue = analogRead(LDRSensor);

    // For finetuning, show the LDR value, so the LDRThreshold can be determined ; once it works disable the next statement with '//'
    // Serial.println(LDRValue); 

    // Only switch on LED's at night when LDR senses low light conditions 
    if (LDRValue < LDRThreshold) {   
      // There is enough light, the stairs/ledstips will not be activated
      readPIRInputs = false;
    }
    else {
      alarmValueTop = LOW;
      alarmValueBottom = LOW;
    }
  }

  // Read the PIR inputs 
  if (readPIRInputs) {
    alarmValueTop = digitalRead(alarmPinTop); // Constantly poll the PIR at the top of the stairs
    alarmValueBottom = digitalRead(alarmPinBottom); // Constantly poll the PIR at the bottom of the stairs
  }
  
  // Check if PIR Top was triggered an leds must be turned on
  if ( (alarmValueTop == HIGH) && (downUp == 0) ) { // the 2nd term indicates that there is currently no activity (up or down)
    timeOut=millis(); // Timestamp when the PIR is triggered. The LED cycle wil then start.
    downUp = 1;
    colourWipeDown(strip.Color(255, 255, 250), turnOnSpeed ); // Warm White,led-light from top to down
  }

  // Check if PIR Bottom was triggered an leds must be turned on
  if ( (alarmValueBottom == HIGH) && (downUp == 0)) { // the 2nd term indicates that there is currently no activity (up or down)
    timeOut=millis(); // Timestamp when the PIR is triggered. The LED cycle wil then start.
    downUp = 2;
    colourWipeUp(strip.Color(255, 255, 250), turnOnSpeed); // Warm White,led-light from bottom to top
  }

  // Logic to turn the leds off (determines the turn-off direction)
  if ( (downUp!=0) && (timeOut+keepLedsOnTime < millis()) ) { //switch off LED's in the direction of travel.
    if (downUp == 1) {
      downUp = 3;     // mode = turn off leds from top to down
      colourWipeDown(strip.Color(0, 0, 0), turnOffSpeed); // Off
      downUp=5;      // Stairs are just turned off    
    }
    if (downUp == 2) {
      downUp = 4;  // mode = turn off leds from bottom to top      
      colourWipeUp(strip.Color(0, 0, 0), turnOffSpeed); // Off
      downUp=5;      // Stairs are just turned off          
    }
  }

  // Enable Breathe Effect when needed.
  if (downUp==0) {          // Currently no activity on the stairs ? (in idle mode, not turned (or turning) on or off ?) 
    if (readPIRInputs) {    // Also the PIR sensors are read (so when LDRs are enabled, then it is dark enough)
      handleBreathe();      // so....Enable the cool "breathe effect" of the led strip lights  
    }
  }
  else if (downUp==5) {     // eventually the stairs led lights will be turned off again (mode=5)
    delay(keepLedsOffTime); // allow small delay/pause and then activate the stairs again with the breathe and motion detection function
    downUp=0;               // set to 0 to allow breathe/motion detection (-1 for debugging one run)
  }
}



void handleBreathe() {

  // blue value changes
  breathe = breathe + change;
  
  // breathe the LED from 20 = off to 100 = fairly bright, change values if needed
  if ( (breathe >= 100 || breathe <= 20) ) {
  
    change = -change;         // toggle the value to increase/decrease the breathe value
  
    timeTemp = millis();
    timeDiff = timeTemp - timeLoopStart;
  
    // Program execution was shorter than 150 msec ? Then delay up to 150 msec, for a smooth breathe
    // NOTE: shorten the 150-numbers to a lower (same) value when breath is to slow..
    if (timeDiff < 150) {
      delay(150-timeDiff);  // Pause at beginning and end of each breath
    }
    else {
      // Program execution was longer than 150 msec, so no delay needed
    }
  }
  else {

    // For each stair/step, "breathe" the configured number of pixels 
    for (uint16_t k = 0; k < LEDSTRIPS; k++) {
      int startFirst = (NUMPIXELS/LEDSTRIPS) * k;
      int endFirst = startFirst + BREATHELEDS;

      // Turn on first "BREATHELEDS" of each stripm with the breathe color.
      for (uint16_t i = startFirst; i < endFirst; i++) {
            strip.setPixelColor(i, strip.Color(0,0,breathe));
      }

      int startLast = ((NUMPIXELS/LEDSTRIPS) * k) + (LEDSTRIPS - BREATHELEDS) ;
      int endLast= ((NUMPIXELS/LEDSTRIPS) * k) + BREATHELEDS;

      // Turn on last "BREATHELEDS" of each stripm with the breathe color.
      for (uint16_t i = startLast; i < endLast; i++) {
            strip.setPixelColor(i, strip.Color(0,0,breathe));
      }
    }
    strip.show();
  
    timeTemp = millis();
    timeDiff = timeTemp - timeLoopStart;
  
    // Program execution (timeDiff) was shorter than 25 msec ? Then delay up to 25 msec, for a smooth breathe
    // NOTE: shorten the 25-numbers to a lower (same) value when breath is to slow..
    if (timeDiff < 25) {
      delay(25-timeDiff);
    }
    else {
      // Program execution was longer than 25 msec, no delay needed
    }
  }
}


// Fade light each step strip
void colourWipeDown(uint32_t c, uint16_t wait) {

  for (uint16_t k = 0; k < LEDSTRIPS; k++){
    
    int start = (NUMPIXELS/LEDSTRIPS) *k;
    // Serial.println(k);

    for (uint16_t j = start; j < start + LEDSPERSTRIP; j++){
      strip.setPixelColor(j, c);
    }
    strip.show();
    delay(wait);
  }
}


// Fade light each step strip
void colourWipeUp(uint32_t c, uint16_t wait) {

  for (uint16_t k = LEDSTRIPS; k > 0; k--){

    int start = NUMPIXELS/LEDSTRIPS *k;
    // Serial.println(k);

    int x = start;
    do
    {
      strip.setPixelColor(x-1, c);
      x--;
    } while (x > start - LEDSPERSTRIP);

    strip.show();
    delay(wait);
  }
}

void clearStrip(){
  // All pixels off
  for (int l=0; l<NUMPIXELS; l++){
    strip.setPixelColor(l, strip.Color(0,0,0));
  }

  strip.show(); // This sends the updated pixel's to the hardware.  
}

