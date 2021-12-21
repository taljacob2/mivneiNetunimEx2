
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
    // TODO: polymorph
    MinHeapWhenAlsoHavingMaxHeap<E> *minHeap = nullptr;

  protected:
    // TODO: polymorph
    MaxHeapWhenAlsoHavingMinHeap<E> *maxHeap = nullptr;

  public:
    DoublePointerMinHeapAndMaxHeapComponent(
            MinHeapWhenAlsoHavingMaxHeap<E> *minHeap,
            MaxHeapWhenAlsoHavingMinHeap<E> *maxHeap)
        : minHeap(minHeap), maxHeap(maxHeap) {}

  public:
    virtual ~DoublePointerMinHeapAndMaxHeapComponent() { deleteThis(); }

  protected:
    void deleteThis() const {

        while (!minHeap->isEmpty()) {
            // FIXME: bug. element is already free'd by the above `minHeap`.
            //  need to delete (with marking as `nullptr only(!)` from the maxHeap
            //  at once when deleting from `minHeap`
            //      need to get the index of maxHeap, get to the element
            //      there and mark it as null, reduce the maxHeap's
            //      logicalSize by 1, and fixHeap(i) as if the element was
            //      deleted successfully.

            // Get the root from `minHeap`.
            ElementInMinHeapAndMaxHeap<E> *minHeapRoot = minHeap->deleteRoot();

            /*
             * Extract the corresponding index of this root element's from
             * `maxHeap`, and delete it from the `maxHeap`.
             */
            maxHeap->deleteElement(minHeapRoot->getMaxHeapIndex());

            // `delete` the ElementInMinHeapAndMaxHeap<E> from memory.
            delete minHeapRoot;
        }

        delete minHeap;

        delete maxHeap;
    }

  public:
    MinHeapWhenAlsoHavingMaxHeap<E> *getMinHeap() { return minHeap; }

  public:
    MaxHeapWhenAlsoHavingMinHeap<E> *getMaxHeap() { return maxHeap; }

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
    /**
     * @todo `delete` `deepCopiedEWrapper`.
     */
    EWrapper *deleteFromBothHeaps(EWrapper *eWrapper) {

        // Backup fields of the given `eWrapper`.
        auto  lessMinHeapIndex   = eWrapper->getMinHeapIndex();
        auto  lessMaxHeapIndex   = eWrapper->getMaxHeapIndex();
        auto *deepCopiedEWrapper = new EWrapper(eWrapper->getElement());

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
