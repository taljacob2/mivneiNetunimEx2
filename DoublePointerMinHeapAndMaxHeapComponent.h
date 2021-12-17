
#ifndef DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
#define DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H

#include "MaxHeapWhenAlsoHavingMinHeap.h"
#include "MinHeapWhenAlsoHavingMaxHeap.h"

template<typename E> class DoublePointerMinHeapAndMaxHeapComponent {

  protected:
    HeapAdt<ElementInMinHeapAndMaxHeap<E>> *minHeap = nullptr;

  protected:
    HeapAdt<ElementInMinHeapAndMaxHeap<E>> *maxHeap = nullptr;

  public:
    DoublePointerMinHeapAndMaxHeapComponent(const HeapAdt<E> &minHeap,
                                            const HeapAdt<E> &maxHeap)
        : minHeap(minHeap), maxHeap(maxHeap) {}

  public:
    virtual ~DoublePointerMinHeapAndMaxHeapComponent() = default;

  public:
    const HeapAdt<E> &getMinHeap() const { return minHeap; }

  public:
    const HeapAdt<E> &getMaxHeap() const { return maxHeap; }

  public:
    void insertToBothHeaps(E *element) {
        minHeap->insert(element);
        minHeap->insert(element);
    }

  public:
    void deleteFromBothHeaps(E *element) {}
};

#endif // DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
