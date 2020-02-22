//Arduino code to receive I2C communication from RoboRIO
// v003

#include <Wire.h>
#include <FastLED.h>

#define DATA_PIN    11
#define LED_TYPE    P9813
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define CLK_PIN   13
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          50

// Define the digital input pins for reading in LED states
int dataPin1 = 5;  
int dataPin2 = 6;    
int dataPin3 = 7;     

// Define data array [3 bits]
int data[3];
int LEDCode;

// Variables for color strip
uint8_t gHue = 0;
 
void setup() {
  // Setup the digital input pins
  pinMode(dataPin1, INPUT);
  pinMode(dataPin2, INPUT);    
  pinMode(dataPin3, INPUT);

  // Debugging
  // open the serial port at 9600 bps:
  Serial.begin(9600);

  // Set up LED strip
  FastLED.addLeds<P9813, DATA_PIN, CLK_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);
}
 
void loop() {
  // Read data and convert to decimal LED code
  readData();
  LEDCode = convertBinToLEDCode();
  //Serial.println(LEDCode);
  
  // Display proper LED codes
  /*  LED States:                 LEDCode:    Color:
   *  Off                         0           N/A
   *  Shooter - Spool Up          1           Flashing Yellow           (shooter command active)
   *  Shooter - At Speed          2           Yellow                    (within 100 rpm of setpt)
   *  Shooter - Shooting          3           Flashing Orange
   *  Vision Locked               4           Red
   *  Vision Drive                5           Flashing Green
   *  Intake Balls                6           Cyan
   *  At optimal distance?
   */

   switch(LEDCode) {
      case 0:
        off();
        break;
      case 1:
        Shooter_SpoolUPp();
        break;
      case 2:
        Shooter_AtSpeed();
        break;
      case 3:
        Shooter_Shooting();
        break;
      case 4:
        Vision_Locked();
        break;
      case 5:
        Vision_Drive();
        break;
      case 6:
        Intake_Balls();
        break;
   }
}

void readData() {
    data[0] = digitalRead(dataPin1);
    data[1] = digitalRead(dataPin2);
    data[2] = digitalRead(dataPin3);
    String str = String(data[0]) + String(data[1]) + String(data[2]);
    Serial.println(str);
}

int convertBinToLEDCode() {
    return 1 * data[2] + 2 * data[1] + 4 * data[0];
    // Bits are combined into binary number, therefore the last digit is 2^0
}


// LED light command functions
void Shooter_SpoolUp() {    // Flashing yellow
    fill_solid(leds, NUM_LEDS, CRGB(255,255,0));
    FastLED.show();
    delay(250);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(250);
}

void Shooter_AtSpeed() {    // Yellow
    fill_solid(leds, NUM_LEDS, CRGB(255,255,0)); 
    FastLED.show();
}
void Shooter_Shooting() {   // Flashing orange
    fill_solid(leds, NUM_LEDS, CRGB(255,69,0)); 
    FastLED.show();
    delay(250);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0)); 
    FastLED.show();
    delay(250);
}

void Vision_Locked() {    // Red
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
}

void Vision_Drive() {     // Flashing green
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
    delay(250);
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    delay(250);
}

void Intake_Balls() {     // Cyan
    fill_solid(leds, NUM_LEDS, CRGB(0,255,255));
    FastLED.show();
}

void off() {    // All LEDs off
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0)); 
    FastLED.show();
}
