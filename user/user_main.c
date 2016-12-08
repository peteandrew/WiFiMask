#include <esp8266.h>
#include "stdout.h"
#include "ws2812_i2s.h"
#include "leds.h"
#include "pattern.h"


// 0 - all red
// 1 - all green
// 2 - all blue
// 3 - left eyebrow red
// 4 - left eyebrow green
// 5 - left eyebrow blue
// 6 - right eyebrow red
// 7 - right eyebrow green
// 8 - right eyebrow blue
// 9 - tash red
// 10 - tash green
// 11 - tash blue
uint8_t mode = 0;
uint8_t last_leds[512*3] = {0};
uint32_t frame = 0;

uint8_t buttonShortPress = 0;
uint8_t buttonLongPress = 0;


static ETSTimer pattern_timer;
static void ICACHE_FLASH_ATTR patternTimer(void *arg) {
	if (buttonShortPress) {
		if (++mode > 11) {
			mode = 0;
		}
		buttonShortPress = 0;
		os_printf("\nMode: %d\n", mode);
	}
	if (buttonLongPress) {
		switch(mode) {
			case 0:
				incrementRed();
				os_printf("\nIncrement all red\n");
				break;
			case 1:
				incrementBlue();
				os_printf("\nIncrement all blue\n");
				break;
			case 2:
				incrementGreen();
				os_printf("\nIncrement all green\n");
				break;
			case 3:
			  incrementLeftEyebrowRed();
				os_printf("\nIncrement left eyebrow red\n");
				break;
			case 4:
			  incrementLeftEyebrowBlue();
				os_printf("\nIncrement left eyebrow blue\n");
				break;
			case 5:
			  incrementLeftEyebrowGreen();
				os_printf("\nIncrement left eyebrow green\n");
				break;
			case 6:
			  incrementRightEyebrowRed();
				os_printf("\nIncrement right eyebrow red\n");
				break;
			case 7:
			  incrementRightEyebrowBlue();
				os_printf("\nIncrement right eyebrow blue\n");
				break;
			case 8:
			  incrementRightEyebrowGreen();
				os_printf("\nIncrement right eyebrow green\n");
				break;
			case 9:
			  incrementTashRed();
				os_printf("\nIncrement tash red\n");
				break;
			case 10:
			  incrementTashBlue();
				os_printf("\nIncrement tash blue\n");
				break;
			case 11:
			  incrementTashGreen();
				os_printf("\nIncrement tash green\n");
				break;
		}
		buttonLongPress = 0;
	}

	int it;
	// Left eyebrow
	for (it=0; it<4; ++it) {
		if (mode < 3) {
			last_leds[3*it+0] = getRed();
			last_leds[3*it+1] = getBlue();
			last_leds[3*it+2] = getGreen();
		} else {
			last_leds[3*it+0] = getLeftEyebrowRed();
			last_leds[3*it+1] = getLeftEyebrowBlue();
			last_leds[3*it+2] = getLeftEyebrowGreen();
		}
	}
	// Right eyebrow
	for (it=4; it<8; ++it) {
		if (mode < 3) {
			last_leds[3*it+0] = getRed();
			last_leds[3*it+1] = getBlue();
			last_leds[3*it+2] = getGreen();
		} else {
			last_leds[3*it+0] = getRightEyebrowRed();
			last_leds[3*it+1] = getRightEyebrowBlue();
			last_leds[3*it+2] = getRightEyebrowGreen();
		}
	}
	// Tash
	for (it=8; it<12; ++it) {
		if (mode < 3) {
			last_leds[3*it+0] = getRed();
			last_leds[3*it+1] = getBlue();
			last_leds[3*it+2] = getGreen();
		} else {
			last_leds[3*it+0] = getTashRed();
			last_leds[3*it+1] = getTashBlue();
			last_leds[3*it+2] = getTashGreen();
		}
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
		if (downCnt > 2 && !buttonLongPress) {
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
