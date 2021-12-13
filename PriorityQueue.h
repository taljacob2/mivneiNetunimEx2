
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "PriorityQueueAdt.h"

template<typename K, typename V>
class PriorityQueue : public PriorityQueueAdt<K, V> {

  public:
    Entry<K, V> max() override {}

  public:
    Entry<K, V> deleteMax() override {}

  public:
    Entry<K, V> min() override {}

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
};

#endif // PRIORITY_QUEUE_H
