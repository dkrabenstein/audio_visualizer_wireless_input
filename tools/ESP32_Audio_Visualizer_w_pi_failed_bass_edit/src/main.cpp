#include <Arduino.h>
#include <FastLED.h>

// --- HARDWARE CONFIGURATION ---
#define LED_PIN     18     // ESP32 GPIO pin connected to WS2812B Data
#define NUM_LEDS    300   // Total number of LEDs
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// --- SERIAL CONFIGURATION ---
#define RX_PIN      16    // Connect to Raspberry Pi TX (GPIO 14 / Pin 8)
#define TX_PIN      17    // Connect to Raspberry Pi RX (GPIO 15 / Pin 10)
#define BAUD_RATE   115200
#define NUM_BINS    16

CRGB leds[NUM_LEDS];

const uint8_t HEADER_0 = 0xFF;
const uint8_t HEADER_1 = 0xFE;

uint8_t currentMode = 0;
uint8_t masterBrightness = 128;
uint8_t fftBins[NUM_BINS];

void renderVisualizer();

void setup() {
  // Serial0: Debug monitor over USB
  Serial.begin(115200);
  
  // Serial2: Hardware UART connected to Pi
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("\n[ESP32] System Booted! Listening on RX2 (GPIO 16)...");

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(masterBrightness);

  // Flash Blue for 1s on startup to test LED hardware
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
  
  // Clear strip after test
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Full packet length = 2 bytes header + 1 byte mode + 1 byte brightness + 16 bin bytes = 20 bytes
  const int PACKET_SIZE = 20;

  while (Serial2.available() >= PACKET_SIZE) {
    // Check for 0xFF header byte
    if (Serial2.read() == HEADER_0) {
      
      // Check for 0xFE second header byte
      if (Serial2.peek() == HEADER_1) {
        Serial2.read(); // Consume HEADER_1

        // Read payload
        currentMode = Serial2.read();
        masterBrightness = Serial2.read();
        FastLED.setBrightness(masterBrightness);

        // Read 16 audio frequency bins
        Serial2.readBytes(fftBins, NUM_BINS);

        // Debug output to Arduino Serial Monitor
        Serial.print("[SYNC] Mode: "); Serial.print(currentMode);

        // Render LEDs with fresh data
        renderVisualizer();
        return;
      }
    }
  }
}

// --- VISUALIZER ROUTINE ---
void renderVisualizer() {
  FastLED.clear();

  switch (currentMode) {
    case 0: // SPECTRUM BARS
      {
        int ledsPerBin = NUM_LEDS / NUM_BINS;
        for (int b = 0; b < NUM_BINS; b++) {
          int litCount = map(fftBins[b], 0, 255, 0, ledsPerBin);
          uint8_t hue = map(b, 0, NUM_BINS - 1, 0, 224);
          for (int i = 0; i < litCount; i++) {
            leds[(b * ledsPerBin) + i] = CHSV(hue, 240, 255);
          }
        }
      }
      break;

    case 1: // BASS PULSE
      {
        uint8_t bass = (fftBins[0] + fftBins[1]) / 2;
        if(bass > 50)
          fill_solid(leds, NUM_LEDS, CHSV(200, 255, 255));
        else
          FastLED.clear();
        Serial.print("Bass: " + (intbass);
      }
      break;

    case 2: // CENTER SPREAD
      {
        int center = NUM_LEDS / 2;
        uint8_t totalVol = 0;
        for (int i = 0; i < NUM_BINS; i++) {
          totalVol += fftBins[i] / NUM_BINS;
        }
        
        int spread = map(totalVol, 0, 255, 0, center);
        for (int i = 0; i < spread; i++) {
          uint8_t hue = map(i, 0, center, 0, 192);
          leds[center + i] = CHSV(hue, 255, 255);
          leds[center - i] = CHSV(hue, 255, 255);
        }
      }
      break;

    case 3: // AUDIO FIRE
      {
        uint8_t audioIntensity = fftBins[1];
        for (int i = 0; i < NUM_LEDS; i++) {
          uint8_t heat = qsub8(inoise8(i * 15, millis() / 5), 30);
          heat = scale8(heat, audioIntensity);
          leds[i] = HeatColor(heat);
        }
      }
      break;
  }

  FastLED.show();
}