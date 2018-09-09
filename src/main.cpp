
/*
   WiFi Web Server

   A simple web server that shows the value of the analog input pins.
   using a WiFi shield.

   This example is written for a network using WPA encryption. For
   WEP or WPA, change the WiFi.begin() call accordingly.

   Circuit:
 * WiFi shield attached
 * Analog inputs attached to pins A0 through A5 (optional)

   created 13 July 2010
   by dlf (Metodo2 srl)
   modified 31 May 2012
   by Tom Igoe

 */

#include <SPI.h>

#include <Arduino.h>
#include <arduino_secrets.h>
#include <WebServer.h>
#include <Properties.h>
#include <Recorder.h>


int keyIndex = 0;                 // your network key Index number (needed only for WEP)


#define BAUD 115200L



WebServer webServer;
Recorder recorder;
long timestamp=millis();
void setup() {
        //Initialize serial and wait for port to open:

        webServer.begin();
        recorder.begin();


}


void loop() {
        // listen for incoming clients
        webServer.loop();
        recorder.loop();
        if ((millis()-timestamp)>1000) {
                int pin=6;
                pinMode(pin, OUTPUT);
                digitalWrite(pin,!digitalRead(pin));
                timestamp=millis();

        }

}
