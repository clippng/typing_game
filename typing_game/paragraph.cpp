#include "paragraph.hpp"

Paragraph::Paragraph() {
	//std::vector<std::string> test = readFile("assets/words.txt");
	//std::vector<std::string> buffer = formatString(example_paragraph);
	//for (int i = 0; i < buffer.size(); i++) {
	//	contents->push_back(buffer.at(i));
	//}
}

std::string Paragraph::readFile(const std::string file_name) { // doesnt work currently
	std::string file_contents;
	std::ifstream stream (file_name);
	
	if (stream.good()) {
		for (std::string word; std::getline(stream, word);) {
			file_contents.append(word);
		}
		std::cout << std::to_string(file_contents.length()) << " characters read." << std::endl; 
	} else {
		std::cerr << "Error: cannot open file: " <<  file_name << std::endl;
	}

	return file_contents;
}

std::vector<std::string> Paragraph::writeParagraph(unsigned int length) {
	std::vector<std::string> paragraph_;

	for (unsigned int i = 0; i < length; ++i) {
		paragraph_.push_back(getWord());
	}

	return paragraph_;
}

// Converts strings into vector<string>
std::vector<std::string> Paragraph::formatString(const std::string string) {
	std::vector<std::string> paragraph_;
	std::string current_word;
	unsigned int word_count = 0;

	for (const char & c : string) {
		if (c == ' ') {
			paragraph_.push_back(current_word);
			current_word.clear();
			++word_count;
		} else {
			current_word += c;
		}
	}
	paragraph_.push_back(current_word);

	return paragraph_;
}

std::string Paragraph::deformatString(const std::vector<std::string> formatted_string) { // havent tested
	std::string deformatted_string;

	for (int i = 0; i < formatted_string.size(); ++i) {
		deformatted_string += formatted_string.at(i);
		deformatted_string += " ";
	}

	return deformatted_string;	
}

unsigned int Paragraph::getCharacterLength() {
	return character_length;
}

unsigned int Paragraph::getWordLength() {
	return word_length;
}

std::string Paragraph::getWord() {
	// get random number between 0 and words vector length
	// retrun words.at(that number)
	return "ok";
}

std::string Paragraph::getWordRandom() {
	unsigned int characters = std::round(std::rand() * 8);
	return "qweqw";
}

std::vector<std::string> Paragraph::getContents() {
	return *contents;
}


std::string Paragraph::getParagraphAsString() {
	return *paragraph_string;
}

void Paragraph::updateLengths() {
	word_length = contents->size();
	character_length = paragraph_string->length();
}