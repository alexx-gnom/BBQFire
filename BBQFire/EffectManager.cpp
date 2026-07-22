#include "EffectManager.h"
#include "Effects.h"

static uint8_t currentEffect = 0;

void SetEffect(uint8_t index)
{
    if (index >= effectCount)
        index = 0;

    currentEffect = index;

    Serial.println();
    Serial.println(F("=========================="));
    Serial.print(F("Effect "));
    Serial.print(currentEffect + 1);
    Serial.print(F("/"));
    Serial.print(effectCount);
    Serial.print(F(": "));
    Serial.println(effects[currentEffect]->name);
    Serial.println(F("=========================="));

    effects[currentEffect]->begin();
}

void NextEffect()
{
    SetEffect(currentEffect + 1);
}

void UpdateEffect()
{
    effects[currentEffect]->loop();
}

const char* CurrentEffectName()
{
    return effects[currentEffect]->name;
}