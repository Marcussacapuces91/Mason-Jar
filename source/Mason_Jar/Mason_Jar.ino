
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include "FastLED.h"

static const uint8_t NUM_LEDS = 3;

CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS); 
}

void loop() {
  static uint8_t hue = 0; 
  static const uint8_t v = 64;

  leds[0] = CHSV(hue, 255, v);
  leds[1] = CHSV(64 + hue, 255, v);
  leds[2] = CHSV(128 + hue++, 255, v);

  FastLED.delay(30);
}
