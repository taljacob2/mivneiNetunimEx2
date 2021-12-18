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
        auto testArray = Input::getTestArray();

        // TODO: print
        std::cout << testArray << std::endl;

        // TestRunner::runAllTests<Entry<int, std::string>>(testArray);

        // testArray.forEach([testArray](std::string *s) { delete s; });

        // // TODO: this works
        for (unsigned long i = 0; i < testArray.size(); i++) {
            std::cout << *testArray.getElement(i) << std::endl;
            delete testArray.getElement(i);
        }

    } catch (std::exception &e) {
        std::cout << Constants::WRONG_INPUT << std::endl;
        // testArray.forEach([testArray](std::string *s) { delete s; });
        return Constants::MAIN_ERROR;
    }

    return 0;
}
