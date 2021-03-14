#pragma once

#include "PCH.h"

#include "GraphicsSystem.h"

namespace cinna
{
	struct EngineContext
	{
		shared_ptr<GraphicsSystem> graphics_system { nullptr };

		ALLEGRO_EVENT_QUEUE* event_queue { nullptr };
		bool redraw_frame { false };
		bool running { false };
		ALLEGRO_TIMER* timer { nullptr };
	};
}
