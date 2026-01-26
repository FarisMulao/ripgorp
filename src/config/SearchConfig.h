#pragma once

#include <string>
#include <filesystem>

namespace ripgorp {

struct SearchConfig {
	std::string pattern;
	std::filesystem::path root;
};

} // namespace ripgorp