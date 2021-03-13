#pragma once

#include "PCH.h"

#include "GraphicsSystem.h"

namespace cinna
{
	struct EngineContext
	{
		shared_ptr<GraphicsSystem> graphics_system { nullptr };

		bool running { false };
		ALLEGRO_EVENT_QUEUE* event_queue { nullptr };
		ALLEGRO_TIMER* timer { nullptr };
	};
}
