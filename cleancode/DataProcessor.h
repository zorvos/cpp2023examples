#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

class DataProcessor {
public:
    explicit DataProcessor(const std::vector<int>& data);

    void processData();
    double getTotalSum() const;

private:
    void processRange(std::vector<int>::iterator begin, std::vector<int>::iterator end);

    std::vector<int> data_;
    std::atomic<double> total_sum_;
    std::mutex mtx_;
};

#endif // DATAPROCESSOR_H
