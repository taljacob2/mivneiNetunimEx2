
#ifndef UNIQUE_H
#define UNIQUE_H

#include <iostream>

template<typename E> class Unique {

  protected:
    E *_element = nullptr;

  protected:
    bool _needToDeleteElement = false;

  public:
    explicit Unique(E &&element) {
        _needToDeleteElement = true;
        _element             = new E(element);

        // TODO: debug
        std::cout << element << std::endl;
    }

  public:
    explicit Unique(E *element) : _element(element) {}

  public:
    virtual ~Unique() { deleteThis(); }

  protected:
    void deleteThis() {
        if (_needToDeleteElement) { delete _element; }
    }

  public:
    bool isNeedToDeleteElement() const { return _needToDeleteElement; }

  public:
    E *getElement() const { return _element; }

  public:
    /**
     * Allow *implicit* conversions.
     * @return the element instance.
     */
    operator E *() const { return _element; }

  public:
    /**
     * Allow *implicit* conversions.
     * @return the element instance.
     */
    operator E() const { return *_element; }
};

#endif // UNIQUE_H
