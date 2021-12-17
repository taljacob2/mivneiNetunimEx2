
#ifndef MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
#define MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H

#include "ElementInMinHeapAndMaxHeap.h"
#include "MinHeap.h"

template<typename E>
class MaxHeapWhenAlsoHavingMinHeap
    : public MinHeap<ElementInMinHeapAndMaxHeap<E>> {

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  public:
    MaxHeapWhenAlsoHavingMinHeap() = default;

  public:
    explicit MaxHeapWhenAlsoHavingMinHeap(long physicalSize)
        : MinHeap<E>(physicalSize) {}

  public:
    MaxHeapWhenAlsoHavingMinHeap(EWrapper *arrayToBuildFrom,
                                 long      sizeOfArrayToBuildFrom)
        : MinHeap<E>(arrayToBuildFrom, sizeOfArrayToBuildFrom) {}

  protected:
    void onSwapIsNeeded(long currentIndex,
                        long indexOfOtherSwappableElement) const override {

        // Update this element's heap-index to the new index:
        (this->_array[currentIndex])
                ->setMaxHeapIndex(indexOfOtherSwappableElement);

        // Update this element's heap-index to the new index:
        (this->_array[indexOfOtherSwappableElement])
                ->setMaxHeapIndex(currentIndex);

        // Swap the elements:
        Heap<EWrapper>::onSwapIsNeeded(currentIndex,
                                       indexOfOtherSwappableElement);
    }
};

#endif // MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
