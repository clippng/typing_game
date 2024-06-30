#include <iostream>


#include "renderer.hpp"
#include "program_options.hpp"

// idea is to have a way to read text from pdfs / txt files and then
// use snippets in a similar way to typeracer -- wanting to do it all
// in the terminal but might use sfml or similar if thats too hard

extern bool RELEASE_BUILD;

int main(int argc, char* argv[]) {
	// parse command line arguments
	try {
		ProgramOptions::parse(argc, argv);
	} catch (std::runtime_error& error) {
		std::cout << error.what() << std::endl;
		exit(1); 
	}

	Renderer* renderer = new Renderer(1080, 720);
	EventHandler* event_handler = new EventHandler;

	SDL_Event event;
	bool should_close = false;
	while (!event_handler->shouldClose()) {
		SDL_PollEvent(&event);
		event_handler->queryEvent(&event);
		// send input to game object here
		if (event_handler->getInput() != 0) {
			std::cout << static_cast<char>(event_handler->getInput()) << std::endl;
		}
		renderer->render();
	}
	
	delete event_handler;
	delete renderer;
	

	return 0;
}

