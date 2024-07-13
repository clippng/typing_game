#pragma once 

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <vector>

#include "event_handler.hpp"

class Renderer {
public:
	Renderer(const uint32_t window_width, const uint32_t window_height);
	~Renderer();

	bool running();

	void render();

	void drawText(const char* text, const uint16_t text_length, SDL_Rect *target);

	std::vector<std::string> substringify(std::string* string, const uint16_t line_length);

	void updateParagraph(std::shared_ptr<std::string> paragraph);

private:

	bool should_close;

	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Window *window;

	const uint32_t width;
	const uint32_t height;

	SDL_Event event; 

	const int init_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER;
	const int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	const char* window_title = "| Typer |";
	const int renderer_flags = SDL_RENDERER_ACCELERATED;
	const int pixel_format = SDL_PIXELFORMAT_RGBA8888;
	const int texture_access = SDL_TEXTUREACCESS_TARGET;

	const SDL_Rect upper_box, lower_box;
	SDL_Rect display_box, typing_box;

	const std::string paragraph = "This is a test paragraph idk how long it has to be to go over lines but hopefully this is enough";
	std::shared_ptr<std::string> input;

	const char* font_path = "/home/tom/Desktop/GitHub/typing_game/fonts/roboto/Roboto-Black.ttf";
	uint16_t font_size = 64;
	SDL_Color font_colour = { 255, 255, 255, 255 };
	TTF_Font *font;
};