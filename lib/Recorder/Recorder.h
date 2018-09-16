#ifndef RECORDER
#define RECORDER

#include <Arduino.h>

 class Recorder {
    long dtInMin=10;
   long timer=-dtInMin*58*1000;
   long interval=dtInMin*59*1000;

 public:
   void begin();
   void loop();
   String unixtToString(long t, bool sommer = false);

 };


#endif
