#pragma once

#include <string>

namespace ripgorp {

class Matcher {
public:
	explicit Matcher(std::string query);

	bool Matches(const std::string& line) const;
private:
	std::string query_;
};

} // namespace ripgorp