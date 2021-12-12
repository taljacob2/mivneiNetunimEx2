#include "Constants.h"
#include <iostream>

/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {
    try {
        std::cout << "Hello, World!" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
