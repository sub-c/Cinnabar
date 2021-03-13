#pragma once

#include "PCH.h"

namespace cinna
{
	struct GraphicsContext
	{
		ALLEGRO_DISPLAY* display { nullptr };
		ALLEGRO_BITMAP* display_buffer { nullptr };
	};
}
