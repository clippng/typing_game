#include "gui.hpp"

GUI::GUI() {

ImGui::CreateContext(); 
initialiseWindows();

}

void GUI::initialiseWindows() {

}

void GUI::update() {
	ImGui::NewFrame();
	ImGui::Render();
}
