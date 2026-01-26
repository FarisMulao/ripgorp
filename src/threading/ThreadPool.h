#pragma once

#include <vector>
#include <thread>
#include <functional>

#include "BlockingQueue.h"
#include "../config/SearchConfig.h"

namespace ripgorp {

class ThreadPool {
public:
	ThreadPool(size_t numThreads, const SearchConfig& config);

	~ThreadPool();

	void Enqueue(std::filesystem::path filePath);

	void Stop();

private:
	void WorkerThread(const SearchConfig& config);

	BlockingQueue<std::filesystem::path> queue_;
	std::vector<std::thread> workers_;
};

} // namespace ripgorp