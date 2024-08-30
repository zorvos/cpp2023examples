#include <iostream>
#include <vector>
#include <ranges>
#include <format>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <numeric>

// Funkcija za obradu opsega podataka
void processRange(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::atomic<int>& total_sum, std::mutex& mtx) {
    int local_sum = 0;
    for (auto it = begin; it != end; ++it) {
        local_sum += (*it) * (*it);  // Primer obrade: kvadriranje svakog elementa
    }

    std::lock_guard<std::mutex> lock(mtx);
    total_sum += local_sum;
}

int main() {
    std::vector<int> numbers(100'000);
    std::iota(numbers.begin(), numbers.end(), 1);  // Popunjava sa vrednostima 1, 2, ..., 100000

    std::atomic<int> total_sum{0};
    std::mutex mtx;

    auto start = std::chrono::high_resolution_clock::now();

    // Deljenje posla na više niti
    const unsigned int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    size_t chunk_size = numbers.size() / num_threads;

    for (unsigned int i = 0; i < num_threads; ++i) {
        auto begin = numbers.begin() + i * chunk_size;
        auto end = (i == num_threads - 1) ? numbers.end() : begin + chunk_size;
        threads.emplace_back(processRange, begin, end, std::ref(total_sum), std::ref(mtx));
    }

    for (auto& th : threads) {
        th.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << std::format("Ukupan zbir kvadrata: {}\n", total_sum.load());
    std::cout << std::format("Vreme trajanja: {:.6f} sekundi\n", elapsed.count());

    return 0;
}
