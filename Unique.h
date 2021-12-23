
#ifndef UNIQUE_H
#define UNIQUE_H

#include "Object.h"
#include <iostream>

/**
 * @brief This special class wraps an *any* pointer of an element and
 *        `delete`s it only if it was not allocated with the `new` operator.
 *        This class is able to wrap a given "rvalue" to a pointer, via
 *        heap allocation with the `new` operator - and knows to `delete` it
 *        automatically when gets destructed.
 *        This way, the user may create for example an *array* of `Unique`
 *        elements, so that he will be able to "polymorph" "rvalues" with
 *        "lvalues" together and not be bothered whether each specific
 *        element should be manually `delete`d or not.
 *
 * @note Also, because this class is a sub-class of `Object`, then even if
 *       the user *accidentally* `delete`d a "rvalue" `Unique` - then no
 *       exception will be thrown, and it will be okay memory-wise without
 *       any leaks.
 * @tparam E the type of element to be stored.
 * @see Object
 */
template<typename E> class Unique : public Object {

  protected:
    E *_element = nullptr;

  protected:
    bool _needToDeleteElement = false;

  public:
    /**
     * @param element a "rvalue" element to be stored.
     *                An extra allocation is needed.
     */
    explicit Unique(E &&element) {
        _needToDeleteElement = true;
        _element             = new E(element);
    }

  public:
    /**
     * @param element a "lvalue" element to be stored.
     *                No extra allocation is needed.
     */
    explicit Unique(E *element) : _element(element) {}

  public:
    Unique(const Unique &unique) = default;

  public:
    virtual ~Unique() { deleteThis(); }

  protected:
    void deleteThis() {
        if (_needToDeleteElement) { delete _element; }
    }

  public:
    bool isNeedToDeleteElement() const { return _needToDeleteElement; }

  public:
    /**
     * @warning use with caution.
     * @param needToDeleteElement .
     */
    void setNeedToDeleteElement(bool needToDeleteElement) {
        _needToDeleteElement = needToDeleteElement;
    }

  public:
    E *getElement() const { return _element; }

  public:
    /**
     * Allow *implicit* conversions.
     * @return the element instance.
     */
    explicit operator E() const { return *getElement(); }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Unique &unique) {
        os << (E) unique;
        return os;
    }

  public:
    bool operator==(const Unique &rhs) const {
        return *_element == *(rhs._element); // Compare by value.
    }
    bool operator!=(const Unique &rhs) const { return !(rhs == *this); }

  public:
    bool operator<(const Unique &rhs) const {
        return *_element < *(rhs._element); // Compare by value.
    }
    bool operator>(const Unique &rhs) const { return rhs < *this; }
    bool operator<=(const Unique &rhs) const { return !(rhs < *this); }
    bool operator>=(const Unique &rhs) const { return !(*this < rhs); }
};

#endif // UNIQUE_H
