#include "ThreadPool.h"
#include "../search/FileScanner.h"
#include "../search/Matcher.h"
#include <iostream>

namespace ripgorp {

void ThreadPool::WorkerThread(const SearchConfig& config) {
	Matcher matcher(config.pattern);
	std::filesystem::path filePath;

	while(queue_.WaitPop(filePath)) {
		FileScanner scanner(filePath);

		if (!scanner.IsOpen()) {
			std::cerr << "Failed to open file: " << filePath << "\n";
			continue;
		}

		std::string line;
		size_t lineNumber = 1;

		while (scanner.GetLine(line)) {
			if (matcher.Matches(line)) {
				// not thread safe, will deal with later :D - could lead to race when printing
				std::cout << filePath << ":" << lineNumber << ": " << line << "\n";
			}
			lineNumber++;
		}
	}
}

ThreadPool::ThreadPool(size_t numThreads, const SearchConfig& config) {
	workers_.reserve(numThreads);

	for (size_t i = 0; i < numThreads; i++) {
		// have to wrap config with std::ref to avoid the thread making a copy
		workers_.emplace_back(&ThreadPool::WorkerThread, this, std::ref(config));
	}
}

ThreadPool::~ThreadPool() {
	for (auto& worker : workers_) {
		if (worker.joinable()) {
			worker.join();
		}
	}
}

void ThreadPool::Enqueue(std::filesystem::path filePath) {
	queue_.Push(std::move(filePath));
}

void ThreadPool::Stop() {
	queue_.Done();
}

} // namespace ripgorp