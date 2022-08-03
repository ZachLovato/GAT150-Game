#include "InputSystem.h" 
#include <SDL.h>

namespace wrap {

	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_w = SDL_SCANCODE_W;
	const uint32_t key_a = SDL_SCANCODE_A;
	const uint32_t key_s = SDL_SCANCODE_D;
	const uint32_t key_r = SDL_SCANCODE_R;
	const uint32_t key_1 = SDL_SCANCODE_1;
	const uint32_t key_2 = SDL_SCANCODE_2;
	const uint32_t key_3 = SDL_SCANCODE_3;
	const uint32_t key_z = SDL_SCANCODE_Z;


	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;


	void wrap::InputSystem::Initialize()
	{
		int numKeys;
		// get pointer to sdl keyboard states and number of keys 
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

		// resize of keyboard state using numKeys for size 
		m_keyboardState.resize(numKeys);

		// copy the sdl key states to keyboard state 
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin(
		));

		// set previous keyboard state to current keyboard state 
		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		// save previous keyboard state 
		m_prevKeyboardState = m_keyboardState;

		// get current keyboard state 
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		m_prevMouseButtonState = m_mouseButtonState;

		// get present mouse state
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = wrap::Vector2(x, y);
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
	}

	InputSystem::KeyState wrap::InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keyState = KeyState::Idle;

		if (GetKeyDown(key) && !GetPreviousKeyDown(key))
		{
			keyState = InputSystem::KeyState::Pressed;
		}
		if (GetKeyDown(key) && GetPreviousKeyDown(key))
		{
			keyState = InputSystem::KeyState::Held;
		}
		if (!GetKeyDown(key) && GetPreviousKeyDown(key))
		{
			keyState = InputSystem::KeyState::Released;
		}

		return keyState;

	}

	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState keyState = KeyState::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 
		if (GetButtonDown(button) && !GetPreviousButtonDown(button))
		{
			keyState = InputSystem::KeyState::Pressed;
		}
		if (GetButtonDown(button) && GetPreviousButtonDown(button))
		{
			keyState = InputSystem::KeyState::Held;
		}
		if (!GetButtonDown(button) && GetPreviousButtonDown(button))
		{
			keyState = InputSystem::KeyState::Released;
		}

		return keyState;
	}

}

