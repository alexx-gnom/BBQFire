#include <FastLED.h>

#include "Config.h"
#include "Globals.h"
#include "EffectManager.h"
#include "Effects.h"
#include "Button.h"

Button button(BUTTON_PIN);

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    button.Begin();

    EmbersBegin();
}

void loop()
{

    ButtonEvent e = button.Update();

    switch (e)
    {
    case ButtonEvent::Click:
        NextEffect();
        break;

    case ButtonEvent::DoubleClick:
        // поки нічого
        break;

    case ButtonEvent::LongPress:
        // теж поки нічого
        break;

    default:
        break;
    }
    
    UpdateEffect();

    FastLED.show();
}