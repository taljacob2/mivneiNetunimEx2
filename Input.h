
#ifndef INPUT_H
#define INPUT_H

#include "BaseArray.h"
#include "Constants.h"
#include "Unique.h"
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
     * @brief Gets the an _array of tests from the input-stream, and asserts
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
     * @return an _array that each element of it is a line inputted.
     * @todo delete[] testArray.
     */
    static void
    getTestArray(unsigned long &numberOfTestsDeclared) {
        numberOfTestsDeclared = getValidTestArraySize();
    }

  private:
    /**
     * @brief Gets the number of tests for the user to input.
     * @return `numberOfTests` gotten. This value serves as the size of
     *         `testArray` in the system.
     * @throws std::runtime_error in case the size gotten is not a number, or
     *         in case the number gotten is non-positive.
     * @see getTestArray(unsigned long &)
     */
    static unsigned long getValidTestArraySize() {
        std::string numberOfTestsString;
        numberOfTestsString = getLine(std::cin);

        if (!predicateIsStringAnUnsignedNumber(numberOfTestsString)) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        unsigned long numberOfTests = stol(numberOfTestsString);
        if (numberOfTests < 1) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        return numberOfTests;
    }

  private:
    /**
     * @brief Gets all the tests inputted, and places them as elements in
     *        `testArray` with the type of `std::string`s.
     * @param testArray an empty _array of `std::string`s, to be initialized
     *                  with all the tests the user inputted.
     * @return the number of tests inputted.
     */
    static unsigned long
    initializeTestArray(BaseArray<std::string> &testArray) {
        unsigned long numberOfTestsInputted = 0;
        std::string   line;
        while (!((line = getLine(std::cin)).empty())) {
            testArray.setElement((std::string &&) line, numberOfTestsInputted);
            numberOfTestsInputted++;

            // TODO: debug:
            std::cout << "numberOfTestsInputted:" << numberOfTestsInputted
                      << std::endl;
        }

        // TODO: debug:
        std::cout << "done input:" << std::endl;

        // if (numberOfTestsInputted != testArray.size()) {
        //     throw std::runtime_error(Constants::WRONG_INPUT);
        // }

        return numberOfTestsInputted;
    }

  public:
    /**
     * @brief this method returns a test string, which is an element of @p
     *        testArray ( = `testArray[i]`), that is split by a given @p
     *        delimiter char to multiple strings.
     *
     * @param testArray an _array that contains multiple test strings.
     * @param delimiter the delimiter char to split the extracted test with.
     * @param i the index of the current test in the @p testArray given, you
     *          wish to extract.
     * @throws std::runtime_error in case the `testArray[i]` is not valid.
     * @see validateTest(std::string *&, char &, int)
     * @todo delete [] splitArray.
     */
    static BaseArray<std::string> getTest(std::string &testLine, char delimiter,
                                          unsigned long i) {
        try {

            // Split the `testLine` by ' ' delimiter.
            BaseArray<std::string> splitArray = split(testLine, delimiter);

            assertSplit(testLine, splitArray, i);

            return splitArray;
        } catch (std::exception &e) { throw; }
    }

  private:
    static void assertSplit(std::string &           testLine,
                            BaseArray<std::string> &splitArray,
                            unsigned long           i) {

        // Assert first letter.
        assertFirstLetter(testLine, splitArray, i);

        // Assert parameters after first letter.
        if (splitArray.size() > 1) { assertAllowedTwoParameters(splitArray); }
    }

  private:
    static void assertFirstLetter(std::string &           testLine,
                                  BaseArray<std::string> &splitArray,
                                  unsigned long           i) {
        if (i == 0) {
            if ((testLine.length() != 1) && (testLine[0] == FIRST_LETTER)) {
                throw std::runtime_error(Constants::WRONG_INPUT);
            }
        } else {
            if (!predicateIsValidLetter(splitArray.getElement(0)) ||
                testLine[0] == FIRST_LETTER) {
                throw std::runtime_error(Constants::WRONG_INPUT);
            }
        }
    }

  private:
    static void assertAllowedTwoParameters(BaseArray<std::string> &splitArray) {

        // Allow only the letter `ALLOWED_TWO_PARAMETERS_LETTER`.
        if (splitArray.getElement(0).c_str()[0] !=
            ALLOWED_TWO_PARAMETERS_LETTER) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        mergeLastParameterWhenThereAreMoreThanThreeElements(splitArray);

        /*
         * Assert having exactly two parameters after the allowed letter,
         * while allowing the last parameter to contain ' ' chars within it.
         */
        if (splitArray.size() != 3) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }

        // First parameter must be an `int` number.
        if (!predicateIsStringAnInt(splitArray.getElement(1))) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
    }

  private:
    /**
     * @brief If the *last parameter* has the ' ' char within it, merge the
     *        split strings of it to one.
     */
    static void mergeLastParameterWhenThereAreMoreThanThreeElements(
            BaseArray<std::string> &splitArray) {
        if (splitArray.size() > 3) {
            splitArray.mergeElements(2, 3, splitArray.size() - 1,
                                     [&splitArray](auto &s1, auto &s2) {
                                         return s1 + " " + s2;
                                     });
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
     * @param str the `std::string` to check if it represents an `unsigned`
     *            number.
     * @return `true` if the @p str given represents an `unsigned` number.
     *          Else, `false`.
     */
    static bool predicateIsStringAnUnsignedNumber(std::string &str) {
        for (char c : str) {
            if (!(('0' <= c) && (c <= '9'))) { return false; }
        }
        return true;
    }

  private:
    /**
     * @param str the `std::string` to check if it represents an `int`
     *            number.
     * @return `true` if the @p str given represents an `int` number.
     *          Else, `false`.
     */
    static bool predicateIsStringAnInt(std::string &str) {
        if ((!(('0' <= str[0]) && (str[0] <= '9'))) &&
            (!((str[0] == '+') || str[0] == '-'))) {
            return false;
        }
        for (unsigned long int i = 1; i < str.length(); i++) {
            if (!(('0' <= str[i]) && (str[i] <= '9'))) { return false; }
        }
        return true;
    }

  public:
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

  public:
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
        std::string returnValue = (char *) "";

        // Ignore the first char if it is an `endingChar`.

        // TODO: check if can disable
        // istream.get(input);                           // DISABLED
        // if (input != endingChar) { istream.unget(); } // DISABLED

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
     * @param str the `std::string` to split by the given @p delimiter.
     * @param delimiter a `std::string` that the given @p str will be
     *                  split by.
     * @param outputSplitArray an _array of `std::string`s after split.
     * @param outputSplitArraySize the size of the @p outputSplitArray.
     * @todo delete[] @p outputSplitArray.
     */
    static BaseArray<std::string> split(std::string &str, char delimiter) {
        BaseArray<std::string> splitArray(
                countNumberOfDelimiterInString(str, delimiter) + 1);
        splitPrivate(str, delimiter, splitArray);
        return splitArray;
    }

  private:
    /**
     * @see split(std::string &, char, std::string *&, int &)
     */
    static void splitPrivate(std::string &stringToSplit, char delimiter,
                             BaseArray<std::string> &splitArray) {
        long unsigned int stringToSplitIndex = 1;
        long unsigned int splitArrayIndex    = 0;
        long unsigned int startIndex         = 0;
        for (; stringToSplitIndex < stringToSplit.length();
             stringToSplitIndex++) {
            if ((stringToSplit[stringToSplitIndex] == delimiter) &&
                (stringToSplit[stringToSplitIndex - 1] != delimiter)) {
                splitArray.setElement(
                        stringToSplit.substr(startIndex,
                                             stringToSplitIndex - startIndex),
                        splitArrayIndex); // TODO: NOTE: "rvalue" "set"
                splitArrayIndex++;
                startIndex = stringToSplitIndex + 1;
            }
        }

        // There is no delimiter after the last string, so create a special case
        if (stringToSplit[stringToSplitIndex - 1] != delimiter) {
            splitArray.setElement(
                    stringToSplit.substr(startIndex,
                                         stringToSplitIndex - startIndex),
                    splitArrayIndex);
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
