#ifndef LEDS_H
#define LEDS_H

uint16_t getNumLeds();
void setNumLeds(uint16_t numLeds);

uint8_t getPattern();
void setPattern(uint8_t pattern);

uint8_t getRed();
void setRed(uint8_t value);
uint8_t getGreen();
void setGreen(uint8_t value);
uint8_t getBlue();
void setBlue(uint8_t value);

#endif
