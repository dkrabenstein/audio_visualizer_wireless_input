#include <Arduino.h>
#include <FastLED.h>

// --- HARDWARE CONFIGURATION ---
#define LED_PIN     18     // ESP32 GPIO pin connected to WS2812B Data
#define NUM_LEDS    300   // Total number of LEDs
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  // Serial0: Debug monitor over USB
  Serial.begin(115200);


  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // Flash Blue for 1s on startup to test LED hardware
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
  
  // Clear strip after test
  FastLED.clear();
  FastLED.show();
}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();

  delay(1000);
}
