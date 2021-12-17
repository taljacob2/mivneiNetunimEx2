
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

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  protected:
    MinHeap<EWrapper> *minHeap = nullptr;

  protected:
    MaxHeap<EWrapper> *maxHeap = nullptr;

  public:
    DoublePointerMinHeapAndMaxHeapComponent(MinHeap<EWrapper> *minHeap,
                                            MaxHeap<EWrapper> *maxHeap)
        : minHeap(minHeap), maxHeap(maxHeap) {}

  public:
    virtual ~DoublePointerMinHeapAndMaxHeapComponent() = default;

  public:
    MinHeap<EWrapper> *getMinHeap() { return minHeap; }

  public:
    MaxHeap<EWrapper> *getMaxHeap() { return maxHeap; }

  public:
    static E &getElementFromElementInMinHeapAndMaxHeap(
            EWrapper *elementInMinHeapAndMaxHeap) {
        return elementInMinHeapAndMaxHeap->getElement();
    }

  public:
    void insertToBothHeaps(E *element) {
        EWrapper eWrapper(element);
        minHeap->insert(&eWrapper);
        maxHeap->insert(&eWrapper);
    }

  public:
    EWrapper deleteFromBothHeaps(EWrapper *eWrapper) {

        // Backup fields of the given `eWrapper`.
        auto     lessMinHeapIndex   = eWrapper->getMinHeapIndex();
        auto     lessMaxHeapIndex   = eWrapper->getMaxHeapIndex();
        EWrapper deepCopiedEWrapper = deepCopyEWrapper(eWrapper);

        // Delete the pointer to the element.
        eWrapper->setElement(nullptr);
        minHeap->fixHeap(lessMinHeapIndex);
        maxHeap->fixHeap(lessMaxHeapIndex);

        /*
         * Return a deep-copy of the given `eWrapper`,
         * with its indexes reset to 0.
         */
        return deepCopiedEWrapper;
    }

  protected:
    EWrapper deepCopyEWrapper(EWrapper *eWrapper) const {
        E &      copiedElement = *(eWrapper->getElement());
        EWrapper copiedEWrapper(copiedElement);
        return copiedEWrapper;
    }
};

#endif // DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
