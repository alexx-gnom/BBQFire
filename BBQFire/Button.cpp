#include "Button.h"

Button::Button(uint8_t pin)
    : _pin(pin)
{
}

void Button::Begin()
{
    pinMode(_pin, INPUT_PULLUP);
}

ButtonEvent Button::Update()
{
    ButtonEvent event = ButtonEvent::None;

    bool reading = digitalRead(_pin);
    uint32_t now = millis();

    if (reading != _lastReading)
    {
        _lastDebounceTime = now;
        _lastReading = reading;
    }

    if ((now - _lastDebounceTime) > DebounceTime)
    {
        if (reading != _stableState)
        {
            _stableState = reading;

            if (_stableState == LOW)
            {
                _pressTime = now;
                _longPressSent = false;
            }
            else
            {
                if (!_longPressSent)
                {
                    if (_waitingSecondClick &&
                        (now - _lastClickTime) < DoubleClickTime)
                    {
                        _waitingSecondClick = false;
                        event = ButtonEvent::DoubleClick;
                    }
                    else
                    {
                        _waitingSecondClick = true;
                        _lastClickTime = now;
                    }
                }
            }
        }
    }

    if (_stableState == LOW &&
        !_longPressSent &&
        (now - _pressTime) > LongPressTime)
    {
        _longPressSent = true;
        _waitingSecondClick = false;
        event = ButtonEvent::LongPress;
    }

    if (_waitingSecondClick &&
        (now - _lastClickTime) > DoubleClickTime)
    {
        _waitingSecondClick = false;
        event = ButtonEvent::Click;
    }

    return event;
}