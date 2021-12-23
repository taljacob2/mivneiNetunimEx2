
#ifndef MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
#define MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H

#include "ElementInMinHeapAndMaxHeap.h"
#include "MinHeap.h"

/**
 * @note `ElementInMinHeapAndMaxHeap<E>` will be also be referred as `EWrapper`.
 */
template<typename E>
class MaxHeapWhenAlsoHavingMinHeap
    : public MaxHeap<ElementInMinHeapAndMaxHeap<E>> {

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  public:
    MaxHeapWhenAlsoHavingMinHeap() = default;

  public:
    explicit MaxHeapWhenAlsoHavingMinHeap(unsigned long physicalSize)
        : MaxHeap<EWrapper>(physicalSize) {}

  public:
    MaxHeapWhenAlsoHavingMinHeap(EWrapper *    arrayToBuildFrom,
                                 unsigned long sizeOfArrayToBuildFrom)
        : MaxHeap<EWrapper>(arrayToBuildFrom, sizeOfArrayToBuildFrom) {}

  protected:
    void onSwapIsNeeded(unsigned long index1,
                        unsigned long index2) const override {

        // Update this element's heap-index to the new index:
        (this->_array[index1])->setMaxHeapIndex(index2);

        // Update this element's heap-index to the new index:
        (this->_array[index2])->setMaxHeapIndex(index1);

        // Swap the elements:
        Heap<EWrapper>::onSwapIsNeeded(index1, index2);
    }

  protected:
    void onUpdateElementWithIndex(EWrapper *&   element,
                                  unsigned long newIndex) const override {
        // Heap<EWrapper>::onUpdateElementWithIndex(element, newIndex);
        element->setMaxHeapIndex(newIndex);
    }
};

#endif // MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
