#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "Embers.h"

namespace
{
    constexpr uint8_t EMBER_COUNT = 18;

    struct Ember
    {
        float position;
        float radius;

        float brightness;

        float targetBrightness;

        float twinkleSpeed;
    };

    Ember embers[EMBER_COUNT];

    //--------------------------------------------------------------------

    float RandomFloat(float minValue, float maxValue)
    {
        return minValue +
               (float)random16(10000) / 10000.0f *
               (maxValue - minValue);
    }

    //--------------------------------------------------------------------

    void Respawn(Ember& e)
    {
        e.position = RandomFloat(0, NUM_LEDS - 1);

        e.radius = RandomFloat(2.5f, 5.5f);

        e.brightness = RandomFloat(20, 80);

        e.targetBrightness = RandomFloat(140, 255);

        e.twinkleSpeed = RandomFloat(0.01f, 0.05f);
    }

    //--------------------------------------------------------------------

    void Update()
    {
        EVERY_N_MILLISECONDS(30)
        {
            for (auto& e : embers)
            {
                if (e.brightness < e.targetBrightness)
                {
                    e.brightness += 2;
                }
                else
                {
                    e.brightness -= RandomFloat(0.2f, 0.8f);

                    if (e.brightness < 10)
                        Respawn(e);
                }
            }
        }
    }

    //--------------------------------------------------------------------

    void Render()
    {
        fill_solid(leds, NUM_LEDS, CRGB::Black);

        float t = millis() * 0.002f;

        for (const auto& e : embers)
        {
            float pulse = 0.85f +
                          0.15f * sin(t * 20.0f * e.twinkleSpeed);

            float intensity = e.brightness * pulse;

            for (int led = 0; led < NUM_LEDS; led++)
            {
                float d = fabs(led - e.position);

                if (d > e.radius)
                    continue;

                float k = 1.0f - d / e.radius;

                uint8_t value = constrain(intensity * k, 0, 255);

                leds[led].r = qadd8(leds[led].r, value);
                leds[led].g = qadd8(leds[led].g, value / 5);
            }
        }
    }
}

void EmbersBegin()
{
    random16_set_seed(analogRead(A0));

    for (auto& e : embers)
        Respawn(e);
}

void EmbersLoop()
{
    Update();
    Render();
}

const Effect embersEffect =
{
    "Embers",
    EmbersBegin,
    EmbersLoop
};