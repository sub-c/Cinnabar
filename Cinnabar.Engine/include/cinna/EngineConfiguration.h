#pragma once

#include "PCH.h"

#include "EngineConstants.h"
#include "GraphicsConstants.h"

namespace cinna
{
	struct EngineConfiguration
	{
		string configuration_path_app_name {};
		string configuration_path_filename { EngineConstants::DEFAULT_CONFIGURATION_FILENAME };
		string configuration_path_org_name {};

		bool debug_enabled { true };

		int display_buffer_height { GraphicsConstants::DEFAULT_DISPLAY_BUFFER_RESOLUTION_HEIGHT };
		int display_buffer_width { GraphicsConstants::DEFAULT_DISPLAY_BUFFER_RESOLUTION_WIDTH };
		int display_default_resolution_height { GraphicsConstants::DEFAULT_DISPLAY_RESOLUTION_HEIGHT };
		int display_default_resolution_width { GraphicsConstants::DEFAULT_DISPLAY_RESOLUTION_WIDTH };
		string display_window_title { GraphicsConstants::DEFAULT_DISPLAY_WINDOW_TITLE };

		int updates_per_second { EngineConstants::DEFAULT_UPDATES_PER_SECOND };
	};
}
