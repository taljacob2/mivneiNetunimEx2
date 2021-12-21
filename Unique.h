
#ifndef UNIQUE_H
#define UNIQUE_H

#include "Object.h"
#include <iostream>

template<typename E> class Unique : public Object {

  protected:
    E *_element = nullptr;

  protected:
    bool _needToDeleteElement = false;

  public:
    explicit Unique(E &&element) {
        _needToDeleteElement = true;
        _element             = new E(element);
    }

  public:
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
        return _element == rhs._element;
    }
    bool operator!=(const Unique &rhs) const { return !(rhs == *this); }

  public:
    bool operator<(const Unique &rhs) const {
        return _element < rhs._element;
    }
    bool operator>(const Unique &rhs) const { return rhs < *this; }
    bool operator<=(const Unique &rhs) const { return !(rhs < *this); }
    bool operator>=(const Unique &rhs) const { return !(*this < rhs); }
};

#endif // UNIQUE_H
