#include "ExternalSort.h"

int main() {
    ExternalSort::generateNumbers();
    ExternalSort::sortChunks();
    ExternalSort::mergeChunks();
    remove("numbers.txt");
    return 0;
}

