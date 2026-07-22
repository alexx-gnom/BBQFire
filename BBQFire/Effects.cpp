#include "Effects.h"

const Effect* effects[] =
{
    &embersEffect,
    &coalBedEffect,
    &forgeEffect
};

const uint8_t effectCount =
    sizeof(effects) / sizeof(effects[0]);