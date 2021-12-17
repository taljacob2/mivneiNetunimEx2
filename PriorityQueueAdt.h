
#ifndef PRIORITY_QUEUE_ADT_H
#define PRIORITY_QUEUE_ADT_H

/**
 * @brief An interface for a Priority-Queue.
 *        Each element in this data-structure is represented by a an `Entry`
 *        that has a `key` and a `value`.
 *
 * @tparam E The type of each element. **Must** be `comparable`.
 *           The *priority* of each element is based on this comparable `key`.
 */
template<typename E> class PriorityQueueAdt {

  public:
    PriorityQueueAdt() = default;

  public:
    virtual ~PriorityQueueAdt() = default;

  public:
    /**
     * @return the highest priority element, *without removing it* from the
     *         data-structure.
     */
    virtual E *max() = 0;

  public:
    /**
     * @return the highest priority element, *and removes it* from the
     *         data-structure.
     */
    virtual E *deleteMax() = 0;

  public:
    /**
     * @return the lowest priority element, *without removing it* from the
     *         data-structure.
     */
    virtual E *min() = 0;

  public:
    /**
     * @return the lowest priority element, *and removes it* from the
     *         data-structure.
     */
    virtual E *deleteMin() = 0;

  public:
    /**
     * @brief creates this new empty data-structure.
     */
    virtual void createEmpty() = 0;

  public:
    /**
     * @brief inserts an element to the data-structure.
     * @param element the element to insert.
     */
    virtual void insert(E *element) = 0;

  public:
    /**
     * @return the median priority element.
     */
    virtual E *median() = 0;

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
     * priorityQueueAdt->print(std::cout);
     * @endcode
     *
     * Tip:
     *
     * Define the `print` method like so (for example):
     *
     * @code
     *   public:
     *     friend std::ostream &operator<<(std::ostream &os, const PriorityQueueAdtSubClass &priorityQueue) {
     *         return printThis(os, priorityQueue);
     *     }
     *
     *   private:
     *     std::ostream &print(std::ostream &       os,
     *                         const PriorityQueueAdt<K, V> &priorityQueueAdt) const override {
     *         return printThis(os, *this);
     *     }
     *
     *   private:
     *     static std::ostream &printThis(std::ostream &os, const PriorityQueueAdtSubClass<K, V>
     *    &priorityQueue) {
     *              ...
     *           }
     * @endcode
     * @param os output-stream.
     * @param priorityQueueAdt a `PriorityQueueAdt`.
     * @return the given @p os.
     */
    virtual std::ostream &print(std::ostream &os) const = 0;
};

#endif // PRIORITY_QUEUE_ADT_H
