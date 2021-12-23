#include "Constants.h"
#include "Input.h"
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
        TestRunner::getTestArrayAndRunAllTests();
    } catch (std::exception &e) {
        std::cout << Constants::WRONG_INPUT << std::endl;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
