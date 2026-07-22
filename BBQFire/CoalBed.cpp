#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "CoalBed.h"

namespace
{
    // Власна палітра жару
    const CRGBPalette16 CoalPalette =
{
    CRGB(0,0,0),
    CRGB(12,0,0),
    CRGB(30,0,0),
    CRGB(60,5,0),

    CRGB(100,15,0),
    CRGB(150,40,0),
    CRGB(220,90,0),
    CRGB(255,170,40),

    CRGB(255,220,120),
    CRGB(255,170,40),
    CRGB(220,90,0),
    CRGB(150,40,0),

    CRGB(100,15,0),
    CRGB(60,5,0),
    CRGB(20,0,0),
    CRGB(0,0,0)
};
}

void CoalBedBegin()
{
    FastLED.clear();
}

void CoalBedLoop()
{
    uint32_t t = millis();

    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        //-------------------------------------------------------
        // Велика структура жару
        //-------------------------------------------------------

        uint8_t heat =
            inoise8(i * 22, t / 30);

        //-------------------------------------------------------
        // "Кисень"
        //-------------------------------------------------------

        uint8_t oxygen =
            inoise8(4000 + i * 14, t / 10);

        //-------------------------------------------------------
        // Поєднання
        //-------------------------------------------------------

        uint16_t value = heat;
        value *= oxygen;
        value >>= 8;

        //-------------------------------------------------------
        // Трохи підсилюємо контраст
        //-------------------------------------------------------

        value = scale8(value, 220);

        //-------------------------------------------------------
        // Мінімальний поріг
        //-------------------------------------------------------

        if (value < 15)
            value = 0;

        leds[i] = ColorFromPalette(
            CoalPalette,
            value,
            value,
            LINEARBLEND);
    }
}

const Effect coalBedEffect =
{
    "Coal Bed",
    CoalBedBegin,
    CoalBedLoop
};