#include "event_handler.hpp"


EventHandler::EventHandler() {

}

EventHandler::~EventHandler() {

}

void EventHandler::queryEvent(SDL_Event* event) {
	key_down = 0;
	switch (event->type) {
		case SDL_QUIT: should_close = true; break;
		case SDL_KEYDOWN:
			if (event->key.keysym.sym == SDLK_ESCAPE) {
				should_close = true; 
			} else {
				key_down = event->key.keysym.sym;
			} break;
		case SDL_KEYUP: key_down = 0; break;
	}
}

const SDL_Keycode EventHandler::getInput() {
	return key_down;
}
