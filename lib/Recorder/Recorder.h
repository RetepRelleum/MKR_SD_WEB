#ifndef RECORDER
#define RECORDER

#include <Arduino.h>

 class Recorder {
   long timer=-590000;
   long interval=600000;
 public:
   void begin();
   void loop();
   String unixtToString(long t, bool sommer = false);

 };


#endif
