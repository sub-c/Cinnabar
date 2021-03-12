#pragma once

#include "PCH.h"

#include "EcsAgent.h"
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
		void ensure_allegro_system_success(bool system_result, string_view const system_name);
		void register_engine_components();
		void register_engine_systems();
		void setup_allegro();
		void shutdown_allegro();

		shared_ptr<GraphicsSystem> graphics_system_ { nullptr };
	};
}
