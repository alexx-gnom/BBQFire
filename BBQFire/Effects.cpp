#include "Effects.h"

const Effect* effects[] =
{
    &embersEffect,
    &coalBedEffect,
    &forgeEffect,
    &fireplaceEffect,
    &plasmaEffect
};

const uint8_t effectCount =
    sizeof(effects) / sizeof(effects[0]);