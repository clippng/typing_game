#include <stdexcept>
#include <iostream>
#include <string>


#include "renderer.hpp"

// fix text warping in rects

Renderer::Renderer(const uint32_t window_width, const uint32_t window_height) :
	width(window_width), height(window_height),	
	upper_box(4, 4 , window_width - 8, window_height / 2 - 4),
	lower_box(4, window_height / 2 + 4, window_width - 8, window_height / 2 - 4) {
	try {
		if (SDL_Init(init_flags) != 0) {
			throw std::runtime_error("Couldn't initialise SDL");
		}

		window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

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
	typing_box = { 8, (int)window_height / 2 + 4, 0, 0 };
	display_box = { 8, 8, 0, 0 };
	should_close = false;
}

Renderer::~Renderer() {
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

bool Renderer::running() {
	return !should_close;
}


void Renderer::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer); 

//	TTF_SizeText(font, input->c_str(), &typing_box.w, &typing_box.h);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &upper_box);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &lower_box);

	drawText(input->c_str(), input->length(), &typing_box);
	drawText(paragraph.c_str(), paragraph.length(), &display_box);

	SDL_RenderPresent(renderer);
}

void Renderer::drawText(const char* text, const uint16_t text_length, SDL_Rect *target) {
	if (text) {
		const int max_w = lower_box.w;
		int w, lines, line_height;
		TTF_SizeUTF8(font, text, &w, &line_height);
		w > max_w ? target->w = max_w : target->w = w;
		lines = (w / max_w) + 1;
		if (lines > 6) {
			throw std::runtime_error("String too long to render.");
		}
		target->h = line_height * lines;

		surface = TTF_RenderUTF8_Solid_Wrapped(font, text, font_colour, width);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, target);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
}

std::vector<std::string> Renderer::substringify(std::string* string, const uint16_t line_length) {
	std::vector<std::string> substrings;
	std::string substring;
	for (int i = 0; i < string->length();) {
		substring = "";
		while (substring.length() < line_length) {
			substring += string->at(i);
			++i;
		}
		// int j = substring.length();
		// while (substring[j] != ' ' || j == 0) {
		// 	--j;
		// }
		// substring.erase(j, 0);
		substrings.push_back(substring);
	}
	std::cout << substrings.size() << std::endl;
	return substrings;
}

void Renderer::updateParagraph(std::shared_ptr<std::string> paragraph) {
	input = paragraph;
}