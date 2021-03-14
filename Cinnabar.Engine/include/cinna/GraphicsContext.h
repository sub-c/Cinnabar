#pragma once

#include "PCH.h"

namespace cinna
{
	struct GraphicsContext final
	{
		ALLEGRO_DISPLAY* display { nullptr };
		ALLEGRO_BITMAP* display_buffer { nullptr };
		ALLEGRO_COLOR display_clear_color {};
	};
}
