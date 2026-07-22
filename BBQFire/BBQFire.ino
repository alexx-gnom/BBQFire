#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "EffectManager.h"
#include "Effects.h"

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    EmbersBegin();
}

void loop()
{
    UpdateEffect();

    FastLED.show();
}