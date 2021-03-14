#pragma once

#include "PCH.h"

#include "EngineConfiguration.h"
#include "GraphicsConfiguration.h"

namespace cinna
{
	struct ConfigurationContext final
	{
		EngineConfiguration engine_configuration {};
		GraphicsConfiguration graphics_configuration {};

		string configuration_filename {};
	};
}
