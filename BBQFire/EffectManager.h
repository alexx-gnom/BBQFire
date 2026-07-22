#pragma once

#include <Arduino.h>

typedef void (*EffectBegin)();
typedef void (*EffectLoop)();

struct Effect
{
    const char* name;
    EffectBegin begin;
    EffectLoop loop;
};

void NextEffect();
void UpdateEffect();
const char* CurrentEffectName();