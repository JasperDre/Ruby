#include "GamePCH.h"
#include "PlayerController.h"

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
#if WIN32
		const InputEvent* pInput = dynamic_cast<InputEvent*>(pEvent);

		if (pInput->GetInputDeviceType() == InputDeviceTypes::InputDeviceType_Keyboard)
		{
			const int keyID = pInput->GetID();

			if (pInput->GetInputState() == InputStates::InputState_Pressed)
			{
				m_InputReleased = false;

				if (keyID == VK_UP || keyID == 'W') { ClearInput(); m_Up = true; }
				if (keyID == VK_DOWN || keyID == 'S') { ClearInput(); m_Down = true; }
				if (keyID == VK_LEFT || keyID == 'A') { ClearInput(); m_Left = true; }
				if (keyID == VK_RIGHT || keyID == 'D') { ClearInput(); m_Right = true; }
			}

			if (pInput->GetInputState() == InputStates::InputState_Released)
			{
				if (keyID == VK_UP || keyID == 'W') { m_Up = false; }
				if (keyID == VK_DOWN || keyID == 'S') { m_Down = false; }
				if (keyID == VK_LEFT || keyID == 'A') { m_Left = false; }
				if (keyID == VK_RIGHT || keyID == 'D') { m_Right = false; }

				if (m_Up == false && m_Down == false && m_Left == false && m_Right == false)
					m_InputReleased = true;
			}
		}
#endif
	}
}
