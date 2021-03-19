#include "PCH.h"

#include "ConfigurationContext.h"
#include "DebugContext.h"
#include "EcsAgent.h"
#include "InputContext.h"
#include "InputSystem.h"

namespace cinna
{
	void InputSystem::handle_end_of_frame()
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		
		controller_state.Down.just_pressed = false;
		controller_state.Left.just_pressed = false;
		controller_state.Right.just_pressed = false;
		controller_state.Up.just_pressed = false;

		controller_state.A.just_pressed = false;
		controller_state.B.just_pressed = false;
		controller_state.L.just_pressed = false;
		controller_state.R.just_pressed = false;
		controller_state.Select.just_pressed = false;
		controller_state.Start.just_pressed = false;
		controller_state.X.just_pressed = false;
		controller_state.Y.just_pressed = false;
	}

	void InputSystem::handle_keyboard_event(ALLEGRO_EVENT const& event)
	{
		auto& debug_context = ecs_agent->get_component<DebugContext>();
		debug_context.text_lines->emplace_back("KEY EVENT");

		switch (event.type)
		{
			case ALLEGRO_EVENT_KEY_DOWN:
				handle_key_down(event.keyboard.keycode);
				break;

			case ALLEGRO_EVENT_KEY_UP:
				handle_key_up(event.keyboard.keycode);
				break;
		}
	}

	void InputSystem::handle_joystick_event(ALLEGRO_EVENT const& event)
	{

	}

	void InputSystem::handle_mouse_event(ALLEGRO_EVENT const& event)
	{

	}

	// Private function ///////////////////////////////////////////////////////////////////////////

	void InputSystem::button_down(Button& button)
	{
		button.just_pressed = true;
		button.pressed = true;
	}

	void InputSystem::button_up(Button& button)
	{
		button.just_pressed = false;
		button.pressed = false;
	}

	void InputSystem::handle_key_down(int key_code)
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		auto& input_config = ecs_agent->get_component<ConfigurationContext>().input_configuration;

		if (key_code == input_config.KeyCodeDown) { button_down(controller_state.Down); }
		if (key_code == input_config.KeyCodeLeft) { button_down(controller_state.Left); }
		if (key_code == input_config.KeyCodeRight) { button_down(controller_state.Right); }
		if (key_code == input_config.KeyCodeUp) { button_down(controller_state.Up); }

		if (key_code == input_config.KeyCodeA) { button_down(controller_state.A); }
		if (key_code == input_config.KeyCodeB) { button_down(controller_state.B); }
		if (key_code == input_config.KeyCodeL) { button_down(controller_state.L); }
		if (key_code == input_config.KeyCodeR) { button_down(controller_state.R); }
		if (key_code == input_config.KeyCodeSelect) { button_down(controller_state.Select); }
		if (key_code == input_config.KeyCodeStart) { button_down(controller_state.Start); }
		if (key_code == input_config.KeyCodeX) { button_down(controller_state.X); }
		if (key_code == input_config.KeyCodeY) { button_down(controller_state.Y); }
	}

	void InputSystem::handle_key_up(int key_code)
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		auto& input_config = ecs_agent->get_component<ConfigurationContext>().input_configuration;
		
		if (key_code == input_config.KeyCodeDown) { button_up(controller_state.Down); }
		if (key_code == input_config.KeyCodeLeft) { button_up(controller_state.Left); }
		if (key_code == input_config.KeyCodeRight) { button_up(controller_state.Right); }
		if (key_code == input_config.KeyCodeUp) { button_up(controller_state.Up); }

		if (key_code == input_config.KeyCodeA) { button_up(controller_state.A); }
		if (key_code == input_config.KeyCodeB) { button_up(controller_state.B); }
		if (key_code == input_config.KeyCodeL) { button_up(controller_state.L); }
		if (key_code == input_config.KeyCodeR) { button_up(controller_state.R); }
		if (key_code == input_config.KeyCodeSelect) { button_up(controller_state.Select); }
		if (key_code == input_config.KeyCodeStart) { button_up(controller_state.Start); }
		if (key_code == input_config.KeyCodeX) { button_up(controller_state.X); }
		if (key_code == input_config.KeyCodeY) { button_up(controller_state.Y); }
	}
}
