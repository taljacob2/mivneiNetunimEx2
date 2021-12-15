
#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "Heap.h"
#include "my_algorithms.h"

/**
 * @brief This class implements a **Maximum-Heap** which its elements are
 *        pointers to **lvalue `Entries`** that are composed of a *key* and a *value*.
 *
 * @li Once the heap has been built by @link buildHeap @endlink or
 * @link MaxHeap(Entry<K, V> *, long int) @endlink, its *physical-size* is
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
 * @see Heap
 */
template<typename K, typename V> class MaxHeap : public Heap<K, V> {

  public:
    MaxHeap(Entry<K, V> *arrayToBuildFrom, long sizeOfArrayToBuildFrom)
        : Heap<K, V>(arrayToBuildFrom, sizeOfArrayToBuildFrom) {}

  public:
    explicit MaxHeap(long physicalSize) : Heap<K, V>(physicalSize) {}

  public:
    MaxHeap() : Heap<K, V>() {}

  public:
    virtual ~MaxHeap() = default;

  private:
    long getIndexOfChildToSwapWithParent(Entry<K, V> **array, long size,
                                         long indexToElement1,
                                         long indexToElement2) override {
        return my_algorithms::max(array, size, indexToElement1,
                                  indexToElement2);
    }

  private:
    bool predicateIsSwapNeeded(Entry<K, V> element1,
                               Entry<K, V> element2) override {
        return element1 < element2;
    }
};

#endif // MAX_HEAP_H
