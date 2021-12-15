
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "PriorityQueueAdt.h"

/**
 * @brief This *priority-queue* is implemented b y four *Heaps*, and each of
 *        these Heaps' elements are *Entries* that are composed by a *key* and a *value*.
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
    HeapAdt<K, V> *_greaterThanMedianMaxHeap = new MaxHeap<K, V>();

  private:
    HeapAdt<K, V> *_greaterThanMedianMinHeap = new MinHeap<K, V>();

  private:
    HeapAdt<K, V> *_lowerOrEqualToMedianMaxHeap = new MaxHeap<K, V>();

  private:
    HeapAdt<K, V> *_lowerOrEqualToMedianMinHeap = new MinHeap<K, V>();

  public:
    explicit PriorityQueue(bool invokeCreateEmpty) {
        if (invokeCreateEmpty) { this->createEmpty(); }
    }

  public:
    PriorityQueue() = default;

  public:
    virtual ~PriorityQueue() {
        delete _greaterThanMedianMaxHeap;
        delete _greaterThanMedianMinHeap;
        delete _lowerOrEqualToMedianMaxHeap;
        delete _lowerOrEqualToMedianMinHeap;
    }

  public:
    Entry<K, V> max() override {
        return *this->_greaterThanMedianMaxHeap->root(); // FIXME: check
    }

  public:
    Entry<K, V> deleteMax() override {}

  public:
    Entry<K, V> min() override {
        return *this->_lowerOrEqualToMedianMinHeap->root(); // FIXME: check
    }

  public:
    Entry<K, V> deleteMin() override {}

  public:
    void createEmpty() override {}

  public:
    void insert(Entry<K, V> &element) override {}

  public:
    /**
     * @return the median priority element - defining the median as the
     *         element that its priority is `ceil (n / 2)`
     */
    Entry<K, V> median() override {}

  private:
    std::ostream &
    print(std::ostream &                os,
          const PriorityQueueAdt<K, V> &priorityQueueAdt) const {
        PriorityQueue &priorityQueue =
                (PriorityQueue &) priorityQueueAdt; // Force cast.
        return printThis(os, priorityQueue);
    }

  private:
    static std::ostream &printThis(std::ostream &             os,
                                   const PriorityQueue<K, V> &priorityQueue) {

        os << priorityQueue._greaterThanMedianMaxHeap->print(
                std::cout, *priorityQueue._greaterThanMedianMaxHeap);

        os << "_greaterThanMedianMaxHeap: " << std::endl
           << *(priorityQueue._greaterThanMedianMaxHeap) << std::endl;

        os << "_greaterThanMedianMinHeap: " << std::endl
           << *(priorityQueue._greaterThanMedianMinHeap) << std::endl;

        os << "_lowerOrEqualToMedianMaxHeap: " << std::endl
           << *(priorityQueue._lowerOrEqualToMedianMaxHeap) << std::endl;

        os << "_lowerOrEqualToMedianMinHeap: " << std::endl
           << *(priorityQueue._lowerOrEqualToMedianMinHeap) << std::endl;
        return os;
    }
};

#endif // PRIORITY_QUEUE_H
