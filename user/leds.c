#include <c_types.h>
#include "leds.h"

#define MAX_RED 30
#define MAX_GREEN 30
#define MAX_BLUE 30

static uint16_t leds = 12;
static uint8_t patternNum = 1;

static uint8_t leftEyebrowRed = 0;
static uint8_t leftEyebrowGreen = 0;
static uint8_t leftEyebrowBlue = 0;

static uint8_t rightEyebrowRed = 0;
static uint8_t rightEyebrowGreen = 0;
static uint8_t rightEyebrowBlue = 0;

static uint8_t tashRed = 0;
static uint8_t tashGreen = 0;
static uint8_t tashBlue = 0;

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
  return 0;
}
void ICACHE_FLASH_ATTR setRed(uint8_t value) {}

uint8_t ICACHE_FLASH_ATTR getGreen() {
  return 0;
}
void ICACHE_FLASH_ATTR setGreen(uint8_t value) {}

uint8_t ICACHE_FLASH_ATTR getBlue() {
  return 0;
}
void ICACHE_FLASH_ATTR setBlue(uint8_t value) {}

uint8_t ICACHE_FLASH_ATTR getLeftEyebrowRed() {
  return leftEyebrowRed;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowRed() {
  if (leftEyebrowRed++ > MAX_RED) leftEyebrowRed = 0;
}
uint8_t ICACHE_FLASH_ATTR getLeftEyebrowGreen() {
  return leftEyebrowGreen;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowGreen() {
  if (leftEyebrowGreen++ > MAX_GREEN) leftEyebrowGreen = 0;
}
uint8_t ICACHE_FLASH_ATTR getLeftEyebrowBlue() {
  return leftEyebrowBlue;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowBlue() {
  if (leftEyebrowBlue++ > MAX_BLUE) leftEyebrowBlue = 0;
}

uint8_t ICACHE_FLASH_ATTR getRightEyebrowRed() {
  return rightEyebrowRed;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowRed() {
  if (rightEyebrowRed++ > MAX_RED) rightEyebrowRed = 0;
}
uint8_t ICACHE_FLASH_ATTR getRightEyebrowGreen() {
  return rightEyebrowGreen;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowGreen() {
  if (rightEyebrowGreen++ > MAX_GREEN) rightEyebrowGreen = 0;
}
uint8_t ICACHE_FLASH_ATTR getRightEyebrowBlue() {
  return rightEyebrowBlue;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowBlue() {
  if (rightEyebrowBlue++ > MAX_BLUE) rightEyebrowBlue = 0;
}

uint8_t ICACHE_FLASH_ATTR getTashRed() {
  return tashRed;
}
void ICACHE_FLASH_ATTR incrementTashRed() {
  if (tashRed++ > MAX_RED) tashRed = 0;
}
uint8_t ICACHE_FLASH_ATTR getTashGreen() {
  return tashGreen;
}
void ICACHE_FLASH_ATTR incrementTashGreen() {
  if (tashGreen++ > MAX_GREEN) tashGreen = 0;
}
uint8_t ICACHE_FLASH_ATTR getTashBlue() {
  return tashBlue;
}
void ICACHE_FLASH_ATTR incrementTashBlue() {
  if (tashBlue++ > MAX_BLUE) tashBlue = 0;
}
