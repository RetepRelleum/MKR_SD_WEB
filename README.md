# Webserver für Arduino
## MKR1000 WIFI mit MKR SD Proto Shield

Entweder man benutzt eine Cloude oder speichert die Daten lokal in einer SD Karte.

Diese Projekt beinhaltet einen Webserver mit Zugriff auf das Web Directory der SD Karte.

SD Root
* PROPERTY.PRP \\\\ [File mit MIME-TYPE des Webserver](https://wiki.selfhtml.org/wiki/MIME-Type/%C3%9Cbersicht)
* Web \\\\ Root Directory  des Webservers
 * LOG \\\\ Directory des logging tools
       - 20180825.CSV \\\\ Erstellt täglich ein File mit 5 Minuten Werte
 * JS \\\\ Directory für Javascript Files
 * MKR \\\\ Directory mit speziellen Befehlen


Webserver mit Zugriff auf alle File auf der SD Karte unter dem Directory WEB.
Zusätzlich noch folgende Funktionen

http://mkr/MKR/DIR() liest alle File auf der SD Karte ab dem Directory WEB als CSV File
http://mkr/MKR/GETDIO()

![Alt text](./controllers_brief.svg)
<img src="./web/img/off.svg">
