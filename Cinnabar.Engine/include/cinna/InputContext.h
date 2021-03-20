#pragma once

#include "PCH.h"

#include "ControllerState.h"

namespace cinna
{
	struct InputContext final
	{
		ControllerState controller_state {};
		ALLEGRO_JOYSTICK* current_joystick { nullptr };
	};
}
