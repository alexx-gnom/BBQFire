#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "Aurora.h"

namespace
{
    const CRGBPalette16 AuroraPalette =
    {
        CRGB(0,0,0),
        CRGB(0,8,20),
        CRGB(0,25,60),
        CRGB(0,60,120),

        CRGB(0,120,140),
        CRGB(0,180,120),
        CRGB(80,255,180),
        CRGB(180,255,255),

        CRGB::White,
        CRGB(180,255,255),
        CRGB(80,255,180),
        CRGB(0,180,120),

        CRGB(0,120,140),
        CRGB(0,60,120),
        CRGB(0,20,50),
        CRGB(0,0,0)
    };
}

void AuroraBegin()
{
    FastLED.clear();
}

void AuroraLoop()
{
    uint32_t t = millis();

    for(uint16_t i = 0; i < NUM_LEDS; i++)
    {
        uint8_t color =
            inoise8(
                i * 30,
                t / 18
            );

        uint8_t bright =
            inoise8(
                6000 + i * 15,
                t / 27
            );

        bright = scale8(bright, 220);

        CRGB c =
            ColorFromPalette(
                AuroraPalette,
                color,
                bright,
                LINEARBLEND);

        // Легке мерехтіння
        c.nscale8_video(
            220 + sin8(t / 40 + i * 3) / 8);

        leds[i] = c;
    }
}

const Effect auroraEffect =
{
    "Aurora",
    AuroraBegin,
    AuroraLoop
};