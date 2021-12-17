
#ifndef HEAP_ADT_H
#define HEAP_ADT_H

#include "Entry.h"

/**
 * @brief This class represents an *abstract* **Heap**,
 *        which its elements are *Entries* that are composed by a
 *        *key* and a *value*.
 *
 * The heap compares its elements to each other, by the comparable `key` field
 * located in each `Entry` element.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @note The terms `element`, `node` and 'entry' are synonyms.
 * @note The terms `heap` and `tree` are synonyms.
 * @note The term `<<predicate-resulted>>` is a result of a predicate method
 *       that returns `bool`, and tells whether a `node` should be *swapped*
 *       with its `parent` or not.
 * @note DEVELOPER NOTE: `long int` and `long` types are the same.
 * @see Entry
 */
template<typename K, typename V> class HeapAdt {

  public:
    HeapAdt() = default;

  public:
    virtual ~HeapAdt() = default;

  public:
    /**
     * @brief Returns the *root element* of the heap, without removing it
     *        from the heap.
     *
     * @return the *root element* of the heap.
     */
    virtual Entry<K, V> *getRoot() = 0;

  public:
    /**
     * @brief Deletes the *root element* from the heap, and returns it.
     *
     * @return the *root element* removed from the heap.
     */
    virtual Entry<K, V> *deleteRoot() = 0;

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     */
    virtual void insert(Entry<K, V> *elementToInsert) = 0;

  public:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **downwards**.
     *
     * @param indexToFixFrom fixes the heap from this index **downwards** until
     *                       the leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       `<<predicate-resulted>>` than one of his children,
     *       or when the root is a leaf.
     * @see fixHeapUpwards(long int)
     */
    virtual void fixHeap(long int indexToFixFrom) = 0;

  public:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **upwards**.
     *
     * @param indexToFixFrom fixes the heap from this index **upwards** until
     *                       the root of the heap.
     * @note this method will continue to run until the root is no longer
     *       `predicated` than one of his children, or when the root is a leaf.
     * @see fixHeap(long int)
     */
    virtual void fixHeapUpwards(long int indexToFixFrom) = 0;

  public:
    /**
     * @brief Builds a **Heap** by giving an arrayToBuildFrom of
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

  public:
    /**
     * @note This is an extension method - made for convenience.
     * @return The logicalSize of the data-structure.
     */
    virtual long int getLogicalSize() const = 0;

  public:
    /**
     * @brief Force the sub-classes of this class to implement the `print`
     *        method, so others could print this class' sub-classes
     *        polymorphically.
     *
     * @note This is an extension method - made for convenience.
     *
     * For example, you could print this class like so:
     * @code
     * heapAdt->print(std::cout);
     * @endcode
     *
     * Tip:
     *
     * Define the `print` method like so (for example):
     *
     * @code
     *   public:
     *     friend std::ostream &operator<<(std::ostream &os, const HeapAdtSubClass &heap) {
     *         return printThis(os, heap);
     *     }
     *
     *   private:
     *     std::ostream &print(std::ostream &       os,
     *                         const HeapAdt<K, V> &heapAdt) const override {
     *         return printThis(os, *this);
     *     }
     *
     *   private:
     *     static std::ostream &printThis(std::ostream &os, const HeapAdtSubClass<K, V>
     *    &heap) {
     *                os << "_array{\n";
     *
     *                  // In case the _array is empty, print a message instead of elements.
     *              if (heap._logicalSize == 0) {
     *                  os << "The _array is empty."
     *                     << "\n";
     *              }
     *              for (long int i = 0; i < heap._logicalSize; i++) {
     *                  os << *heap._array[i] << ";";
     *                  os << "\n";
     *              }
     *              os << "}; ";
     *
     *              os << "_logicalSize: " << heap._logicalSize
     *              << ", _physicalSize: " << heap._physicalSize << ";"
     *              << "\n";
     *           }
     * @endcode
     *
     * @param os output-stream.
     * @param heapAdt a `HeapAdt`.
     * @return the given @p os.
     */
    virtual std::ostream &print(std::ostream &os) const = 0;
};

#endif // HEAP_ADT_H
