#include <Adafruit_NeoPixel.h>

#define PIN1 D3
#define PIN2 D2
#define PIN3 D1

Adafruit_NeoPixel _strip1 = Adafruit_NeoPixel(99,   PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel _strip2 = Adafruit_NeoPixel(100, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel _strip3 = Adafruit_NeoPixel(99,   PIN3, NEO_GRB + NEO_KHZ800);

void setup() { 
  _strip1.begin();
  _strip2.begin();
  _strip3.begin();
  
  _strip1.show();
  _strip2.show();
  _strip3.show();
}

void loop() {
  // brightness
  _strip1.setBrightness(13);
  _strip2.setBrightness(13);
   _strip3.setBrightness(13);

  // Strip 1
  colorWipe(_strip1.Color(255, 0, 0), 50);
  colorWipe(_strip1.Color(0, 255, 0), 50);
  colorWipe(_strip1.Color(0, 0, 255), 50);

  theaterChase(_strip1.Color(127, 127, 127), 50);
  theaterChase(_strip1.Color(127, 0, 0), 50);
  theaterChase(_strip1.Color(0, 0, 127), 50);

  // Strip 2
  colorWipe(_strip2.Color(255, 0, 0), 50);
  colorWipe(_strip2.Color(0, 255, 0), 50);
  colorWipe(_strip2.Color(0, 0, 255), 50);
  
  theaterChase(_strip2.Color(127, 127, 127), 50);
  theaterChase(_strip2.Color(127, 0, 0), 50);
  theaterChase(_strip2.Color(0, 0, 127), 50);
  
  // Strip 3
  colorWipe(_strip3.Color(255, 0, 0), 50);
  colorWipe(_strip3.Color(0, 255, 0), 50);
  colorWipe(_strip3.Color(0, 0, 255), 50);

  theaterChase(_strip3.Color(127, 127, 127), 50);
  theaterChase(_strip3.Color(127, 0, 0), 50);
  theaterChase(_strip3.Color(0, 0, 127), 50);

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i < _strip2.numPixels(); i++) {    
    _strip1.setPixelColor(i, c);
    _strip1.show();

    _strip2.setPixelColor(i, c);
    _strip2.show();

    _strip3.setPixelColor(i, c);
    _strip3.show();

    delay(wait);
  }
}

void rainbow(uint8_t wait) {  
  for(uint16_t j=0;  j <256; j++) {
    for(uint16_t i = 0; i < _strip2.numPixels(); i++) {
      _strip1.setPixelColor(i, Wheel1((i + j) & 255));
      _strip2.setPixelColor(i, Wheel2((i + j) & 255));
      _strip3.setPixelColor(i, Wheel3((i + j) & 255));
    }
    
    _strip1.show();
    _strip2.show();
    _strip3.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {  
  for(uint16_t j = 0; j < 256 * 5; j++) {
    for(uint16_t i = 0; i < _strip2.numPixels(); i++) {
      _strip1.setPixelColor(i, Wheel1(((i * 256 / _strip1.numPixels()) + j) & 255));
      _strip2.setPixelColor(i, Wheel2(((i * 256 / _strip1.numPixels()) + j) & 255));
      _strip3.setPixelColor(i, Wheel3(((i * 256 / _strip1.numPixels()) + j) & 255));
    }
    
    _strip1.show();
    _strip2.show();
    _strip3.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < _strip2.numPixels(); i = i + 3) {
        _strip1.setPixelColor(i + q, c);
        _strip2.setPixelColor(i + q, c);
        _strip3.setPixelColor(i + q, c);
      }
      
      _strip1.show();
      _strip2.show();
      _strip3.show();
      delay(wait);

      for (uint16_t i = 0; i < _strip2.numPixels(); i = i + 3) {
        _strip1.setPixelColor(i + q, 0);
        _strip2.setPixelColor(i + q, 0);
        _strip3.setPixelColor(i + q, 0);
      }
    }
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < _strip2.numPixels(); i = i + 3) {
        _strip1.setPixelColor(i + q, Wheel1( (i + j) % 255));
        _strip2.setPixelColor(i + q, Wheel2( (i + j) % 255));
        _strip3.setPixelColor(i + q, Wheel3( (i + j) % 255));
      }
      
      _strip1.show();
      _strip2.show();
      _strip3.show();
      delay(wait);

      for (uint16_t i = 0; i < _strip2.numPixels(); i = i + 3) {
        _strip1.setPixelColor(i + q, 0);
        _strip2.setPixelColor(i + q, 0);
        _strip3.setPixelColor(i + q, 0);
      }
    }
  }
}

uint32_t Wheel1(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  
  if(wheelPos < 85)
    return _strip1.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  
  if(wheelPos < 170) {
    wheelPos -= 85;
    return _strip1.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  
  wheelPos -= 170;
  return _strip1.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

uint32_t Wheel2(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  
  if(wheelPos < 85)
    return _strip2.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  
  if(wheelPos < 170) {
    wheelPos -= 85;
    return _strip2.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  
  wheelPos -= 170;
  return _strip2.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

uint32_t Wheel3(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  
  if(wheelPos < 85)
    return _strip3.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  
  if(wheelPos < 170) {
    wheelPos -= 85;
    return _strip3.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  
  wheelPos -= 170;
  return _strip3.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

