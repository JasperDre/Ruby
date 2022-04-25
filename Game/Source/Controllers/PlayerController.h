#ifndef __PlayerController_H__
#define __PlayerController_H__

class Event;

class PlayerController
{
protected:
    bool m_Up;
    bool m_Down;
    bool m_Left;
    bool m_Right;
	bool m_InputReleased;

public:
    void OnEvent(Event* pEvent);

	void ClearInput() { m_Up = false; m_Down = false; m_Left = false; m_Right = false; }

    bool IsForwardHeld() { return m_Up; }
    bool IsReverseHeld() { return m_Down; }
    bool IsTurnLeftHeld() { return m_Left; }
    bool IsTurnRightHeld() { return m_Right; }

	bool IsInputReleased() { return m_InputReleased; }
};


#endif //__PlayerController_H__
