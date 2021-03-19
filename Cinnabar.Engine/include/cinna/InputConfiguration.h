#pragma once

#include "InputConstants.h"

namespace cinna
{
	struct InputConfiguration final
	{
		int KeyCodeDown { InputConstants::DEFAULT_KEYCODE_DOWN };
		int KeyCodeLeft { InputConstants::DEFAULT_KEYCODE_LEFT };
		int KeyCodeRight { InputConstants::DEFAULT_KEYCODE_RIGHT };
		int KeyCodeUp { InputConstants::DEFAULT_KEYCODE_UP };

		int KeyCodeA { InputConstants::DEFAULT_KEYCODE_A };
		int KeyCodeB { InputConstants::DEFAULT_KEYCODE_B };
		int KeyCodeL { InputConstants::DEFAULT_KEYCODE_L };
		int KeyCodeR { InputConstants::DEFAULT_KEYCODE_R };
		int KeyCodeSelect { InputConstants::DEFAULT_KEYCODE_SELECT };
		int KeyCodeStart { InputConstants::DEFAULT_KEYCODE_START };
		int KeyCodeX { InputConstants::DEFAULT_KEYCODE_X };
		int KeyCodeY { InputConstants::DEFAULT_KEYCODE_Y };
	};
}
