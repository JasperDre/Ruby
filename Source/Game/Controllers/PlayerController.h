#pragma once

class Event;

class PlayerController
{
public:
	PlayerController();

    void OnEvent(Event* pEvent);

	void ClearInput() { myIsUp = false; myIsDown = false; myIsLeft = false; myIsRight = false; }

    [[nodiscard]] bool IsForwardHeld() const { return myIsUp; }
    [[nodiscard]] bool IsReverseHeld() const { return myIsDown; }
    [[nodiscard]] bool IsTurnLeftHeld() const { return myIsLeft; }
    [[nodiscard]] bool IsTurnRightHeld() const { return myIsRight; }
    [[nodiscard]] bool IsInputReleased() const { return myIsInputReleased; }

protected:
    bool myIsUp;
    bool myIsDown;
    bool myIsLeft;
    bool myIsRight;
	bool myIsInputReleased;
};