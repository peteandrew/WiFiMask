/*
Some random cgi routines. Used in the LED example and the page that returns the entire
flash as a binary. Also handles the hit counter on the main page.
*/

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain
 * this notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */


#include <esp8266.h>
#include "cgi.h"
#include "leds.h"


int ICACHE_FLASH_ATTR cgiLeds(HttpdConnData *connData) {
	int len;
	char buff[1024];

	if (connData->conn==NULL) {
		//Connection aborted. Clean up.
		return HTTPD_CGI_DONE;
	}

	len=httpdFindArg(connData->post->buff, "leds", buff, sizeof(buff));
	if (len!=0) {
		os_printf("Set number of LEDs to %s", buff);
		setNumLeds((uint16_t)atoi(buff));
	}

	len=httpdFindArg(connData->post->buff, "pattern", buff, sizeof(buff));
	if (len!=0) {
		os_printf("Set pattern to %s", buff);
		setPattern((uint8_t)atoi(buff));
	}

	len=httpdFindArg(connData->post->buff, "red", buff, sizeof(buff));
	if (len!=0) {
		os_printf("Set red to %s", buff);
		setRed((uint8_t)atoi(buff));
	}

	len=httpdFindArg(connData->post->buff, "green", buff, sizeof(buff));
	if (len!=0) {
		os_printf("Set green to %s", buff);
		setGreen((uint8_t)atoi(buff));
	}

	len=httpdFindArg(connData->post->buff, "blue", buff, sizeof(buff));
	if (len!=0) {
		os_printf("Set blue to %s", buff);
		setBlue((uint8_t)atoi(buff));
	}

	httpdRedirect(connData, "index.tpl");
	return HTTPD_CGI_DONE;
}


int ICACHE_FLASH_ATTR tplLeds(HttpdConnData *connData, char *token, void **arg) {
	char buff[128];
	if (token==NULL) return HTTPD_CGI_DONE;

	if (os_strcmp(token, "numleds")==0) {
		os_sprintf(buff, "%d", (int)getNumLeds());
	} else if (os_strcmp(token, "pattern")==0) {
		os_sprintf(buff, "%d", (int)getPattern());
	} else if (os_strcmp(token, "red")==0) {
		os_sprintf(buff, "%d", (int)getRed());
	} else if (os_strcmp(token, "green")==0) {
		os_sprintf(buff, "%d", (int)getGreen());
	} else if (os_strcmp(token, "blue")==0) {
		os_sprintf(buff, "%d", (int)getBlue());
	}
	httpdSend(connData, buff, -1);
	return HTTPD_CGI_DONE;
}
