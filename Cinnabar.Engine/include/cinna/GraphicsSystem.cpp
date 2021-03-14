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

		al_set_new_window_title(GraphicsConstants::DEFAULT_DISPLAY_WINDOW_TITLE.c_str());
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		graphics_context.display = al_create_display(1920, 1080);
		if (graphics_context.display == nullptr)
		{
			graphics_context.display = al_create_display(GraphicsConstants::DEFAULT_DISPLAY_RESOLUTION_WIDTH, GraphicsConstants::DEFAULT_DISPLAY_RESOLUTION_HEIGHT);
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

		graphics_context.display_clear_color = al_map_rgb_f(
			GraphicsConstants::DEFAULT_DISPLAY_CLEAR_COLOR_R,
			GraphicsConstants::DEFAULT_DISPLAY_CLEAR_COLOR_G,
			GraphicsConstants::DEFAULT_DISPLAY_CLEAR_COLOR_B);
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

	void GraphicsSystem::draw_frame()
	{
		auto& graphics_context = ecs_agent->get_component<GraphicsContext>();

		al_set_target_bitmap(graphics_context.display_buffer);
		al_clear_to_color(graphics_context.display_clear_color);

		al_set_target_backbuffer(graphics_context.display);
		al_draw_scaled_bitmap(
			graphics_context.display_buffer,
			0,
			0,
			al_get_bitmap_width(graphics_context.display_buffer),
			al_get_bitmap_height(graphics_context.display_buffer),
			0,
			0,
			al_get_display_width(graphics_context.display),
			al_get_display_height(graphics_context.display),
			0);
		al_flip_display();
	}
}
