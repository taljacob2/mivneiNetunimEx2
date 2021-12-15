
#ifndef MIN_HEAP_ADT_H
#define MIN_HEAP_ADT_H

#include "Entry.h"

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
 */
template<typename K, typename V> class MinHeapADT {

  public:
    /**
     * @brief Deletes the *minimal element* from the heap, and returns it.
     *
     * @return the *minimal element* removed from the heap.
     */
    virtual Entry<K, V> *deleteMin() = 0;

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     */
    virtual void insert(Entry<K, V> *elementToInsert) = 0;

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param indexToFixFrom fixes the heap from this index downwards until the
     *                       leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       larger than one of his children, or when the root is a leaf.
     */
    virtual void fixHeap(long int indexToFixFrom) = 0;

  public:
    /**
     * @brief Builds a **Minimum-Heap** by giving an arrayToBuildFrom of
     *        elements as a parameter.
     *
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     */
    virtual void buildHeap(Entry<K, V> *arrayToBuildFrom,
                           long int     sizeOfArrayToBuildFrom) = 0;

  public:
    /**
     * @brief boolean value whether this heap empty or not.
     *
     * @return boolean value. *true* if the heap is empty, *false* if the
     *         heap is not empty.
     */
    virtual bool isEmpty() = 0;

  public:
    /**
     * @brief clears the heap from elements.
     */
    virtual void makeEmpty() = 0;
};


#endif // MIN_HEAP_ADT_H
