#include <iostream>
#include <filesystem>
#include "search/FileScanner.h"
#include "search/Matcher.h"

void findMatches(const std::filesystem::path& filepath, const std::string& query) {
	ripgorp::FileScanner scanner(filepath);
	if (!scanner.IsOpen()) {
		std::cerr << "Failed to open file: " << filepath << "\n";
		return;
	}
	ripgorp::Matcher matcher(query);
	std::string line;
	int line_number = 0;
	while (scanner.GetLine(line)) {
		++line_number;
		if (matcher.Matches(line)) {
			std::cout << "Match found at line " << line_number << ": " << line << "\n";
		}
	}
}


int main() {
	std::filesystem::path filepath = "../../../src/main.cpp";
	std::string query = "std::cout";

	findMatches(filepath, query);

    return 0;
}