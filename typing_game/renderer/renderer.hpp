#pragma once 

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "event_handler.hpp"

class Renderer {
public:
	Renderer(const uint32_t window_width, const uint32_t window_height);
	~Renderer();

	bool running();

	void render();

	void drawText(const char* text, const SDL_Rect *target);

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
	const int texture_access = SDL_TEXTUREACCESS_STREAMING;

	const SDL_Rect text_box;
	const SDL_Rect typing_box;

	const char* paragraph = "This is a test paragraph idk how long it has to be to go over lines but hopefully this is enough";

	const char* current_paragraph = "asd Add.";

	const char* font_path = "/home/tom/Desktop/GitHub/typing_game/fonts/roboto/Roboto-Black.ttf";
	uint16_t font_size = 108;
	SDL_Color font_colour = { 255, 255, 255, 255 };
	TTF_Font *font;
};