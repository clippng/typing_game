#include "event_handler.hpp"


EventHandler::EventHandler() {

}

EventHandler::~EventHandler() {

}

void EventHandler::queryEvent(SDL_Event event) {
	switch (event.type) {
		case SDL_QUIT: should_close = true; break;
		case SDL_KEYDOWN: /*do something*/ break;
		case SDL_KEYUP: break;
	}
}