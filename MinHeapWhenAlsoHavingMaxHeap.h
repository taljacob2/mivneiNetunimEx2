
#ifndef MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H
#define MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H

#include "ElementInMinHeapAndMaxHeap.h"
#include "Entry.h"
#include "MinHeap.h"

template<typename K, typename V>
class MinHeapWhenAlsoHavingMaxHeap
    : public MinHeap<ElementInMinHeapAndMaxHeap<Entry<K, V>>> {

  protected:
    void onIsSwapNeeded(long currentIndex,
                        long indexOfOtherSwappableElement) const override {

        // Update this element's heap-index to the new index:
        (this->_array[currentIndex])
                ->setMinHeapIndex(indexOfOtherSwappableElement);

        // Update this element's heap-index to the new index:
        (this->_array[indexOfOtherSwappableElement])
                ->setMinHeapIndex(currentIndex);

        // Swap the elements:
        Heap<ElementInMinHeapAndMaxHeap<Entry<K, V>>>::onSwapIsNeeded(
                currentIndex, indexOfOtherSwappableElement);
    }
};

#endif // MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H
