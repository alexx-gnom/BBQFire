#pragma once

#include <Arduino.h>

enum class ButtonEvent
{
    None,
    Click,
    DoubleClick,
    LongPress
};

class Button
{
public:
    explicit Button(uint8_t pin);

    void Begin();
    ButtonEvent Update();

private:
    uint8_t _pin;

    bool _lastReading = HIGH;
    bool _stableState = HIGH;

    uint32_t _lastDebounceTime = 0;
    uint32_t _pressTime = 0;
    uint32_t _lastClickTime = 0;

    bool _waitingSecondClick = false;
    bool _longPressSent = false;

    static constexpr uint16_t DebounceTime = 30;
    static constexpr uint16_t LongPressTime = 700;
    static constexpr uint16_t DoubleClickTime = 300;
};