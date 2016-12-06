/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain
 * this notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <esp8266.h>
#include "httpd.h"
#include "httpdespfs.h"
#include "cgi.h"
#include "stdout.h"
//#include "auth.h"
#include "espfs.h"
#include "captdns.h"
#include "webpages-espfs.h"
#include "ws2812_i2s.h"
#include "leds.h"
#include "pattern.h"


/*
This is the main url->function dispatching data struct.
In short, it's a struct with various URLs plus their handlers. The handlers can
be 'standard' CGI functions you wrote, or 'special' CGIs requiring an argument.
They can also be auth-functions. An asterisk will match any url starting with
everything before the asterisks; "*" matches everything. The list will be
handled top-down, so make sure to put more specific rules above the more
general ones. Authorization things (like authBasic) act as a 'barrier' and
should be placed above the URLs they protect.
*/
HttpdBuiltInUrl builtInUrls[]={
	{"*", cgiRedirectApClientToHostname, "esp8266.nonet"},
	{"/", cgiRedirect, "/index.tpl"},
	{"/index.tpl", cgiEspFsTemplate, tplLeds},
	{"/index.cgi", cgiLeds, NULL},
	{"*", cgiEspFsHook, NULL}, //Catch-all cgi function for the filesystem
	{NULL, NULL, NULL}
};


uint8_t constClr[3];
uint8_t last_leds[512*3] = {0};
uint32_t frame = 0;

static ETSTimer pattern_timer;
static void ICACHE_FLASH_ATTR patternTimer(void *arg) {
	constClr[0] = getRed();
	constClr[1] = getGreen();
	constClr[2] = getBlue();

  int it;
  for(it=0; it<getNumLeds(); ++it) {
		uint32_t hex = hex_pattern( getPattern(), it, getNumLeds(), frame, constClr );
		last_leds[3*it+0] = (hex>>8);
		last_leds[3*it+1] = (hex);
		last_leds[3*it+2] = (hex>>16);
  }
	frame++;
	// os_printf("Frame: %d\n", (int)frame);
  ws2812_push( last_leds, 3*getNumLeds());
}

//Main routine. Initialize stdout, the I/O, filesystem and the webserver and we're done.
void user_init(void) {
	stdoutInit();
	captdnsInit();

	// 0x40200000 is the base address for spi flash memory mapping, ESPFS_POS is the position
	// where image is written in flash that is defined in Makefile.
#ifdef ESPFS_POS
	espFsInit((void*)(0x40200000 + ESPFS_POS));
#else
	espFsInit((void*)(webpages_espfs_start));
#endif

	httpdInit(builtInUrls, 80);

	ws2812_init();
	os_timer_disarm(&pattern_timer);
	os_timer_setfn(&pattern_timer, patternTimer, NULL);
	os_timer_arm(&pattern_timer, 20, 1);

	os_printf("\nReady\n");
}

void user_rf_pre_init() {
	//Not needed, but some SDK versions want this defined.
}
