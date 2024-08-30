#include <iostream>
#include <vector>
#include <ranges>
#include <concepts>

// Koncept za proveru da li je tip integralan
template<typename T>
concept Integral = std::is_integral_v<T>;

// Funkcija koja generiše niz brojeva od 1 do n
auto generate_numbers(int n) -> std::vector<int> {
    std::vector<int> numbers(n);
    for (int i = 1; i <= n; ++i) {
        numbers[i - 1] = i;
    }
    return numbers;
}

// Glavna funkcija
int main() {
    // Generisanje brojeva od 1 do 100
    auto numbers = generate_numbers(100);

    // Korišćenje ranges za filtriranje parnih brojeva i njihovo kvadriranje
    auto results = numbers
                 | std::views::filter([](Integral auto n) { return n % 2 == 0; })  // filtriranje parnih brojeva
                 | std::views::transform([](Integral auto n) { return n * n; });   // kvadriranje

    // Ispisivanje rezultata
    for (Integral auto num : results) {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    return 0;
}

