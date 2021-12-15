
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "Heap.h"
#include "my_algorithms.h"
#include <exception>
#include <ostream>
#include <stdexcept>
#include <string>

/**
 * @brief This class implements a **Minimum-Heap** which its elements are
 *        pointers to **lvalue `Entries`** that are composed of a *key* and a *value*.
 *
 * @li Once the heap has been built by @link buildHeap @endlink or
 * @link MinHeap(Entry<K, V> *, long int) @endlink, its *physical-size* is
 * treated as a constant - thus unchangeable. In case the user wishes to
 * change the *physical-size* of the heap, there is a *must* to invoke @link
 * buildHeap @endlink again.
 * @li The heap compares its elements to each other, by the comparable `key`
 * field located in each `Entry` element.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @note The terms `element`, `node` and 'entry' are synonyms.
 * @attention The `Entries` pointed must be **lvalues**.
 * @see Entry
 * @see MinHeapAdt
 */
template<typename K, typename V> class MinHeap : public Heap<K, V> {


};

#endif // MIN_HEAP_H
