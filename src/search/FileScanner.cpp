#include "FileScanner.h"

namespace ripgorp
{

	FileScanner::FileScanner(std::filesystem::path filepath) : file_(filepath) {}

	bool FileScanner::IsOpen() const {
		return file_.is_open();
	}

	bool FileScanner::GetLine(std::string& line) {
		return static_cast<bool>(std::getline(file_, line));
	}

} // namespace ripgorp