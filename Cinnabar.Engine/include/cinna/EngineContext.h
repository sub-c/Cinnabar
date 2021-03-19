#pragma once

#include "PCH.h"

#include "AudioSystem.h"
#include "ConfigurationSystem.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"

namespace cinna
{
	struct EngineContext final
	{
		shared_ptr<AudioSystem> audio_system { nullptr };
		shared_ptr<ConfigurationSystem> configuration_system { nullptr };
		shared_ptr<GraphicsSystem> graphics_system { nullptr };
		shared_ptr<InputSystem> input_system { nullptr };

		ALLEGRO_EVENT_QUEUE* event_queue { nullptr };
		bool redraw_frame { false };
		bool running { false };
		ALLEGRO_TIMER* timer { nullptr };
	};
}
