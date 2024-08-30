#include <iostream>
#include <vector>
#include <ranges>
#include <format>
#include <chrono>

int main() {
    // Using std::ranges to work with ranges
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    auto squared = numbers | std::views::transform([](int n) { return n * n; });

    std::cout << "Squares of numbers:\n";
    for (int square : squared) {
        std::cout << square << ' ';
    }
    std::cout << '\n';

    // Using std::format for type-safe string formatting
    int age = 30;
    double pi = 3.14159;
    std::string formatted = std::format("Age: {}, Pi: {:.2f}", age, pi);

    std::cout << formatted << '\n';

    // Using std::chrono for time handling
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate a task
    for (volatile int i = 0; i < 1'000'000; ++i);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time taken: " << std::format("{:.6f} seconds", elapsed.count()) << '\n';

    return 0;
}
