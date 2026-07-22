#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "Plasma.h"

namespace
{
    const CRGBPalette16 PlasmaPalette =
    {
        CRGB(5,0,15),
        CRGB(20,0,60),
        CRGB(60,0,120),
        CRGB(120,0,255),

        CRGB(60,40,255),
        CRGB(0,120,255),
        CRGB(0,220,255),
        CRGB(120,255,255),

        CRGB::White,
        CRGB(120,255,255),
        CRGB(0,220,255),
        CRGB(0,120,255),

        CRGB(60,40,255),
        CRGB(120,0,255),
        CRGB(40,0,80),
        CRGB(5,0,15)
    };
}

void PlasmaBegin()
{
    FastLED.clear();
}

void PlasmaLoop()
{
    uint32_t t = millis();

    for(uint16_t i = 0; i < NUM_LEDS; i++)
    {
        uint8_t v = 0;

        v += sin8(i * 6 + t / 12);

        v += sin8(i * 11 - t / 18);

        v += inoise8(i * 28, t / 10);

        v /= 3;

        leds[i] = ColorFromPalette(
            PlasmaPalette,
            v,
            255,
            LINEARBLEND);
    }
}

const Effect plasmaEffect =
{
    "Plasma",
    PlasmaBegin,
    PlasmaLoop
};