
#ifndef INPUT_H
#define INPUT_H

#include "Constants.h"
#include <exception>
#include <functional>
#include <iostream>
#include <vector>

/**
 * @brief This class bundles together all the input functions of the program.
 *
 * @version 1.0
 */
class Input {

  public:
    static std::string *getTestArray() {
        int   numberOfTests = getValidNumberOfTests();
        auto *testArray     = new std::string[numberOfTests];
        initializeTestArray(testArray, numberOfTests);
        return testArray;
    }

  private:
    /**
     * @return numberOfTests gotten.
     * @throws runtime_error in case of `numberOfTests < 1`.
     */
    static int getValidNumberOfTests() {
        int numberOfTests;
        std::cin >> numberOfTests;
        if (numberOfTests < 1) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
        return numberOfTests;
    }

  private:
    static void initializeTestArray(std::string *&testArray,
                                    int           numberOfTests) {
        int sizeCounter = 0;

        for (int i = 0; i < numberOfTests; i++) {
            testArray[i] = getLine(std::cin);
            sizeCounter++;
        }

        if (sizeCounter != numberOfTests) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
    }

  private:
    /**
     * @tparam T an element with a type that **must** be `comparable` to `0`.
     * @param element element to check.
     * @return `true` if the @p element given was found positive. Else, `false`.
     */
    template<typename T> static bool predicateIsPositive(T element) {
        return element > 0;
    }

  private:
    /**
     * @param str element to check.
     * @return `true` if the @p str given was found as a `char` between
     *         `Constants::MINIMUM_LETTER` and `Constants::MAXIMUM_LETTER`.
     *         Else, `false`.
     * @see Constants::Constants
     */
    static bool predicateIsValidLetter(std::string &str) {
        return (str.length() == 1) && (Constants::MINIMUM_LETTER <= str[0]) &&
               (str[0] <= Constants::MAXIMUM_LETTER);
    }

  private:
    static std::string getLine(std::istream &istream) {
        char        input;
        std::string returnValue;

        // Ignore the first char if it is a `Constants::NEW_LINE`.
        istream.get(input);
        if (input != Constants::NEW_LINE) { istream.unget(); }

        istream.get(input);
        while (input != Constants::NEW_LINE) {
            returnValue += input;
            istream.get(input);
        }
        return returnValue;
    }
};

#endif // INPUT_H
