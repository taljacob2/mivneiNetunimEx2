
#ifndef INPUT_H
#define INPUT_H

#include "Constants.h"
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * @brief This class bundles together all the input functions of the program.
 *
 * @version 1.0
 */
class Input {

  private:
    /**
     * The minimum letter which is valid to be inputted.
     * @see predicateIsValidLetter(std::string &)
     */
    static constexpr char MINIMUM_LETTER = 'a';

  private:
    /**
     * The maximum letter which is valid to be inputted.
     * @see predicateIsValidLetter(std::string &)
     */
    static constexpr char MAXIMUM_LETTER = 'g';

  private:
    /**
     * The letter which must be the presented at first, when validating
     * the testArray.
     * @see validateTestArray(std::string *, int)s
     */
    static constexpr char FIRST_LETTER = 'e';

  private:
    /**
     * The letter which after it the user needs to provide 2 parameters.
     * @see validateTestArray(std::string *, int)
     */
    static constexpr char ALLOWED_TWO_PARAMETERS_LETTER = 'f';

  public:
    /**
     * @brief Gets the an array of tests from the input-stream, and assert the
     *        validity of it.
     *
     * For example:
     * a valid input would be:
     * @code
     * 6
     * e
     * f 3 hi
     * f 2 why
     * f 9 bye
     * f 7 day
     * g
     * @endcode
     *
     * @return an array that each element of it is a line inputted.
     * @todo delete[] testArray.
     */
    static std::string *getTestArray(int &testArraySize) {
        testArraySize   = getValidNumberOfTests();
        auto *testArray = new std::string[testArraySize];
        initializeTestArray(testArray, testArraySize);
        validateTestArray(testArray, testArraySize);
        return testArray;
    }

  private:
    static void validateTestArray(std::string *testArray, int testArraySize) {
        for (int i = 0; i < testArraySize; i++) {

            // Split the current line by ' ' delimiter.
            int          splitArraySize = 0;
            std::string *splitArray     = nullptr;
            split(testArray[i], ' ', splitArray, splitArraySize);

            // Validate first letter.
            if (i == 0) {
                if (!((testArray[i].length() == 1) &&
                      testArray[i][0] == FIRST_LETTER)) {
                    throw std::runtime_error(Constants::WRONG_INPUT);
                }
            } else {
                if (!predicateIsValidLetter(splitArray[0])) {
                    throw std::runtime_error(Constants::WRONG_INPUT);
                }
            }

            // Validate parameters after first letter.
            if (splitArraySize > 1) {
                assertAllowedTwoParameters(splitArray, splitArraySize);
            }

            delete[] splitArray;
        }
    }

  private:
    static void assertAllowedTwoParameters(const std::string *splitArray,
                                           int                splitArraySize) {

        // Allow only the letter `ALLOWED_TWO_PARAMETERS_LETTER`.
        if (splitArray[0].c_str()[0] != ALLOWED_TWO_PARAMETERS_LETTER) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        // Assert having exactly two parameters after the allowed letter.
        if (splitArraySize != 3) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        // First parameter must be a positive number.
        if (!predicateIsPositive<int>(std::stoi(splitArray[1]))) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
    }

  private:
    /**
     * @return numberOfTests gotten.
     * @throws std::runtime_error in case of `numberOfTests < 1`.
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
     *         `MINIMUM_LETTER` and `MAXIMUM_LETTER`.
     *         Else, `false`.
     * @see MINIMUM_LETTER
     * @see MAXIMUM_LETTER
     */
    static bool predicateIsValidLetter(std::string &str) {
        return (str.length() == 1) && (MINIMUM_LETTER <= str[0]) &&
               (str[0] <= MAXIMUM_LETTER);
    }

  private:
    /**
     * @brief Gets a whole line from an input-stream - from the start of the
     *        line until the `Constants::NEW_LINE` char (not included).
     * @param istream the input-stream to get a line from.
     * @return a `std::string` that contains represents the line gotten from
     *         the given @p istream input-stream.
     * @see Constants::NEW_LINE
     * @see getLineUntilEndingChar(std::istream &, char)
     */
    static std::string getLine(std::istream &istream) {
        return getLineUntilEndingChar(istream, Constants::NEW_LINE);
    }

  private:
    /**
     * @brief Gets a whole line from an input-stream - from the start of the
     *        line until the @p endingChar char (not included).
     * @param istream the input-stream to get a line from.
     * @return a `std::string` that contains represents the line gotten from
     *         the given @p istream input-stream.
     */
    static std::string getLineUntilEndingChar(std::istream &istream,
                                              char          endingChar) {
        char        input;
        std::string returnValue;

        // Ignore the first char if it is an `endingChar`.
        istream.get(input);
        if (input != endingChar) { istream.unget(); }

        istream.get(input);
        while (input != endingChar) {
            returnValue += input;
            istream.get(input);
        }
        return returnValue;
    }

  private:
    /**
     * @brief splits a given string by a given delimiter.
     *
     * @note requires `#include <cstring>`.
     * @param str the `std::string` to split by the given @p delimiter.
     * @param delimiter a `std::string` that the given @p str will be
     *                  split by.
     * @param outputSplitArray an array of `std::string`s after split.
     * @param outputSplitArraySize the size of the @p outputSplitArray.
     * @todo delete[] @p outputSplitArray.
     */
    static void split(std::string &str, char delimiter,
                      std::string *&outputSplitArray,
                      int &         outputSplitArraySize) {
        outputSplitArraySize =
                countNumberOfDelimiterInString(str, delimiter) + 1;
        outputSplitArray = new std::string[outputSplitArraySize];

        // Create a deep-copy of `str` for using `strtok`.
        std::string strCopy = str;
        char *      token   = std::strtok((char *) strCopy.c_str(), &delimiter);
        for (int i = 0; (i < outputSplitArraySize) && (token); i++) {
            outputSplitArray[i] = token;
            token               = std::strtok(nullptr, &delimiter);
        }
    }

  private:
    static int countNumberOfDelimiterInString(std::string &str,
                                              char         delimiter) {
        int returnValue = 0;
        for (long unsigned int i = 1; i < str.length(); i++) {
            if ((str[i] == delimiter) && (str[i - 1] != delimiter)) {
                returnValue++;
            }
        }
        return returnValue;
    }
};

#endif // INPUT_H
