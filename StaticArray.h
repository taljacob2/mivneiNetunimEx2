
#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include "BaseArray.h"
#include <ostream>

/**
 * For example:
 * How to use this class:
 * All the below examples work perfectly, and you don't need to ever again
 * use the `delete` keyword.
 *
 * @code
 *           auto testArray = StaticArray<std::string>(1);
 *
 *           // Example: "inline rvalue"
 *           testArray.push(getLine(std::cin));
 *           std::cout << testArray << std::endl;
 *
 *           // Example: "normal lvalue"
 *           std::string str = getLine(std::cin);
 *           testArray.push(&str);
 *           std::cout << testArray << std::endl;
 *
 *           // Example: "inline anonymous heap allocated lvalue"
 *           testArray.push(new std::string(getLine(std::cin)), true);
 *           std::cout << testArray << std::endl;
 *
 *           // Example: "external heap allocated lvalue"
 *           std::string *str = new std::string(getLine(std::cin));
 *           testArray.push(str);
 *           std::cout << testArray << std::endl;
 *           delete str;
 * @endcode
 *
 * @note DEVELOPER NOTE: You must ensure that the `BaseArray<E>::_physicalSize`
 *       is larger than the logical-`size` by `1` at all times.
 * @tparam E the type of `element` in the array.
 * @version 1.0.3
 */
template<typename E> class StaticArray : public BaseArray<E> {

  protected:
    static constexpr char *IS_EMPTY_MESSAGE =
            (char *) "StaticArray: array is empty.";

  protected:
    static constexpr char *IS_FULL_MESSAGE =
            (char *) "StaticArray: array is full.";

  public:
    explicit StaticArray(unsigned long size) : BaseArray<E>(size) {}

  protected:
    unsigned long _logicalSize = 0;

  protected:
    unsigned long getLogicalSize() const { return _logicalSize; }

  public:
    void setElement(E *element, unsigned long index,
                    bool isAnonymous = false) override {
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        // May throw here.
        BaseArray<E>::setElement(element, index, isAnonymous);
        _logicalSize++;
    }

  public:
    void setElement(E &&element, unsigned long index) override {
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        BaseArray<E>::setElement((E &&) element, index); // May throw here.
        _logicalSize++;
    }

  public:
    E *getElement(unsigned long index) override {
        if (!_logicalSize) { throw std::runtime_error(IS_EMPTY_MESSAGE); }
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        return BaseArray<E>::getElement(index);
    }

  public:
    void push(E *element, bool isAnonymous = false) {
        setElement(element, _logicalSize, isAnonymous); // May throw here.
    }

  public:
    void push(E &&element) {
        setElement((E &&) element, _logicalSize); // May throw here.
    }

  public:
    E *peek() {
        if (!_logicalSize) { throw std::runtime_error(IS_EMPTY_MESSAGE); }

        // May throw here.
        E *returnValue = this->getElement(_logicalSize - 1);

        return returnValue;
    }

  public:
    E *pop() {
        E *lastElement = peek(); // Get last element. May throw here.

        this->deleteElement(_logicalSize - 1); // Delete last element.
        _logicalSize--;

        return lastElement;
    }

  public:
    StaticArray<E> &forEach(const std::function<void(E *)> &callBack,
                            unsigned long sizeToIterateOnTo = 0) override {
        return BaseArray<E>::forEach(callBack, _logicalSize);
    }

  public:
    StaticArray<E> &filter(const std::function<bool(E *)> &predicate,
                           unsigned long sizeToIterateOnTo = 0) override {
        return BaseArray<E>::filter(predicate, _logicalSize);
    }

    /**
     * @note DEVELOPER NOTE: "map" is not `virtual`.
     */
    template<typename E2>
    StaticArray<E2> map(const std::function<E2 *(E *)> &mapFunction,
                        bool                            isAnonymous = false,
                        unsigned long                   sizeToIterateOnTo = 0) {
        return this->map(mapFunction, isAnonymous, _logicalSize);
    }

    /**
     * @note DEVELOPER NOTE: "map" is not `virtual`.
     */
    template<typename E2>
    BaseArray<E2> map(const std::function<E2 && (E *)> &mapFunction,
                      unsigned long                     sizeToIterateOnTo = 0) {
        return this->map(mapFunction, _logicalSize);
    }

  protected:
    bool isOutOfRange(unsigned long index) override {
        return BaseArray<E>::isOutOfRangeStatic(index, _logicalSize);
    }

  public:
    friend std::ostream &operator<<(std::ostream &     os,
                                    const StaticArray &array) {
        array.print(os, array, array._logicalSize);
        return os;
    }
};

#endif // STATIC_ARRAY_H
