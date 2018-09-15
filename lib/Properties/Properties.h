#ifndef PROPERTIES
#define PROPERTIES
#include <Arduino.h>

class Properties {
String fName="PROPERTY.PRP";
public:
String property_get(String key);
void property_set(String key, String value);
void property_reset();
};


#endif
