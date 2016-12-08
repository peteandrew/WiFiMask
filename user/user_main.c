#include <esp8266.h>
#include "stdout.h"
#include "ws2812_i2s.h"
#include "leds.h"
#include "pattern.h"


// 0 - left eyebrow hue
// 1 - left eyebrow sat
// 2 - left eyebrow value
// 3 - right eyebrow hue
// 4 - right eyebrow sat
// 5 - right eyebrow value
// 6 - tash hue
// 7 - tash sat
// 8 - tash value
uint8_t mode = 0;
uint8_t last_leds[512*3] = {0};
uint32_t frame = 0;

uint8_t buttonShortPress = 0;
uint8_t buttonLongPress = 0;


static ETSTimer pattern_timer;
static void ICACHE_FLASH_ATTR patternTimer(void *arg) {
	if (buttonShortPress) {
		if (++mode > 8) {
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
			  incrementLeftEyebrowSat();
				os_printf("\nIncrement left eyebrow sat\n");
				break;
			case 2:
			  incrementLeftEyebrowValue();
				os_printf("\nIncrement left eyebrow value\n");
				break;
			case 3:
			  incrementRightEyebrowHue();
				os_printf("\nIncrement right eyebrow hue\n");
				break;
			case 4:
			  incrementRightEyebrowSat();
				os_printf("\nIncrement right eyebrow sat\n");
				break;
			case 5:
			  incrementRightEyebrowValue();
				os_printf("\nIncrement right eyebrow value\n");
				break;
			case 6:
			  incrementTashHue();
				os_printf("\nIncrement tash hue\n");
				break;
			case 7:
			  incrementTashSat();
				os_printf("\nIncrement tash sat\n");
				break;
			case 8:
			  incrementTashValue();
				os_printf("\nIncrement tash value\n");
				break;
		}
		buttonLongPress = 0;
	}

	int it;
	uint32_t rgb;
	// Tash
	for (it=0; it<4; ++it) {
		if (mode < 9) {
			rgb = HSVtoHEX(getTashHue(), getTashSat(), getTashValue());
		}
		last_leds[3*it+0] = (rgb>>8);
		last_leds[3*it+1] = (rgb);
		last_leds[3*it+2] = (rgb>>16);
	}
	// Right eyebrow
	for (it=4; it<8; ++it) {
		if (mode < 9) {
			rgb = HSVtoHEX(getRightEyebrowHue(), getRightEyebrowSat(), getRightEyebrowValue());
		}
		last_leds[3*it+0] = (rgb>>8);
		last_leds[3*it+1] = (rgb);
		last_leds[3*it+2] = (rgb>>16);
	}
	// Left eyebrow
	for (it=8; it<12; ++it) {
		if (mode < 9) {
			rgb = HSVtoHEX(getLeftEyebrowHue(), getLeftEyebrowSat(), getLeftEyebrowValue());
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
		if (downCnt > 4 && !buttonLongPress) {
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
