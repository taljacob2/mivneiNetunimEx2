
#ifndef DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
#define DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H

#include "MaxHeap.h"
#include "MaxHeapWhenAlsoHavingMinHeap.h"
#include "MinHeapWhenAlsoHavingMaxHeap.h"
#include <ostream>

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
    virtual ~DoublePointerMinHeapAndMaxHeapComponent() { deleteThis(); }

  protected:
    void deleteThis() const {
        while (!minHeap->isEmpty()) { delete minHeap->deleteRoot(); }
        delete minHeap;
        while (!maxHeap->isEmpty()) { delete maxHeap->deleteRoot(); }
        delete maxHeap;
    }

  public:
    MinHeap<EWrapper> *getMinHeap() { return minHeap; }

  public:
    MaxHeap<EWrapper> *getMaxHeap() { return maxHeap; }

  public:
    void insertToBothHeaps(E *element) {
        auto *eWrapper = new EWrapper(element);
        minHeap->insert(eWrapper);
        maxHeap->insert(eWrapper);
    }

  public:
    void insertToBothHeaps(EWrapper *eWrapper) {
        minHeap->insert(eWrapper);
        maxHeap->insert(eWrapper);
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

        // Extract the old pointer from the given `eWrapper`.
        E *copiedElement = (eWrapper->getElement());

        // Construct a new `lvalue` object from that pointer.
        EWrapper copiedEWrapper(copiedElement);

        // Return the new `lvalue` object.
        return copiedEWrapper;
    }

  public:
    friend std::ostream &
    operator<<(std::ostream &                                 os,
               const DoublePointerMinHeapAndMaxHeapComponent &component) {
        component.print(os);
        return os;
    }

  public:
    virtual std::ostream &print(std::ostream &os) const {
        return printThis(os, *this);
    }

  private:
    static std::ostream &
    printThis(std::ostream &os,
              const DoublePointerMinHeapAndMaxHeapComponent<E>
                      &doublePointerMinHeapAndMaxHeapComponent) {
        os << "---------------------------- ";
        os << "minHeap:";
        os << " ----------------------------" << std::endl;
        doublePointerMinHeapAndMaxHeapComponent.minHeap->print(std::cout);

        os << "---------------------------- ";
        os << "maxHeap:";
        os << " ----------------------------" << std::endl;
        doublePointerMinHeapAndMaxHeapComponent.maxHeap->print(std::cout);

        return os;
    }
};

#endif // DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
