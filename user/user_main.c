#include <esp8266.h>
#include "stdout.h"
#include "ws2812_i2s.h"
#include "leds.h"
#include "pattern.h"


// 0 - all red
// 1 - all green
// 2 - all blue
uint8_t mode = 0;
uint8_t constClr[3];
uint8_t last_leds[512*3] = {0};
uint32_t frame = 0;

uint8_t buttonShortPress = 0;
uint8_t buttonLongPress = 0;


static ETSTimer pattern_timer;
static void ICACHE_FLASH_ATTR patternTimer(void *arg) {
	if (buttonShortPress) {
		if (++mode > 2) {
			mode = 0;
		}
		buttonShortPress = 0;
		os_printf("\nMode: %d\n", mode);
	}
	if (buttonLongPress) {
		switch(mode) {
			case 0:
				incrementRed();
				os_printf("\nIncrement red\n");
				break;
			case 1:
				incrementBlue();
				os_printf("\nIncrement blue\n");
				break;
			case 2:
				incrementGreen();
				os_printf("\nIncrement green\n");
				break;
		}
		buttonLongPress = 0;
	}

	constClr[0] = getRed();
	constClr[1] = getGreen();
	constClr[2] = getBlue();

  int it;
  for(it=0; it<getNumLeds(); ++it) {
		//uint32_t hex = hex_pattern( getPattern(), it, getNumLeds(), frame, constClr );
		//last_leds[3*it+0] = (hex>>8);
		//last_leds[3*it+1] = (hex);
		//last_leds[3*it+2] = (hex>>16);
		last_leds[3*it+0] = constClr[0];
		last_leds[3*it+1] = constClr[1];
		last_leds[3*it+2] = constClr[2];
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
