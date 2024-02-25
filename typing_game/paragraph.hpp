#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <random>
#include <bits/types/FILE.h>

class Paragraph {
public:
	Paragraph();
	std::string readFile(const std::string file_name);
	std::vector<std::string> writeParagraph(unsigned int length);
	std::vector<std::string> writeParagraphRandom(unsigned int length);
	std::vector<std::string> formatString(const std::string string);
	std::string deformatString(const std::vector<std::string> formatted_string);
	unsigned int getCharacterLength();
	unsigned int getWordLength();
	
	std::string getWord();
	std::string getWordRandom();

	std::vector<std::string> getContents();
	std::string getParagraphAsString();

	void updateLengths();

private:
	const std::string consonants = "qwrtpsdfghjklzxcvbnm";
	const std::string vowels =  "aeiouy";
	const std::string example_paragraph = "pickpockets' profession demands extraordinary nimbleness and agility, a terrific certainty of movement, not to mention a ready wit, a talent for observation and strained attention.";
	// special characters " .(), ?"":"

	unsigned int character_length;
	unsigned int word_length;

	std::unique_ptr<std::vector<std::string>> contents;
	std::unique_ptr<std::string> paragraph_string; // used to calculate the number of characters
};

 