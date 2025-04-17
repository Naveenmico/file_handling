#ifndef EXTERNALSORT_H
#define EXTERNALSORT_H

#include <fstream>
#include <vector>
#include <queue>

class ExternalSort {
public:
    static void generateNumbers();
    static void sortChunks();
    static void mergeChunks();
};

#endif // EXTERNALSORT_H

