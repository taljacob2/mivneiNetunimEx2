#include "Constants.h"
#include "Input.h"
#include "MaxHeap.h"
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
    try {
        auto testArray = Input::getTestArray();
        TestRunner::runAllTests<Entry<int, std::string>>(testArray);
    } catch (std::exception &e) {
        std::cout << Constants::WRONG_INPUT << std::endl;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
