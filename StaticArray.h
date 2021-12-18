
#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include "BaseArray.h"

/**
 * @note DEVELOPER NOTE: You must ensure that the `BaseArray<E>::_physicalSize`
 *       is larger than the logical-`size` by `1` at all times.
 * @tparam E the type of `element` in the array.
 * @version 1.0.1
 */
template<typename E> class StaticArray : public BaseArray<E> {

  protected:
    static constexpr char *IS_EMPTY_MESSAGE =
            (char *) "StaticArray: array is empty.";

  protected:
    static constexpr char *IS_FULL_MESSAGE =
            (char *) "StaticArray: array is full.";

  public:
    explicit StaticArray(unsigned long size)
        : BaseArray<E>(size + 1), _logicalSize(size) {}

  protected:
    unsigned long _logicalSize = 0;

  public:
    unsigned long size() const { return _logicalSize; }

  public:
    unsigned long getPhysicalSize() = delete; // Disable from use.

  public:
    void setElement(E *element, unsigned long index) override {
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        BaseArray<E>::setElement(element, index); // May throw here.
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
    void push(E *element) {
        setElement(element, _logicalSize); // May throw here.
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
};

#endif // STATIC_ARRAY_H
