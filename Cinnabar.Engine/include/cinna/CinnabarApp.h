#pragma once

#include "PCH.h"

#include "EcsAgent.h"
#include "EngineContext.h"
#include "GraphicsSystem.h"

namespace cinna
{
	class CinnabarApp
	{
	public:
		CinnabarApp();
		virtual ~CinnabarApp();

		void run();

	protected:
		virtual void register_components() = 0;
		virtual void register_systems() = 0;
		virtual void update() = 0;

		shared_ptr<EcsAgent> ecs_agent_ { nullptr };

	private:
		void allegro_ensure_success(bool system_result, string_view const system_name);
		void allegro_setup();
		void allegro_shutdown();
		void engine_initialize();
		void engine_run();
		void engine_shutdown();
		void handle_event(ALLEGRO_EVENT const& event, EngineContext& engine_context);
		void register_engine_components();
		void register_engine_systems();
	};
}
