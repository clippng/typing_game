#include <memory>

#include "game.hpp"

Game::Game() {
	renderer = std::unique_ptr<Renderer>();
	is_running = true;
	start();
}

Game::~Game() {
	
}

void Game::start() {

}

void Game::exit() {

}

void Game::update() {

}

void Game::getInput() {

}

const bool Game::running() {
	return is_running;
}
