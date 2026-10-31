#include <Arduino.h>
#include <FastLED.h>

// --- HARDWARE CONFIGURATION ---
#define LED_PIN     18     // ESP32 GPIO pin connected to WS2812B Data
#define NUM_LEDS    300   // Total number of LEDs
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define LED_VOLTS         5
#define LED_MAX_MILLIAMPS 9000

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(1000);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(LED_VOLTS, LED_MAX_MILLIAMPS);

}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
}
