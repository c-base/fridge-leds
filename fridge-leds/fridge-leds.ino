#include <Adafruit_NeoPixel.h>

#define PIN 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(99, PIN, NEO_GRB + NEO_KHZ800);

void setup() { 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue

  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {  
  for(uint16_t j=0;  j <256; j++) {
    for(uint16_t i = 0; i < strip.numPixels(); i++)
      strip.setPixelColor(i, Wheel((i + j) & 255));
    
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(uint16_t j = 0; j < 256 * 5; j++) {
    for(uint16_t i = 0; i < strip.numPixels(); i++)
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
        strip.setPixelColor(i+q, c);
      
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
        strip.setPixelColor(i + q, 0);      
    }
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
        strip.setPixelColor(i + q, Wheel( (i + j) % 255));
      
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
        strip.setPixelColor(i + q, 0);
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  
  if(WheelPos < 85)
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
