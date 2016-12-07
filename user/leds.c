#include <c_types.h>
#include "leds.h"

#define MAX_RED 40
#define MAX_GREEN 40
#define MAX_BLUE 40

static uint16_t leds = 12;
static uint8_t patternNum = 1;
static uint8_t red = 0;
static uint8_t green = 0;
static uint8_t blue = 0;

uint16_t ICACHE_FLASH_ATTR getNumLeds() {
  return leds;
}
void ICACHE_FLASH_ATTR setNumLeds(uint16_t numLeds) {
  leds = numLeds;
}

uint8_t ICACHE_FLASH_ATTR getPattern() {
  return patternNum;
}
void ICACHE_FLASH_ATTR setPattern(uint8_t pattern) {
  patternNum = pattern;
}

uint8_t ICACHE_FLASH_ATTR getRed() {
  return red;
}
void incrementRed() {
  if (++red > MAX_RED) red = 0;
}
void ICACHE_FLASH_ATTR setRed(uint8_t value) {
  red = value;
}
uint8_t ICACHE_FLASH_ATTR getGreen() {
  return green;
}
void incrementGreen() {
  if (++green > MAX_GREEN) green = 0;
}
void ICACHE_FLASH_ATTR setGreen(uint8_t value) {
  green = value;
}
uint8_t ICACHE_FLASH_ATTR getBlue() {
  return blue;
}
void incrementBlue() {
  if (++blue > MAX_BLUE) blue = 0;
}
void ICACHE_FLASH_ATTR setBlue(uint8_t value) {
  blue = value;
}
