#pragma once

#include <Arduino.h>

#define DEBUG_SERIAL 1

#define LED_PIN         3
#define BUTTON_PIN      2

#define NUM_LEDS        120

#define BRIGHTNESS      255

#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB

#if DEBUG_SERIAL
    #define DEBUG_PRINT(x)    Serial.print(x)
    #define DEBUG_PRINTLN(x)  Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif