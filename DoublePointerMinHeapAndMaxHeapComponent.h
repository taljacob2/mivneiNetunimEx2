
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

            /**
             * - Delete the root from `minHeap`.
             * - Delete its pointer at `maxHeap`.
             * - Delete the EWrapper containing the indexes of `minHeap` and `maxHeap`.
             */
            deleteEWrapperFromBothHeapsViaIndexOfMinHeapElement(0, true);
        }

        delete minHeap;
        delete maxHeap;
    }

  public:
    MinHeapWhenAlsoHavingMaxHeap<E> *getMinHeap() { return minHeap; }

  public:
    MaxHeapWhenAlsoHavingMinHeap<E> *getMaxHeap() { return maxHeap; }

  public:
    void insertToBothHeaps(E &&element) {
        auto *eWrapper = new EWrapper((E &&) element);
        insertToBothHeaps(eWrapper);
    }

  public:
    void insertToBothHeaps(EWrapper *&eWrapper) {
        minHeap->insert(eWrapper);
        maxHeap->insert(eWrapper);
    }

  public:
    /**
     * @return - `nullptr`: when the `EWrapper` was *removed* and `delete`d -
     *           in case @p deleteEWrapper is `true`.
     *         - *EWrapper removed*: when the `EWrapper` was *removed*
     *           without being `delete`d - in case @p deleteEWrapper is `false`.
     */
    EWrapper *deleteEWrapperFromBothHeapsViaIndexOfMinHeapElement(
            unsigned long indexOfEWrapperInMinHeapToDeleteFromBothHeaps,
            bool          deleteEWrapper = false) const {

        // Get the `EWrapper` to delete from `minHeap`.
        EWrapper *eWrapperToDelete = minHeap->deleteElement(
                indexOfEWrapperInMinHeapToDeleteFromBothHeaps);

        /*
         * Extract the corresponding `indexOfEWrapperInMinHeapToDeleteFromBothHeaps`
         * of this `eWrapperToDelete`'s element from `maxHeap`,
         * and delete it from the `maxHeap`.
         */
        maxHeap->deleteElement(eWrapperToDelete->getMaxHeapIndex());

        if (deleteEWrapper) {

            // `delete` the `EWrapper` from memory.
            delete eWrapperToDelete;
            eWrapperToDelete = nullptr;
        }

        return eWrapperToDelete;
    }

  public:
    EWrapper *deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
            unsigned long indexOfEWrapperInMaxHeapToDeleteFromBothHeaps,
            bool          deleteEWrapper = false) const {

        // Get the `EWrapper` to delete from `minHeap`.
        EWrapper *eWrapperToDelete = maxHeap->deleteElement(
                indexOfEWrapperInMaxHeapToDeleteFromBothHeaps);

        /*
         * Extract the corresponding `indexOfEWrapperInMaxHeapToDeleteFromBothHeaps`
         * of this `eWrapperToDelete`'s element from `minHeap`,
         * and delete it from the `minHeap`.
         */
        minHeap->deleteElement(eWrapperToDelete->getMinHeapIndex());

        if (deleteEWrapper) {

            // `delete` the `EWrapper` from memory.
            delete eWrapperToDelete;
            eWrapperToDelete = nullptr;
        }

        return eWrapperToDelete;
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
