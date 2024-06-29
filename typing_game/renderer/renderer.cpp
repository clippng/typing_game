#include <stdexcept>
#include <iostream>
#include <string>


#include "renderer.hpp"

Renderer::Renderer(const uint32_t window_width, const uint32_t window_height) :
	width(window_width), height(window_height), 
	text_box(4, 4 , window_width - 8, window_height / 2 - 4),
	typing_box(4, window_height / 2 + 4, window_width - 8, window_height / 2 - 4) {
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

		if (TTF_Init() != 0) {
			throw std::runtime_error(TTF_GetError());
		}
	} catch (std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
		exit(1);
	}
	font = TTF_OpenFont(font_path, font_size);
	if (font == NULL) {
		std::cout << TTF_GetError() << std::endl;
	}

	should_close = false;
}

Renderer::~Renderer() {
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

bool Renderer::running() {
	return !should_close;
}


void Renderer::render() {
	SDL_RenderClear(renderer);

	drawText(paragraph, &text_box);

	drawText(current_paragraph, &typing_box);

	SDL_RenderPresent(renderer);
}

void Renderer::drawText(const char* text, const SDL_Rect *target) {
	surface = TTF_RenderText_Solid_Wrapped(font, text, font_colour, width);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, target);
}
