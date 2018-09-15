#include <Recorder.h>
#include <Arduino.h>
#include <SD.h>
#include <WiFi101.h>

void Recorder::begin(){

}

void Recorder::loop(){
        long a=millis();
        if ((timer+interval)<a) {
                timer+=interval;
                String time=unixtToString(WiFi.getTime());
                String fname="WEB/LOG/"+time.substring(0,10)+".CSV";
                fname.replace("-","");
                Serial.println(fname);
                File file=SD.open(fname,FILE_WRITE);
                file.print(time);
                for (int i=0; i<7; i++) {
                        file.print(',');
                        file.print(analogRead(i));
                }
                file.println();
                file.close();
        }
}

String Recorder::unixtToString(long t, bool sommer ) {
        long tt = t;
        long wochentag = ((t + 345600) % (604800)) / 86400;
        t += 3600;
        long data [6] = {0, 0, 0, 0, 0, 0};
        data[5] = t % 60; //sek
        t = t / 60;
        data[4] = t % 60; //min
        t = t / 60;
        data[3] = t % 24; //h
        t = t / 24;
        data[0] = t / 365 + 1970; // Year
        data[2] = t % 365;
        long ly;
        for (ly = 1972; ly < data[0]; ly += 4) {
                if (!(ly % 100) && (ly % 400)) continue;
                --data[2];
        }
        if (data[2] < 0) data[2] += 365, --data[0];
        static long const dm[2][12] = {
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
        };
        ly = (data[0] == ly) ? 1 : 0;
        while (data[2] >= dm[ly][data[1]]) data[2] -= dm[ly][data[1]++];
        if (!sommer) {
                if (data[1] > 2 && data[1] < 9) sommer = true;
                if ((data[1] == 2) && (31 - data[2] + wochentag < 7) && (wochentag > 0)) sommer = true;
                if ((data[1] == 2) && (31 - data[2] + wochentag < 7) && (wochentag == 0) && (data[3] > 1)) sommer = true;
                if ((data[1] == 9) && (31 - data[2] + wochentag > 7)) sommer = true;
                if ((data[1] == 9) && (31 - data[2] + wochentag < 7) && (wochentag == 0) && (data[3] < 2)) sommer = true;
                if (sommer) {
                        tt += 3600;
                        return unixtToString(tt, true);
                }
        }
        ++data[2]; //day
        ++data[1]; //mont
        return
                String(data[0]) + "-"
                + (data[1] <= 9 ? "0" + String(data[1]) : String(data[1])) + "-"
                + (data[2] <= 9 ? "0" + String(data[2]) : String(data[2])) + "T"
                + (data[3] <= 9 ? "0" + String(data[3]) : String(data[3])) + ":"
                + (data[4] <= 9 ? "0" + String(data[4]) : String(data[4])) + ":"
                + (data[5] <= 9 ? "0" + String(data[5]) : String(data[5]));
}
