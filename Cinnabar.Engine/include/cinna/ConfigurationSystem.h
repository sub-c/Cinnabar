#pragma once

#include "PCH.h"

#include "EcsSystem.h"
#include "EngineConfiguration.h"
#include "GraphicsConfiguration.h"

namespace cinna
{
	class ConfigurationSystem final : public EcsSystem
	{
	public:
		void apply_engine_configuration(EngineConfiguration& engine_config);
		void configuration_load();
		void configuration_save();

	private:
		void populate_graphics_configuration(ALLEGRO_CONFIG* config, GraphicsConfiguration& graphics_config);
	};
}
