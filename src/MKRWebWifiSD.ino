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
