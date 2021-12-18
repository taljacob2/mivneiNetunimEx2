
#ifndef UNIQUE_H
#define UNIQUE_H

template<typename E> class Unique {

  protected:
    E *_element = nullptr;

  public:
    explicit Unique(E &&element) { _element = new E(element); }

  public:
    virtual ~Unique() {

        // TODO: debug print
        std::cout << "unique is dead" << std::endl;

        // delete _element;
    }

  public:
    E *getElement() const { return _element; }

  public:
    /**
     * Allow *implicit* conversions.
     * @return the element instance.
     */
    operator E() const { return *_element; }
};

#endif // UNIQUE_H
