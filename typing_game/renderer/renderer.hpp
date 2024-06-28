#pragma once 

#include <SDL2/SDL_events.h>
#include <string>

#include <SDL2/SDL.h>
#include <vector>

class Renderer {
public:
	Renderer();
	~Renderer();

	bool running();

	void earlyUpdate();
	void update();
	void render(); // late update
	void handleInput();

private:

	bool should_close;

	SDL_Renderer *renderer;
	SDL_Texture* texture;
	SDL_Window *window;

	int width = 1280;
	int height = 720;

	SDL_Event event; 

	const int init_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER;
	const int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	const char* window_title = "| Typer |";
	const int renderer_flags = SDL_RENDERER_ACCELERATED;
	const int pixel_format = SDL_PIXELFORMAT_RGBA8888;
	const int texture_access = SDL_TEXTUREACCESS_STREAMING;

	const std::string paragraph = "This is a test paragraph idk how long it has to be to go over lines but hopefully this is enough";

};