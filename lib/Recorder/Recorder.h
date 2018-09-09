#ifndef RECORDER
#define RECORDER

#include <Arduino.h>

 class Recorder {
   unsigned long timer=-53990000;
   unsigned long interval=54000000;
 public:
   void begin();
   void loop();
   String unixtToString(uint32_t t, bool sommer = false);

 };


#endif
