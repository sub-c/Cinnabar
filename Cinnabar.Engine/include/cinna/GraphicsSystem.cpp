#include "PCH.h"

#include "CinnabarException.h"
#include "ConfigurationContext.h"
#include "DebugContext.h"
#include "EcsAgent.h"
#include "GraphicsConstants.h"
#include "GraphicsContext.h"
#include "GraphicsSystem.h"

namespace cinna
{
	void GraphicsSystem::display_setup()
	{
		auto& graphics_config = ecs_agent->get_component<ConfigurationContext>().graphics_configuration;
		auto& graphics_context = ecs_agent->get_component<GraphicsContext>();

		if (graphics_context.display != nullptr || graphics_context.display_buffer != nullptr)
		{
			throw CinnabarException("Attempting to create a display while one is already active.");
		}

		al_set_new_window_title(graphics_config.display_window_title.c_str());
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		graphics_context.display = al_create_display(graphics_config.display_resolution_width, graphics_config.display_resolution_height);
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
		graphics_context.display_buffer = al_create_bitmap(graphics_config.display_buffer_resolution_width, graphics_config.display_buffer_resolution_height);
		if (graphics_context.display_buffer == nullptr)
		{
			throw CinnabarException("Could not create display buffer.");
		}

		// debug
		auto& debug_context = ecs_agent->get_component<DebugContext>();
		if (debug_context.enabled)
		{
			debug_context.font = al_create_builtin_font();
		}

		al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);

		graphics_context.display_clear_color = al_map_rgb_f(
			graphics_config.display_clear_color_r,
			graphics_config.display_clear_color_g,
			graphics_config.display_clear_color_b);
	}

	void GraphicsSystem::display_shutdown()
	{
		auto& graphics_context = ecs_agent->get_component<GraphicsContext>();

		if (graphics_context.display == nullptr || graphics_context.display_buffer == nullptr)
		{
			throw CinnabarException("Attempting to destroy a display while none is active.");
		}

		// debug
		auto& debug_context = ecs_agent->get_component<DebugContext>();
		if (debug_context.enabled)
		{
			al_destroy_font(debug_context.font);
			debug_context.font = nullptr;
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
		draw_debug_text();
		al_flip_display();
	}

	// Private functions /////////////////////////////////////////////////////////////////////////////

	void GraphicsSystem::draw_debug_text()
	{
		auto& debug_context = ecs_agent->get_component<DebugContext>();
		if (debug_context.enabled)
		{
			float y_position = 0.0f;
			for (auto line = debug_context.text_lines->begin(); line != debug_context.text_lines->end(); ++line)
			{
				al_draw_text(
					debug_context.font,
					al_map_rgb_f(1.0f, 1.0f, 1.0f),
					0.0f,
					y_position,
					0,
					line->c_str());
				y_position += 8.0f;
			}
			if (y_position > 0.0f)
			{
				debug_context.text_lines->clear();
			}
		}
	}
}
