#include "PlayerController.h"

#include "Events/InputEvent.h"
#include "Input/InputManager.h"

PlayerController::PlayerController()
	: myIsUp(false)
	, myIsDown(false)
	, myIsLeft(false)
	, myIsRight(false)
	, myIsInputReleased(false)
{}

void PlayerController::OnEvent(Event* anEvent)
{
	if (anEvent->GetEventType() == EventTypes::EventType_Input)
	{
		const InputEvent* pInput = dynamic_cast<InputEvent*>(anEvent);
		if (pInput->myIsReleased)
		{
			if (pInput->myKey == Keys::W)
			{
				ClearInput();
				myIsUp = false;
			}

			if (pInput->myKey == Keys::S)
			{
				ClearInput();
				myIsDown = false;
			}

			if (pInput->myKey == Keys::A)
			{
				ClearInput();
				myIsLeft = false;
			}

			if (pInput->myKey == Keys::D)
			{
				ClearInput();
				myIsRight = false;
			}
			
			if (myIsUp == false && myIsDown == false && myIsLeft == false && myIsRight == false)
				myIsInputReleased = true;
		}
		else
		{
			if (pInput->myKey == Keys::W)
			{
				ClearInput();
				myIsUp = true;
			}

			if (pInput->myKey == Keys::S)
			{
				ClearInput();
				myIsDown = true;
			}

			if (pInput->myKey == Keys::A)
			{
				ClearInput();
				myIsLeft = true;
			}

			if (pInput->myKey == Keys::D)
			{
				ClearInput();
				myIsRight = true;
			}

			myIsInputReleased = false;
		}
	}
}
