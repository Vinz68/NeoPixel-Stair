# NeoPixel-Stair & NeoPixel-Breathing-Rings
2 Arduino programs for the NeoPixel led strips and rings.

## NeoPixel-Stair - functions
Stair LedLights, using NeoPixel Ledstrips and an Arduino.

- drives a configurable number of led-strips (one ledstrip per step)
- with configurable number of leds per strip
- has a nice "breathe" function when stairs are not used (smoothly up and down of first and last led of each led-strip ; configurable also)
- switches on or off in top-down or bottop-top direction
  

### Configuration

```javascript

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN             5        // Pin 5 used for the NeoPixels

// How many NeoPixels are attached to the Arduino?
#define LEDSPERSTRIP    36       // 36 leds per strip
#define LEDSTRIPS       16       // 16 steps
```


### Tuning
```javascript
//-------------------------------------------------------------------------
// Tuning part for the Breathe effect en turn-on and turn-off speed 
//-------------------------------------------------------------------------
int change = 2;                   // used in 'breathing' the LED's , make value smalle to make it smoother, or higher to make it faster
int breathe = 25;                 // used in 'breathing' the LED's.
int turnOnSpeed=250;              // speed to turn on next led-strip, in msec between next strip
int turnOffSpeed=100;             // speed to turn on next led-strip, in msec between next strip
int keepLedsOnTime=18000;         // keep leds on for at least .. msec.
int keepLedsOffTime=1500;         // keep leds off for at least .. msec.
```




## NeoPixel-Breathing-Rings - functions
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



