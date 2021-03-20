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
		
		controller_state.down.just_pressed = false;
		controller_state.left.just_pressed = false;
		controller_state.right.just_pressed = false;
		controller_state.up.just_pressed = false;

		controller_state.a.just_pressed = false;
		controller_state.b.just_pressed = false;
		controller_state.l.just_pressed = false;
		controller_state.r.just_pressed = false;
		controller_state.select.just_pressed = false;
		controller_state.start.just_pressed = false;
		controller_state.x.just_pressed = false;
		controller_state.y.just_pressed = false;
	}

	void InputSystem::handle_keyboard_event(ALLEGRO_EVENT const& event)
	{
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
		switch (event.type)
		{
			case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
				handle_joy_down(event.joystick.button);
				break;

			case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
				handle_joy_up(event.joystick.button);
				break;

			case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
				al_reconfigure_joysticks();
				break;
		}
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
		button.pressed = false;
	}

	void InputSystem::handle_joy_down(int joy_code)
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		auto& input_config = ecs_agent->get_component<ConfigurationContext>().input_configuration;

		if (joy_code == input_config.joy_code_down) { button_down(controller_state.down); }
		if (joy_code == input_config.joy_code_left) { button_down(controller_state.left); }
		if (joy_code == input_config.joy_code_right) { button_down(controller_state.right); }
		if (joy_code == input_config.joy_code_up) { button_down(controller_state.up); }

		if (joy_code == input_config.joy_code_a) { button_down(controller_state.a); }
		if (joy_code == input_config.joy_code_b) { button_down(controller_state.b); }
		if (joy_code == input_config.joy_code_l) { button_down(controller_state.l); }
		if (joy_code == input_config.joy_code_r) { button_down(controller_state.r); }
		if (joy_code == input_config.joy_code_select) { button_down(controller_state.select); }
		if (joy_code == input_config.joy_code_start) { button_down(controller_state.start); }
		if (joy_code == input_config.joy_code_x) { button_down(controller_state.x); }
		if (joy_code == input_config.joy_code_y) { button_down(controller_state.y); }
	}

	void InputSystem::handle_joy_up(int joy_code)
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		auto& input_config = ecs_agent->get_component<ConfigurationContext>().input_configuration;

		if (joy_code == input_config.joy_code_down) { button_up(controller_state.down); }
		if (joy_code == input_config.joy_code_left) { button_up(controller_state.left); }
		if (joy_code == input_config.joy_code_right) { button_up(controller_state.right); }
		if (joy_code == input_config.joy_code_up) { button_up(controller_state.up); }

		if (joy_code == input_config.joy_code_a) { button_up(controller_state.a); }
		if (joy_code == input_config.joy_code_b) { button_up(controller_state.b); }
		if (joy_code == input_config.joy_code_l) { button_up(controller_state.l); }
		if (joy_code == input_config.joy_code_r) { button_up(controller_state.r); }
		if (joy_code == input_config.joy_code_select) { button_up(controller_state.select); }
		if (joy_code == input_config.joy_code_start) { button_up(controller_state.start); }
		if (joy_code == input_config.joy_code_x) { button_up(controller_state.x); }
		if (joy_code == input_config.joy_code_y) { button_up(controller_state.y); }
	}

	void InputSystem::handle_key_down(int key_code)
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		auto& input_config = ecs_agent->get_component<ConfigurationContext>().input_configuration;

		if (key_code == input_config.key_code_down) { button_down(controller_state.down); }
		if (key_code == input_config.key_code_left) { button_down(controller_state.left); }
		if (key_code == input_config.key_code_right) { button_down(controller_state.right); }
		if (key_code == input_config.key_code_up) { button_down(controller_state.up); }

		if (key_code == input_config.key_code_a) { button_down(controller_state.a); }
		if (key_code == input_config.key_code_b) { button_down(controller_state.b); }
		if (key_code == input_config.key_code_l) { button_down(controller_state.l); }
		if (key_code == input_config.key_code_r) { button_down(controller_state.r); }
		if (key_code == input_config.key_code_select) { button_down(controller_state.select); }
		if (key_code == input_config.key_code_start) { button_down(controller_state.start); }
		if (key_code == input_config.key_code_x) { button_down(controller_state.x); }
		if (key_code == input_config.key_code_y) { button_down(controller_state.y); }
	}

	void InputSystem::handle_key_up(int key_code)
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		auto& input_config = ecs_agent->get_component<ConfigurationContext>().input_configuration;
		
		if (key_code == input_config.key_code_down) { button_up(controller_state.down); }
		if (key_code == input_config.key_code_left) { button_up(controller_state.left); }
		if (key_code == input_config.key_code_right) { button_up(controller_state.right); }
		if (key_code == input_config.key_code_up) { button_up(controller_state.up); }

		if (key_code == input_config.key_code_a) { button_up(controller_state.a); }
		if (key_code == input_config.key_code_b) { button_up(controller_state.b); }
		if (key_code == input_config.key_code_l) { button_up(controller_state.l); }
		if (key_code == input_config.key_code_r) { button_up(controller_state.r); }
		if (key_code == input_config.key_code_select) { button_up(controller_state.select); }
		if (key_code == input_config.key_code_start) { button_up(controller_state.start); }
		if (key_code == input_config.key_code_x) { button_up(controller_state.x); }
		if (key_code == input_config.key_code_y) { button_up(controller_state.y); }
	}
}
