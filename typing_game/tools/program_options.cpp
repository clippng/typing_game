#include "program_options.hpp"
#include <stdexcept>
#include <iostream>

bool RELEASE_BUILD;

// will eventually need to support taking files as arguments

void ProgramOptions::parse(int argc, char* argv[]) {
	if (argc > 32) {
		throw std::runtime_error("Too many arguments");
	}

	const std::vector<std::string_view> args(argv + 1, argv + argc);

	for (const auto& arg : args) {
		if (arg == "-R" || arg == "--release") {
			RELEASE_BUILD = true;
		}
	}

}