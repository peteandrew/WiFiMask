#include <esp8266.h>
#include "stdout.h"
#include "ws2812_i2s.h"
#include "leds.h"
#include "pattern.h"


// 0 - static left eyebrow hue
// 1 - static right eyebrow hue
// 2 - static tash hue
// 3 - moving dot using feature colour
// 4 - moving dot using feature colour different intensity per feature led
// 5 - moving dot colour cycle
uint8_t mode = 0;
uint8_t last_leds[512*3] = {0};
uint32_t frame = 0;

float colourCycleHue = 0.05;
float colourCycleSat = 1;
float colourCycleValue = 0.07;

uint8_t buttonShortPress = 0;
uint8_t buttonLongPress = 0;


static ETSTimer pattern_timer;
static void ICACHE_FLASH_ATTR patternTimer(void *arg) {
	if (buttonShortPress) {
		if (++mode > 5) {
			mode = 0;
		}
		buttonShortPress = 0;
		os_printf("\nMode: %d\n", mode);
	}
	if (buttonLongPress) {
		switch(mode) {
			case 0:
			  incrementLeftEyebrowHue();
				os_printf("\nIncrement left eyebrow hue\n");
				break;
			case 1:
			  incrementRightEyebrowHue();
				os_printf("\nIncrement right eyebrow hue\n");
				break;
			case 2:
			  incrementTashHue();
				os_printf("\nIncrement tash hue\n");
				break;
		}
		buttonLongPress = 0;
	}

	int currDotLed = (frame/5) % 24;
	if (frame % 12 == 0) {
  	colourCycleHue += 0.01;
		if (colourCycleHue > 1) {
			colourCycleHue = 0;
		}
	}

	int it;
	uint32_t rgb = 0;
	// Tash
	for (it=0; it<4; ++it) {
		rgb = 0;
		if (mode < 3) {
			rgb = HSVtoHEX(getTashHue(), getTashSat(), getTashValue());
		} else {
			switch (mode) {
				case 3:
				  if (currDotLed == it) rgb = HSVtoHEX(getTashHue(), getTashSat(), getTashValue());
					break;
				case 4:
					rgb = HSVtoHEX(getTashHue(), getTashSat(), (currDotLed - it == 1 || currDotLed - it == 0) * (((float)(it % 4) + 1.0) / 4.0) * getTashValue());
					break;
				case 5:
					if (currDotLed == it) rgb = HSVtoHEX(colourCycleHue, colourCycleSat, colourCycleValue);
					break;
			}
		}
		last_leds[3*it+0] = (rgb>>8);
		last_leds[3*it+1] = (rgb);
		last_leds[3*it+2] = (rgb>>16);
	}
	// Right eyebrow
	for (it=4; it<8; ++it) {
		rgb = 0;
		if (mode < 3) {
			rgb = HSVtoHEX(getRightEyebrowHue(), getRightEyebrowSat(), getRightEyebrowValue());
		} else {
			switch (mode) {
				case 3:
				  if (currDotLed == it) rgb = HSVtoHEX(getRightEyebrowHue(), getRightEyebrowSat(), getRightEyebrowValue());
					break;
				case 4:
					rgb = HSVtoHEX(getRightEyebrowHue(), getRightEyebrowSat(), (currDotLed - it == 1 || currDotLed - it == 0) * (((float)(it % 4) + 1.0) / 4.0) * getRightEyebrowValue());
					break;
				case 5:
					if (currDotLed == it) rgb = HSVtoHEX(colourCycleHue, colourCycleSat, colourCycleValue);
					break;
			}
		}
		last_leds[3*it+0] = (rgb>>8);
		last_leds[3*it+1] = (rgb);
		last_leds[3*it+2] = (rgb>>16);
	}
	// // Left eyebrow
	for (it=8; it<12; ++it) {
		rgb = 0;
		if (mode < 3) {
			rgb = HSVtoHEX(getLeftEyebrowHue(), getLeftEyebrowSat(), getLeftEyebrowValue());
		} else {
			switch (mode) {
				case 3:
				  if (currDotLed == it) rgb = HSVtoHEX(getLeftEyebrowHue(), getLeftEyebrowSat(), getLeftEyebrowValue());
					break;
				case 4:
					rgb = HSVtoHEX(getLeftEyebrowHue(), getLeftEyebrowSat(), (currDotLed - it == 1 || currDotLed - it == 0) * (((float)(it % 4) + 1.0) / 4.0) * getLeftEyebrowValue());
					break;
				case 5:
					if (currDotLed == it) rgb = HSVtoHEX(colourCycleHue, colourCycleSat, colourCycleValue);
					break;
			}
		}
		last_leds[3*it+0] = (rgb>>8);
		last_leds[3*it+1] = (rgb);
		last_leds[3*it+2] = (rgb>>16);
	}

	frame++;

  ws2812_push( last_leds, 3*getNumLeds());
}


static ETSTimer button_timer;
static void ICACHE_FLASH_ATTR buttonTimer(void *arg) {
  static int downCnt = 0;
	static int previousLongPress = 0;

	if (!GPIO_INPUT_GET(0)) {
		downCnt++;
		if (previousLongPress || downCnt > 10) {
			buttonLongPress = 1;
			previousLongPress = 1;
			downCnt = 0;
			os_printf("\nLong button press\n");
		}
	} else {
		if (downCnt > 1 && !buttonLongPress) {
			buttonShortPress = 1;
			previousLongPress = 0;
			os_printf("\nShort button press\n");
		}
		downCnt = 0;
		previousLongPress = 0;
	}
}

void user_init(void) {
	stdoutInit();

	wifi_station_disconnect();
  wifi_set_opmode(NULL_MODE); 	 	 // set WiFi mode to null mode.
	wifi_set_sleep_type(MODEM_SLEEP_T);

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0); // Set GPIO0 function
	gpio_output_set(0, 0, 0, 1);

	ws2812_init();
	os_timer_disarm(&pattern_timer);
	os_timer_setfn(&pattern_timer, patternTimer, NULL);
	os_timer_arm(&pattern_timer, 20, 1);

	os_timer_disarm(&button_timer);
	os_timer_setfn(&button_timer, buttonTimer, NULL);
	os_timer_arm(&button_timer, 50, 1);

	os_printf("\nReady\n");
}

void user_rf_pre_init(void) {
}
