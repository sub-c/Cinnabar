#include "PCH.h"

#include "CinnabarApp.h"
#include "CinnabarException.h"
#include "GraphicsContext.h"

namespace cinna
{
	CinnabarApp::CinnabarApp()
	{

	}

	CinnabarApp::~CinnabarApp()
	{

	}

	void CinnabarApp::run()
	{
		allegro_setup();
		engine_initialize();
		register_engine_components();
		register_engine_systems();

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
		ecs_agent_ = make_shared<EcsAgent>();
	}

	void CinnabarApp::engine_run()
	{
		al_rest(3);
	}

	void CinnabarApp::engine_shutdown()
	{
	}

	void CinnabarApp::register_engine_components()
	{
		ecs_agent_->register_component<GraphicsContext>();

		GraphicsContext graphics_context;
		ecs_agent_->add_component(graphics_context);
	}

	void CinnabarApp::register_engine_systems()
	{
		graphics_system_ = ecs_agent_->register_system<GraphicsSystem>();
		{
			EcsSignature signature;
			ecs_agent_->set_system_signature<GraphicsSystem>(signature);
		}
	}
}
