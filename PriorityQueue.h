
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "PriorityQueueAdt.h"

/**
 * @brief This *priority-queue* is implemented b y four *Heaps*, and each of
 *        these Heaps' elements are *Entries* that are composed by a *key* and a *value*.
 *
 * @attention the `median()` is defined as the element that its priority is
 *            `ceil (n / 2)`.
 *
 * @tparam K The `key` type of each entry. **Must** be `comparable`.
 *           The *priority* of each entry is based on this `key`.
 * @tparam V the type of *value* of each entry.
 * @see MinHeap
 * @see MaxHeap
 */
template<typename K, typename V>
class PriorityQueue : public PriorityQueueAdt<K, V> {

  private:
    HeapAdt<K, V> *_greaterThanMedianMaxHeap = nullptr;

  private:
    HeapAdt<K, V> *_greaterThanMedianMinHeap = nullptr;

  private:
    HeapAdt<K, V> *_lessOrEqualToMedianMaxHeap = nullptr;

  private:
    HeapAdt<K, V> *_lessOrEqualToMedianMinHeap = nullptr;

  public:
    explicit PriorityQueue(int physicalSizeOfEachHeap) {
        _greaterThanMedianMaxHeap   = new MaxHeap<K, V>(physicalSizeOfEachHeap);
        _greaterThanMedianMinHeap   = new MinHeap<K, V>(physicalSizeOfEachHeap);
        _lessOrEqualToMedianMaxHeap = new MaxHeap<K, V>(physicalSizeOfEachHeap);
        _lessOrEqualToMedianMinHeap = new MinHeap<K, V>(physicalSizeOfEachHeap);
    }

  public:
    PriorityQueue() = default;

  public:
    virtual ~PriorityQueue() {
        delete _greaterThanMedianMaxHeap;
        delete _greaterThanMedianMinHeap;
        delete _lessOrEqualToMedianMaxHeap;
        delete _lessOrEqualToMedianMinHeap;
    }

  public:
    Entry<K, V> max() override {
        return *_greaterThanMedianMaxHeap->getRoot(); // FIXME: check
    }

  public:
    Entry<K, V> deleteMax() override {}

  public:
    Entry<K, V> min() override {
        return *_lessOrEqualToMedianMinHeap->getRoot(); // FIXME: check
    }

  public:
    Entry<K, V> deleteMin() override {}

  public:
    void createEmpty() override {
        _greaterThanMedianMaxHeap   = new MaxHeap<K, V>();
        _greaterThanMedianMinHeap   = new MaxHeap<K, V>();
        _lessOrEqualToMedianMaxHeap = new MaxHeap<K, V>();
        _lessOrEqualToMedianMinHeap = new MaxHeap<K, V>();
    }

  public:
    void insert(Entry<K, V> &element) override {
        if (getLogicalSize() > 1) {
            if (isLogicalSizeEven()) {
                if (median() < element) {
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

  private:
    void insertToLeftHeap(Entry<K, V> &element) {
        _lessOrEqualToMedianMaxHeap->insert(element);
        _lessOrEqualToMedianMinHeap->insert(element);
    }

  private:
    void insertToRightHeap(Entry<K, V> &element) {
        _greaterThanMedianMaxHeap->insert(element);
        _greaterThanMedianMinHeap->insert(element);
    }

  private:
    void deleteElement(Entry<K, V> &element){

    }

  private:
    long int getLogicalSize() {
        return _greaterThanMedianMinHeap->getLogicalSize() +
               _greaterThanMedianMaxHeap->getLogicalSize();
    }

  private:
    bool isLogicalSizeEven() { return getLogicalSize() % 2 == 0; }

  private:
    bool isLogicalSizeOdd() { return !isLogicalSizeEven(); }

  private:
    bool isLogicalSizeOfHeapAdtEven(HeapAdt<K, V> heapAdt) {
        return heapAdt.getLogicalSize() % 2 == 0;
    }

  private:
    bool isLogicalSizeOfHeapAdtOdd(HeapAdt<K, V> heapAdt) {
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
    Entry<K, V> median() override {
        return *_lessOrEqualToMedianMaxHeap->getRoot(); // FIXME: check
    }

  public:
    friend std::ostream &operator<<(std::ostream &       os,
                                    const PriorityQueue &priorityQueue) {
        return printThis(os, priorityQueue);
    }

  private:
    std::ostream &print(std::ostream &                os,
                        const PriorityQueueAdt<K, V> &priorityQueueAdt) const {
        PriorityQueue &priorityQueue =
                (PriorityQueue &) priorityQueueAdt; // Force cast.
        return printThis(os, priorityQueue);
    }

  private:
    static std::ostream &printThis(std::ostream &             os,
                                   const PriorityQueue<K, V> &priorityQueue) {

        os << "---------------------------- ";
        os << "_greaterThanMedianMaxHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._greaterThanMedianMaxHeap->print(
                std::cout, *priorityQueue._greaterThanMedianMaxHeap);

        os << "---------------------------- ";
        os << "_greaterThanMedianMinHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._greaterThanMedianMinHeap->print(
                std::cout, *priorityQueue._greaterThanMedianMinHeap);

        os << "---------------------------- ";
        os << "_lessOrEqualToMedianMaxHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._lessOrEqualToMedianMaxHeap->print(
                std::cout, *priorityQueue._lessOrEqualToMedianMaxHeap);

        os << "---------------------------- ";
        os << "_lessOrEqualToMedianMinHeap:";
        os << " ----------------------------" << std::endl;
        priorityQueue._lessOrEqualToMedianMinHeap->print(
                std::cout, *priorityQueue._lessOrEqualToMedianMinHeap);
        os << "---------------------------- ";

        return os;
    }
};

#endif // PRIORITY_QUEUE_H
