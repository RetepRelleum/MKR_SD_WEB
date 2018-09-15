# Webserver für Arduino
## MKR1000 WIFI mit MKR SD Proto Shield

Entweder man benutzt eine Cloude oder speichert die Daten lokal in einer SD Karte.

Diese Projekt beinhaltet einen Webserver mit Zugriff auf das Web Directory der SD Karte.

* SD Root
  - PROPERTY.PRP \\\\ [File mit MIME-TYPE des Webserver](https://wiki.selfhtml.org/wiki/MIME-Type/%C3%9Cbersicht)
  - Web \\\\ Root Directory  des Webservers
    - LOG \\\\ Directory des logging tools
         - 20180825.CSV \\\\ Erstellt täglich ein File mit 5 Minuten Werte
    - JS \\\\ Directory für Javascript Files
    - MKR \\\\ Directory mit speziellen Befehlen


Webserver mit Zugriff auf alle File auf der SD Karte unter dem Directory WEB.
Zusätzlich noch folgende Funktionen

* http://mkr/MKR/DIR() liest alle File auf der SD Karte ab dem Directory WEB als CSV File
  - INDEX.HTM,IMG,IMG/OFF.SVG,IMG/OFF2.SVG,IMG/ON2.SVG,IMG/ON.SVG,IMG/OFF1.SVG,IMG/ON1.SVG,JS,JS/DO.JS,JS/DI.JS,JS/AI.JS,LOG,LOG/20180825.CSV,LOG/20180804.CSV,LOG/20180901.CSV,LOG/20180826.CSV,LOG/19700101.CSV,LOG/20180902.CSV,LOG/20180908.CSV,LOG/20180909.CSV,LOG/20180915.CSV,FAVICON.ICO,LOG.HTM,OS.HTM
* http://mkr/MKR/GETDIO(n) Liest den Status des Digitalen Pin n (0-14) des MKR100 als CSV File
  - 1
* http://mkr/MKR/GETDIO() Liest den Status der Digitalen Pin n (0-14) des MKR100 als CSV File
  - 0,1,0,0,1,1,0,1,0,0,0,1,1,1,1

![Alt text](./controllers_brief.svg)
<img src="./web/img/off.svg">
