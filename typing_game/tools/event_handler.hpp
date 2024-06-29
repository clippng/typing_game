#pragma once

#include <SDL2/SDL_events.h>

#include <vector>



class EventHandler {
public:
	EventHandler();
	~EventHandler();

	void queryEvent(SDL_Event event);

	void handleInput(SDL_KeyCode key);

	
private:

	bool should_close = false;


	// SDL events only occur on key presses and releases
	// so this struct holds the current state of each key
	struct KeyDown {
		bool a = false;
		bool b = false;
		bool c = false;
		bool d = false;
		bool e = false;
		bool f = false;
		bool g = false;
		bool h = false;
		bool i = false;
		bool j = false;
		bool k = false;
		bool l = false;
		bool m = false;
		bool n = false;
		bool o = false;
		bool p = false;
		bool q = false;
		bool r = false;
		bool s = false;
		bool t = false;
		bool u = false;
		bool v = false;
		bool w = false;
		bool x = false;
		bool y = false;
		bool z = false;
		
		bool comma = false;
		bool period = false;
		bool hyphen = false;

		bool zero = false;
		bool one = false;
		bool two = false;
		bool three = false;
		bool four = false;
		bool five = false;
		bool six = false;
		bool seven = false;
		bool eight = false;
		bool nine = false;

		
		bool shift = false;
		bool backspace = false;
	};

};