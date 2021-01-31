// NeoPixel Stair Led-strips
// Simple example by: Vincent van Beek
// 06-01-2019

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN               6       // Pin 6 used for the NeoPixels

// How many NeoPixels are attached to the Arduino?
#define NUMBEROFRING      2       // Number of (equal size) NeoPixel rings
#define LEDSPERRING       60      // Number of Pixels per ring
#define NUMPIXELS         NUMBEROFRING*LEDSPERRING 


Adafruit_NeoPixel neoPixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Set up Variables
unsigned long timeLoopStart=0;    // timestamp to remember when loop has started. used to determine the end-delay (keeps loop running in same intervals)
unsigned long timeTemp=0;         // temp. var used in time calculations
unsigned long timeDiff=0;         // temp. var used in time calculations


//-------------------------------------------------------------------------
// Tuning part for the Breathe effect en turn-on and turn-off speed 
//-------------------------------------------------------------------------
int change = 1;                   // used in 'breathing' the LED's , make value smalle to make it smoother, or higher to make it faster
int breathe = 10;                 // used in 'breathing' the LED's.


void setup() {
  neoPixels.begin();              // This initializes the NeoPixel library.
  //neoPixels.setBrightness(35);  // Adjust brightness here
  clearStrips();                  // Initialize all pixels to 'off', and do neoPixels.show()
  delay (100);
}

 
void loop() {

  // register the current time (in msec, for later use to optimize the execution loop)
  timeLoopStart=millis();
  
  handleBreathe();        // Enable the cool "breathe effect" of the led strip lights
}


void handleBreathe() {

  // blue value changes
  breathe = breathe + change;
  
  // breathe the LED from 10 = off to 80 = fairly bright, change values if needed
  if ( (breathe >= 80 || breathe <= 10) ) {
  
    change = -change;         // toggle the value to increase/decrease the breathe value
  
    timeTemp = millis();
    timeDiff = timeTemp - timeLoopStart;
  
    // Program execution was shorter than 250 msec ? Then delay up to 250 msec, for a smooth breathe
    // NOTE: shorten the 250-numbers to a lower (same) value when breath is to slow..
    if (timeDiff < 250) {
      delay(250-timeDiff);  // Pause at beginning and end of each breath
    }
  }
  else {

    // All pixels "breathe"
    for (int l=0; l<NUMPIXELS; l++){
      neoPixels.setPixelColor(l, neoPixels.Color(0,0,breathe));
    }

    neoPixels.show(); // Update the NeoPixel ring


    timeTemp = millis();
    timeDiff = timeTemp - timeLoopStart;
  
    // Program execution (timeDiff) was shorter than .. msec ? Then delay up to .. msec, for a smooth breathe
    // NOTE: shorten the numbers to a lower (same) value when breath is to slow..
    if (timeDiff < 20) {
      delay(20-timeDiff);
    }
  }
}


void clearStrips(){
  // All pixels off
  for (int l=0; l<NUMPIXELS; l++){
    neoPixels.setPixelColor(l, neoPixels.Color(0,0,0));
  }

  neoPixels.show(); // This sends the updated pixel's to the hardware.  
}

