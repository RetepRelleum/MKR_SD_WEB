# Webserver für Arduino

## MKR1000 WIFI mit MKR SD Proto Shield

Entweder man benutzt eine Cloude oder speichert die Daten lokal in einer SD Karte.

Diese Projekt beinhaltet einen Webserver mit Zugriff auf das Web Directory der SD Karte.

-   SD Root
    -   PROPERTY.PRP \\\\ [File mit MIME-TYPE des Webserver](https://wiki.selfhtml.org/wiki/MIME-Type/%C3%9Cbersicht)
    -   Web \\\\ Root Directory  des Webservers
        -   LOG \\\\ Directory des logging tools
            -   20180825.CSV \\\\ Erstellt täglich ein File mit 5 Minuten Werte
        -   JS \\\\ Directory für Javascript Files
        -   MKR \\\\ Directory mit speziellen Befehlen

Zusätzlich hat der Webserver noch folgenden Funktionen.

-   <http://mkr/MKR/DIR(>) liest alle File auf der SD Karte ab dem Directory WEB als CSV File
    -   INDEX.HTM,IMG,IMG/OFF.SVG,IMG/OFF2.SVG,IMG/ON2.SVG,IMG/ON.SVG,IMG/OFF1.SVG,IMG/ON1.SVG,JS,JS/DO.JS,JS/DI.JS,JS/AI.JS,LOG,LOG/20180825.CSV,LOG/20180804.CSV,LOG/20180901.CSV,LOG/20180826.CSV,LOG/19700101.CSV,LOG/20180902.CSV,LOG/20180908.CSV,LOG/20180909.CSV,LOG/20180915.CSV,FAVICON.ICO,LOG.HTM,OS.HTM
-   <http://mkr/MKR/GETDIO(pin>) Liest den Status des Digitalen Pin  (0-14) des MKR100 als CSV File
    -   1
-   <http://mkr/MKR/GETDIO(>) Liest den Status der Digitalen Pin  (0-14) des MKR100 als CSV File
    -   0,1,0,0,1,1,0,1,0,0,0,1,1,1,1
-   <http://mkr/MKR/SETDIO(pin,value>) Setzt den Status des Digitalen Pins (0-14) des MKR100 mit value HIGH 1 or LOW 0 return 1 erfolgreich 0 nicht erfolgreich
    \-1
-   <http://mkr/MKR/GETAIO(pin>) Liest den Wert des Analogen Pin (0-6) des MKR100 als CSV File Werten von 0-1023
    -   143
-   <http://mkr/MKR/GETAIO(>) Liest den Wert der Analogen Pins (0-6) des MKR100 als CSV File Werten von 0-1023
    -   608,440,507,182,421,316,240
-   <http://mkr/MKR/GETDATA(pin>) Liest 512 Werte inkl. Zeit in Mikrosekunden des Analogen Pin (0-6) des MKR100 als CSV File Werten von 0-1023
    -   0,466
    -   422,440
    -   844,360
    -   1266,377
    -   ...

Das Arduino Projekt besteht aus dem Komponenten:

## WebServer

Der Webserver stellt die Webserverfunktionalität zur Verfügung. Inkl. der oben erwähnten MKR Funktionalität welche in der Klasse MKRRequest definiert wurden.
Um den Webserver starten zu können benenne das File arduino_secrets_.h in arduino_secrets.h um und ergänze die WIFI Zugangsdaten.

## Recorder

Der Recorder speichert alle 15 Minuten die Analogwerte in File YYYYMMDD.CSV

## HTML

Für die Darstellung auf einer Webseite stehen die Javascript Klassen **DI,DO,AI** zur Verfügung. Sie sind folgendermassen in das HTML File einzubinden:

```javascript
<script type="text/javascript" src="js/DO.js"></script>
<script type="text/javascript" src="js/DI.js"></script>
<script type="text/javascript" src="js/AI.js"></script>
```

und müssen folgendermassen initialisiert werden:

```javascript
<script>
function interval() {
    aISetValue();
    dISetValue();
    dOSetValue();
}

function onLoad() {
    new DO(document.getElementById(String("do1" )), 1,"img/on.svg", "img/off.svg", "50");
    new DI(document.getElementById(String("di1" )), 1 "img/on2.svg", "img/off2.svg", "50");
    new AI(document.getElementById(String("ai1" )), 1, 10000, 50);
    setInterval(interval, 2000);
}
 </script>
```
```html
<div id="do1"></div>
<div id="di1"></div>
<div id="ai1"></div>
```
und sieht dann folgendermassen aus
<img src="./web/img/off.svg"> oder <img src="./web/img/on.svg">

e
<img src="./web/img/on2.svg" width=100 height=100> oder <img src="./web/img/off2.svg" width=100 height=100>

e
<svg><rect width=100 height=100 stroke=gray fill=white></rect><g stroke=black><line x1=1 y1=20 x2=99 y2=20></line><line x1=1 y1=40 x2=99 y2=40></line><line x1=1 y1=60 x2=99 y2=60></line><line x1=1 y1=80 x2=99 y2=80 ></line></g><rect width=80 height=40 y=60 x="10" fill=blue></rect></svg>

d
