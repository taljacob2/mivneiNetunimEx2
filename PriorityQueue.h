
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
        _lessOrEqualToMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<EWrapper>(
                                physicalSizeOfEachHeap),
                        new MaxHeapWhenAlsoHavingMinHeap<EWrapper>(
                                physicalSizeOfEachHeap));

        _greaterThanMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<EWrapper>(
                                physicalSizeOfEachHeap),
                        new MaxHeapWhenAlsoHavingMinHeap<EWrapper>(
                                physicalSizeOfEachHeap));
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
    virtual ~PriorityQueue() { deleteThis(); }

  private:
    void deleteThis() const {
        if (_lessOrEqualToMedianDoubleHeap) {
            delete _lessOrEqualToMedianDoubleHeap->getMinHeap();
            delete _lessOrEqualToMedianDoubleHeap->getMaxHeap();
            delete _lessOrEqualToMedianDoubleHeap;
        }

        if (_greaterThanMedianDoubleHeap) {
            delete _greaterThanMedianDoubleHeap->getMinHeap();
            delete _greaterThanMedianDoubleHeap->getMaxHeap();
            delete _greaterThanMedianDoubleHeap;
        }
    }

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
        deleteThis();
        _lessOrEqualToMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<EWrapper>(),
                        new MaxHeapWhenAlsoHavingMinHeap<EWrapper>());

        _greaterThanMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<EWrapper>(),
                        new MaxHeapWhenAlsoHavingMinHeap<EWrapper>());
    }

  public:
    void insert(E *element) override {
        if (getLogicalSize() > 1) {
            if (isLogicalSizeEven()) {
                if (median() < *element) {
                    _greaterThanMedianDoubleHeap->getMaxHeap()->insert(element);
                } else {

                    /*
                     * Transfer the maximum from `_lessOrEqualToMedianDoubleHeap->getMaxHeap()`
                     * to `_greaterThanMedianDoubleHeap->getMaxHeap()`
                     */
                    _greaterThanMedianDoubleHeap->getMaxHeap()->insert(
                            _lessOrEqualToMedianDoubleHeap->getMaxHeap()
                                    ->deleteRoot());
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
