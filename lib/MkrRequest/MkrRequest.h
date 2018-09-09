#ifndef MKRREQUEST
#define MKRREQUEST
#include <Arduino.h>
#include <WiFi101.h>
#include <SD.h>


class MkrRequest {
/**
 * [rekursive funktion umd file auf directory zu lesen ]
 * @method printDirectory
 * @param  dir            directory name
 * @param  di             pfad zu directory name
 * @param  client         WiFiClient
 */
void printDirectory(File dir, String di,WiFiClient client);
/**
 * function um alle file als cvs fiel anzuzeigen
 * http://mkr1000/mkr/dir()
 * @method dir
 * @param  path   url pfad zum Beispiel mkr/dir()
 * @param  client WiFiClient für die Retourantwort
 * @return        true wenn dir == WEB/MKR/DIR(x) ansonsten false
 */
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
