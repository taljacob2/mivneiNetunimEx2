
#ifndef MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
#define MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H

#include "ElementInMinHeapAndMaxHeap.h"
#include "MinHeap.h"

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
    void
    onSwapIsNeeded(unsigned long currentIndex,
                   unsigned long indexOfOtherSwappableElement) const override {

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

  protected:
    void onInsert(EWrapper *&elementInserted) const override {
        // Heap<EWrapper>::onInsert(elementInserted);
        onUpdateElementWithIndex(elementInserted, this->_logicalSize - 1);
    }

  protected:
    void onUpdateElementWithIndex(EWrapper *&   element,
                                  unsigned long newIndex) const override {
        // Heap<EWrapper>::onUpdateElementWithIndex(element, newIndex);
        element->setMaxHeapIndex(newIndex);
    }
};

#endif // MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
