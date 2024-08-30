#include <iostream>
#include <vector>
#include <ranges>
#include <format>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <numeric>
#include <cmath>
#include "DataProcessor.h"

// Funkcija za kreiranje skupa podataka
std::vector<int> generateData(size_t size) {
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 1);
    return data;
}

int main() {
    const size_t data_size = 100'000;
    auto numbers = generateData(data_size);

    DataProcessor processor(numbers);

    auto start = std::chrono::high_resolution_clock::now();
    processor.processData();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << std::format("Ukupan zbir kvadratnih korena: {:.2f}\n", processor.getTotalSum());
    std::cout << std::format("Vreme trajanja: {:.6f} sekundi\n", elapsed.count());

    return 0;
}
