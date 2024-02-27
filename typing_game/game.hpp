#pragma once 

#include <memory>
#include <string>

#include "lib_imgui/imgui.h"
#include "paragraph.hpp"
#include "gui.hpp"

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
	int last_key_pressed;
	std::unique_ptr<Paragraph> current_paragraph;
	std::unique_ptr<GUI> gui;
};