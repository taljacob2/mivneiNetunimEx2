#include "Constants.h"
#include "Input.h"
#include <iostream>

void runTest(std::string *&test) {
    // TODO: do something with `test` here...
}

void runAllTests(std::string *&testArray, int testArraySize) {
    char delimiter = ' ';
    for (int i = 0; i < testArraySize; i++) {
        std::string *test = Input::getTest(testArray, delimiter, i);
        runTest(test);
        delete[] test;
    }
}

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

        runAllTests(testArray, testArraySize);

        delete[] testArray;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        delete[] testArray;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
