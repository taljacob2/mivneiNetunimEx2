
#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include "BaseArray.h"

/**
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
    explicit StaticArray(unsigned long physicalSize)
            : BaseArray<E>(physicalSize) {}

  protected:
    unsigned long _logicalSize = 0;

  public:
    unsigned long getLogicalSize() const { return _logicalSize; }

  public:
    void push(E *element) {
        if (_logicalSize == this->_physicalSize) {
            throw std::runtime_error(IS_FULL_MESSAGE);
        }

        // May throw here.
        this->setElement(element, _logicalSize);
        _logicalSize++;
    }

  public:
    E *pop() {
        if (!_logicalSize) { throw std::runtime_error(IS_EMPTY_MESSAGE); }

        // May throw here.
        E *returnValue = this->getElement(_logicalSize - 1);
        _logicalSize--;

        return this->getElement(returnValue);
    }
};

#endif // STATIC_ARRAY_H
