
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "DoublePointerMinHeapAndMaxHeapComponent.h"
#include "PriorityQueueAdt.h"

/**
 * @brief This *priority-queue* is implemented by four *Heaps*, and each of
 *        these Heaps' elements are *Entries* that are composed by a *key* and a *value*.
 *
 * @attention the `median()` is defined as the element that its priority is
 *            `ceil(n / 2)`.
 *
 * @tparam E The type of each element. **Must** be `comparable`.
 *           The *priority* of each element is based on this comparable `key`.
 * @see DoublePointerMinHeapAndMaxHeapComponent
 */
template<typename E> class PriorityQueue : public PriorityQueueAdt<E> {

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  private:
    static constexpr unsigned long SIZE = 100;

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<E> *_lessOrEqualToMedianDoubleHeap =
            nullptr;

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<E> *_greaterThanMedianDoubleHeap =
            nullptr;

  public:
    explicit PriorityQueue(int physicalSizeOfEachHeap) {
        createDoubleHeapWithPhysicalSize(_lessOrEqualToMedianDoubleHeap,
                                         physicalSizeOfEachHeap);
        createDoubleHeapWithPhysicalSize(_greaterThanMedianDoubleHeap,
                                         physicalSizeOfEachHeap);
    }

  public:
    /**
     * @warning invoking this method does *not* initialize any field.
     *          So, if you decide to use this method, *you may not* invoke any
     *          of the methods in this class. Instead, you *must* invoke the
     *          `createEmpty()` method beforehand, and only then you are
     *          allowed to invoke the other methods in this class.
     *          @li This kind of implementation is served only because of a
     *          request given by the customer ( = the course lecturer).
     */
    // TODO: remove debug with `createEmpty`
    PriorityQueue() = default;
    // PriorityQueue() { createEmpty(); }

  public:
    virtual ~PriorityQueue() { deleteThis(); }

  protected:
    void deleteThis() const {
        delete _lessOrEqualToMedianDoubleHeap;
        delete _greaterThanMedianDoubleHeap;
    }

  public:
    E *max() override {

        // FIXME: check
        return _greaterThanMedianDoubleHeap->getMaxHeap()
                ->getRoot()
                ->getElement();
    }

  public:
    E *deleteMax() override {}

  public:
    E *min() override {

        // FIXME: check
        return _lessOrEqualToMedianDoubleHeap->getMinHeap()
                ->getRoot()
                ->getElement();
    }

  public:
    E *deleteMin() override {}

  public:
    void createEmpty() override {
        createDoubleHeap(_lessOrEqualToMedianDoubleHeap);
        createDoubleHeap(_greaterThanMedianDoubleHeap);
    }

  protected:
    void
    createDoubleHeap(DoublePointerMinHeapAndMaxHeapComponent<E> *
                             &fieldOfDoublePointerMinHeapAndMaxHeapComponent) {

        auto *minHeap = new MinHeapWhenAlsoHavingMaxHeap<E>(SIZE);

        auto *maxHeap = new MaxHeapWhenAlsoHavingMinHeap<E>(SIZE);

        // Polymorphing `MinHeap` and `MaxHeap` through parameters.
        fieldOfDoublePointerMinHeapAndMaxHeapComponent =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(minHeap,
                                                               maxHeap);
    }

    // protected:
    //   void createDoubleHeapWithPhysicalSize(
    //           DoublePointerMinHeapAndMaxHeapComponent<E> *
    //                   &     fieldOfDoublePointerMinHeapAndMaxHeapComponent,
    //           unsigned long physicalSize) {
    //
    //       // Polymorphing `MinHeap` and `MaxHeap` through parameters.
    //       fieldOfDoublePointerMinHeapAndMaxHeapComponent =
    //               new DoublePointerMinHeapAndMaxHeapComponent<E>(
    //                       (MinHeap<EWrapper> *) new MinHeapWhenAlsoHavingMaxHeap<
    //                               EWrapper>(physicalSize),
    //                       (MaxHeap<EWrapper> *) new MaxHeapWhenAlsoHavingMinHeap<
    //                               EWrapper>(physicalSize));
    //   }

  public:
    void insert(E &&element) override {
        if (getLogicalSize() > 1) {
            if (isLogicalSizeEven()) {
                if (*median() < element) {

                    // Insert the given EWrapper to the "greater" heap.
                    _greaterThanMedianDoubleHeap->insertToBothHeaps(
                            (E &&) element);
                } else {
                    transferTheMaxElementFromLessToGreater();

                    // Insert the given EWrapper to the "less" heap.
                    _lessOrEqualToMedianDoubleHeap->insertToBothHeaps(
                            (E &&) element);
                }
            } else if (isLogicalSizeOdd()) {

                // Insert the given EWrapper to the "less" heap.
                _lessOrEqualToMedianDoubleHeap->insertToBothHeaps(
                        (E &&) element);
            }
        } else {

            // TODO: debug
            std::cout << "inside insert. element is:" << element << std::endl;


            // Insert the given EWrapper to the "less" heap.
            _lessOrEqualToMedianDoubleHeap->insertToBothHeaps((E &&) element);
        }
    }

  protected:
    void transferTheMaxElementFromLessToGreater() const {
        transferElementFromLessDoubleHeapViaIndexOfMaxHeapToGreaterDoubleHeap(
                0);
    }

  protected:
    void transferElementFromLessDoubleHeapViaIndexOfMaxHeapToGreaterDoubleHeap(
            unsigned long index) const {

        // Delete the `EWrapper` from both "less" heaps.
        EWrapper *eWrapperToTransferToGreater =
                _lessOrEqualToMedianDoubleHeap
                        ->deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
                                index, false);

        // Transfer it to both "greater" heaps.
        _greaterThanMedianDoubleHeap->insertToBothHeaps(
                eWrapperToTransferToGreater);
    }

  public:
    /**
     * @return the median priority element - defining the median as the
     *         element that its priority is `ceil(n / 2)`
     * @throws std::runtime_error in case there are no elements in the
     *         `_lessOrEqualToMedianMaxHeap` heap, and the user requested to
     *         retrieve the root.
     */
    E *median() override {

        // FIXME: check
        return _lessOrEqualToMedianDoubleHeap->getMaxHeap()
                ->getRoot()
                ->getElement();
    }

  protected:
    long int getLogicalSize() {
        return _lessOrEqualToMedianDoubleHeap->getMaxHeap()->getLogicalSize() +
               _greaterThanMedianDoubleHeap->getMaxHeap()->getLogicalSize();
    }

  protected:
    bool isLogicalSizeEven() { return getLogicalSize() % 2 == 0; }

  protected:
    bool isLogicalSizeOdd() { return !isLogicalSizeEven(); }

  protected:
    bool isLogicalSizeOfHeapAdtEven(HeapAdt<EWrapper> *heapAdt) {
        return heapAdt->getLogicalSize() % 2 == 0;
    }

  protected:
    bool isLogicalSizeOfHeapAdtOdd(HeapAdt<EWrapper> *heapAdt) {
        return !isLogicalSizeOfHeapAdtEven(heapAdt);
    }

  public:
    friend std::ostream &operator<<(std::ostream &       os,
                                    const PriorityQueue &priorityQueue) {
        priorityQueue.print(os);
        return os;
    }

  public:
    std::ostream &print(std::ostream &os) const override {
        return printThis(os, *this);
    }

  private:
    static std::ostream &printThis(std::ostream &          os,
                                   const PriorityQueue<E> &priorityQueue) {
        constexpr char *PRINT_WHEN_EMPTY = (char *) "empty.";

        os << "---------------------------- ";
        os << "_lessOrEqualToMedianDoubleHeap:";
        os << " ----------------------------" << std::endl;
        if (priorityQueue._lessOrEqualToMedianDoubleHeap->getMinHeap()
                    ->getLogicalSize()) {
            priorityQueue._lessOrEqualToMedianDoubleHeap->print(std::cout);
        } else {
            os << PRINT_WHEN_EMPTY << std::endl;
        }

        os << "---------------------------- ";
        os << "_greaterThanMedianDoubleHeap:";
        os << " ----------------------------" << std::endl;
        if (priorityQueue._greaterThanMedianDoubleHeap->getMinHeap()
                    ->getLogicalSize()) {
            priorityQueue._greaterThanMedianDoubleHeap->print(std::cout);
        } else {
            os << PRINT_WHEN_EMPTY << std::endl;
        }

        os << " ----------------------------------------"
              "--------------------------------------------"
           << std::endl;

        return os;
    }
};

#endif // PRIORITY_QUEUE_H
