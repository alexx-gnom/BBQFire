#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "Forge.h"

namespace
{
    const CRGBPalette16 ForgePalette =
    {
        CRGB(0,0,0),
        CRGB(10,0,0),
        CRGB(30,0,0),
        CRGB(60,4,0),

        CRGB(100,18,0),
        CRGB(160,45,0),
        CRGB(230,90,0),
        CRGB(255,170,40),

        CRGB(255,255,180),
        CRGB(255,170,40),
        CRGB(230,90,0),
        CRGB(160,45,0),

        CRGB(100,18,0),
        CRGB(60,4,0),
        CRGB(20,0,0),
        CRGB(0,0,0)
    };

    uint8_t heat[NUM_LEDS];

    float frontPos;
    float frontSpeed;
    bool frontActive;

    uint32_t lastSpawn;
}

void ForgeBegin()
{
    memset(heat, 0, sizeof(heat));

    frontActive = false;
    lastSpawn = millis();

    FastLED.clear();
}

void ForgeLoop()
{
    uint32_t now = millis();

    //----------------------------------------------------
    // Охолодження
    //----------------------------------------------------

    for(uint16_t i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(1,4));
    }

    //----------------------------------------------------
    // Новий "подих"
    //----------------------------------------------------

    if(!frontActive)
    {
        if(now - lastSpawn > random16(1500,3500))
        {
            frontActive = true;
            frontPos = -12.0f;
            frontSpeed = random(20,35) / 10.0f;

            lastSpawn = now;
        }
    }

    //----------------------------------------------------
    // Рух фронту
    //----------------------------------------------------

    if(frontActive)
    {
        frontPos += frontSpeed;

        if(frontPos > NUM_LEDS + 12)
        {
            frontActive = false;
        }

        for(int i=-10;i<=10;i++)
        {
            int pos = (int)frontPos + i;

            if(pos < 0 || pos >= NUM_LEDS)
                continue;

            uint8_t energy =
                255 - abs(i)*24;

            heat[pos] =
                qadd8(
                    heat[pos],
                    energy
                );
        }
    }

    //----------------------------------------------------
    // Перемішування тепла
    //----------------------------------------------------

    for(uint16_t i=1;i<NUM_LEDS-1;i++)
    {
        heat[i] =
        (
            heat[i-1]+
            heat[i]+
            heat[i+1]
        )/3;
    }

    //----------------------------------------------------
    // Відображення
    //----------------------------------------------------

    for(uint16_t i=0;i<NUM_LEDS;i++)
    {
        uint8_t value = heat[i];

        value =
            qadd8(
                value,
                scale8(
                    inoise8(i*35,now/3),
                    25
                )
            );

        leds[i] =
            ColorFromPalette(
                ForgePalette,
                value,
                value,
                LINEARBLEND
            );
    }
}

const Effect forgeEffect =
{
    "Forge",
    ForgeBegin,
    ForgeLoop
};