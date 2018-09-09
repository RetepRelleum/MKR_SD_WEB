#include <Properties.h>
#include <Arduino.h>
#include <SD.h>

String Properties:: property_get(String key){
        key.toLowerCase();
        File file=SD.open(fName,FILE_READ);
        if (file) {
                String iKey="";
                boolean readKey=true;
                String iValue="";
                while (file.available()) {
                        char c=file.read();

                        if (c == '\n') {
                                readKey=true;
                                if (key.equalsIgnoreCase(iKey)) {
                                        file.close();
                                        delay(10);

                                        return iValue;
                                }
                                iKey="";
                                iValue="";
                        }else if (c=='=') {
                                readKey=false;
                        }else if (c=='\r') {
                        }else{
                                if (readKey) {
                                        iKey+=c;
                                }else {
                                        iValue+=c;
                                }
                        }
                }
                file.close();

        }
        return "";
}


void Properties::property_set(String key, String value){
        File file=SD.open(fName,FILE_WRITE);
        if (file) {
                file.print(key);
                file.print("=");
                file.print(value);
                file.print('\n');
                file.close();

        }
}

void Properties::property_reset(){
        SD.remove(fName);
}
