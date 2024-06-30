#pragma once

#include <SDL2/SDL_events.h>
#include <string>
#include <memory>


class EventHandler {
public:
	EventHandler();
	~EventHandler();

	inline bool shouldClose() { return should_close; }

	void queryEvent(SDL_Event* event);

	std::shared_ptr<std::string> getInput();

	void clearInputBuffer();


private:
	bool should_close = false;

	std::shared_ptr<std::string> input_string;


	bool shift_held;
	bool caps_lock;

};