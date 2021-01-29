# NeoPixel-Stairs & NeoPixel-BreathingRings
2 Arduino program sketches for the NeoPixel led strips and rings.
The sketeched depends on thel Adafuit Neopixel library, which you might need to install in your Arduino IDE: 
- Tools -> Manage Libraries -> search for "Neopixel" and select and install "Adafruit Neopixel" 

## NeoPixel-Stairs - functions
Stair LedLights, using NeoPixel Ledstrips and an Arduino.

- drives a configurable number of led-strips (one ledstrip per stair step)
- with configurable number of leds per strip
- switches on or off in top-down or bottom-top direction
- supports a Light dependent resistor (LDR), when enabled (useLDR=true), led lights will not turned on during daylight.
- has a nice "breathe" function when stairs are not used (smoothly up and down of intensity of each led-strip)  
- has setting BRIGHTNESS to controll the brightness of the LEDSs

### Configuration

```javascript

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN             5       // Pin used for the NeoPixels

// How many NeoPixels are attached to the Arduino?
#define LEDSPERSTRIP    36    // Number of leds per strip
#define LEDSTRIPS       16    // Number of stair steps (led strips)
#define BREATHELEDS     1     // Number of leds used in breathe function. 
                              // NOTE:  The number indicates the number of Begin Leds and Last leds per strip 
                              //        so with setting = "1", the first and last leds of the ledstrip would be used for the breathe function.
#define BRIGHTNESS      35        // Adjust brightness of the leds here 

// Configuration of the Passive Infrared (PIR)
int alarmPinTop = 10;         // PIR at the top of the stairs
int alarmPinBottom = 11;      // PIR at the bottom of the stairs

// Configuration of the Light dependent resistor (LDR)
bool useLDR = true;           // flag, when true the program uses the LDR, set to "false" if you don't have a LDR sensor.
int LDRSensor = A0;           // Light dependent resistor, Analog Input line  

long LDRThreshold = 600;      // Only switch on LED's at night when LDR senses low light conditions 
                              // => you may have to change this value for your circumstances!

```


### Tuning
```javascript

//-------------------------------------------------------------------------
// Tuning part for the Breathe effect and turn-on and turn-off speed 
//-------------------------------------------------------------------------
int change          = 2;         // used in 'breathing' the LED's , make value smalle to make it smoother, or higher to make it faster
int breathe         = 25;        // used in 'breathing' the LED's.
int turnOnSpeed     = 250;       // speed to turn on next led-strip, in msec between next strip
int turnOffSpeed    = 100;       // speed to turn on next led-strip, in msec between next strip
int keepLedsOnTime  = 18000;     // keep leds on for at least .. msec.
int keepLedsOffTime = 1500;      // keep leds off for at least .. msec.
```


### Tip
Using the Serial monitor, via tools->Serial monitor (or Ctl-Shift-M), you can view the serial output and verify your configuration.


## NeoPixel-BreathingRings - functions
Just a cool script to smoothly brighten and soften the leds in a nice color.
I used 2 NeoPixel rings with 60 leds each and used a blue calm color... but change it to your needs of course...

```javascript
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN             6        // Pin 6 used for the NeoPixels

// How many NeoPixels are attached to the Arduino?
#define NUMBEROFRING      2       // Number of (equal size) NeoPixel rings
#define LEDSPERRING       60      // Number of Pixels per ring
#define NUMPIXELS         NUMBEROFRING*LEDSPERRING 
```



