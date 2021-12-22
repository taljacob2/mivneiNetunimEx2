
#ifndef HEAP_H
#define HEAP_H

#include "HeapAdt.h"
#include "my_algorithms.h"
#include <cmath>

/**
 * @note The term `<<predicate-resulted>>` is a result of a predicate method
 *       that returns `bool`, and tells whether a `node` should be *swapped*
 *       with its `parent` or not. In this implementation,
 *       `<<predicate-resulted>>` is defined to be the result of the
 *       @link predicateIsSwapNeeded(E, E) @endlink method.
 * @tparam E the type of each `element`.
 * @see HeapAdt
 */
template<typename E> class Heap : public HeapAdt<E> {

  protected:
    static constexpr char *IS_EMPTY_MESSAGE = (char *) "Heap: heap is empty.";

  protected:
    static constexpr char *IS_FULL_MESSAGE = (char *) "Heap: array is full.";

  protected:
    static constexpr char *OUT_OF_RANGE_MESSAGE =
            (char *) "Heap: out of range.";

  protected:
    /**
     * @see fixHeap(unsigned long)
     * @see fixHeapUpwards(unsigned long)
     * @see fixHeapWhile(unsigned long, Direction)
     */
    enum class Direction { UPWARDS, DOWNWARDS };

  protected:
    /**
     * Array of pointers to **lvalue `E`** that serve as `elements`.
     * Initialized to `nullptr`.
     */
    E **_array = nullptr;

  protected:
    /// The *physical-size* of the `_array`. Initialized to `0`.
    unsigned long _physicalSize = 0;

  protected:
    /// The *logical-size* of the `_array`. Initialized to `0`.
    unsigned long _logicalSize = 0;

  public:
    unsigned long getLogicalSize() const override { return _logicalSize; }

  public:
    /**
     * @brief Constructor, initializes the `_array`.
     *
     * Builds a **Heap** by giving an @p arrayToBuildFrom of
     * **lvalue `E`** as a parameter. Done by invoking the
     * @link buildHeap @endlink method.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     * @see buildHeap
     */
    Heap(E *arrayToBuildFrom, unsigned long sizeOfArrayToBuildFrom) {
        buildHeap(arrayToBuildFrom, sizeOfArrayToBuildFrom);
    }

  public:
    /**
     * @brief Constructor, sets the `_physicalSize` of the `_array` to be @p
     *        _physicalSize.
     *
     * @note the content of the `_array` remains empty.
     * @param physicalSize set the `_physicalSize` of the `_array` to be this size.
     */
    explicit Heap(unsigned long physicalSize) {
        this->_physicalSize = physicalSize;
        this->_array        = new E *[physicalSize];
        for (unsigned long i = 0; i < _physicalSize; i++) {
            _array[i] = nullptr;
        }
    }

  public:
    /**
     * @brief Default constructor creates an arbitrary physicalSize of 100.
     */
    Heap() : Heap(100) {}

  public:
    virtual ~Heap() { deleteThis(); }

  private:
    void deleteThis() { delete[] _array; }

  public:
    /**
     * @return the root element, which is the top element in the heap.
     * @throws std::runtime_error in case there are no elements in the heap,
     *         and the user requested to retrieve the root.
     * @see getElement(unsigned long)
     */
    E *getRoot() override { return getElement(0); }

  public:
    /**
     * @return an element in the heap corresponds to the given @p index.
     * @throws std::out_of_range in case the index provided is out of range.
     * @throws std::runtime_error in case there are no elements in the heap,
     *         and the user requested to retrieve the root.
     */
    E *getElement(unsigned long index) {
        if (!_logicalSize) {
            throw std::runtime_error(IS_EMPTY_MESSAGE);
        } else {
            assertOutOfRange(index);
            return this->_array[index];
        }
    }

  public:
    /**
     * @brief Deletes the *root element* from the heap, and returns it.
     *
     * @note After removing the *root element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap afterwards.
     * @attention in case the `_logicalSize` of the `_array` is `0`,
     *            this method returns `null_ptr`.
     * @return the *root element* removed from the heap.
     * @throws std::runtime_error in case the heap is already empty.
     * @throws std::out_of_range in case the index provided is out of range.
     * @see fixHeap(unsigned long)
     * @see deleteElement(unsigned long)
     */
    E *deleteRoot() override { return deleteElement(0); }

  public:
    /**
     * @brief Deletes the *element* from the heap, and returns it.
     *
     * @note After removing the *element* from the heap, this method
     *       calls the @link fixHeap(index) @endlink method, in order to fix
     *       the heap afterwards.
     * @attention in case the `_logicalSize` of the `_array` is `0`,
     *            this method returns `nullptr`.
     * @return the *element* removed from the heap.
     * @throws std::runtime_error in case the heap is already empty.
     * @throws std::out_of_range in case the index provided is out of range.
     * @see fixHeap(unsigned long)
     * @see deleteElement(unsigned long, bool)
     */
    E *deleteElement(unsigned long index) { return deleteElement(index, true); }

  private:
    /**
     * @brief Deletes the *element* from the heap, and returns it.
     * @deprecated Caution when setting @p fixHeapAfterDeletion to `false`.
     *
     * @note After removing the *element* from the heap, this method
     *       calls the @link fixHeap(index) @endlink method, in order to fix
     *       the heap afterwards - only if the @p fixHeapAfterDeletion
     *       parameter is `true`.
     * @attention in case the `_logicalSize` of the `_array` is `0`,
     *            this method returns `nullptr`.
     * @param fixHeapAfterDeletion determines if the method will call the
     *                             @link fixHeap(index) @endlink method, after
     *                             deletion, to ensure that the heap is still
     *                             valid.
     * @return the *element* removed from the heap.
     * @throws std::runtime_error in case the heap is already empty.
     * @throws std::out_of_range in case the index provided is out of range.
     * @see fixHeap(unsigned long)
     */
    E *deleteElement(unsigned long index, bool fixHeapAfterDeletion) {

        /* Save the value of `element` to return in the end of the method. */
        E *returnElement = getElement(index);

        if (this->_logicalSize >= 2) {
            deleteElementWhenThereAreTwoOrMoreElements(index,
                                                       fixHeapAfterDeletion);
        } else if (this->_logicalSize > 0) {

            /* Delete `_array[0]` manually. */
            this->_array[0] = nullptr;

            /* Decrease the `_logicalSize` of the _array by `1`. */
            this->_logicalSize--;
        }
        return returnElement;
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when there are `2` or more elements in the heap.
     *
     * @note After removing the *root element* from the heap, this method
     *       calls the @link fixHeap(indexOfElementToDelete) @endlink method,
     *       in order to fix the heap afterwards - only if the @p
     *       fixHeapAfterDeletion parameter is `true`.
     * @param fixHeapAfterDeletion determines if the method will call the
     *                             @link fixHeap(indexOfElementToDelete)
     *                             @endlink method, after deletion, to
     *                             ensure that the heap is still valid.
     * @see fixHeap(unsigned long)
     */
    void deleteElementWhenThereAreTwoOrMoreElements(
            unsigned long indexOfElementToDelete, bool fixHeapAfterDeletion) {

        /*
         * There are at least `2` elements in the heap,
         * so we are able to delete an element.
         */

        /* Set the `indexOfElementToDelete` element in the `_array` to be the `last` element. */
        // TODO: need to update EWrapper's indexes here.
        this->_array[indexOfElementToDelete] =
                this->_array[this->_logicalSize - 1];
        onUpdateElementWithIndex(_array[indexOfElementToDelete],
                                 indexOfElementToDelete);

        /* Set the `last` element to be `nullptr`. */
        this->_array[this->_logicalSize - 1] = nullptr;

        /*
         * Decrease the `_logicalSize` of the `_array` by `1`,
         * before invoking `fixHeap(indexOfElementToDelete)`.
         */
        this->_logicalSize--;

        /* After deletion, invoke `fixHeap(indexOfElementToDelete)` to fix the heap. */
        if (fixHeapAfterDeletion) { fixHeap(indexOfElementToDelete); }
    }

  public:
    /**
     * @brief Builds a **Heap** by giving an @p arrayToBuildFrom of
     *        **lvalue `E`** as a parameter.
     *
     * Done by making an _array of pointers to the elements given in the @p
     * arrayToBuildFrom.
     * @param arrayToBuildFrom the given _array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the _array to build the
     *                               heap from.
     * @note In case there is already an `allocated` `_array` in this heap,
     *       this method ensures to `delete []` it *before* handling the
     *       building process.
     * @attention the `E` elements in the @p arrayToBuildFrom must be
     *            **lvalues**.
     */
    void buildHeap(E *           arrayToBuildFrom,
                   unsigned long sizeOfArrayToBuildFrom) override {

        /* Delete the old _array if there is any. */
        deleteThis();

        /* Initialize a `new` empty _array of pointers to elements given. */
        this->_physicalSize = sizeOfArrayToBuildFrom;
        this->_logicalSize  = sizeOfArrayToBuildFrom;
        this->_array        = new E *[sizeOfArrayToBuildFrom];
        for (unsigned long i = 0; i < sizeOfArrayToBuildFrom; i++) {
            this->_array[i] = &arrayToBuildFrom[i];
        }

        /*
         * `currentIndex` should be in between `0` and `(_logicalSize / 2)`.
         * Note: the almost last level has `(_logicalSize / 2)` `nodes`.
         */
        unsigned long lastIndex = this->_logicalSize - 1;
        for (unsigned long currentIndex = getParentIndex(lastIndex);
             currentIndex >= 0; currentIndex--) {
            fixHeap(currentIndex);
        }
    }

  public:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **downwards**.
     * @param indexToFixFrom an index of an element in the heap, that the
     *                       user wishes to fix the heap from.
     * @see fixHeap(unsigned long, Direction)
     */
    void fixHeap(unsigned long indexToFixFrom) override {
        fixHeap(indexToFixFrom, Direction::DOWNWARDS);
    }

  public:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **upwards**.
     * @param indexToFixFrom an index of an element in the heap, that the
     *                       user wishes to fix the heap from.
     * @see fixHeap(unsigned long, Direction)
     */
    void fixHeapUpwards(unsigned long indexToFixFrom) override {
        fixHeap(indexToFixFrom, Direction::UPWARDS);
    }

  private:
    /**
     * @brief This method *fixes* the heap from a given @p indexToFixFrom till
     *        the *end* of the heap. The *end* of the heap could be either the
     *        *root* of the heap (the topmost element), or the rightmost leaf.
     *        The *end* of the heap is determined by the given @p direction that the
     *        user wishes to fix the heap to. This could be *downwards* or *upwards*.
     *
     * For example, if the user picks the `Direction::DOWNWARDS` direction
     * then this method would handle a heap that is *valid* from the root
     * downwards until the @p indexToFixFrom, and from there and on
     * downwards the heap is *invalid* - means: that the `node` in the
     * @p indexToFixFrom is no `<<predicate-resulted>>` than both of its
     * children.
     *
     * The method ensures to *correct* the heap by *fixing* its
     * validity - means, checking that each `node` is
     * `NOT <<predicate-resulted>>` than
     * both of its children.
     *
     * @param indexToFixFrom the method fixes the heap from this index
     *                       downwards until the leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       `<<predicate-resulted>>` than both of its children,
     *       or when the root is a leaf.
     * @attention there is no use to give @p indexToFixFrom that is `<<predicate-resulted>>`
     *            than `(_logicalSize / 2)`, because indexes larger than
     *            `(_logicalSize / 2)` point to leaf `node`s, thus the method
     *            will have no effect, as explained earlier.
     * @throws std::out_of_range in case the index provided is out of range.
     * @see Direction
     * @see fixHeap(unsigned long)
     * @see fixHeapUpwards(unsigned long)
     */
    void fixHeap(unsigned long indexToFixFrom, Direction direction) {

        /* Check that `indexToFixFrom` is a legal index. */
        assertOutOfRange(indexToFixFrom);

        fixHeapLegalIndex(indexToFixFrom, direction);
    }

  private:
    /**
     * @param index the index to assert is *not* out of range of the heap's
     *              logical size.
     * @throws std::out_of_range in case the index provided is out of range.
     */
    void assertOutOfRange(unsigned long index) {
        if ((index < 0) || (this->_logicalSize <= index)) {

            // TODO: print debug
            std::cout << "index =" << index << std::endl;
            std::cout << "_logicalSize =" << _logicalSize << std::endl;

            // std::string message;
            // message.append("The index provided is out of range. There are ");
            // message.append(std::to_string(_logicalSize));
            // message.append(" elements in the heap.\n");

            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when the provided @p currentIndex is a legal index.
     *        This method is being invoked by the @link fixHeap(unsigned long,
     *        Direction) @endlink method.
     *
     * @param currentIndex has been checked as a legal index. Should be
     *                     in between `0` and `(_logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @param direction tells the `Direction` of which the `fixHeap` would
     *                  iterate.
     * @see fixHeap(unsigned long)
     * @see fixHeapUpwards(unsigned long)
     * @see Direction
     */
    void fixHeapLegalIndex(unsigned long indexToFixFrom, Direction direction) {

        /*
         * `currentIndex` should be in between `0` and `(_logicalSize / 2)`.
         *
         * Note: the `almost last` level has `(_logicalSize / 2)` `nodes`.
         * Attention: there is no use to give `indexToFixFrom` that is larger
         *            than `(_logicalSize / 2)`.
         */
        unsigned long currentIndex = indexToFixFrom;
        if (this->_array[currentIndex] == nullptr) {

            /*
             * The `indexToFixFrom` is out of range. Throw a message.
             * Note: should not be happening here, thanks to already checked
             * scenario.
             */
            // std::string message;
            // message.append(
            //         "The index provided is out of range. The element "
            //         "you have provided is `nullptr`. Thus, in-comparable.\n");

            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        /* _array[currentIndex] is not `nullptr`. Thus, comparable. */
        fixHeapWhile(currentIndex, direction);
    }

  protected:
    /**
     * @brief This method is a *protected* method, that represents a `while`
     *        that is being invoked by the @link fixHeap(unsigned long) @endlink method.
     *
     * The `while` loop has `2` stop conditions:
     *  @li there are no children to the `node` that is being iterated ( =
     *  the `node` that is being iterated is a `leaf`.
     *  @li the `node` that is being iterated is *not* `swappable` with each of
     *  its children.
     * @param currentIndex should be in between `0` and `(_logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @see fixHeap(unsigned long)
     * @see fixHeapUpwards(unsigned long)
     * @see Direction
     */
    void fixHeapWhile(unsigned long currentIndex, Direction direction) {

        /* _array[currentIndex] is not `nullptr`. Thus, comparable. */
        while ((0 <= currentIndex) && (currentIndex < (_logicalSize / 2))) {

            /* Get the index that points to the `swappable` element. */
            unsigned long indexOfSwappableChildOfCurrentRoot =
                    getIndexOfChildToSwapWithParent(_array, _logicalSize,
                                                    currentIndex * 2 + 1,
                                                    currentIndex * 2 + 2);
            if (_array[indexOfSwappableChildOfCurrentRoot] != nullptr) {

                /*
                 * There is a living element.
                 * Compare by keys.
                 * `swap` the elements if needed, to maintain the validity of
                 * the heap as a `Heap`.
                 */
                if (predicateIsSwapNeeded(
                            _array[currentIndex],
                            _array[indexOfSwappableChildOfCurrentRoot])) {
                    onSwapIsNeeded(currentIndex,
                                   indexOfSwappableChildOfCurrentRoot);

                    /*
                     * Set the updated iterator index to the replaced index.
                     * Note: this enlarges the index.
                     */
                    if (direction == Direction::DOWNWARDS) {
                        currentIndex = indexOfSwappableChildOfCurrentRoot;
                    } else if (direction == Direction::UPWARDS) {
                        currentIndex = getParentIndex(currentIndex);
                    }
                } else {
                    /*
                     * Second stop condition:
                     * the parent is not smaller than its child. break.
                     */
                    break;
                }
            } else {

                /*
                 * There is no element to compare with.
                 * Thus, this `node` does not have children,
                 * and is actually a leaf.
                 */
                break;
            }
        }
    }

  protected:
    virtual void onSwapIsNeeded(unsigned long index1,
                                unsigned long index2) const {
        my_algorithms::swap(_array, index1, index2);
    }

  protected:
    /**
     * @brief This method enables the sub-classes of `this` class,
     *        to add logic right after an update of an element to another index.
     * @param element an element that was just changed its index.
     */
    virtual void onUpdateElementWithIndex(E *&          element,
                                          unsigned long newIndex) const {}

  protected:
    /**
     * @note in case @p currentIndex is `0`, then the result will be `-1`.
     * @param currentIndex the index of the element to get its parent element
     *                     index.
     * @return the index of the parent element of the element which its index
     *         is the given @p currentIndex.
     */
    static unsigned long getParentIndex(unsigned long currentIndex) {
        return floor(((double) (currentIndex - 1)) / 2);
    }

  protected:
    /**
     * @see fixHeapWhile(unsigned long, Direction)
     */
    virtual unsigned long
    getIndexOfChildToSwapWithParent(E **array, unsigned long size,
                                    unsigned long indexToElement1,
                                    unsigned long indexToElement2) = 0;

  protected:
    /**
     * @attention *must* pass by pointer, so that the elements won't destruct
     *            themselves.
     * @see fixHeapWhile(unsigned long, Direction)
     */
    virtual bool predicateIsSwapNeeded(E *&element1, E *&element2) = 0;

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     * @throws std::logic_error in case the heap is already full.
     */
    void insert(E *elementToInsert) override {
        if (this->_physicalSize <= this->_logicalSize) {

            /* The heap is already full. Throw a message. */
            // std::string message;
            // message.append("The heap is already full, and contains ");
            // message.append(std::to_string(_physicalSize));
            // message.append(" elements.\n");

            throw std::logic_error(IS_FULL_MESSAGE);
        }

        /* If there is enough space in the _array. */
        insertWhenThereIsEnoughSpace(elementToInsert);
    }

  protected:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when there is enough space in the heap to insert an
     *        additional @p elementToInsert element.
     *
     * @param elementToInsert is the element required to be inserted to the
     *                        heap.
     * @see insert(E *)
     */
    void insertWhenThereIsEnoughSpace(E *elementToInsert) {

        /* Add the `elementToInsert` as the `last` element in the _array. */
        this->_array[this->_logicalSize++] = elementToInsert;
        unsigned long currentIndex         = this->_logicalSize - 1;
        onUpdateElementWithIndex(elementToInsert, currentIndex);

        /*
         * Check upwards the heap, whether there is a need to `swap` the
         * elements according to the insertion, to ensure the heap is valid.
         * While there is at least `1` child in the _array.
         */
        while (0 < currentIndex) {

            /*
             * Beginning with the inserted element, compare each child to
             * its parent, to check if there is a need to `swap` between
             * them, in order to ensure validity of the heap, as a `Heap`.
             */
            if (predicateIsSwapNeeded(
                        this->_array[getParentIndex(currentIndex)],
                        this->_array[currentIndex])) {
                onSwapIsNeeded(getParentIndex(currentIndex), currentIndex);

                /* Step upwards to the parent of the element. */
                currentIndex = getParentIndex(currentIndex);
            } else {

                /* There is no need to `swap`. Thus, the heap is valid. */
                break;
            }
        }
    }

  public:
    /**
     * @brief returns a boolean value that determines whether this heap is
     *        empty or not.
     *
     * @return boolean value of *true* if the heap is empty, or else, *false* if
     *         the heap is not empty.
     */
    bool isEmpty() override { return !(this->_logicalSize); }

  public:
    void makeEmpty() override { this->_logicalSize = 0; }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Heap &heap) {
        return printThis(os, heap);
    }

  public:
    std::ostream &print(std::ostream &os) const override {
        return printThis(os, *this);
    }

  private:
    static std::ostream &printThis(std::ostream &os, const Heap<E> &heap) {
        os << "_array{\n";

        /* In case the _array is empty, print a message instead of elements. */
        if (heap._logicalSize == 0) {
            os << "The _array is empty."
               << "\n";
        }
        for (unsigned long i = 0; i < heap._logicalSize; i++) {
            os << *heap._array[i] << ";";
            os << "\n";
        }
        os << "}; ";

        os << "_logicalSize: " << heap._logicalSize
           << ", _physicalSize: " << heap._physicalSize << ";"
           << "\n";
        return os;
    }
};

#endif // HEAP_H
