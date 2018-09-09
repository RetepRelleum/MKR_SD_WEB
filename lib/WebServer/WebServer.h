#ifndef WEBSERVER
#define WEBSERVER


#include <arduino_secrets.h>
#include <WiFi101.h>
#include <Properties.h>


class WebServer {

int status = WL_IDLE_STATUS;
Properties p;
void printWiFiStatus();

public:
void begin();
void loop();
String getContentType(String content);
};
#endif
