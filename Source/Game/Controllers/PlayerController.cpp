#include "GamePCH.h"
#include "PlayerController.h"

#include "Events/InputEvent.h"

PlayerController::PlayerController()
	: myIsUp(false)
	, myIsDown(false)
	, myIsLeft(false)
	, myIsRight(false)
	, myIsInputReleased(false)
{}

void PlayerController::OnEvent(Event* pEvent)
{
	if (pEvent->GetEventType() == EventTypes::EventType_Input)
	{
		const InputEvent* pInput = dynamic_cast<InputEvent*>(pEvent);
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
