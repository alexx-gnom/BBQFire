#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "Fireplace.h"

namespace
{
    struct Flame
    {
        bool active;

        int16_t pos;          // 8.8 fixed point

        int8_t velocity;      // -2..2

        uint8_t radius;

        uint8_t brightness;

        uint16_t life;

        uint16_t age;
    };

    constexpr uint8_t FLAME_COUNT = 8;

    Flame flames[FLAME_COUNT];

    const CRGBPalette16 FirePalette =
    {
        CRGB::Black,
        CRGB(30,0,0),
        CRGB(90,5,0),
        CRGB(180,25,0),

        CRGB(255,70,0),
        CRGB(255,140,0),
        CRGB(255,210,80),
        CRGB::White,

        CRGB::White,
        CRGB(255,210,80),
        CRGB(255,140,0),
        CRGB(255,70,0),

        CRGB(180,25,0),
        CRGB(90,5,0),
        CRGB(30,0,0),
        CRGB::Black
    };

    void SpawnFlame()
    {
        for(uint8_t i=0;i<FLAME_COUNT;i++)
        {
            if(flames[i].active)
                continue;

            flames[i].active = true;

            flames[i].pos = random16(NUM_LEDS << 8);

            flames[i].velocity = random8(5) - 2;

            flames[i].radius = random8(4,12);

            flames[i].brightness = random8(170,255);

            flames[i].life = random16(400,1200);

            flames[i].age = 0;

            break;
        }
    }
}

void FireplaceBegin()
{
    memset(flames,0,sizeof(flames));

    FastLED.clear();
}

void FireplaceLoop()
{
    fadeToBlackBy(leds,NUM_LEDS,70);

    if(random8()<35)
        SpawnFlame();

    for(uint8_t f=0;f<FLAME_COUNT;f++)
    {
        Flame& flame = flames[f];

        if(!flame.active)
            continue;

        flame.age += 20;

        if(flame.age >= flame.life)
        {
            flame.active = false;
            continue;
        }

        flame.pos += flame.velocity;

        uint8_t fade =
            map(flame.age,0,flame.life,255,0);

        uint8_t value =
            scale8(flame.brightness,fade);

        int16_t center = flame.pos >> 8;

        for(int8_t dx=-flame.radius;dx<=flame.radius;dx++)
        {
            int16_t led = center + dx;

            if(led<0 || led>=NUM_LEDS)
                continue;

            uint8_t dist = abs(dx);

            uint8_t level =
                qsub8(value,dist*(255/flame.radius));

            leds[led] +=
                ColorFromPalette(
                    FirePalette,
                    level,
                    level,
                    LINEARBLEND);
        }
    }
}

const Effect fireplaceEffect =
{
    "Fireplace",
    FireplaceBegin,
    FireplaceLoop
};