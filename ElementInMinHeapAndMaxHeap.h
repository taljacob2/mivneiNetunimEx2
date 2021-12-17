
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
    E *_element = nullptr;

  protected:
    long int _maxHeapIndex = 0;

  protected:
    long int _minHeapIndex = 0;

  public:
    explicit ElementInMinHeapAndMaxHeap(E *element) : _element(element) {}

  public:
    virtual ~ElementInMinHeapAndMaxHeap() = default;

  public:
    E *getElement() const { return _element; }

  public:
    long getMaxHeapIndex() const { return _maxHeapIndex; }

  public:
    void setMaxHeapIndex(long maxHeapIndex) { _maxHeapIndex = maxHeapIndex; }

  public:
    long getMinHeapIndex() const { return _minHeapIndex; }

  public:
    void setMinHeapIndex(long minHeapIndex) { _minHeapIndex = minHeapIndex; }

  public:
    bool operator<(const ElementInMinHeapAndMaxHeap &rhs) const {
        return _element < rhs._element;
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
        return _element == rhs._element;
    }
    bool operator!=(const ElementInMinHeapAndMaxHeap &rhs) const {
        return !(rhs == *this);
    }

  public:
    friend std::ostream &
    operator<<(std::ostream &                    os,
               const ElementInMinHeapAndMaxHeap &entryInMinHeapAndMaxHeap) {
        os << entryInMinHeapAndMaxHeap._element;
        return os;
    }
};

#endif // ELEMENT_IN_MIN_HEAP_AND_MAX_HEAP_H
