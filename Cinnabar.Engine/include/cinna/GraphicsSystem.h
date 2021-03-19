#pragma once

#include "PCH.h"

#include "EcsSystem.h"

namespace cinna
{
	class GraphicsSystem final : public EcsSystem
	{
	public:
		void display_setup();
		void display_shutdown();
		void draw_frame();

	private:
		void draw_debug_text();
	};
}
