
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "Heap.h"
#include "my_algorithms.h"

/**
 * @brief This class implements a **Minimum-Heap** which its elements are
 *        pointers to **lvalue `Entries`** that are composed of a *key* and a *value*.
 *
 * @li Once the heap has been built by @link buildHeap @endlink or
 * @link MinHeap(E *, long int) @endlink, its *physical-size* is
 * treated as a constant - thus unchangeable. In case the user wishes to
 * change the *physical-size* of the heap, there is a *must* to invoke @link
 * buildHeap @endlink again.
 * @li The heap compares its elements to each other, by the comparable `key`
 * field located in each `element`.
 * @tparam E the type of each element.
 * @note The terms `element`, `node` are synonyms.
 * @attention The `elements` pointed must be **lvalues**.
 * @see Heap
 */
template<typename E> class MinHeap : public Heap<E> {

  public:
    MinHeap(E *arrayToBuildFrom, long sizeOfArrayToBuildFrom)
        : Heap<E>(arrayToBuildFrom, sizeOfArrayToBuildFrom) {}

  public:
    explicit MinHeap(long physicalSize) : Heap<E>(physicalSize) {}

  public:
    MinHeap() : Heap<E>() {}

  public:
    virtual ~MinHeap() = default;

  private:
    long getIndexOfChildToSwapWithParent(E **array, long size,
                                         long indexToElement1,
                                         long indexToElement2) override {
        return my_algorithms::min(array, size, indexToElement1,
                                  indexToElement2);
    }

  private:
    bool predicateIsSwapNeeded(E element1, E element2) override {
        return element1 > element2;
    }
};

#endif // MIN_HEAP_H
