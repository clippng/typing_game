#include <memory>

#include "game.hpp"

Game::Game() {
	gui = std::unique_ptr<GUI>();
	is_running = true;
	start();
}

void Game::start() {

}

void Game::exit() {
}

void Game::update() {
	gui->update();
}

void Game::getInput() {

}

const bool Game::running() {
	return is_running;
}
