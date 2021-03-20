#pragma once

#include "Button.h"

namespace cinna
{
	struct ControllerState final
	{
		Button down {};
		Button left {};
		Button right {};
		Button up {};

		Button a {};
		Button b {};
		Button l {};
		Button r {};
		Button select {};
		Button start {};
		Button x {};
		Button y {};
	};
}
