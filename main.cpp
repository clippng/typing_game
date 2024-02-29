#include "typing_game/game.hpp"

#include <vulkan/vulkan.hpp>
// idea is to have a way to read text from pdfs / txt files and then
// use snippets in a similar way to typeracer -- wanting to do it all
// in the terminal but might use sfml or similar if thats too hard

// error linking vulkan sdl with imgui

int main() {
	VkResult test;
	Game game;

	while (game.running()) {
		game.update(); 
	}
	game.exit();
	
	return 0;
}
