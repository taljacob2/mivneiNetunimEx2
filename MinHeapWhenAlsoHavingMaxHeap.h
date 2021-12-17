

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
        Heap<ElementInMinHeapAndMaxHeap<Entry<K, V>>>::onSwapIsNeeded(
                currentIndex, indexOfOtherSwappableElement);
        this->_array
        currentIndex.
    }
};

#endif // MIN_HEAP_WHEN_ALSO_HAVING_MAX_HEAP_H
