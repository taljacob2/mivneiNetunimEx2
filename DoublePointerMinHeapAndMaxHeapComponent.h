
#ifndef DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
#define DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H

#include "MaxHeapWhenAlsoHavingMinHeap.h"
#include "MinHeapWhenAlsoHavingMaxHeap.h"

template<typename E> class DoublePointerMinHeapAndMaxHeapComponent {

  protected:
    MinHeapWhenAlsoHavingMaxHeap<E> minHeap;

  protected:
    MaxHeapWhenAlsoHavingMinHeap<E> maxHeap;

  public:
    DoublePointerMinHeapAndMaxHeapComponent(
            const MinHeapWhenAlsoHavingMaxHeap<E> &minHeap,
            const MaxHeapWhenAlsoHavingMinHeap<E> &maxHeap)
        : minHeap(minHeap), maxHeap(maxHeap) {}

  public:
    virtual ~DoublePointerMinHeapAndMaxHeapComponent() = default;

  public:
    const MinHeapWhenAlsoHavingMaxHeap<E> &getMinHeap() const {
        return minHeap;
    }

  public:
    const MaxHeapWhenAlsoHavingMinHeap<E> &getMaxHeap() const {
        return maxHeap;
    }

  public:
    void insert(E *element) {
        minHeap.insert(element);
        maxHeap.insert(element);
    }
};

#endif // DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
