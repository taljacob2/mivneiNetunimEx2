
#ifndef ELEMENT_IN_MIN_HEAP_AND_MAX_HEAP_H
#define ELEMENT_IN_MIN_HEAP_AND_MAX_HEAP_H

#include <ostream>

/**
 * @brief This class is designed to wrap an `Element` with two indexes.
 *        @li one index tells at which index this `element` is placed on
 *        a minimum-heap.
 *        @li the other index tells at which index this `element` is placed on
 *        a maximum-heap.
 * @tparam E the type of `element`, that *must* be *comparable* to other
 *         `elements`.
 */
template<typename E> class ElementInMinHeapAndMaxHeap {

  protected:
    Unique<E> *_uniqueElement = nullptr;

  protected:
    long int _maxHeapIndex = 0;

  protected:
    long int _minHeapIndex = 0;

  public:
    explicit ElementInMinHeapAndMaxHeap(E *element) {
        _uniqueElement = new Unique<E>(element);
    }

  public:
    explicit ElementInMinHeapAndMaxHeap(E &&element) {
        _uniqueElement = new Unique<E>((E &&) element);
    }

  public:
    virtual ~ElementInMinHeapAndMaxHeap() {

        // TODO: debug:
        std::cout << "DELETING EWRAPPER" << *this << std::endl;

        delete _uniqueElement;
    }

  public:
    Unique<E> *getUniqueElement() const { return _uniqueElement; }

  public:
    void setUniqueElement(Unique<E> *uniqueElement) {
        _uniqueElement = uniqueElement;
    }

  public:
    long getMaxHeapIndex() const { return _maxHeapIndex; }

  public:
    void setMaxHeapIndex(long maxHeapIndex) { _maxHeapIndex = maxHeapIndex; }

  public:
    long getMinHeapIndex() const { return _minHeapIndex; }

  public:
    void setMinHeapIndex(long minHeapIndex) { _minHeapIndex = minHeapIndex; }

  public:
    friend std::ostream &
    operator<<(std::ostream &                    os,
               const ElementInMinHeapAndMaxHeap &entryInMinHeapAndMaxHeap) {
        os << *(entryInMinHeapAndMaxHeap._uniqueElement);
        return os;
    }

  public:
    bool operator<(const ElementInMinHeapAndMaxHeap &rhs) const {
        return _uniqueElement < rhs._uniqueElement;
    }
    bool operator>(const ElementInMinHeapAndMaxHeap &rhs) const {
        return rhs < *this;
    }
    bool operator<=(const ElementInMinHeapAndMaxHeap &rhs) const {
        return !(rhs < *this);
    }
    bool operator>=(const ElementInMinHeapAndMaxHeap &rhs) const {
        return !(*this < rhs);
    }

  public:
    bool operator==(const ElementInMinHeapAndMaxHeap &rhs) const {
        return _uniqueElement == rhs._uniqueElement;
    }
    bool operator!=(const ElementInMinHeapAndMaxHeap &rhs) const {
        return !(rhs == *this);
    }
};

#endif // ELEMENT_IN_MIN_HEAP_AND_MAX_HEAP_H
