#include <iostream>
#include <string>
#include <memory>


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

	std::string word = "io";
	SDL_Event event;
	bool should_close = false;
	SDL_StartTextInput();
	std::shared_ptr<std::string> input;
	input = event_handler->getInput();
	renderer->updateParagraph(input);
	std::string strr = "qweqweqweqwe";
	std::vector<std::string> res = renderer->substringify(&strr, 3);
	for (auto i = 0; i < res.size(); ++i) {
		std::cout << res.at(i) << std::endl;
	}
	while (!event_handler->shouldClose()) {
		// SDL_Delay(30); // do this but with regard to real time
		SDL_PollEvent(&event);
		event_handler->queryEvent(&event);
		
		renderer->render();
	}
	SDL_StopTextInput();
	
	delete event_handler;
	delete renderer;
	

	return 0;
}

