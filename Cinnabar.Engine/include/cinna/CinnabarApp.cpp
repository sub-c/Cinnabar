#include "PCH.h"

#include "CinnabarApp.h"
#include "CinnabarException.h"
#include "EngineConstants.h"
#include "EngineContext.h"
#include "GraphicsContext.h"

namespace cinna
{
	CinnabarApp::CinnabarApp()
	{
		ecs_agent_ = make_shared<EcsAgent>();
	}

	CinnabarApp::~CinnabarApp()
	{
	}

	void CinnabarApp::run()
	{
		allegro_setup();
		register_engine_components();
		register_engine_systems();
		register_components();
		register_systems();

		engine_initialize();
		engine_run();

		engine_shutdown();
		allegro_shutdown();
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
	}

	void CinnabarApp::allegro_shutdown()
	{
		al_uninstall_system();
	}

	void CinnabarApp::engine_initialize()
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();
		auto& graphics_context = ecs_agent_->get_component<GraphicsContext>();

		engine_context.event_queue = al_create_event_queue();

		engine_context.timer = al_create_timer(ALLEGRO_BPS_TO_SECS(EngineConstants::DefaultUpdatesPerSecond));
		al_register_event_source(engine_context.event_queue, al_get_timer_event_source(engine_context.timer));
		al_start_timer(engine_context.timer);

		engine_context.graphics_system->display_setup();
		al_register_event_source(engine_context.event_queue, al_get_display_event_source(graphics_context.display));
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
		}
	}

	void CinnabarApp::engine_shutdown()
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();
		auto& graphics_context = ecs_agent_->get_component<GraphicsContext>();

		al_unregister_event_source(engine_context.event_queue, al_get_display_event_source(graphics_context.display));
		engine_context.graphics_system->display_shutdown();

		al_stop_timer(engine_context.timer);
		al_unregister_event_source(engine_context.event_queue, al_get_timer_event_source(engine_context.timer));
		al_destroy_timer(engine_context.timer);

		al_destroy_event_queue(engine_context.event_queue);
	}

	void CinnabarApp::handle_event(ALLEGRO_EVENT const& event, EngineContext& engine_context)
	{
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			engine_context.running = false;
		}
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			auto a = 5;
		}
	}

	void CinnabarApp::register_engine_components()
	{
		ecs_agent_->register_component<EngineContext>();
		ecs_agent_->register_component<GraphicsContext>();

		EngineContext engine_context;
		ecs_agent_->add_component(engine_context);

		GraphicsContext graphics_context;
		ecs_agent_->add_component(graphics_context);
	}

	void CinnabarApp::register_engine_systems()
	{
		auto& engine_context = ecs_agent_->get_component<EngineContext>();

		engine_context.graphics_system = ecs_agent_->register_system<GraphicsSystem>();
		{
			EcsSignature signature;
			ecs_agent_->set_system_signature<GraphicsSystem>(signature);
		}
	}
}
