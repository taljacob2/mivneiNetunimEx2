
#ifndef BASE_ARRAY_H
#define BASE_ARRAY_H

#include "Unique.h"
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
 * @version 1.0.1
 */
template<typename E> class BaseArray {

  protected:
    static constexpr char *PHYSICAL_SIZE_MESSAGE =
            (char *) "BaseArray: `physicalSize` must be at least `1`.";

  protected:
    static constexpr char *OUT_OF_RANGE_MESSAGE =
            (char *) "BaseArray: out of range.";

  protected:
    static constexpr char *ELEMENT_IS_NULL_MESSAGE =
            (char *) "BaseArray: Element is `nullptr`.";

  protected:
    Unique<E> **_array = nullptr;

  protected:
    unsigned long _physicalSize = 100;

  protected:
    bool _deleteFromHeapAfterUse = false;

  public:
    bool isDeleteFromHeapAfterUse() const { return _deleteFromHeapAfterUse; }

  public:
    void setDeleteFromHeapAfterUse(bool deleteFromHeapAfterUse) {
        _deleteFromHeapAfterUse = deleteFromHeapAfterUse;
    }

  public:
    unsigned long size() const { return _physicalSize; }

  public:
    explicit BaseArray(unsigned long physicalSize) {
        if (physicalSize < 1) {
            throw std::invalid_argument(PHYSICAL_SIZE_MESSAGE);
        }
        _physicalSize = physicalSize;
        _array        = new Unique<E> *[_physicalSize]();
    }

  public:
    BaseArray(const BaseArray &other) { *this = other; }

  public:
    BaseArray(BaseArray &&other) noexcept { *this = std::move(other); }

  public:
    virtual ~BaseArray() { deleteThis(); }

  protected:
    void deleteThis() {
        for (unsigned long i = 0; i < size(); i++) { delete _array[i]; }
        delete[] _array;
    }

  public:
    virtual E *getElement(unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        E *element = _array[index]->getElement(); // Shallow copy pointer.

        if (_array[index]->isNeedToDeleteElement()) {
            delete _array[index]; // Delete the old unique pointer.
            _array[index] = new Unique<E>(nullptr);
        }

        return element;
    }

  public:
    virtual void setElement(E *element, unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        auto *unique        = new Unique<E>(element);
        this->_array[index] = unique;
    }

  public:
    virtual void setElement(E &&element, unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        auto *unique        = new Unique<E>((E &&) element);
        this->_array[index] = unique;
    }

  public:
    virtual E *deleteElement(unsigned long index) {
        Unique<E> *uniqueDeleted  = _array[index];
        E *        elementDeleted = uniqueDeleted->getElement();
        if (!uniqueDeleted->isNeedToDeleteElement()) {
            uniqueDeleted = nullptr;
        }
        return elementDeleted;
    }

    // FIXME: make virtual // FIXME: change to unique
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
    BaseArray<E> &forEach(const std::function<void(E *)> &callBack) {
        for (unsigned long i = 0; i < _physicalSize; i++) {
            callBack((E *) _array[i]);
        }

        return *this;
    }

    // FIXME: change to unique
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
    BaseArray<E> &filter(const std::function<bool(E *)> &predicate,
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
        for (int i = 0; i < this->_physicalSize; i++) {
            if (predicate(getElement(i))) { newArraySize++; }
        }

        E **newArray = new E *[newArraySize];
        for (unsigned long i = 0; i < _physicalSize; i++) {
            E &element = getElement(i);
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
        return *this;
    }

    // FIXME: change to unique
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
    BaseArray<E2> &map(const std::function<E2 &(const E &)> &mapFunction,
                       bool deleteOriginalArrayElements = false) {

        /*
         * Must iterate over the array once.
         * The `for-loop`'s content is:
         * - `insert` the new mapped-elements to `newArray`.
         * - `delete` elements from `_array`.
         */

        BaseArray<E2> e2Array(_physicalSize);
        for (unsigned long i = 0; i < _physicalSize; i++) {
            E &element = getElement(i);
            e2Array.setElement(mapFunction(element));

            /**
             * This element should be filtered out from the array.
             * `delete` the element if the user required to.
             */
            if (deleteOriginalArrayElements) { delete element; }
        }

        deleteThis();
        return e2Array;
    }

    // FIXME: change to unique
  public:
    /**
     * @brief Shallow-Copying `this` object.
     * @return a shallow-copy of `this` object.
     */
    BaseArray<E> &copy() {
        BaseArray<E> copyArray(_physicalSize);
        for (unsigned long i = 0; i < _physicalSize; i++) {
            copyArray._array[i] = _array[i]; // Shallow-Copy the reference.
        }

        return copyArray;
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

  protected:
    virtual bool isOutOfRange(unsigned long index) {

        // `_physicalSize` *must* be at least 1.
        return !((0 <= index) && (index < _physicalSize));
    }

  protected:
    void assertNotNull(E *element) {
        if (element == nullptr) {
            std::string msg = (char *) ELEMENT_IS_NULL_MESSAGE;
            std::string msg2 =
                    (char *) "Use the `getElement(unsigned long)`"
                             " method to retrieve it, instead of this"
                             " method.";
            throw std::runtime_error(msg + " " + msg2);
        }
    }

  public:
    BaseArray &operator=(const BaseArray &other) {

        // Guard self assignment
        if (this == &other) { return *this; }

        // Free the existing resource.
        deleteThis();

        // Copy the data pointer and its size from the source object.
        this->_physicalSize = other._physicalSize;
        for (unsigned long i = 0; i < _physicalSize; i++) {
            _array[i] = other._array[i]; // Shallow-Copy the reference.
        }

        return *this;
    }

  public:
    BaseArray &operator=(BaseArray &&other) noexcept {

        // Guard self assignment
        if (this != &other) {

            // Free the existing resource.
            deleteThis();

            // Copy the data pointer and its size from the source object.
            this->_physicalSize = other._physicalSize;
            for (unsigned long i = 0; i < _physicalSize; i++) {
                _array[i] = other._array[i]; // Shallow-Copy the reference.
            }

            /*
             * Release the data pointer from the source object so that
             * the destructor does not free the memory multiple times.
             */
            other._physicalSize = 0;
            other._array        = nullptr;
        }
        return *this;
    }

  public:
    friend std::ostream &operator<<(std::ostream &os, const BaseArray &array) {
        return print(os, array);
    }

  private:
    /**
     * @note This method is `nullptr` resistant - Instead of crashing, it prints
     *       "nullptr".
     */
    static std::ostream &print(std::ostream &os, const BaseArray &array) {
        os << '[';
        if (array._physicalSize) {
            printElement(os, (array._array[0])->getElement());
        }
        for (unsigned long i = 1; i < array._physicalSize; i++) {
            os << " ,";
            printElement(os, (array._array[0])->getElement());
        }
        os << ']';
        return os;
    }

  protected:
    static void printElement(std::ostream &os, E *element) {
        if (element == nullptr) {
            os << "nullptr";
        } else {
            os << *element;
        }
    }
};

#endif // BASE_ARRAY_H
