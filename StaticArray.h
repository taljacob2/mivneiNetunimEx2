
#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include "ArrayBase.h"

/**
 * @tparam E the type of `element` in the array.
 * @version 1.0
 */
template<typename E> class StaticArray : public ArrayBase<E> {

  protected:
    static constexpr char *IS_EMPTY_MESSAGE =
            (char *) "StaticArray: array is empty.";

  protected:
    static constexpr char *IS_FULL_MESSAGE =
            (char *) "StaticArray: array is full.";

  public:
    explicit StaticArray(unsigned long physicalSize) : ArrayBase<E>(physicalSize) {}

  protected:
    unsigned long _logicalSize = 0;

  public:
    void push(E &element) {
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        // May throw here.
        this->setElement(element, _logicalSize);
        _logicalSize++;
    }

  public:
    void pushNull() {
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        // May throw here.
        this->setNull(_logicalSize);
        _logicalSize++;
    }

  public:
    E &pop() {
        if (!_logicalSize) { throw std::runtime_error(IS_EMPTY_MESSAGE); }

        // May throw here.
        E& returnValue = this->getElement(_logicalSize - 1);
        _logicalSize--;

        return returnValue;
    }

  public:
    E *popAsPointer() {
        if (!_logicalSize) { throw std::runtime_error(IS_EMPTY_MESSAGE); }

        // May throw here.
        E *returnValue = this->getElementAsPointer(_logicalSize - 1);
        _logicalSize--;

        return this->getElementAsPointer(returnValue);
    }
};

#endif // STATIC_ARRAY_H
