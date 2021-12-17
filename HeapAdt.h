
#ifndef HEAP_ADT_H
#define HEAP_ADT_H

/**
 * @brief This class represents an *abstract* **Heap**,
 *        which its elements are *comparable* to each other.
 *
 * The heap compares its elements to each other, by a comparable `key`
 * located in each element.
 * @tparam E the type of each `element`.
 * @note The terms `element`, `node` are synonyms.
 * @note The terms `heap` and `tree` are synonyms.
 * @note The term `<<predicate-resulted>>` is a result of a predicate method
 *       that returns `bool`, and tells whether a `node` should be *swapped*
 *       with its `parent` or not.
 */
template<typename E> class HeapAdt {

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
    virtual E *getRoot() = 0;

  public:
    /**
     * @brief Deletes the *root element* from the heap, and returns it.
     *
     * @return the *root element* removed from the heap.
     */
    virtual E *deleteRoot() = 0;

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     */
    virtual void insert(E *elementToInsert) = 0;

  public:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **downwards**.
     *
     * @param indexToFixFrom fixes the heap from this index **downwards** until
     *                       the leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       `<<predicate-resulted>>` than one of his children,
     *       or when the root is a leaf.
     * @see fixHeapUpwards(unsigned long)
     */
    virtual void fixHeap(unsigned long indexToFixFrom) = 0;

  public:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **upwards**.
     *
     * @param indexToFixFrom fixes the heap from this index **upwards** until
     *                       the root of the heap.
     * @note this method will continue to run until the root is no longer
     *       `predicated` than one of his children, or when the root is a leaf.
     * @see fixHeap(unsigned long)
     */
    virtual void fixHeapUpwards(unsigned long indexToFixFrom) = 0;

  public:
    /**
     * @brief Builds a **Heap** by giving an arrayToBuildFrom of
     *        elements as a parameter.
     *
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     */
    virtual void buildHeap(E *           arrayToBuildFrom,
                           unsigned long sizeOfArrayToBuildFrom) = 0;

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
    virtual unsigned long getLogicalSize() const = 0;

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
     *              for (unsigned long i = 0; i < heap._logicalSize; i++) {
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
