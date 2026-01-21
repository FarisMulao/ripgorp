#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace ripgorp
{

class FileScanner {
public:
	explicit FileScanner(std::filesystem::path filepath);

	bool IsOpen() const;
	bool GetLine(std::string& line);

private:
	std::ifstream file_;
};

} // namespace ripgorp