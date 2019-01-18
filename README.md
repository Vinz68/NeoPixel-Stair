# NeoPixel-Stairs & NeoPixel-BreathingRings
2 Arduino program sketches for the NeoPixel led strips and rings.

## NeoPixel-Stairs - functions
Stair LedLights, using NeoPixel Ledstrips and an Arduino.

- drives a configurable number of led-strips (one ledstrip per stair step)
- with configurable number of leds per strip
- switches on or off in top-down or bottop-top direction
- supports a Light dependent resistor (LDR), when enabled led lights only turned on when dark enough
- has a nice "breathe" function when stairs are not used (smoothly up and down of intensity of each led-strip ; configurable also)  

### Configuration

```javascript

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN             5        // Pin used for the NeoPixels

// How many NeoPixels are attached to the Arduino?
#define LEDSPERSTRIP    36       // Number of leds per strip
#define LEDSTRIPS       16       // Number of stair steps (led strips)
#define BREATHELEDS     1         // Number of leds used in breathe function. 
                                  // NOTE:  The number indicates the number of Begin Leds and Last leds per strip 
                                  //        so with setting = "1", the first and last leds of the ledstrip would be used for the breathe function.
```





### Tuning
```javascript
//-------------------------------------------------------------------------
// Tuning part for the Breathe effect en turn-on and turn-off speed 
//-------------------------------------------------------------------------
int change          = 2;         // used in 'breathing' the LED's , make value smalle to make it smoother, or higher to make it faster
int breathe         = 25;        // used in 'breathing' the LED's.
int turnOnSpeed     = 250;       // speed to turn on next led-strip, in msec between next strip
int turnOffSpeed    = 100;       // speed to turn on next led-strip, in msec between next strip
int keepLedsOnTime  = 18000;     // keep leds on for at least .. msec.
int keepLedsOffTime = 1500;      // keep leds off for at least .. msec.

// Configuration of the Light dependent resistor (LDR)
bool useLDR = true;               // flag, when true the program uses the LDR, set to "false" if you don't have a LDR sensor.
int LDRSensor = A0;               // Light dependent resistor, Analog Input line 
```



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



