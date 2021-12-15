
#ifndef MY_ALGORITHMS_H
#define MY_ALGORITHMS_H


#include "Constants.h"
#include <exception>
#include <iostream>


/**
 * @brief this class bundles together all the generic algorithms
 *        methods in the program.
 */
class my_algorithms {

  public:
    /**
     * @brief Compares two elements pointed out from two pointers, by their
     *        given indexes, and returns the index to the pointer that points
     *        to the larger element out of them.
     *
     * The method ensures safety:
     * @li The method makes sure to ensure that the @p indexToElement1 and @p
     * indexToElement2 provided are not out of range.
     * @li The method makes sure to ensure that the elements are not
     * `nullptr`, and if they are `nullptr`, the method knows how to handle
     * them.
     * @note if element is a `nullptr`, prioritize to return the index of the
     *       *other* element given.
     *       If both element are `nullptr`, return the index of the *first*
     *       element.
     * @attention if @p indexToElement2 is out fo range, but @p
     *            indexToElement1 is not out of range, the method returns the
     *            @p indexToElement1.
     * @param array an _array of pointers to elements.
     * @param indexToElement1 index of pointer to first element to compare.
     * @param indexToElement2 index of pointer to second element to compare.
     * @return the index of the pointer that points to the larger element.
     * @throws std::out_of_range in case *both* of the indexes
     *         @p indexToElement1 and @p indexToElement2 provided are
     *         out of range.
     */
    template<class T>
    static long int max(T **array, long int size, long int indexToElement1,
                        long int indexToElement2) {
        if (((indexToElement2 < size) && (0 <= indexToElement2)) &&
            ((indexToElement1 < size) && (0 <= indexToElement1))) {

            /*
             * If `indexToElement2` is not out-of-range.
             * and `indexToElement1` is not out-of-range.
             */
            if (array[indexToElement2] == nullptr) {
                return indexToElement1;
            } else if (array[indexToElement2] != nullptr) {
                if (array[indexToElement1] == nullptr) {
                    return indexToElement2;
                } else {

                    // Both elements are not nullptr. Compare regularly.
                    return (*array[indexToElement1]) > (*array[indexToElement2])
                                   ? indexToElement1
                                   : indexToElement2;
                }
            }
        } else if ((indexToElement1 < size) && (0 <= indexToElement1)) {

            /* If `indexToElement1` is not out-of-range. */
            return indexToElement1;
        }

        /*
         * Both `indexToElement1` and `indexToElement2` are out-of-range.
         * Throw a message.
         */
        // std::string message;
        // message.append("Both of the indexes provided are out of range. "
        //                "There are ");
        // message.append(std::to_string(size));
        // message.append(" elements in the _array.\n");

        throw std::out_of_range(Constants::WRONG_INPUT);
    }

  public:
    /**
     * @brief Compares two elements pointed out from two pointers, by their
     *        given indexes, and returns the index to the pointer that points
     *        to the smaller element out of them.
     *
     * The method ensures safety:
     * @li The method makes sure to ensure that the @p indexToElement1 and @p
     * indexToElement2 provided are not out of range.
     * @li The method makes sure to ensure that the elements are not
     * `nullptr`, and if they are `nullptr`, the method knows how to handle
     * them.
     * @note if element is a `nullptr`, prioritize to return the index of the
     *       *other* element given.
     *       If both element are `nullptr`, return the index of the *first*
     *       element.
     * @attention if @p indexToElement2 is out fo range, but @p
     *            indexToElement1 is not out of range, the method returns the
     *            @p indexToElement1.
     * @param array an _array of pointers to elements.
     * @param indexToElement1 index of pointer to first element to compare.
     * @param indexToElement2 index of pointer to second element to compare.
     * @return the index of the pointer that points to the smaller element.
     * @throws std::out_of_range in case *both* of the indexes
     *         @p indexToElement1 and @p indexToElement2 provided are
     *         out of range.
     */
    template<class T>
    static long int min(T **array, long int size, long int indexToElement1,
                        long int indexToElement2) {
        if (((indexToElement2 < size) && (0 <= indexToElement2)) &&
            ((indexToElement1 < size) && (0 <= indexToElement1))) {

            /*
             * If `indexToElement2` is not out-of-range.
             * and `indexToElement1` is not out-of-range.
             */
            if (array[indexToElement2] == nullptr) {
                return indexToElement1;
            } else if (array[indexToElement2] != nullptr) {
                if (array[indexToElement1] == nullptr) {
                    return indexToElement2;
                } else {

                    // Both elements are not nullptr. Compare regularly.
                    return (*array[indexToElement1]) < (*array[indexToElement2])
                                   ? indexToElement1
                                   : indexToElement2;
                }
            }
        } else if ((indexToElement1 < size) && (0 <= indexToElement1)) {

            /* If `indexToElement1` is not out-of-range. */
            return indexToElement1;
        }

        /*
         * Both `indexToElement1` and `indexToElement2` are out-of-range.
         * Throw a message.
         */
        // std::string message;
        // message.append("Both of the indexes provided are out of range. "
        //                "There are ");
        // message.append(std::to_string(size));
        // message.append(" elements in the _array.\n");

        throw std::out_of_range(Constants::WRONG_INPUT);
    }

  public:
    /**
     * @brief generic `swap` algorithm of two elements in an _array.
     *
     * @tparam T elements to be swapped.
     * @param array the _array which contains the elements.
     * @param index1 the first element index to be swapped.
     * @param index2 the second element index to be swapped.
     */
    template<class T>
    static void swap(T *array, long int index1, long int index2) {
        T tmp         = array[index1];
        array[index1] = array[index2];
        array[index2] = tmp;
    }

  public:
    /**
     * @brief generic `swap` algorithm of two elements.
     *
     * @tparam T elements to be swapped.
     * @param element1 first element.
     * @param element2 second element.
     */
    template<class T> static void swap(T &element1, T &element2) {
        T tmp    = element1;
        element1 = element2;
        element2 = tmp;
    }

};

#endif // MY_ALGORITHMS_H
