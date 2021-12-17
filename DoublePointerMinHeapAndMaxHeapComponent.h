
#ifndef DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
#define DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H

#include "MaxHeap.h"
#include "MaxHeapWhenAlsoHavingMinHeap.h"
#include "MinHeapWhenAlsoHavingMaxHeap.h"

/**
 * @see MinHeap
 * @see MaxHeap
 * @see ElementInMinHeapAndMaxHeap
 */
template<typename E> class DoublePointerMinHeapAndMaxHeapComponent {

  protected:
    MinHeap<ElementInMinHeapAndMaxHeap<E>> *minHeap = nullptr;

  protected:
    MaxHeap<ElementInMinHeapAndMaxHeap<E>> *maxHeap = nullptr;

  public:
    DoublePointerMinHeapAndMaxHeapComponent(const MinHeap<E> &minHeap,
                                            const MaxHeap<E> &maxHeap)
        : minHeap(minHeap), maxHeap(maxHeap) {}

  public:
    virtual ~DoublePointerMinHeapAndMaxHeapComponent() = default;

  public:
    MinHeap<E> *getMinHeap() { return minHeap; }

  public:
    MaxHeap<E> *getMaxHeap() { return maxHeap; }

  public:
    void insertToBothHeaps(E *element) {
        minHeap->insert(element);
        minHeap->insert(element);
    }

  public:
    void deleteFromBothHeaps(E *element) {
        // TODO: implement. via `i` ? or via a `pointer`? need to check.
    }
};

#endif // DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
