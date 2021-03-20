#pragma once

#include "InputConstants.h"

namespace cinna
{
	struct InputConfiguration final
	{
		int joy_code_down { InputConstants::DEFAULT_JOYCODE_DOWN };
		int joy_code_left { InputConstants::DEFAULT_JOYCODE_LEFT };
		int joy_code_right { InputConstants::DEFAULT_JOYCODE_RIGHT };
		int joy_code_up { InputConstants::DEFAULT_JOYCODE_UP };

		int joy_code_a { InputConstants::DEFAULT_JOYCODE_A };
		int joy_code_b { InputConstants::DEFAULT_JOYCODE_B };
		int joy_code_l { InputConstants::DEFAULT_JOYCODE_L };
		int joy_code_r { InputConstants::DEFAULT_JOYCODE_R };
		int joy_code_select { InputConstants::DEFAULT_JOYCODE_SELECT };
		int joy_code_start { InputConstants::DEFAULT_JOYCODE_START };
		int joy_code_x { InputConstants::DEFAULT_JOYCODE_X };
		int joy_code_y { InputConstants::DEFAULT_JOYCODE_Y };

		int key_code_down { InputConstants::DEFAULT_KEYCODE_DOWN };
		int key_code_left { InputConstants::DEFAULT_KEYCODE_LEFT };
		int key_code_right { InputConstants::DEFAULT_KEYCODE_RIGHT };
		int key_code_up { InputConstants::DEFAULT_KEYCODE_UP };

		int key_code_a { InputConstants::DEFAULT_KEYCODE_A };
		int key_code_b { InputConstants::DEFAULT_KEYCODE_B };
		int key_code_l { InputConstants::DEFAULT_KEYCODE_L };
		int key_code_r { InputConstants::DEFAULT_KEYCODE_R };
		int key_code_select { InputConstants::DEFAULT_KEYCODE_SELECT };
		int key_code_start { InputConstants::DEFAULT_KEYCODE_START };
		int key_code_x { InputConstants::DEFAULT_KEYCODE_X };
		int key_code_y { InputConstants::DEFAULT_KEYCODE_Y };
	};
}
