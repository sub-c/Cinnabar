#include "PCH.h"

#include "cinna/EngineConfiguration.h"
#include "GameApp.h"

int main(int argc, char* argv[])
{
	try
	{
		cinna::EngineConfiguration engine_config;
		engine_config.configuration_path_app_name = "AppName";
		engine_config.configuration_path_filename = "App.cfg";
		engine_config.debug_enabled = true;
		engine_config.display_default_resolution_height = 1080;
		engine_config.display_default_resolution_width = 1920;
		engine_config.display_window_title = "Game App";
		engine_config.updates_per_second = 60;

		auto game_app = make_unique<GameApp>();
		game_app->run(engine_config);
	}
	catch (exception ex)
	{
		al_show_native_message_box(
			nullptr,
			"App",
			"An exception occurred:",
			ex.what(),
			nullptr,
			0);
	}

	return 0;
}