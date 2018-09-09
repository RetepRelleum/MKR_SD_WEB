#ifndef PROPERTIES
#define PROPERTIES

#include <Arduino.h>

class Properties {
public:
property_get(String key);
property_set(String key, String value);
property_reset();
}
