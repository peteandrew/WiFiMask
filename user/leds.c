#include <c_types.h>
#include "leds.h"

#define MAX_HUE 1
#define MAX_SAT 0.5
#define MAX_VALUE 1

static uint16_t leds = 12;
static uint8_t patternNum = 1;

static float leftEyebrowHue = 0;
static float leftEyebrowSat = 0;
static float leftEyebrowValue = 0;

static float rightEyebrowHue = 0;
static float rightEyebrowSat = 0;
static float rightEyebrowValue = 0;

static float tashHue = 0;
static float tashSat = 0;
static float tashValue = 0;

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



float ICACHE_FLASH_ATTR getLeftEyebrowHue() {
  return leftEyebrowHue;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowHue() {
  leftEyebrowHue += 0.01;
  if (leftEyebrowHue > MAX_HUE) leftEyebrowHue = 0;
}
float ICACHE_FLASH_ATTR getLeftEyebrowSat() {
  return leftEyebrowSat;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowSat() {
  leftEyebrowSat += 0.01;
  if (leftEyebrowSat > MAX_SAT) leftEyebrowSat = 0;
}
float ICACHE_FLASH_ATTR getLeftEyebrowValue() {
  return leftEyebrowValue;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowValue() {
  leftEyebrowValue += 0.01;
  if (leftEyebrowValue++ > MAX_VALUE) leftEyebrowValue = 0;
}

float ICACHE_FLASH_ATTR getRightEyebrowHue() {
  return rightEyebrowHue;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowHue() {
  rightEyebrowHue += 0.01;
  if (rightEyebrowHue > MAX_HUE) rightEyebrowHue = 0;
}
float ICACHE_FLASH_ATTR getrightEyebrowSat() {
  return rightEyebrowSat;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowSat() {
  rightEyebrowSat += 0.01;
  if (rightEyebrowSat > MAX_SAT) rightEyebrowSat = 0;
}
float ICACHE_FLASH_ATTR getRightEyebrowValue() {
  return rightEyebrowValue;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowValue() {
  rightEyebrowValue += 0.01;
  if (rightEyebrowValue++ > MAX_VALUE) rightEyebrowValue = 0;
}

float ICACHE_FLASH_ATTR getTashHue() {
  return tashHue;
}
void ICACHE_FLASH_ATTR incrementTashHue() {
  tashHue += 0.01;
  if (tashHue > MAX_HUE) tashHue = 0;
}
float ICACHE_FLASH_ATTR getTashSat() {
  return tashSat;
}
void ICACHE_FLASH_ATTR incrementTashSat() {
  tashSat += 0.01;
  if (tashSat > MAX_SAT) tashSat = 0;
}
float ICACHE_FLASH_ATTR getTashValue() {
  return tashValue;
}
void ICACHE_FLASH_ATTR incrementTashValue() {
  tashValue += 0.01;
  if (tashValue++ > MAX_VALUE) tashValue = 0;
}
