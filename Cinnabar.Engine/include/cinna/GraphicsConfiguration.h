#pragma once

#include "PCH.h"

#include "GraphicsConstants.h"

namespace cinna
{
	struct GraphicsConfiguration final
	{
		int display_buffer_resolution_height { GraphicsConstants::DEFAULT_DISPLAY_BUFFER_RESOLUTION_HEIGHT };
		int display_buffer_resolution_width { GraphicsConstants::DEFAULT_DISPLAY_BUFFER_RESOLUTION_WIDTH };
		float display_clear_color_b { GraphicsConstants::DEFAULT_DISPLAY_CLEAR_COLOR_B };
		float display_clear_color_g { GraphicsConstants::DEFAULT_DISPLAY_CLEAR_COLOR_G };
		float display_clear_color_r { GraphicsConstants::DEFAULT_DISPLAY_CLEAR_COLOR_R };
		bool display_fullscreen { GraphicsConstants::DEFAULT_DISPLAY_FULLSCREEN };
		int display_resolution_height { GraphicsConstants::DEFAULT_DISPLAY_RESOLUTION_HEIGHT };
		int display_resolution_width { GraphicsConstants::DEFAULT_DISPLAY_RESOLUTION_WIDTH };
		bool display_vsync { GraphicsConstants::DEFAULT_DISPLAY_VSYNC };
		string display_window_title { GraphicsConstants::DEFAULT_DISPLAY_WINDOW_TITLE };
	};
}
