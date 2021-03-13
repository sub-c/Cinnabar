#include "PCH.h"

#include "CinnabarException.h"
#include "EcsAgent.h"
#include "GraphicsConstants.h"
#include "GraphicsContext.h"
#include "GraphicsSystem.h"

namespace cinna
{
	void GraphicsSystem::display_setup()
	{
		auto& graphics_context = ecs_agent->get_component<GraphicsContext>();

		if (graphics_context.display != nullptr || graphics_context.display_buffer != nullptr)
		{
			throw CinnabarException("Attempting to create a display while one is already active.");
		}

		al_set_new_window_title(GraphicsConstants::WINDOWS_TITLE.c_str());
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		graphics_context.display = al_create_display(1920, 1080);
		if (graphics_context.display == nullptr)
		{
			graphics_context.display = al_create_display(GraphicsConstants::DISPLAY_RESOLUTION_WIDTH, GraphicsConstants::DISPLAY_RESOLUTION_HEIGHT);
			if (graphics_context.display == nullptr)
			{
				stringstream ss;
				ss << "Could not create a display sized " << 1920 << "x" << 1080 << ".";
				throw CinnabarException(ss);
			}
		}

		al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP | ALLEGRO_NO_PRESERVE_TEXTURE);
		graphics_context.display_buffer = al_create_bitmap(1920, 1080);
		if (graphics_context.display_buffer == nullptr)
		{
			throw CinnabarException("Could not create display buffer.");
		}
		al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);
	}

	void GraphicsSystem::display_shutdown()
	{
		auto& graphics_context = ecs_agent->get_component<GraphicsContext>();

		if (graphics_context.display == nullptr || graphics_context.display_buffer == nullptr)
		{
			throw CinnabarException("Attempting to destroy a display while none is active.");
		}

		al_destroy_bitmap(graphics_context.display_buffer);
		graphics_context.display_buffer = nullptr;

		al_destroy_display(graphics_context.display);
		graphics_context.display = nullptr;
	}
}
