
#ifndef PRIORITY_QUEUE_ADT_H
#define PRIORITY_QUEUE_ADT_H

#include "Entry.h"

/**
 * @brief An interface for a Priority-Queue.
 *        Each element in this data-structure is represented by a an `Entry`
 *        that has a `key` and a `value`.
 *
 * @tparam K The `key` type of each element. **Must** be `comparable`.
 *           The *priority* of each element is based on this `key`.
 * @tparam V The `value` type of each element.
 * @see Entry
 */
template<typename K, typename V> class PriorityQueueAdt {

    /**
     * @return the highest priority element, *without removing it* from the
     *         data-structure.
     */
    Entry<K, V> max() = 0;

    /**
     * @return the highest priority element, *and removes it* from the
     *         data-structure.
     */
    Entry<K, V> deleteMax() = 0;

    /**
     * @return the lowest priority element, *without removing it* from the
     *         data-structure.
     */
    Entry<K, V> min() = 0;

    /**
     * @return the lowest priority element, *and removes it* from the
     *         data-structure.
     */
    Entry<K, V> deleteMin() = 0;

    /**
     * @brief creates this new empty data-structure.
     */
    void createEmpty() = 0;

    /**
     * @brief inserts an element to the data-structure.
     * @param element the element to insert.
     */
    void insert(Entry<K, V> &element) = 0;

    /**
     * @return the median priority element.
     */
    Entry<K, V> median() = 0;
};

#endif // PRIORITY_QUEUE_ADT_H
