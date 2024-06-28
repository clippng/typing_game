#include <stdexcept>
#include <iostream>
#include <vector>

#include "renderer.hpp"

Renderer::Renderer() {
	try {
		if (SDL_Init(init_flags) != 0) {
			throw std::runtime_error("Couldn't initialise SDL");
		}

		window = SDL_CreateWindow("TESTT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

		if (!window) {
			throw std::runtime_error("Couldn't initialise SDL");
		}

		renderer = SDL_CreateRenderer(window, -1, renderer_flags);

		if (!renderer) {
			throw std::runtime_error("Couldn't initialise SDL");
		}

		texture = SDL_CreateTexture(renderer, pixel_format, texture_access, width, height);

		if (!texture) {
			throw std::runtime_error("Couldn't initialise SDL");
		}
	} catch (std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
		exit(1);
	}
	should_close = false;
}

Renderer::~Renderer() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

bool Renderer::running() {
	return !should_close;
}

void Renderer::earlyUpdate() {
	
}

void Renderer::update() {

}

void Renderer::render() {

}

void Renderer::handleInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
			default:
				break;
		}
	}
}
