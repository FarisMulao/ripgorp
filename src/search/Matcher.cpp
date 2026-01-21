#include "Matcher.h"

namespace ripgorp
{
	Matcher::Matcher(std::string query) : query_(std::move(query)) {}

	bool Matcher::Matches(const std::string& line) const {
		return line.find(query_) != std::string::npos;
	}

} //namespace ripgorp
