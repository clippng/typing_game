#pragma once 

#include <memory>
#include <string>

#include "../libs/imgui/imgui.h"

class GUI {
public:
	GUI();

	void initialiseWindows();
	void update();

private:
	
	
	const std::string title = "Typing Game";
	const std::string header = "test";
	const std::string paragraph = "This is a test paragraph idk how long it has to be to go over lines but hopefully this is enough";
	
};