#include <c_types.h>
#include "leds.h"

#define MAX_HUE 1
#define MIN_SAT 0.6
#define MAX_SAT 1
#define MAX_VALUE 0.09

static uint16_t leds = 12;
static uint8_t patternNum = 1;

static float leftEyebrowHue = 0.05;
static float leftEyebrowSat = MAX_SAT;
static float leftEyebrowValue = MAX_VALUE;

static float rightEyebrowHue = 0.01;
static float rightEyebrowSat = MAX_SAT;
static float rightEyebrowValue = MAX_VALUE;

static float tashHue = 0.7;
static float tashSat = MAX_SAT;
static float tashValue = MAX_VALUE;

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
  leftEyebrowSat += 0.004;
  if (leftEyebrowSat > MAX_SAT) leftEyebrowSat = MIN_SAT;
}
float ICACHE_FLASH_ATTR getLeftEyebrowValue() {
  return leftEyebrowValue;
}
void ICACHE_FLASH_ATTR incrementLeftEyebrowValue() {
  leftEyebrowValue += 0.001;
  if (leftEyebrowValue > MAX_VALUE) leftEyebrowValue = 0;
}

float ICACHE_FLASH_ATTR getRightEyebrowHue() {
  return rightEyebrowHue;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowHue() {
  rightEyebrowHue += 0.01;
  if (rightEyebrowHue > MAX_HUE) rightEyebrowHue = 0;
}
float ICACHE_FLASH_ATTR getRightEyebrowSat() {
  return rightEyebrowSat;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowSat() {
  rightEyebrowSat += 0.004;
  if (rightEyebrowSat > MAX_SAT) rightEyebrowSat = MIN_SAT;
}
float ICACHE_FLASH_ATTR getRightEyebrowValue() {
  return rightEyebrowValue;
}
void ICACHE_FLASH_ATTR incrementRightEyebrowValue() {
  rightEyebrowValue += 0.001;
  if (rightEyebrowValue > MAX_VALUE) rightEyebrowValue = 0;
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
  tashSat += 0.004;
  if (tashSat > MAX_SAT) tashSat = MIN_SAT;
}
float ICACHE_FLASH_ATTR getTashValue() {
  return tashValue;
}
void ICACHE_FLASH_ATTR incrementTashValue() {
  tashValue += 0.001;
  if (tashValue > MAX_VALUE) tashValue = 0;
}
