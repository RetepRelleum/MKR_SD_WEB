#ifndef RECORDER
#define RECORDER

#include <Arduino.h>

 class Recorder {
   unsigned long timer=0;
   unsigned long interval=1000*60;
 public:
   void begin();
   void loop();
   String unixtToString(uint32_t t, bool sommer = false);

 };


#endif
