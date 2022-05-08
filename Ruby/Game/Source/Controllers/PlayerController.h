#pragma once

class Event;

class PlayerController
{
public:
    void OnEvent(Event* pEvent);

	void ClearInput() { m_Up = false; m_Down = false; m_Left = false; m_Right = false; }

    [[nodiscard]] bool IsForwardHeld() const { return m_Up; }
    [[nodiscard]] bool IsReverseHeld() const { return m_Down; }
    [[nodiscard]] bool IsTurnLeftHeld() const { return m_Left; }
    [[nodiscard]] bool IsTurnRightHeld() const { return m_Right; }
    [[nodiscard]] bool IsInputReleased() const { return m_InputReleased; }

protected:
    bool m_Up;
    bool m_Down;
    bool m_Left;
    bool m_Right;
	bool m_InputReleased;
};