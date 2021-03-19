#pragma once

#include "Button.h"

namespace cinna
{
	struct ControllerState final
	{
		Button Down {};
		Button Left {};
		Button Right {};
		Button Up {};

		Button A {};
		Button B {};
		Button L {};
		Button R {};
		Button Select {};
		Button Start {};
		Button X {};
		Button Y {};
	};
}
