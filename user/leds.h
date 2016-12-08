#ifndef LEDS_H
#define LEDS_H

uint16_t getNumLeds();
void setNumLeds(uint16_t numLeds);

uint8_t getPattern();
void setPattern(uint8_t pattern);

uint8_t getRed();
void incrementRed();
void setRed(uint8_t value);

uint8_t getGreen();
void incrementGreen();
void setGreen(uint8_t value);

uint8_t getBlue();
void incrementBlue();
void setBlue(uint8_t value);

uint8_t getLeftEyebrowRed();
void incrementLeftEyebrowRed();
uint8_t getLeftEyebrowGreen();
void incrementLeftEyebrowGreen();
uint8_t getLeftEyebrowBlue();
void incrementLeftEyebrowBlue();

uint8_t getRightEyebrowRed();
void incrementRightEyebrowRed();
uint8_t getRightEyebrowGreen();
void incrementRightEyebrowGreen();
uint8_t getRightEyebrowBlue();
void incrementRightEyebrowBlue();

uint8_t getTashRed();
void incrementTashRed();
uint8_t getTashGreen();
void incrementTashGreen();
uint8_t getTashBlue();
void incrementTashBlue();

#endif
