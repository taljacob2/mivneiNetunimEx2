
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
     * @brief Gets the an array of tests from the input-stream, and asserts
     *        only its size validity.
     *
     * For example:
     * a valid input would be:
     * @code
     * 6
     * e
     * f 3 hi
     * f 2 why
     * f 9 bye
     * f 7 day hello hey
     * g
     * @endcode
     *
     * @return an array that each element of it is a line inputted.
     * @todo delete[] testArray.
     */
    static std::string *getTestArray(int &testArraySize) {
        testArraySize   = getValidTestArraySize();
        auto *testArray = new std::string[testArraySize];
        initializeTestArray(testArray, testArraySize);
        // validateTestArray(testArray, testArraySize);
        return testArray;
    }

  private:
    /**
     * @brief Gets the number of tests for the user to input.
     * @return `numberOfTests` gotten. This value serves as the size of
     *         `testArray` in the system.
     * @throws std::runtime_error in case the size gotten is not a number, or
     *         in case the number gotten is non-positive.
     * @see getTestArray(int &)
     */
    static int getValidTestArraySize() {
        std::string numberOfTestsString;
        std::cin >> numberOfTestsString;

        if (!predicateIsStringAnInt(numberOfTestsString)) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        int numberOfTestsInt = stoi(numberOfTestsString);
        if (numberOfTestsInt < 1) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        return numberOfTestsInt;
    }

  private:
    /**
     * @brief Gets all the tests inputted, and places them as elements in
     *        `testArray` with the type of `std::string`s.
     * @param testArray an empty array of `std::string`s, to be initialized
     *                  with all the tests the user inputted.
     * @param testArraySize the size of the given @p testArray.
     */
    static void initializeTestArray(std::string *&testArray,
                                    int           testArraySize) {
        int sizeCounter = 0;

        for (int i = 0; i < testArraySize; i++) {
            testArray[i] = getLine(std::cin);
            sizeCounter++;
        }

        if (sizeCounter != testArraySize) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
    }

  private:
    /**
     * @brief Checks the given @p testArray for its validity.
     * @param testArray the array of strings the user inputted.
     * @param testArraySize the size of the given @p testArray.
     * @throws std::runtime_error in case the given @p testArray is not valid.
     * @see initializeTestArray(std::string *&, int)
     * @see assertSplit(int, int, std::string *&, std::string *&)
     */
    static void validateTestArray(std::string *testArray, int testArraySize) {
        for (int i = 0; i < testArraySize; i++) {
            validateTest(testArray, ' ', i);
        }
    }

  private:
    /**
     * @deprecated this implementation validates a test string (of `testArray[i]`),
     *             without returning it.
     * @throws std::runtime_error in case the `testArray[i]` is not valid.
     * @see getTest(std::string *&, char &, int)
     */
    static void validateTest(std::string *&testArray, char delimiter, int i) {
        std::string *splitArray = nullptr;
        try {

            // Split the current line by ' ' delimiter.
            int splitArraySize = 0;
            split(testArray[i], delimiter, splitArray, splitArraySize);

            assertSplit(i, splitArraySize, testArray, splitArray);

            delete[] splitArray;
        } catch (std::exception &e) {
            delete[] splitArray;
            throw;
        }
    }

  public:
    /**
     * @brief this method validates a test string which is an element of @p
     *        testArray ( = `testArray[i]`), splits it by a given @p delimiter
     *        char and returns the split-array of those strings.
     *
     * @param testArray an array that contains multiple test strings.
     * @param delimiter the delimiter char to split the extracted test with.
     * @param i the index of the current test in the @p testArray given, you
     *          wish to extract.
     * @throws std::runtime_error in case the `testArray[i]` is not valid.
     * @see validateTest(std::string *&, char &, int)
     * @todo delete [] splitArray.
     */
    static std::string *getTest(std::string *&testArray, char delimiter,
                                int i) {
        std::string *splitArray = nullptr;
        try {

            // Split the current line by ' ' delimiter.
            int splitArraySize = 0;
            split(testArray[i], delimiter, splitArray, splitArraySize);

            assertSplit(i, splitArraySize, testArray, splitArray);

            // delete[] splitArray;
            return splitArray;
        } catch (std::exception &e) {
            delete[] splitArray;
            throw;
        }
    }

  private:
    static void assertSplit(int i, int splitArraySize, std::string *&testArray,
                            std::string *&splitArray) {

        // Assert first letter.
        assertFirstLetter(i, testArray, splitArray);

        // Assert parameters after first letter.
        if (splitArraySize > 1) {
            assertAllowedTwoParameters(splitArray, splitArraySize);
        }
    }

  private:
    static void assertFirstLetter(int i, std::string *&testArray,
                                  std::string *&splitArray) {
        if (i == 0) {
            if (!((testArray[i].length() == 1) &&
                  testArray[i][0] == FIRST_LETTER)) {
                throw std::runtime_error(Constants::WRONG_INPUT);
            }
        } else {
            if (!predicateIsValidLetter(splitArray[0]) ||
                testArray[i][0] == FIRST_LETTER) {
                throw std::runtime_error(Constants::WRONG_INPUT);
            }
        }
    }

  private:
    static void assertAllowedTwoParameters(std::string *&splitArray,
                                           int           splitArraySize) {

        // Allow only the letter `ALLOWED_TWO_PARAMETERS_LETTER`.
        if (splitArray[0].c_str()[0] != ALLOWED_TWO_PARAMETERS_LETTER) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        mergeLastParameterWhenThereAreMoreThanThreeElements(splitArray,
                                                            splitArraySize);

        /*
         * Assert having exactly two parameters after the allowed letter,
         * while allowing the last parameter to contain ' ' chars within it.
         */
        if (splitArraySize != 3) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        // First parameter must be an `int` number.
        if (!predicateIsStringAnInt(splitArray[1])) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        // First parameter must be a positive number.
        if (!predicateIsPositive<int>(std::stoi(splitArray[1]))) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
    }

  private:
    /**
     * @brief If the *last parameter* has the ' ' char within it, merge the
     *        split strings of it to one.
     */
    static void mergeLastParameterWhenThereAreMoreThanThreeElements(
            std::string *&splitArray, int &splitArraySize) {
        if (splitArraySize > 3) {
            for (int i = 3; i < splitArraySize; i++) {
                splitArray[2] += splitArray[i];
            }
            splitArraySize = 3;
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
     * @param str the `std::string` to check if it represents an `int` number.
     * @return `true` if the @p str given represents an `int` number. Else,
     *         `false`.
     */
    static bool predicateIsStringAnInt(std::string &str) {
        for (char c : str) {
            if (!(('0' <= c) && (c <= '9'))) { return false; }
        }
        return true;
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

        splitPrivate(str, delimiter, outputSplitArray);
    }

  private:
    /**
     * @see split(std::string &, char, std::string *&, int &)
     */
    static void splitPrivate(std::string &stringToSplit, char delimiter,
                             std::string *&splitArray) {
        long unsigned int stringToSplitIndex = 1;
        long unsigned int splitArrayIndex    = 0;
        long unsigned int startIndex         = 0;
        for (; stringToSplitIndex < stringToSplit.length();
             stringToSplitIndex++) {
            if ((stringToSplit[stringToSplitIndex] == delimiter) &&
                (stringToSplit[stringToSplitIndex - 1] != delimiter)) {
                splitArray[splitArrayIndex] = stringToSplit.substr(
                        startIndex, stringToSplitIndex - startIndex);
                splitArrayIndex++;
                startIndex = stringToSplitIndex + 1;
            }
        }

        // There is no delimiter after the last string, so create a special case
        if (stringToSplit[stringToSplitIndex - 1] != delimiter) {
            splitArray[splitArrayIndex] = stringToSplit.substr(
                    startIndex, stringToSplitIndex - startIndex);
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
