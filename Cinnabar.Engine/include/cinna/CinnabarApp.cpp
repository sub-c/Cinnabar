#include "PCH.h"

#include "AudioContext.h"
#include "AudioSystem.h"
#include "CinnabarApp.h"
#include "CinnabarException.h"
#include "ConfigurationContext.h"
#include "ConfigurationSystem.h"
#include "EngineConfiguration.h"
#include "EngineConstants.h"
#include "EngineContext.h"
#include "GraphicsContext.h"
#include "InputContext.h"

namespace cinna
{
	CinnabarApp::CinnabarApp()
	{
		ecs_agent_ = make_shared<EcsAgent>();

	}

	CinnabarApp::~CinnabarApp()
	{
	}

	void CinnabarApp::run(EngineConfiguration& engine_config)
	{
		try
		{
			allegro_setup();
			register_engine_components();
			register_engine_systems();
			register_components();
			register_systems();

			engine_setup(engine_config);
			engine_run();

			engine_shutdown();
			allegro_shutdown();
		}
		catch (CinnabarException ex)
		{
			ALLEGRO_DISPLAY* display = nullptr;
			if (ecs_agent_->is_component_registered<GraphicsContext>())
			{
				display = ecs_agent_->get_component<GraphicsContext>().display;
			}
			al_show_native_message_box(
				display,
				"Cinnabar Engine",
				"An exception occurred:",
				ex.what(),
				nullptr,
				ALLEGRO_MESSAGEBOX_ERROR);
		}
		
	}

	// Private functions //////////////////////////////////////////////////////////////////////////

	void CinnabarApp::allegro_ensure_success(bool system_result, string_view const system_name)
	{
		if (!system_result)
		{
			stringstream ss;
			ss << "Could not initialize Allegro system: " << system_name;
			throw CinnabarException(ss);
		}
	}

	void CinnabarApp::allegro_setup()
	{
		allegro_ensure_success(al_init(), "Core");
		allegro_ensure_success(al_install_keyboard(), "Keyboard");
		allegro_ensure_success(al_install_mouse(), "Mouse");
		allegro_ensure_success(al_install_joystick(), "Joystick");
		allegro_ensure_success(al_init_image_addon(), "Image");
		allegro_ensure_success(al_init_native_dialog_addon(), "Native dialog");
	}

	void CinnabarApp::allegro_shutdown()
	{
		al_shutdown_native_dialog_addon();
		al_shutdown_image_addon();
		al_uninstall_joystick();
		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_uninstall_system();
	}

	void CinnabarApp::engine_run()
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();

		ALLEGRO_EVENT event;
		engine_context.running = true;
		al_flush_event_queue(engine_context.event_queue);
		while (engine_context.running)
		{
			al_wait_for_event(engine_context.event_queue, &event);
			handle_event(event, engine_context);

			if (engine_context.redraw_frame && al_is_event_queue_empty(engine_context.event_queue))
			{
				engine_context.graphics_system->draw_frame();
				engine_context.redraw_frame = false;
			}
		}
	}

	void CinnabarApp::engine_setup(EngineConfiguration& engine_config)
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();
		auto& graphics_context = ecs_agent_->get_component<GraphicsContext>();

		engine_context.configuration_system->apply_engine_configuration(engine_config);
		engine_context.configuration_system->configuration_load();

		engine_context.event_queue = al_create_event_queue();

		al_register_event_source(engine_context.event_queue, al_get_keyboard_event_source());
		al_register_event_source(engine_context.event_queue, al_get_mouse_event_source());
		al_register_event_source(engine_context.event_queue, al_get_joystick_event_source());

		engine_context.timer = al_create_timer(ALLEGRO_BPS_TO_SECS(engine_config.updates_per_second));
		al_register_event_source(engine_context.event_queue, al_get_timer_event_source(engine_context.timer));
		al_start_timer(engine_context.timer);

		engine_context.graphics_system->display_setup();
		al_register_event_source(engine_context.event_queue, al_get_display_event_source(graphics_context.display));
	}

	void CinnabarApp::engine_shutdown()
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();
		auto& graphics_context = ecs_agent_->get_component<GraphicsContext>();

		engine_context.configuration_system->configuration_save();

		al_unregister_event_source(engine_context.event_queue, al_get_display_event_source(graphics_context.display));
		engine_context.graphics_system->display_shutdown();

		al_stop_timer(engine_context.timer);
		al_unregister_event_source(engine_context.event_queue, al_get_timer_event_source(engine_context.timer));
		al_destroy_timer(engine_context.timer);

		al_unregister_event_source(engine_context.event_queue, al_get_joystick_event_source());
		al_unregister_event_source(engine_context.event_queue, al_get_mouse_event_source());
		al_unregister_event_source(engine_context.event_queue, al_get_keyboard_event_source());

		al_destroy_event_queue(engine_context.event_queue);
	}

	void CinnabarApp::handle_shutdown_event(ALLEGRO_EVENT const& event, EngineContext& engine_context)
	{
		if (can_shutdown())
		{
			engine_context.running = false;
		}
	}

	void CinnabarApp::handle_event(ALLEGRO_EVENT const& event, EngineContext& engine_context)
	{
		switch (event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				handle_shutdown_event(event, engine_context);
				break;

			case ALLEGRO_EVENT_TIMER:
				handle_timer_event(event, engine_context);
				break;

			default:
				break;
		}
	}

	void CinnabarApp::handle_timer_event(ALLEGRO_EVENT const& event, EngineContext& engine_context)
	{
		update();
		engine_context.redraw_frame = true;
	}

	void CinnabarApp::register_engine_components()
	{
		ecs_agent_->register_component<AudioContext>();
		ecs_agent_->register_component<ConfigurationContext>();
		ecs_agent_->register_component<EngineContext>();
		ecs_agent_->register_component<GraphicsContext>();
		ecs_agent_->register_component<InputContext>();

		AudioContext audio_context;
		ecs_agent_->add_component(audio_context);

		ConfigurationContext configuration_context;
		ecs_agent_->add_component(configuration_context);

		EngineContext engine_context;
		ecs_agent_->add_component(engine_context);

		GraphicsContext graphics_context;
		ecs_agent_->add_component(graphics_context);

		InputContext input_context;
		ecs_agent_->add_component(input_context);
	}

	void CinnabarApp::register_engine_systems()
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();

		engine_context.audio_system = ecs_agent_->register_system<AudioSystem>();
		{
			EcsSignature signature;
			ecs_agent_->set_system_signature<AudioSystem>(signature);
		}

		engine_context.configuration_system = ecs_agent_->register_system<ConfigurationSystem>();
		{
			EcsSignature signature;
			ecs_agent_->set_system_signature<ConfigurationSystem>(signature);
		}

		engine_context.graphics_system = ecs_agent_->register_system<GraphicsSystem>();
		{
			EcsSignature signature;
			ecs_agent_->set_system_signature<GraphicsSystem>(signature);
		}
	}
}
