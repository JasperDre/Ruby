#include "GamePCH.h"
#include "PlayerController.h"

#include "Events/InputEvent.h"

PlayerController::PlayerController()
	: m_Up(false)
	, m_Down(false)
	, m_Left(false)
	, m_Right(false)
	, m_InputReleased(false)
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
				m_Up = false;
			}

			if (pInput->myKey == Keys::S)
			{
				ClearInput();
				m_Down = false;
			}

			if (pInput->myKey == Keys::A)
			{
				ClearInput();
				m_Left = false;
			}

			if (pInput->myKey == Keys::D)
			{
				ClearInput();
				m_Right = false;
			}
			
			if (m_Up == false && m_Down == false && m_Left == false && m_Right == false)
				m_InputReleased = true;
		}
		else
		{
			if (pInput->myKey == Keys::W)
			{
				ClearInput();
				m_Up = true;
			}

			if (pInput->myKey == Keys::S)
			{
				ClearInput();
				m_Down = true;
			}

			if (pInput->myKey == Keys::A)
			{
				ClearInput();
				m_Left = true;
			}

			if (pInput->myKey == Keys::D)
			{
				ClearInput();
				m_Right = true;
			}

			m_InputReleased = false;
		}
	}
}
