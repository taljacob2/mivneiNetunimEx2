
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

  protected:
    static constexpr char *PHYSICAL_SIZE_MESSAGE =
            (char *) "Array: `physicalSize` must be at least `1`.";

  protected:
    static constexpr char *OUT_OF_RANGE_MESSAGE =
            (char *) "Array: out of range.";

  protected:
    static constexpr char *ELEMENT_IS_NULL_MESSAGE =
            (char *) "Array: Element is `nullptr`.";

  protected:
    E **_array = nullptr;

  protected:
    unsigned long _physicalSize = 100;

  protected:
    unsigned long getPhysicalSize() const { return _physicalSize; }

  public:
    explicit Array(unsigned long physicalSize) {
        if (physicalSize < 1) {
            throw std::invalid_argument(PHYSICAL_SIZE_MESSAGE);
        }
        _physicalSize = physicalSize;
        _array        = new E *[_physicalSize];
    }

  public:
    Array(Array &copyArray) { this = copyArray.copy(); }

  public:
    virtual ~Array() { deleteThis(); }

  protected:
    void deleteThis() { delete[] _array; }

  public:
    virtual E &getElement(unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        E *pElement = _array[index];

        if (pElement == nullptr) {
            std::string msg = (char *) ELEMENT_IS_NULL_MESSAGE;
            std::string msg2 =
                    (char *) "Use the `getElementAsPointer(unsigned long)`"
                             " method to retrieve it, instead of this"
                             " method.";
            throw std::runtime_error(msg + " " + msg2);
        }

        return *pElement;
    }

  public:
    /**
     * @note In case there are `nullptr`s in the array, you may use this
     *       method to retrieve them without an error.
     */
    virtual E *getElementAsPointer(unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        return _array[index];
    }

  protected:
    virtual bool isOutOfRange(unsigned long index) {

        // `_physicalSize` *must* be at least 1.
        return !((0 <= index) && (index < _physicalSize));
    }

  public:
    /**
     * @brief This method will *invoke* the given @p callBack function on
     *        each element in the array.
     *
     * @param callBack a `void` function that each element in the array will
     *                 be invoked with.
     *                  @note You are suggested to use a "lambda" function
     *                        for this function - so that it will be quicker
     *                        for you to use this method.
     * @return `this` object. So that you may "chain" this method with another.
     */
    Array<E> &forEach(const std::function<void(E &)> &callBack) {
        for (int i = 0; i < _physicalSize; i++) { callBack(_array[i]); }

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
     *                        for this function - so that it will be quicker
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
        for (int i = 0; i < _physicalSize; i++) {
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
     *                    deleteOriginalArrayElements parameter,
     *                    they may also be `deleted` from the heap.
     *                    @note You are suggested to use a "lambda" function
     *                          for this function - so that it will be
     *                          quicker for you to use this method.
     * @param deleteOriginalArrayElements set this parameter to `true` if the
     *                                    elements in `this` array are allocated
     *                                    via the heap, so that this method will
     *                                    `delete` them if they are filtered out.
     *                                    Else, it means you allocated the elements
     *                                    locally, and in this case set this
     *                                    parameter to `false`.
     * @return the array of type `E2` mapped by `this` array. This way, you
     *         may also "chain" this method with another.
     */
    template<typename E2>
    Array<E2> &map(const std::function<E2 &(E &)> &mapFunction,
                   bool deleteOriginalArrayElements = false) {

        /*
         * Must iterate over the array once.
         * The `for-loop`'s content is:
         * - `insert` the new mapped-elements to `newArray`.
         * - `delete` elements from `_array`.
         */

        Array<E2> e2Array(_physicalSize);
        for (int i = 0; i < _physicalSize; i++) {
            E &element = _array[i];
            e2Array[i] = mapFunction(element);

            /**
             * This element should be filtered out from the array.
             * `delete` the element if the user required to.
             */
            if (deleteOriginalArrayElements) { delete element; }
        }

        deleteThis();
        return e2Array;
    }

  protected:
    /**
     * @brief Shallow-Copying `this` object.
     * @return a shallow-copy of `this` object.
     */
    Array<E> copy() {
        Array<E> copyArray(_physicalSize);
        for (int i = 0; i < _physicalSize; i++) {
            copyArray[i] = _array[i]; // Shallow-Copy the reference.
        }

        return copyArray;
    }

  public:
    virtual void setElement(E &element, unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        /*
         * IMPORTANT: Polymorphic use.
         * A "pointer ( = *)" is the parent-class of a "reference ( = &)".
         */
        E *pElement         = &element;
        this->_array[index] = pElement;
    }

  public:
    /**
     * @warning Use with caution.
     */
    virtual void setNull(unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        this->_array[index] = nullptr;
    }

  protected:
    /**
     * @brief Update the fields of `this` object.
     * @param newArraySize .
     * @param newArray .
     */
    void update(unsigned long newArraySize, E **newArray) {
        deleteThis();
        _array        = newArray;
        _physicalSize = newArraySize;
    }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Array &array) {
        return print(os, array);
    }

  private:
    /**
     * @note This method is `nullptr` resistant - Instead of crashing, it prints
     *       "nullptr".
     */
    static std::ostream &print(std::ostream &os, const Array &array) {
        os << '[';
        if (array._physicalSize) { printElement(os, array._array[0]); }
        for (unsigned long i = 1; i < array._physicalSize; i++) {
            os << " ,";
            printElement(os, array._array[i]);
        }
        os << ']';
        return os;
    }

  protected:
    static void printElement(std::ostream &os, const E *element) {
        if (element == nullptr) {
            os << "nullptr";
        } else {
            os << *element;
        }
    }
};

#endif // ARRAY_H
