#pragma once 

#include <string>

#include "paragraph.hpp"
#include "renderer.hpp"

class Game {
public:
	Game();
	~Game();
	void start();
	void exit();
	void update();
	void getInput();
	const bool running();
	
private:
	bool is_running;

	std::unique_ptr<Paragraph> current_paragraph;
	std::unique_ptr<Renderer> renderer;
};