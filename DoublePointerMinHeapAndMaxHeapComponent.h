
#ifndef DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
#define DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H

#include "MinHeapWhenAlsoHavingMaxHeap.h"
#include "MaxHeapWhenAlsoHavingMinHeap.h"

template<typename E>
class DoublePointerMinHeapAndMaxHeapComponent {

  protected:
    MinHeapWhenAlsoHavingMaxHeap<E> minHeap;

  protected:
    MaxHeapWhenAlsoHavingMinHeap<E> maxHeap;

};

#endif // DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
