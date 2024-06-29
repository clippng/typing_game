#pragma once 

#include <string>

#include "paragraph.hpp"
#include "renderer.hpp"

class Game {
public:
	Game();
	void start();
	void exit();
	void update();
	void getInput();
	const bool running();
	
private:
	bool is_running;
	// int last_key_pressed;
	std::unique_ptr<Paragraph> current_paragraph;
	std::unique_ptr<Renderer> gui;
};