#pragma once

#include <SDL2/SDL_events.h>



class EventHandler {
public:
	EventHandler();
	~EventHandler();

	inline bool shouldClose() { return should_close; }

	void queryEvent(SDL_Event* event);

	const SDL_Keycode getInput();


private:
	bool should_close = false;

	SDL_Keycode key_down;

	uint32_t key_held;

};