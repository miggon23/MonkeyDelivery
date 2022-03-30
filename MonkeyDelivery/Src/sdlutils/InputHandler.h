// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <vector>
#include "../utils/Singleton.h"
#include "../utils/Vector2D.h"
// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

class InputHandler : public Singleton<InputHandler> {

	friend Singleton<InputHandler>;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	virtual ~InputHandler() {
	}

	// clear the state
	inline void clearState() {
		isCloseWindoEvent_ = false;
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;
		isMouseButtonEvent_ = false;
		isMouseMotionEvent_ = false;
		for (auto i = 0u; i < 3; i++) {
			mbState_[i] = false;
		}
	}

	// update the state with a new event
	inline void update(const SDL_Event& event) {
		int whichOne;
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		case SDL_WINDOWEVENT:
			handleWindowEvent(event);
			break;
		case SDL_JOYBUTTONDOWN:
			whichOne = event.jaxis.which;
			m_buttonStates[whichOne][event.jbutton.button] = true;
			break;
		case SDL_JOYBUTTONUP:
			whichOne = event.jaxis.which;
			m_buttonStates[whichOne][event.jbutton.button] = false;
			break;
		case SDL_JOYAXISMOTION:
			handleJoyMotion(event);
		default:
			break;
		}
	}

	// refresh
	inline void refresh() {
		SDL_Event event;

		clearState();
		while (SDL_PollEvent(&event))
			update(event);
	}
	inline bool getButtonState(int joy, int buttonNumber)
	{
		if (SDL_NumJoysticks() > joy) {
			return m_buttonStates[joy][buttonNumber];
		}

		return false;
	}
	inline bool bJoysticksInitialised() {
		return m_bJoysticksInitialised;
	}

	// close window event

	inline bool closeWindowEvent() {
		return isCloseWindoEvent_;
	}

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}

	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return keyDownEvent() && kbState_[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return keyUpEvent() && kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonEvent_;
	}

	inline const std::pair<Sint32, Sint32>& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

	//joystick
	inline int xvalue(int joy, int stick) {
		if (m_joystickValues.size() > 0) {
			if (stick == 0) {
				return m_joystickValues[joy].first.getX();
			}
			else if (stick == 1) {
				return m_joystickValues[joy].second.getX();
			}
		}
		return 0;
	}
	inline int yvalue(int joy, int stick) {
		if (m_joystickValues.size() > 0) {
			if (stick == 0) {
				return m_joystickValues[joy].first.getY();
			}
			else if (stick == 1) {
				return m_joystickValues[joy].second.getY();
			}
		}
		return 0;
	}

	inline void handleJoyMotion(const SDL_Event& event) {
		int whichOne = event.jaxis.which;
		auto m_sens = 10000;

		if (event.jaxis.axis == 0) {
			if (event.jaxis.value > m_sens) {
				m_joystickValues[whichOne].first.setX(1);
			}
			else if (event.jaxis.value < -m_sens) {
				m_joystickValues[whichOne].first.setX(-1);
			}
			else {
				m_joystickValues[whichOne].first.setX(0);
			}
		}

		if (event.jaxis.axis == 1) {
			if (event.jaxis.value > m_sens) {
				m_joystickValues[whichOne].first.setY(1);
			}
			else if (event.jaxis.value < -m_sens) {
				m_joystickValues[whichOne].first.setY(-1);
			}
			else {
				m_joystickValues[whichOne].first.setY(0);
			}
		}

		if (event.jaxis.axis == 3) {
			if (event.jaxis.value > m_sens) {
				m_joystickValues[whichOne].second.setX(1);
			}
			else if (event.jaxis.value < -m_sens) {
				m_joystickValues[whichOne].second.setX(-1);
			}
			else {
				m_joystickValues[whichOne].second.setX(0);
			}
		}

		if (event.jaxis.axis == 4) {
			if (event.jaxis.value > m_sens) {
				m_joystickValues[whichOne].second.setY(1);
			}
			else if (event.jaxis.value < -m_sens) {
				m_joystickValues[whichOne].second.setY(-1);
			}
			else {
				m_joystickValues[whichOne].second.setY(0);
			}
		}
	}

private:
	InputHandler() {
		kbState_ = SDL_GetKeyboardState(0);
		initialiseJoysticks();
		clearState();
	}

	inline void onKeyDown(const SDL_Event&) {
		isKeyDownEvent_ = true;
	}

	inline void onKeyUp(const SDL_Event&) {
		isKeyUpEvent_ = true;
	}

	inline void onMouseMotion(const SDL_Event& event) {
		isMouseMotionEvent_ = true;
		mousePos_.first = event.motion.x;
		mousePos_.second = event.motion.y;

	}

	inline void onMouseButtonChange(const SDL_Event& event, bool isDown) {
		isMouseButtonEvent_ = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mbState_[LEFT] = isDown;
			break;
		case SDL_BUTTON_MIDDLE:
			mbState_[MIDDLE] = isDown;
			break;
		case SDL_BUTTON_RIGHT:
			mbState_[RIGHT] = isDown;
			break;
		default:
			break;
		}
	}

	inline void handleWindowEvent(const SDL_Event& event) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			isCloseWindoEvent_ = true;
			break;
		default:
			break;
		}
	}
	inline void initialiseJoysticks()
	{
		if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
		{
			SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		}
		if (SDL_NumJoysticks() > 0)
		{
			m_buttonStates.resize(SDL_NumJoysticks());
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				SDL_Joystick* joy = SDL_JoystickOpen(i);

				if (joy)
				{
					std::vector<bool> tempButtons;
					for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
					{
						tempButtons.push_back(false);
					}
					//m_buttonStates.push_back(tempButtons);
					m_buttonStates[SDL_JoystickInstanceID(joy)] = tempButtons;
					m_joystickValues.emplace_back();
				}
				else
				{
					std::cout << SDL_GetError();
				}
			}
			SDL_JoystickEventState(SDL_ENABLE);
			m_bJoysticksInitialised = true;
		}
		else
		{
			m_bJoysticksInitialised = false;
		}
	}

	bool isCloseWindoEvent_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	bool m_bJoysticksInitialised;
	std::pair<Sint32, Sint32> mousePos_;
	std::array<bool, 3> mbState_;
	const Uint8* kbState_;
	std::vector<std::vector<bool>> m_buttonStates;
	std::vector < std::pair < Vector2D<int>, Vector2D<int> >> m_joystickValues;
}
;

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::instance();
}

