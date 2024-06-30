#include "event_handler.hpp"


EventHandler::EventHandler() {
	input_string = std::unique_ptr<std::string>(new std::string);
}

EventHandler::~EventHandler() {

}

void EventHandler::queryEvent(SDL_Event* event) {
	switch (event->type) {
		case SDL_QUIT: should_close = true; break;
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_ESCAPE: should_close = true; break;
				case SDLK_BACKSPACE: if (input_string->size()) { input_string->pop_back(); } break;
			} break;
		case SDL_TEXTINPUT: *input_string += event->text.text; break;
		
	}
}


// works for standard ascii keys but not modifier keys
// will need to hold more than 1 input key at once
std::shared_ptr<std::string> EventHandler::getInput() {
	return input_string;
}

void EventHandler::clearInputBuffer() {
	*input_string = "";
}
