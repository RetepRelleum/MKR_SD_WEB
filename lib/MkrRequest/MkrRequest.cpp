
#include "MkrRequest.h"
#include <Arduino.h>
#include <SD.h>
#include <WiFi101.h>


void MkrRequest::printDirectory(File dir, String di,WiFiClient client) {
        String d=di;
        while (true) {

                client.println("1");
                File entry =  dir.openNextFile();
                if (!entry) {
                        // no more files
                        break;
                }
                client.print(d);
                client.print(entry.name());
                client.print(',');
                if (entry.isDirectory()) {
                        di=d+entry.name()+"/";;
                        printDirectory(entry,di,client);
                }
                entry.close();
        }
}

boolean MkrRequest::dir(String path,WiFiClient client){
        if(path.startsWith("DIR()")) {
                File f=SD.open("/WEB");
                printDirectory(f,"",client);
                f.close();
                return true;
        }else return false;
}

boolean MkrRequest::getDIo(String path,WiFiClient client){
        if(path.startsWith("GETDIO(")) {
                path.replace("GETDIO(","");
                path.replace(")","");
                path.trim();
                if (path.length()==0) {
                        for(int i=0; i<15; i++) {
                                client.println(diRead(i));
                                if (i<14) {
                                        client.println(",");
                                }
                        }
                }else{
                        client.println(diRead(path.toInt()));
                }
                return true;
        }else return false;
}
boolean MkrRequest::setDIo(String path,WiFiClient client){
        if(path.startsWith("SETDIO(")) {
                path.replace("SETDIO(","");
                path.replace(")","");
                path.trim();

                int pin=path.substring(0,path.indexOf(",")).toInt();
                int value=path.substring(path.indexOf(",")+1).toInt();

                if (pin<20 && value<2) {
                        Serial.println(pin);
                        Serial.println(value);
                        pinMode(pin, OUTPUT);
                        diWrite(pin, value);

                        client.println("1");
                        return true;
                }
        }
        return false;
}
boolean MkrRequest::getAIo(String path,WiFiClient client){
        if(path.startsWith("GETAIO(")) {
                path.replace("GETAIO(","");
                path.replace(")","");
                path.trim();
                if (path.length()==0) {
                        for(int i=0; i<7; i++) {

                                client.println(analogRead(i));
                                if (i<6) {
                                        client.println(",");
                                }
                        }
                }else{
                        pMode(path.toInt(),INPUT);
                        client.println(analogRead(path.toInt()));
                }
                return true;
        }else return false;
}
boolean MkrRequest::getData(String path,WiFiClient client){
        int data[512];
        if(path.startsWith("GETDATA(")) {
                path.replace("GETDATA(","");
                path.replace(")","");
                path.trim();
                int pin=path.substring(0,path.indexOf(",")).toInt();
                if (pin<7) {
                        unsigned long m1=micros();

                        for(int i=0; i<512; i++) {
                                data[i]=analogRead(pin);
                        }
                        unsigned long m2=micros();
                        unsigned long dl=(m2-m1)/512;
                        for(int i=0; i<512; i++) {
                                client.print(i*dl);
                                client.print(",");
                                client.println(data[i]);
                        }

                }
                return true;
        }else return false;

/**
 * function um alle file als cvs fiel anzuzeigen
 * http://mkr1000/mkr/dir()
 * @method dir
 * @param  path   url pfad zum Beispiel mkr/dir()
 * @param  client WiFiClient für die Retourantwort
 * @return        true wenn dir == mkr/dir() ansonsten false
 */
}

boolean MkrRequest::parse(String path,WiFiClient client){
        path.replace("/WEB/MKR/", "");
        if (dir(path,client)) return true;
        if (getDIo(path,client)) return true;
        if (setDIo(path,client)) return true;
        if (getAIo(path,client)) return true;
        if (getData(path,client)) return true;
        return false;
}


int MkrRequest::diRead( int pin){
        if (pin== 8) return 0;
        if (pin==9) return 0;
        if (pin==10) return 0;
        if (pin>14) return 0;
        return digitalRead(pin);
}

void MkrRequest::diWrite( int pin,int value){
        if (pin== 8) return;
        if (pin==9) return;
        if (pin==10) return;
        if (pin>14) return;
        digitalWrite(pin,value);
}

void MkrRequest::pMode( int pin,int value){
        if (pin== 8) return;
        if (pin==9) return;
        if (pin==10) return;
        if (pin>14) return;
        pMode(pin,value);
}
