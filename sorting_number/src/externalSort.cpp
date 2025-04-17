#include "ExternalSort.h"
#include <algorithm>

#define NUMBERS 1000000
#define CHUNK_SIZE 1000
#define CHUNKS NUMBERS / CHUNK_SIZE

void ExternalSort::generateNumbers() {
    std::ofstream file("numbers.txt");
    for (int i = 0; i < NUMBERS; i++) {
        file << rand() % NUMBERS << "\n";
    }
    file.close();
}

void ExternalSort::sortChunks() {
    std::ifstream input("numbers.txt");
    std::vector<int> numbers(CHUNK_SIZE);
    for (int i = 0; i < CHUNKS; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            input >> numbers[j];
        }
        std::sort(numbers.begin(), numbers.end());
        std::ofstream output("chunk" + std::to_string(i) + ".txt");
        for (int num : numbers) {
            output << num << "\n";
        }
        output.close();
    }
    input.close();
}

struct Compare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first > b.first;
    }
};

void ExternalSort::mergeChunks() {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> min_heap;
    std::vector<std::ifstream> chunks(CHUNKS);
    for (int i = 0; i < CHUNKS; i++) {
        chunks[i].open("chunk" + std::to_string(i) + ".txt");
        int num;
        chunks[i] >> num;
        min_heap.push({num, i});
    }
    std::ofstream output("sorted.txt");
    while (!min_heap.empty()) {
        std::pair<int, int> smallest = min_heap.top();
        min_heap.pop();
        output << smallest.first << "\n";
        if (chunks[smallest.second] >> smallest.first) {
            min_heap.push(smallest);
        }
    }
    output.close();
    for (int i = 0; i < CHUNKS; i++) {
        chunks[i].close();
        remove(("chunk" + std::to_string(i) + ".txt").c_str());
    }
}

