#pragma once

#include "Event.h"

enum class InputDeviceTypes
{
    InputDeviceType_Keyboard,
    InputDeviceType_Mouse,
    InputDeviceType_Gamepad,
    InputDeviceType_NumTypes,
};

enum class InputStates
{
    InputState_Pressed,
    InputState_Released,
    InputState_Held,
    InputState_NumStates,
};

enum class GamepadIDs
{
    GamepadID_LeftStick,
    GamepadID_RightStick,
};

class InputEvent : public Event
{
public:
    InputEvent()
        : m_ID(0)
        , m_Position(0.0f)
        , m_InputDeviceType(InputDeviceTypes::InputDeviceType_Gamepad)
        , m_InputState(InputStates::InputState_Held)
    {}

    InputEvent(InputDeviceTypes devicetype, InputStates state, int id, vec2 pos)
        : m_ID(id)
        , m_Position(pos)
        , m_InputDeviceType(devicetype)
        , m_InputState(state)
    {}

    InputEvent(InputDeviceTypes devicetype, InputStates state, GamepadIDs id, vec2 pos)
        : m_GamepadID(id)
        , m_Position(pos)
        , m_InputDeviceType(devicetype)
        , m_InputState(state)
    {}

    [[nodiscard]] EventTypes GetEventType() const override { return EventTypes::EventType_Input; }
    [[nodiscard]] InputDeviceTypes GetInputDeviceType() const { return m_InputDeviceType; }
    [[nodiscard]] InputStates GetInputState() const { return m_InputState; }
    [[nodiscard]] int GetID() const { return m_ID; }
    [[nodiscard]] GamepadIDs GetGamepadID() const { return m_GamepadID; }
    [[nodiscard]] vec2 GetPosition() const { return m_Position; }

protected:
    union
    {
        int m_ID;
        GamepadIDs m_GamepadID;
    };

    vec2 m_Position;
    InputDeviceTypes m_InputDeviceType;
    InputStates m_InputState;
};