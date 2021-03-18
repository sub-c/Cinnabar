#pragma once

#include "PCH.h"

#include "AudioConfiguration.h"
#include "EngineConfiguration.h"
#include "GraphicsConfiguration.h"

namespace cinna
{
	struct ConfigurationContext final
	{
		AudioConfiguration audio_configuration {};
		EngineConfiguration engine_configuration {};
		GraphicsConfiguration graphics_configuration {};

		string configuration_filename {};
	};
}
