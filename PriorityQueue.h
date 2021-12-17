
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

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<ElementInMinHeapAndMaxHeap<E>>
            *_lessOrEqualToMedianDoubleHeap = nullptr;

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<ElementInMinHeapAndMaxHeap<E>>
            *_greaterThanMedianDoubleHeap = nullptr;

  public:
    explicit PriorityQueue(int physicalSizeOfEachHeap) {
        _lessOrEqualToMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<E>(
                                physicalSizeOfEachHeap),
                        new MaxHeapWhenAlsoHavingMinHeap<E>(
                                physicalSizeOfEachHeap));

        _greaterThanMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<E>(
                                physicalSizeOfEachHeap),
                        new MaxHeapWhenAlsoHavingMinHeap<E>(
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
    PriorityQueue() {
        _lessOrEqualToMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<E>(),
                        new MaxHeapWhenAlsoHavingMinHeap<E>());

        _greaterThanMedianDoubleHeap =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(
                        new MinHeapWhenAlsoHavingMaxHeap<E>(),
                        new MaxHeapWhenAlsoHavingMinHeap<E>());
    }

  public:
    virtual ~PriorityQueue() { deleteThis(); }

  private:
    void deleteThis() const {
        delete _lessOrEqualToMedianDoubleHeap->minHeap;
        delete _lessOrEqualToMedianDoubleHeap->maxHeap;
        delete _lessOrEqualToMedianDoubleHeap;

        delete _greaterThanMedianDoubleHeap->minHeap;
        delete _greaterThanMedianDoubleHeap->maxHeap;
        delete _greaterThanMedianDoubleHeap;
    }

  public:
    E max() override {
        return *_greaterThanMedianMaxHeap->getRoot(); // FIXME: check
    }

  public:
    E deleteMax() override {}

  public:
    E min() override {
        return *_lessOrEqualToMedianMinHeap->getRoot(); // FIXME: check
    }

  public:
    E deleteMin() override {}

  public:
    void createEmpty() override {
        deleteThis();
        _greaterThanMedianMaxHeap   = new MaxHeap<E>();
        _greaterThanMedianMinHeap   = new MaxHeap<E>();
        _lessOrEqualToMedianMaxHeap = new MaxHeap<E>();
        _lessOrEqualToMedianMinHeap = new MaxHeap<E>();
    }

  public:
    void insert(E *element) override {
        if (getLogicalSize() > 1) {
            if (isLogicalSizeEven()) {
                if (median() < *element) {
                    _greaterThanMedianMaxHeap->insert(element);
                } else {

                    // Transfer the maximum from `_lessOrEqualToMedianMaxHeap` to `_greaterThanMedianMaxHeap`
                    _greaterThanMedianMaxHeap->insert(
                            _lessOrEqualToMedianMaxHeap->deleteRoot());
                    _lessOrEqualToMedianMaxHeap->insert(element);
                }
            } else if (isLogicalSizeOdd()) {
                _lessOrEqualToMedianMaxHeap->insert(element);
            }
        } else {
            _lessOrEqualToMedianMaxHeap->insert(element);
        }
    }

  protected:
    void insertToLeftHeap(E *element) {
        _lessOrEqualToMedianMaxHeap->insert(element);
        _lessOrEqualToMedianMinHeap->insert(element);
    }

  protected:
    void insertToRightHeap(E *element) {
        _greaterThanMedianMaxHeap->insert(element);
        _greaterThanMedianMinHeap->insert(element);
    }

  protected:
    void deleteElement(E *element) {}

  protected:
    long int getLogicalSize() {
        return _greaterThanMedianMinHeap->getLogicalSize() +
               _greaterThanMedianMaxHeap->getLogicalSize();
    }

  protected:
    bool isLogicalSizeEven() { return getLogicalSize() % 2 == 0; }

  protected:
    bool isLogicalSizeOdd() { return !isLogicalSizeEven(); }

  protected:
    bool isLogicalSizeOfHeapAdtEven(
            HeapAdt<ElementInMinHeapAndMaxHeap<E>> *heapAdt) {
        return heapAdt->getLogicalSize() % 2 == 0;
    }

  protected:
    bool
    isLogicalSizeOfHeapAdtOdd(HeapAdt<ElementInMinHeapAndMaxHeap<E>> *heapAdt) {
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
        return *_lessOrEqualToMedianMaxHeap->getRoot(); // FIXME: check
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
    static std::ostream &printThis(std::ostream &             os,
                                   const PriorityQueue<K, V> &priorityQueue) {

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
