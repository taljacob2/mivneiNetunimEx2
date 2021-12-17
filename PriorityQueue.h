
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

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<E> *_lessOrEqualToMedianDoubleHeap =
            nullptr;

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<E> *_greaterThanMedianDoubleHeap =
            nullptr;

  public:
    explicit PriorityQueue(int physicalSizeOfEachHeap) {
        MinHeapWhenAlsoHavingMaxHeap<E> lessMinHeapWhenAlsoHavingMaxHeap(
                physicalSizeOfEachHeap);
        MinHeapWhenAlsoHavingMaxHeap<E> lessMaxHeapWhenAlsoHavingMinHeap(
                physicalSizeOfEachHeap);
        DoublePointerMinHeapAndMaxHeapComponent<E> lessDoubleHeap(
                lessMinHeapWhenAlsoHavingMaxHeap,
                lessMaxHeapWhenAlsoHavingMinHeap);
        _lessOrEqualToMedianDoubleHeap = &lessDoubleHeap;

        MinHeapWhenAlsoHavingMaxHeap<E> greaterMinHeapWhenAlsoHavingMaxHeap(
                physicalSizeOfEachHeap);
        MinHeapWhenAlsoHavingMaxHeap<E> greaterMaxHeapWhenAlsoHavingMinHeap(
                physicalSizeOfEachHeap);
        DoublePointerMinHeapAndMaxHeapComponent<E> greaterDoubleHeap(
                greaterMinHeapWhenAlsoHavingMaxHeap,
                greaterMaxHeapWhenAlsoHavingMinHeap);
        _greaterThanMedianDoubleHeap = &greaterDoubleHeap;
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
    PriorityQueue() = default;

  public:
    virtual ~PriorityQueue() = default;

  public:
    E max() override {

        // FIXME: check
        return getElement(_greaterThanMedianDoubleHeap->getMaxHeap());
    }

  public:
    E deleteMax() override {}

  public:
    E min() override {

        // FIXME: check
        return getElement(_lessOrEqualToMedianDoubleHeap->getMinHeap());
    }

  public:
    E deleteMin() override {}

  public:
    void createEmpty() override {
        MinHeapWhenAlsoHavingMaxHeap<E> lessMinHeapWhenAlsoHavingMaxHeap;
        MinHeapWhenAlsoHavingMaxHeap<E> lessMaxHeapWhenAlsoHavingMinHeap;
        DoublePointerMinHeapAndMaxHeapComponent<E> lessDoubleHeap(
                lessMinHeapWhenAlsoHavingMaxHeap,
                lessMaxHeapWhenAlsoHavingMinHeap);
        _lessOrEqualToMedianDoubleHeap = &lessDoubleHeap;

        MinHeapWhenAlsoHavingMaxHeap<E> greaterMinHeapWhenAlsoHavingMaxHeap;
        MinHeapWhenAlsoHavingMaxHeap<E> greaterMaxHeapWhenAlsoHavingMinHeap;
        DoublePointerMinHeapAndMaxHeapComponent<E> greaterDoubleHeap(
                greaterMinHeapWhenAlsoHavingMaxHeap,
                greaterMaxHeapWhenAlsoHavingMinHeap);
        _greaterThanMedianDoubleHeap = &greaterDoubleHeap;
    }

  public:
    void insert(E *element) override {
        if (getLogicalSize() > 1) {
            if (isLogicalSizeEven()) {
                if (median() < *element) {
                    _greaterThanMedianDoubleHeap->insertToBothHeaps(element);
                } else {

                    /*
                     * Transfer the maximum from `_lessOrEqualToMedianDoubleHeap->getMaxHeap()`
                     * to `_greaterThanMedianDoubleHeap->getMaxHeap()`
                     */
                    // FIXME: here

                    /*
                     * 1. Get the left maximum EWrapper.
                     * 2. Get the index where it is used in the maximum-heap and
                     *    delete the element there by the index.
                     * 3. Do the same for the minimum-heap.
                     */
                    EWrapper *leftMaximumEWrapper =
                            _lessOrEqualToMedianDoubleHeap->getMaxHeap()
                                    ->getRoot();

                    auto leftMinHeapIndex =
                            leftMaximumEWrapper->getMinHeapIndex();
                    auto leftMaxHeapIndex =
                            leftMaximumEWrapper->getMaxHeapIndex();


                    _greaterThanMedianDoubleHeap->insertToBothHeaps();


                    _greaterThanMedianDoubleHeap->insertToBothHeaps(
                            ElementInMinHeapAndMaxHeap<E>(
                                    _lessOrEqualToMedianDoubleHeap->getMaxHeap()
                                            ->deleteRoot()));
                    _lessOrEqualToMedianDoubleHeap->getMaxHeap()->insert(
                            element);
                }
            } else if (isLogicalSizeOdd()) {
                _lessOrEqualToMedianDoubleHeap->getMaxHeap()->insert(element);
            }
        } else {
            _lessOrEqualToMedianDoubleHeap->getMaxHeap()->insert(element);
        }
    }

  protected:
    void deleteElement(E *element) {}

  protected:
    E &getElement(HeapAdt<EWrapper> *heapAdt) {
        return DoublePointerMinHeapAndMaxHeapComponent<E>::
                getElementFromElementInMinHeapAndMaxHeap(heapAdt->getRoot());
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
    /**
     * @return the median priority element - defining the median as the
     *         element that its priority is `ceil(n / 2)`
     * @throws std::runtime_error in case there are no elements in the
     *         `_lessOrEqualToMedianMaxHeap` heap, and the user requested to
     *         retrieve the root.
     */
    E median() override {

        // FIXME: check
        return getElement(
                _lessOrEqualToMedianDoubleHeap->getMaxHeap()->getRoot());
    }

  public:
    friend std::ostream &operator<<(std::ostream &       os,
                                    const PriorityQueue &priorityQueue) {
        return printThis(os, priorityQueue);
    }

  private:
    std::ostream &print(std::ostream &os) const override {
        return printThis(os, *this);
    }

  private:
    static std::ostream &printThis(std::ostream &          os,
                                   const PriorityQueue<E> &priorityQueue) {

        os << "---------------------------- ";
        os << "_greaterThanMedianMaxHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._greaterThanMedianMaxHeap->print(std::cout);

        os << "---------------------------- ";
        os << "_greaterThanMedianMinHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._greaterThanMedianMinHeap->print(std::cout);

        os << "---------------------------- ";
        os << "_lessOrEqualToMedianMaxHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._lessOrEqualToMedianMaxHeap->print(std::cout);

        os << "---------------------------- ";
        os << "_lessOrEqualToMedianMinHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._lessOrEqualToMedianMinHeap->print(std::cout);
        os << "---------------------------- ";

        return os;
    }
};

#endif // PRIORITY_QUEUE_H
