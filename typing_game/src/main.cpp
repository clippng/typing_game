#include <iostream>


#include "renderer.hpp"

// idea is to have a way to read text from pdfs / txt files and then
// use snippets in a similar way to typeracer -- wanting to do it all
// in the terminal but might use sfml or similar if thats too hard

// error linking vulkan sdl with imgui

int main() {
	Renderer *renderer = new Renderer(1080, 720);
	EventHandler *event_handler = new EventHandler;
	SDL_Event event;
	bool should_close = false;
	while (!should_close) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE: should_close = true; break;
					}
				case SDL_QUIT: should_close = true; break;
			}
		}
		renderer->render();
	}
	
	delete event_handler;
	delete renderer;
	

	return 0;
}

