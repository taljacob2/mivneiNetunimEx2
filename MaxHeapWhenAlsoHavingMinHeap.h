
#ifndef MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
#define MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H

#include "ElementInMinHeapAndMaxHeap.h"
#include "Entry.h"
#include "MinHeap.h"

template<typename K, typename V>
class MaxHeapWhenAlsoHavingMinHeap
    : public MinHeap<ElementInMinHeapAndMaxHeap<Entry<K, V>>> {

  protected:
    void onIsSwapNeeded(long currentIndex,
                        long indexOfOtherSwappableElement) const override {

        // Update this element's heap-index to the new index:
        (this->_array[currentIndex])
                ->setMaxHeapIndex(indexOfOtherSwappableElement);

        // Update this element's heap-index to the new index:
        (this->_array[indexOfOtherSwappableElement])
                ->setMaxHeapIndex(currentIndex);

        // Swap the elements:
        Heap<ElementInMinHeapAndMaxHeap<Entry<K, V>>>::onSwapIsNeeded(
                currentIndex, indexOfOtherSwappableElement);
    }
};

#endif // MAX_HEAP_WHEN_ALSO_HAVING_MIN_HEAP_H
