
#ifndef MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H
#define MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H

#include "ElementInMinHeapAndMaxHeap.h"
#include "MinHeap.h"

template<typename E>
class MinHeapWhenAlsoHavingMaxHeap
    : public MinHeap<ElementInMinHeapAndMaxHeap<E>> {

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  public:
    MinHeapWhenAlsoHavingMaxHeap() = default;

  public:
    explicit MinHeapWhenAlsoHavingMaxHeap(unsigned long physicalSize)
        : MinHeap<EWrapper>(physicalSize) {}

  public:
    MinHeapWhenAlsoHavingMaxHeap(EWrapper *    arrayToBuildFrom,
                                 unsigned long sizeOfArrayToBuildFrom)
        : MinHeap<EWrapper>(arrayToBuildFrom, sizeOfArrayToBuildFrom) {}

  protected:
    void
    onSwapIsNeeded(unsigned long currentIndex,
                   unsigned long indexOfOtherSwappableElement) const override {

        // Update this element's heap-index to the new index:
        (this->_array[currentIndex])
                ->setMinHeapIndex(indexOfOtherSwappableElement);

        // Update this element's heap-index to the new index:
        (this->_array[indexOfOtherSwappableElement])
                ->setMinHeapIndex(currentIndex);

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
        element->setMinHeapIndex(newIndex);
    }
};

#endif // MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H
