# NeoPixel-Stair
Stair LedLights, using NeoPixel Ledstrips and an Arduino.

## Functions:
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
