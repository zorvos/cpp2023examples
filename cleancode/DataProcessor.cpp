#include "DataProcessor.h"
#include <cmath>
#include <algorithm>

DataProcessor::DataProcessor(const std::vector<int>& data)
    : data_(data), total_sum_(0) {}

void DataProcessor::processData() {
    const unsigned int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    size_t chunk_size = data_.size() / num_threads;

    for (unsigned int i = 0; i < num_threads; ++i) {
        auto begin = data_.begin() + i * chunk_size;
        auto end = (i == num_threads - 1) ? data_.end() : begin + chunk_size;
        threads.emplace_back(&DataProcessor::processRange, this, begin, end);
    }

    for (auto& th : threads) {
        th.join();
    }
}

double DataProcessor::getTotalSum() const {
    return total_sum_.load();
}

void DataProcessor::processRange(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    double local_sum = 0;
    for (auto it = begin; it != end; ++it) {
        local_sum += std::sqrt(*it);
    }

    std::lock_guard<std::mutex> lock(mtx_);
    total_sum_ += local_sum;
}
