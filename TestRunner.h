
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "Entry.h"
#include "Input.h"
#include "PriorityQueueKv.h"
#include <string>

/**
 * @brief This class bundles all the requests to receive inputs from the
 *        user, and run them. Each input received is referred as a "test".
 *        Each "test" needs to be run.
 */
class TestRunner {

  public:
    static void getTestArrayAndRunAllTests() {
        unsigned long numberOfTestsDeclared =
                Input::getValidNumberOfTestsDeclared();
        runAllTests(numberOfTestsDeclared);
    }

  private:
    /**
     * @brief Gets the "tests" from input-stream, run the "test" while
     *        asserting the amount of them via the declaration by the user
     *        received as @p numberOfTestsDeclared.
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
     * @param numberOfTestsDeclared the amount of "tests" declared by the
     *                              user, received before calling this function.
     */
    static void runAllTests(unsigned long &numberOfTestsDeclared) {

        // Polymorph with adt
        PriorityQueueKv<int, std::string> priorityQueueKv;
        auto &                            priorityQueueKvAdt =
                (PriorityQueueKvAdt<int, std::string> &) priorityQueueKv;

        /*
         * IMPORTANT: the below loop ends only when the user inputs another
         * whole `\n` line - As said in the "mama" forum at:
         * https://mama.mta.ac.il/mod/forum/discuss.php?d=5015.
         */
        unsigned long i = 0;
        std::string   line;
        for (; !((line = Input::getLine(std::cin)).empty()); i++) {
            if (i >= numberOfTestsDeclared) {

                /*
                 * `i` is larger than `numberOfTestsDeclared`.
                 * The actual number-of-tests-inputted is not the same as the
                 * user has declared in the first place.
                 */
                throw std::runtime_error(Constants::WRONG_INPUT);
            }

            BaseArray<std::string> test = Input::getTest(line, ' ', i);
            runTest<int, std::string>(test, priorityQueueKvAdt);
        }

        if (i != numberOfTestsDeclared) {

            /*
             * `i` is smaller than `numberOfTestsDeclared`.
             * The actual number-of-tests-inputted is not the same as the
             * user has declared in the first place.
             */
            throw std::runtime_error(Constants::WRONG_INPUT);
        }
    }

  private:
    template<typename K, typename V>
    static void runTest(BaseArray<std::string> &  test,
                        PriorityQueueKvAdt<K, V> &priorityQueueKvAdt) {
        invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
                test, priorityQueueKvAdt);
    }

  private:
    static void invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
            BaseArray<std::string> &              test,
            PriorityQueueKvAdt<int, std::string> &priorityQueueKvAdt) {
        try {
            char methodLetterToInvokeInPriorityQueue = test.getElement(0)[0];
            if (methodLetterToInvokeInPriorityQueue == 'a') {
                std::cout << priorityQueueKvAdt.max() << std::endl;
            } else if (methodLetterToInvokeInPriorityQueue == 'b') {
                std::cout << priorityQueueKvAdt.deleteMax() << std::endl;
            } else if (methodLetterToInvokeInPriorityQueue == 'c') {
                std::cout << priorityQueueKvAdt.min() << std::endl;
            } else if (methodLetterToInvokeInPriorityQueue == 'd') {
                std::cout << priorityQueueKvAdt.deleteMin() << std::endl;
            } else if (methodLetterToInvokeInPriorityQueue == 'e') {
                priorityQueueKvAdt.createEmpty();
            } else if (methodLetterToInvokeInPriorityQueue == 'f') {
                priorityQueueKvAdt.insert(stoi(test.getElement(1)),
                                          test.getElement(2));
            } else if (methodLetterToInvokeInPriorityQueue == 'g') {
                std::cout << priorityQueueKvAdt.median() << std::endl;
            }
        } catch (std::exception &e) { throw; }
    }
};

#endif // TEST_RUNNER_H
