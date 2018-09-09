#include <WebServer.h>
#include <Arduino.h>
#include <WiFi101.h>
#include <Properties.h>
#include <SD.h>
#include <MkrRequest.h>

WiFiServer server(80);



void WebServer::printWiFiStatus() {
        // print the SSID of the network you're attached to:
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        // print your WiFi shield's IP address:
        IPAddress ip = WiFi.localIP();
        Serial.print("IP Address: ");
        Serial.println(ip);

        // print the received signal strength:
        long rssi = WiFi.RSSI();
        Serial.print("signal strength (RSSI):");
        Serial.print(rssi);
        Serial.println(" dBm");
}
void WebServer::begin(){

        // check for the presence of the shield:
        if (WiFi.status() == WL_NO_SHIELD) {
                Serial.println("WiFi shield not present");
                // don't continue:
                while (true);
        }
        // attempt to connect to WiFi network:
        while (status != WL_CONNECTED) {
                Serial.print("Attempting to connect to SSID: ");
                Serial.println(WLAN_SSID);
                // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
                status = WiFi.begin(WLAN_SSID, WLAN_PASS);

                // wait 10 seconds for connection:
                  while (status != WL_CONNECTED){
                    delay(100);
                  }
        }
        server.begin();
        // you're connected now, so print out the status:
        printWiFiStatus();
        if (!SD.begin(chipSelect)) {
                Serial.println("Card failed, or not present");
                // don't do anything more:
                while (1);
        }
        Serial.println("card initialized.");
}

String WebServer::getContentType(String content){
      Serial.println("------------");
        Serial.println(content);
        content.toLowerCase();
        String ret=p.property_get(content);
        Serial.println(ret);
        if (ret.length()==0) {
                ret="text/html";
        }
        Serial.println(ret);

        return ret;
}
void WebServer::loop(){
        WiFiClient client = server.available();
        if (client) {
                Serial.println("new client");
                // an http request ends with a blank line
                boolean currentLineIsBlank = true;
                String line="";
                String path="";
                while (client.connected()) {
                        if (client.available()) {
                                char c = client.read();
                                Serial.write(c);
                                line+=c;
                                if (c == '\n' && currentLineIsBlank) {
                                        path.remove(path.length()-1);
                                        if (path.equalsIgnoreCase("/")) {
                                                path="/INDEX.HTM";
                                        }
                                        path="/WEB"+path;
                                        // send a standard http response header
                                        client.println("HTTP/1.1 200 OK");
                                        client.print("Content-Type: ");
                                        if (path.substring(0,8).equalsIgnoreCase("/WEB/MKR")) {
                                                client.println(getContentType("csv"));
                                        }else{
                                                client.println(getContentType(path.substring(path.length()-3)));
                                        }
                                        client.println("Connection: close"); // the connection will be closed after completion of the response
                                        client.println();
                                        path.toUpperCase();
                                        MkrRequest mkrRequest;
                                        if (!mkrRequest.parse(path,client)) {
                                                File dataFile = SD.open(path);
                                                if (dataFile) {
                                                        while (dataFile.available()) {
                                                                int av= dataFile.available();
                                                                if (av<50) {
                                                                        char a[av];
                                                                        dataFile.read(a,av);
                                                                        client.write(a,av);
                                                                }else{
                                                                        char a[50];
                                                                        dataFile.read(a,50);
                                                                        client.write(a,50);
                                                                }
                                                        }
                                                        dataFile.close();
                                                }else{
                                                        client.println("<!DOCTYPE html>");
                                                        client.println("<html>");
                                                        client.println("<head>");
                                                        client.println("<title>Fehler</title>");
                                                        client.println("</head>");
                                                        client.println("<body>");
                                                        client.println("<h1>Fiel not found</h1>");
                                                        client.println("</body>");
                                                        client.println("</html>");
                                                }
                                        }
                                        break;
                                }
                                if (c == '\n') {
                                        // you're starting a new line
                                        currentLineIsBlank = true;
                                        if (line.startsWith("GET")) {
                                                line.replace("GET ", "");
                                                line.remove(line.indexOf("HTTP/1.1"));
                                                path=line;

                                        }
                                        line="";
                                }
                                else if (c != '\r') {
                                        // you've gotten a character on the current line
                                        currentLineIsBlank = false;
                                }
                        }
                }
                // give the web browser time to receive the data
                delay(1);
                // close the connection:
                client.stop();
                Serial.println("client disconnected");
        }
}
