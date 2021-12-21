
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

        // TODO: debug print
        std::cout << *eWrapper << std::endl;
        insertToBothHeaps(eWrapper);
    }

  public:
    void insertToBothHeaps(EWrapper *&eWrapper) {
        minHeap->insert(eWrapper); // FIXME: bug here.
        maxHeap->insert(eWrapper);
    }

  protected:
    /**
     * @return - `nullptr`: when the `EWrapper` was *removed* and `delete`d -
     *           in case @p deleteEWrapper is `true`.
     *         - *EWrapper removed*: when the `EWrapper` was *removed*
     *           without being `delete`d - in case @p deleteEWrapper is `false`.
     */
    static EWrapper *deleteEWrapperFromBothHeaps(
            Heap<EWrapper> *heap1, Heap<EWrapper> *heap2,
            unsigned long indexOfEWrapperGivenHeap1ToDeleteFromBothHeaps,
            bool          deleteEWrapper = true) {

        // Get the `EWrapper` to delete from `minHeap`.
        EWrapper *heap1EWrapperToDelete = heap1->deleteElement(
                indexOfEWrapperGivenHeap1ToDeleteFromBothHeaps);

        /*
         * Extract the corresponding `indexOfEWrapperInMinHeapToDeleteFromBothHeaps`
         * of this `heap1EWrapperToDelete`'s element from `heap2`,
         * and delete it from the `heap2`.
         */
        heap2->deleteElement(heap1EWrapperToDelete->getMaxHeapIndex());

        if (deleteEWrapper) {

            // `delete` the `EWrapper` from memory.
            delete heap1EWrapperToDelete;
            heap1EWrapperToDelete = nullptr;
        }

        return heap1EWrapperToDelete;
    }

  public:
    EWrapper *deleteEWrapperFromBothHeapsViaIndexOfMinHeapElement(
            unsigned long indexOfEWrapperInMinHeapToDeleteFromBothHeaps,
            bool          deleteEWrapper = false) const {

        return deleteEWrapperFromBothHeaps(
                minHeap, maxHeap, indexOfEWrapperInMinHeapToDeleteFromBothHeaps,
                deleteEWrapper);
    }

  public:
    EWrapper *deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
            unsigned long indexOfEWrapperInMaxHeapToDeleteFromBothHeaps,
            bool          deleteEWrapper = false) const {

        return deleteEWrapperFromBothHeaps(
                maxHeap, minHeap, indexOfEWrapperInMaxHeapToDeleteFromBothHeaps,
                deleteEWrapper);
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
