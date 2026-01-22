#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <concepts>

namespace ripgorp {

template <typename T>
	requires std::moveable<T>;
class BlockingQueue {
public:
	void Push(T value) {
		std::unique_lock<std::mutex> lock(mutex_);
		queue_.push(std::move(value));
		cv_.notify_one();
	}

	bool WaitPop(T& value) {
		std::unique_lock<std::mutex> lock(mutex_);
		cv_.wait(lock, [this] { return !queue_.empty() || is_done_;  });

		if(queue_.empty()) {
			return false;
		}

		value = std::move(queue_.front());
		queue_.pop();
		return true;
	}

	void Done() {
		std::unique_lock<std::mutex> lock(mutex_);
		is_done_ = true;
		cv_.notify_all();
	}

private:
	std::mutex mutex_;
	std::condition_variable cv_;
	std::queue<T> queue_;
	bool is_done_ = false;
};

} //namespace ripgorp