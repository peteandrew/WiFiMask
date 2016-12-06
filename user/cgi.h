#ifndef CGI_H
#define CGI_H

#include "httpd.h"

int cgiLeds(HttpdConnData *connData);
int tplLeds(HttpdConnData *connData, char *token, void **arg);

#endif
