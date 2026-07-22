#include "EffectManager.h"
#include "Effects.h"

static const Effect* effects[] =
{
    &embersEffect
};

static uint8_t currentEffect = 0;

void NextEffect()
{
    currentEffect++;

    if(currentEffect >= sizeof(effects)/sizeof(effects[0]))
        currentEffect = 0;

    effects[currentEffect]->begin();
}

void UpdateEffect()
{
    effects[currentEffect]->loop();
}

const char* CurrentEffectName()
{
    return effects[currentEffect]->name;
}