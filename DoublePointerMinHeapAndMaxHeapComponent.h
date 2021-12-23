
#ifndef DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H
#define DOUBLE_POINTER_MIN_HEAP_AND_MAX_HEAP_COMPONENT_H

#include "MaxHeap.h"
#include "MaxHeapWhenAlsoHavingMinHeap.h"
#include "MinHeapWhenAlsoHavingMaxHeap.h"
#include <ostream>

/**
 * @brief This class contains two `Heap`s, that share a mutual
 *        `ElementInMinHeapAndMaxHeap` together. In this way, an element
 *        within one heap can be instantly reached by the other heap.
 *        This is done by the indexes stored for each heap within every
 *        `ElementInMinHeapAndMaxHeap`.
 *
 * @note `ElementInMinHeapAndMaxHeap<E>` will be also be referred as `EWrapper`.
 * @see MinHeapWhenAlsoHavingMaxHeap
 * @see MaxHeapWhenAlsoHavingMinHeap
 * @see ElementInMinHeapAndMaxHeap
 */
template<typename E> class DoublePointerMinHeapAndMaxHeapComponent {

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  protected:
    MinHeapWhenAlsoHavingMaxHeap<E> *minHeap = nullptr;

  protected:
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
    /**
     * @brief "wraps" a given @p element with an `EWrapper`, and inserts it
     *        to both heaps.
     * @param element an element to be "wrapped" with an `EWrapper` to insert.
     */
    void insertToBothHeaps(E &&element) {
        auto *eWrapper = new EWrapper((E &&) element);
        insertToBothHeaps(eWrapper);
    }

  public:
    /**
     * @brief inserts an *already-created* `EWrapper` to both heaps.
     * @param eWrapper the `EWrapper` to insert.
     */
    void insertToBothHeaps(EWrapper *&eWrapper) {
        minHeap->insert(eWrapper);
        maxHeap->insert(eWrapper);
    }

  public:
    /**
     * @return One of these returns:
     *         - `nullptr`: when the `EWrapper` was *removed* and `delete`d -
     *           in case @p deleteEWrapper is `true`.
     *         - the *EWrapper removed*: when the `EWrapper` was *removed*
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
        } else {
            eWrapperToDelete->setMaxHeapIndex(0); // Reset index.
            eWrapperToDelete->setMinHeapIndex(0); // Reset index.
        }

        return eWrapperToDelete;
    }

  public:
    /**
     * @return One of these returns:
     *         - `nullptr`: when the `EWrapper` was *removed* and `delete`d -
     *           in case @p deleteEWrapper is `true`.
     *         - the *EWrapper removed*: when the `EWrapper` was *removed*
     *           without being `delete`d - in case @p deleteEWrapper is `false`.
     */
    EWrapper *deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
            unsigned long indexOfEWrapperInMaxHeapToDeleteFromBothHeaps,
            bool          deleteEWrapper = false) const {

        // Get the `EWrapper` to delete from `maxHeap`.
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
        } else {
            eWrapperToDelete->setMaxHeapIndex(0); // Reset index.
            eWrapperToDelete->setMinHeapIndex(0); // Reset index.
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
