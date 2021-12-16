
#ifndef ARRAY_H
#define ARRAY_H

#include <functional>
#include <iostream>

/**
 * @brief This class wraps an array of a *constant size*, and `delete`s it on
 *        destruction.
 *
 * Use this class instead of the old fashioned way:
 * @code
 * CLASS_TYPE *classTypeArray = new CLASS_TYPE [someDynamicSize];
 * @endcode
 * to *avoid* concerning yourself with the need to `delete` the allocated
 * array afterwards.
 * @tparam E the type of `element` in the array.
 *
 * @version 1.0
 */
template<typename E> class Array {

  private:
    E **_array = nullptr;

  private:
    unsigned long _size = 0;

  public:
    unsigned long getSize() const { return _size; }

  public:
    explicit Array(unsigned long size) {
        _size  = size;
        _array = new E *[_size];
    }

  public:
    Array(Array &copyArray) { this = copyArray.copy(); }

  public:
    virtual ~Array() { deleteThis(); }

  private:
    void deleteThis() { delete[] _array; }

  public:
    E &operator[](unsigned long i) { return _array[i]; }

  public:
    const E &operator[](unsigned long i) const { return _array[i]; }

  public:
    Array<E> &forEach(const std::function<void(E &)> &callBack) {
        for (int i = 0; i < _size; i++) { callBack(_array[i]); }

        return this;
    }

  public:
    /**
     * @brief This method will *filter* out from the array the elements that
     *        do not return `true` the given @p predicate function.
     *
     * @param predicate a `bool` function such that only the elements that
     *                  are returning `true` to this @p predicate function
     *                  would remain in the array. The others would be
     *                  `deleted` from the array. And based on the given @p
     *                  deleteFilteredElements parameter, they may also be
     *                  `deleted` from the heap.
     *                  @note You are suggested to use a "lambda" function
     *                        for this @p predicate - so that it will be quicker
     *                        for you to use this method.
     * @param deleteFilteredElements set this parameter to `true` if the
     *                               elements in `this` array are allocated
     *                               via the heap, so that this method will
     *                               `delete` them if they are filtered out.
     *                               Else, it means you allocated the elements
     *                               locally, and in this case set this
     *                               parameter to `false`.
     * @return `this` object. So that you may "chain" this method with another.
     */
    Array<E> &filter(const std::function<bool(E &)> &predicate,
                     bool deleteFilteredElements = false) {
        unsigned long newArraySize = 0;

        /*
         * Must iterate over the array twice.
         * The `for-loops`' content is:
         * 1. Count the `newArraySize`.
         * 2. - `insert` the elements that are `true` with the predicate
         *      given to `newArray`.
         *    - `delete` elements that are `false` with the predicate
         *      given from `_array`.
         */
        forEach([&newArraySize, predicate](E &e) {
            if (predicate(e)) { newArraySize++; }
        });

        E **newArray = new E *[newArraySize];
        for (int i = 0; i < _size; i++) {
            E &element = _array[i];
            if (predicate(element)) {
                newArray[i] = element;
                continue;
            }

            /**
             * This element should be filtered out from the array.
             * `delete` the element if the user required to.
             */
            if (deleteFilteredElements) { delete element; }
        }

        update(newArraySize, newArray);
        return this;
    }

  public:
    /**
     * @brief This method will *map* out another `Array` from `this` array.
     *
     * @tparam E2 the type of `element`s in the returned `Array`.
     * @param mapFunction a `E2`-return-type function that each element in
     *                    the array will be invoked with, and *maps* that element
     *                    to another object of type `E2`.
     *                    Afterwards, the elements in `this` array would be
     *                    `deleted` from the array. And based on the given @p
     *                    deleteFilteredElements parameter,
     *                    they may also be `deleted` from the heap.
     *                    @note You are suggested to use a "lambda" function
     *                          for this @p mapFunction - so that it will be
     *                          quicker for you to use this method.
     * @param deleteFilteredElements set this parameter to `true` if the
     *                               elements in `this` array are allocated
     *                               via the heap, so that this method will
     *                               `delete` them if they are filtered out.
     *                               Else, it means you allocated the elements
     *                               locally, and in this case set this
     *                               parameter to `false`.
     * @return the array of type `E2` mapped by `this` array. This way, you
     *         may also "chain" this method with another.
     */
    template<typename E2>
    Array<E2> &map(const std::function<E2 &(E &)> &mapFunction,
                   bool deleteFilteredElements = false) {

        /*
         * Must iterate over the array once.
         * The `for-loop`'s content is:
         * - `insert` the new mapped-elements to `newArray`.
         * - `delete` elements from `_array`.
         */

        Array<E2> e2Array(_size);
        for (int i = 0; i < _size; i++) {
            E &element = _array[i];
            e2Array[i] = mapFunction(element);

            /**
             * This element should be filtered out from the array.
             * `delete` the element if the user required to.
             */
            if (deleteFilteredElements) { delete element; }
        }

        deleteThis();
        return e2Array;
    }

  private:
    /**
     * @brief Shallow-Copying `this` object.
     * @return a shallow-copy of `this` object.
     */
    Array<E> copy() {
        Array<E> copyArray(_size);
        for (int i = 0; i < _size; i++) {
            copyArray[i] = _array[i]; // Shallow-Copy the reference.
        }

        return copyArray;
    }

  private:
    /**
     * @brief Update the fields of `this` object.
     * @param newArraySize .
     * @param newArray .
     */
    void update(unsigned long newArraySize, E **newArray) {
        deleteThis();
        _array = newArray;
        _size  = newArraySize;
    }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Array &array) {
        os << '[';
        if (array._size) { os << array[0]; }
        for (int i = 1; i < array._size; i++) { os << " ," << array[i]; }
        os << ']';
        return os;
    }
};

#endif // ARRAY_H
