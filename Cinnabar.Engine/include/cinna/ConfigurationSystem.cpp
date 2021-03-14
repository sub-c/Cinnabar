#include "PCH.h"

#include "CinnabarException.h"
#include "ConfigurationConstants.h"
#include "ConfigurationContext.h"
#include "ConfigurationSystem.h"
#include "EcsAgent.h"
#include "GraphicsConfiguration.h"

namespace cinna
{
	void ConfigurationSystem::apply_engine_configuration(EngineConfiguration& engine_config)
	{
		auto& config_context = ecs_agent->get_component<ConfigurationContext>();
		auto& graphics_config = config_context.graphics_configuration;

		al_set_app_name(engine_config.configuration_path_app_name.c_str());
		al_set_org_name(engine_config.configuration_path_org_name.c_str());
		config_context.configuration_filename = engine_config.configuration_path_filename;

		graphics_config.display_buffer_resolution_height = engine_config.display_buffer_height;
		graphics_config.display_buffer_resolution_width = engine_config.display_buffer_width;
		graphics_config.display_resolution_height = engine_config.display_default_resolution_height;
		graphics_config.display_resolution_width = engine_config.display_default_resolution_width;
		graphics_config.display_window_title = engine_config.display_window_title;
	}

	void ConfigurationSystem::configuration_load()
	{

	}

	void ConfigurationSystem::configuration_save()
	{
		auto& config_context = ecs_agent->get_component<ConfigurationContext>();

		auto* config_path = al_get_standard_path(ALLEGRO_USER_SETTINGS_PATH);
		auto const* config_path_cstr = al_path_cstr(config_path, ALLEGRO_NATIVE_PATH_SEP);
		if (!al_filename_exists(config_path_cstr) && !al_make_directory(config_path_cstr))
		{
			stringstream ss;
			ss << "Could not create configuration directory: " << config_path_cstr;
			throw CinnabarException(ss);
		}

		ALLEGRO_CONFIG* config = al_create_config();
		populate_graphics_configuration(config, config_context.graphics_configuration);

		al_set_path_filename(config_path, config_context.configuration_filename.c_str());
		config_path_cstr = al_path_cstr(config_path, ALLEGRO_NATIVE_PATH_SEP);
		al_save_config_file(config_path_cstr, config);

		al_destroy_config(config);
		al_destroy_path(config_path);
	}

	// Private functions //////////////////////////////////////////////////////////////////////////

	void ConfigurationSystem::populate_graphics_configuration(ALLEGRO_CONFIG* config, GraphicsConfiguration& graphics_config)
	{
		stringstream ss;

		ss.str("");
		ss << graphics_config.display_fullscreen;
		al_set_config_value(
			config,
			ConfigurationConstants::DISPLAY_SECTION.c_str(),
			ConfigurationConstants::DISPLAY_FULLSCREEN.c_str(),
			ss.str().c_str());

		ss.str("");
		ss << graphics_config.display_resolution_height;
		al_set_config_value(
			config,
			ConfigurationConstants::DISPLAY_SECTION.c_str(),
			ConfigurationConstants::DISPLAY_RESOLUTION_HEIGHT.c_str(),
			ss.str().c_str());

		ss.str("");
		ss << graphics_config.display_resolution_width;
		al_set_config_value(
			config,
			ConfigurationConstants::DISPLAY_SECTION.c_str(),
			ConfigurationConstants::DISPLAY_RESOLUTION_WIDTH.c_str(),
			ss.str().c_str());

		ss.str("");
		ss << graphics_config.display_vsync;
		al_set_config_value(
			config,
			ConfigurationConstants::DISPLAY_SECTION.c_str(),
			ConfigurationConstants::DISPLAY_VSYNC.c_str(),
			ss.str().c_str());
	}
}