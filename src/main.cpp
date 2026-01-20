#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

void findMatches(const std::filesystem::path& filepath, const std::string& query) {
	std::ifstream file(filepath);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filepath << "\n";
		return;
	}

	std::string line;
	std::size_t lineNumber = 1;

	while (std::getline(file, line)) {
		if (line.find(query) != std::string::npos) {
			std::cout << filepath << ":" << lineNumber << ": " << line << "\n";
		}
		++lineNumber;
	}
}

int main() {
	std::filesystem::path filepath = "../../../src/main.cpp";
	std::string query = "std::cout";

	std::cout << "Searching in: " << filepath << "\n";

	std::cout << "working dir: " << std::filesystem::current_path() << "\n";

	findMatches(filepath, query);

    return 0;
}