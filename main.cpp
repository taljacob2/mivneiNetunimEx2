#include "Constants.h"
#include "Input.h"
#include "MinHeap.h"
#include "TestRunner.h"
#include <iostream>

/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {
    std::string *testArray = nullptr;
    try {
        int testArraySize = 0;
        testArray         = Input::getTestArray(testArraySize);

        TestRunner::runAllTests(testArray, testArraySize);

        // TODO: testing heaps:
        MinHeap<int, std::string> minHeap;
        minHeap.insert(new Entry<int, std::string>(3, "hello"));
        std::cout << minHeap;

        delete[] testArray;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        delete[] testArray;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
