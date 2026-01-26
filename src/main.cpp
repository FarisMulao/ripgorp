#include <iostream>
#include <thread>
#include "config/SearchConfig.h"
#include "threading/ThreadPool.h"

int main() {
    ripgorp::SearchConfig config;
    config.pattern = "c";

    const auto num_threads = std::thread::hardware_concurrency();
    ripgorp::ThreadPool pool(num_threads, config);

    pool.Enqueue("../../../CMakeLists.txt");

    pool.Stop();

    return 0;
}