#ifndef MKRREQUEST
#define MKRREQUEST
#include <Arduino.h>
#include <WiFi101.h>
#include <SD.h>


class MkrRequest {
/**
 * [printDirectory description]
 * @method printDirectory
 * @param  dir            [description]
 * @param  di             [description]
 * @param  client         [description]
 */
void printDirectory(File dir, String di,WiFiClient client);
boolean dir(String path,WiFiClient client);
boolean getDIo(String path,WiFiClient client);
boolean setDIo(String path,WiFiClient client);
boolean getAIo(String path,WiFiClient client);
boolean getData(String path,WiFiClient client);
int diRead(int pin);
void diWrite(int pin,int value);
void pMode(int pin,int mode);
public:
boolean parse(String path,WiFiClient client);
};


#endif
