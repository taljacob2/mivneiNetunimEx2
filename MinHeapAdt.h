
#ifndef MIN_HEAP_ADT_H
#define MIN_HEAP_ADT_H

#include "Entry.h"
#include "HeapAdt.h"

/**
 * @brief This class represents an *abstract* **Minimum-Heap**,
 *        which its elements are *Entries* that are composed by a
 *        *key* and a *value*.
 *
 * The heap compares its elements to each other, by the comparable `key` field
 * located in each `Entry` element.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @note The terms `element`, `node` and 'entry' are synonyms.
 * @see Entry
 * @see HeapAdt
 */
template<typename K, typename V> class MinHeapAdt : public HeapAdt<K, V> {

  public:
    /**
     * @brief Deletes the *minimal element* from the heap, and returns it.
     *
     * @return the *minimal element* removed from the heap.
     * @see deleteRoot()
     */
    virtual Entry<K, V> *deleteMin() = 0;
};


#endif // MIN_HEAP_ADT_H
