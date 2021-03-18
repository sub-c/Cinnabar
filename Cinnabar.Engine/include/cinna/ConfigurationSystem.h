#pragma once

#include "PCH.h"

#include "AudioConfiguration.h"
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
		template <typename T>
		T get_config_value(ALLEGRO_CONFIG const* config, char const* section, char const* key)
		{
			stringstream ss;
			ss << al_get_config_value(config, section, key);
			T value;
			ss >> value;
			return value;
		}

		template <typename T>
		void set_config_value(ALLEGRO_CONFIG* config, char const* section, char const* key, T value)
		{
			stringstream ss;
			ss << value;
			al_set_config_value(config, section, key, ss.str().c_str());
		}

		void configuration_load_audio(ALLEGRO_CONFIG* config, AudioConfiguration& audio_config);
		void configuration_load_graphics(ALLEGRO_CONFIG* config, GraphicsConfiguration& graphics_config);
		void configuration_save_audio(ALLEGRO_CONFIG* config, AudioConfiguration& audio_config);
		void configuration_save_graphics(ALLEGRO_CONFIG* config, GraphicsConfiguration& graphics_config);
	};
}
