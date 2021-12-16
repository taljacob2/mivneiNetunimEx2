
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
 *       `predicateIsSwapNeeded(Entry<K, V>, Entry<K, V>)` method.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @see HeapAdt
 */
template<typename K, typename V> class Heap : public HeapAdt<K, V> {

  private:
    /**
     * @see fixHeap(long int)
     * @see fixHeapUpwards(long int)
     * @see fixHeapWhile(long int, Direction)
     */
    enum class Direction { UPWARDS, DOWNWARDS };

  protected:
    /**
     * Array of pointers to **lvalue `Entries`** that serve as `elements`.
     * Initialized to `nullptr`.
     */
    Entry<K, V> **_array = nullptr;

  protected:
    /// The *physical-size* of the *_array*. Initialized to `0`.
    long int _physicalSize = 0;

  protected:
    /// The *logical-size* of the *_array*. Initialized to `0`.
    long int _logicalSize = 0;

  public:
    long int getLogicalSize() const override { return _logicalSize; }

  public:
    /**
     * @brief Constructor, initializes the *_array*.
     *
     * Builds a **Heap** by giving an @p arrayToBuildFrom of
     * **lvalue `Entries`** as a parameter. Done by invoking the
     * @link buildHeap @endlink method.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     * @see buildHeap
     */
    Heap(Entry<K, V> *arrayToBuildFrom, long int sizeOfArrayToBuildFrom) {
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
    explicit Heap(long int physicalSize) {
        this->_physicalSize = physicalSize;
        this->_array        = new Entry<K, V> *[physicalSize];
        for (int i = 0; i < _physicalSize; i++) { _array[i] = nullptr; }
    }

  public:
    /**
     * @brief Default constructor creates an arbitrary physicalSize of 100.
     */
    Heap() : Heap(100) {}

  public:
    virtual ~Heap() { deleteThis(); }

  private:
    void deleteThis() {
        for (int i = 0; i < _physicalSize; i++) { delete _array[i]; }
        delete[] _array;
    }

  public:
    /**
     * @return the root element, which is the top element in the heap.
     * @throws std::runtime_error in case there are no elements in the heap,
     *         and the user requested to retrieve the root.
     */
    Entry<K, V> *root() override {
        if (!_logicalSize) {
            throw std::runtime_error(Constants::WRONG_INPUT);
        } else {
            return this->_array[0];
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
     * @throws std::logic_error in case the heap is already empty.
     * @see fixHeap(long int)
     * @see deleteRoot(bool)
     */
    Entry<K, V> *deleteRoot() override { return deleteRoot(true); }

  private:
    /**
     * @brief Deletes the *root element* from the heap, and returns it.
     * @deprecated Caution when setting @p fixHeapAfterDeletion to `false`.
     *
     * @note After removing the *root element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap
     *       afterwards - only if the @p fixHeapAfterDeletion parameter is `true`.
     * @attention in case the `_logicalSize` of the `_array` is `0`,
     *            this method returns `null_ptr`.
     * @param fixHeapAfterDeletion determines if the method will call the
     *                             *fixHeap(0)* method, after deletion, to
     *                             ensure that the heap is still valid.
     * @return the *root element* removed from the heap.
     * @throws std::logic_error in case the heap is already empty.
     * @see fixHeap(long int)
     */
    Entry<K, V> *deleteRoot(bool fixHeapAfterDeletion) {

        /* Save the value of `root` to return in the end of the method. */
        Entry<K, V> *returnElement = root();

        if (this->_logicalSize >= 2) {
            deleteRootWhenThereAreTwoOrMoreElements(fixHeapAfterDeletion);
        } else if (this->_logicalSize > 0) {

            /* Delete `_array[0]` manually. */
            this->_array[0] = nullptr;

            /* Decrease the `_logicalSize` of the _array by `1`. */
            this->_logicalSize--;
        } else {

            /* `_logicalSize` is 0. */
            // throw std::logic_error("You have tried to delete an element from "
            //                        "an empty heap.\n");
            throw std::logic_error(Constants::WRONG_INPUT);
        }
        return returnElement;
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when there are `2` or more elements in the heap.
     *
     * @note After removing the *root element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap
     *       afterwards - only if the @p fixHeapAfterDeletion parameter is `true`.
     * @param fixHeapAfterDeletion determines if the method will call the
     *                             *fixHeap(0)* method, after deletion, to
     *                             ensure that the heap is still valid.
     * @see deleteRoot()
     * @see fixHeap(long int)
     */
    void deleteRootWhenThereAreTwoOrMoreElements(bool fixHeapAfterDeletion) {

        /*
         * There are at least `2` elements in the heap,
         * so we are able to delete an element.
         */

        /* Set the `first` element in the _array to be the `last` element. */
        this->_array[0] = this->_array[this->_logicalSize - 1];

        /* Set the `last` element to be `nullptr`. */
        this->_array[this->_logicalSize - 1] = nullptr;

        /*
         * Decrease the `_logicalSize` of the _array by `1`,
         * before invoking `fixHeap(0)`.
         */
        this->_logicalSize--;

        /* After deletion, invoke `fixHeap(0)` to fix the heap. */
        if (fixHeapAfterDeletion) { fixHeap(0); }
    }

  public:
    /**
     * @brief Builds a **Heap** by giving an @p arrayToBuildFrom of
     *        **lvalue `Entries`** as a parameter.
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
     * @attention the `Entries` elements in the @p arrayToBuildFrom must be
     *            **lvalues**.
     */
    void buildHeap(Entry<K, V> *arrayToBuildFrom,
                   long int     sizeOfArrayToBuildFrom) override {

        /* Delete the old _array if there is any. */
        deleteThis();

        /* Initialize a `new` empty _array of pointers to elements given. */
        this->_physicalSize = sizeOfArrayToBuildFrom;
        this->_logicalSize  = sizeOfArrayToBuildFrom;
        this->_array        = new Entry<K, V> *[sizeOfArrayToBuildFrom];
        for (long int i = 0; i < sizeOfArrayToBuildFrom; i++) {
            this->_array[i] = &arrayToBuildFrom[i];
        }

        /*
         * `currentIndex` should be in between `0` and `(_logicalSize / 2)`.
         * Note: the almost last level has `(_logicalSize / 2)` `nodes`.
         */
        long int lastIndex = this->_logicalSize - 1;
        for (long int currentIndex = (lastIndex - 1) / 2; currentIndex >= 0;
             currentIndex--) {
            fixHeap(currentIndex);
        }
    }

  protected:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **downwards**.
     * @param indexToFixFrom an index of an element in the heap, that the
     *                       user wishes to fix the heap from.
     * @see fixHeap(long int, Direction)
     */
    void fixHeap(long int indexToFixFrom) override {
        fixHeap(indexToFixFrom, Direction::DOWNWARDS);
    }

  protected:
    /**
     * @brief Fixes the heap from a given @p indexToFixFrom and **upwards**.
     * @param indexToFixFrom an index of an element in the heap, that the
     *                       user wishes to fix the heap from.
     * @see fixHeap(long int, Direction)
     */
    void fixHeapUpwards(long int indexToFixFrom) override {
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
     * @see fixHeap(long int)
     * @see fixHeapUpwards(long int)
     */
    void fixHeap(long int indexToFixFrom, Direction direction) {

        /* Check that `indexToFixFrom` is a legal index. */
        if ((indexToFixFrom < 0) || (this->_logicalSize <= indexToFixFrom)) {

            /* The `indexToFixFrom` is out of range. Throw a message. */
            // std::string message;
            // message.append("The index provided is out of range. There are ");
            // message.append(std::to_string(_logicalSize));
            // message.append(" elements in the heap.\n");

            throw std::out_of_range(Constants::WRONG_INPUT);
        }
        fixHeapLegalIndex(indexToFixFrom, direction);
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when the provided @p currentIndex is a legal index.
     *        This method is being invoked by the @link fixHeap(long int,
     *        Direction) @endlink method.
     *
     * @param currentIndex has been checked as a legal index. Should be
     *                     in between `0` and `(_logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @param direction tells the `Direction` of which the `fixHeap` would
     *                  iterate.
     * @see fixHeap(long int)
     * @see fixHeapUpwards(long int)
     * @see Direction
     */
    void fixHeapLegalIndex(long int indexToFixFrom, Direction direction) {

        /*
         * `currentIndex` should be in between `0` and `(_logicalSize / 2)`.
         *
         * Note: the `almost last` level has `(_logicalSize / 2)` `nodes`.
         * Attention: there is no use to give `indexToFixFrom` that is larger
         *            than `(_logicalSize / 2)`.
         */
        long int currentIndex = indexToFixFrom;
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

            throw std::out_of_range(Constants::WRONG_INPUT);
        }

        /* _array[currentIndex] is not `nullptr`. Thus, comparable. */
        fixHeapWhile(currentIndex, direction);
    }

  private:
    /**
     * @brief This method is a *protected* method, that represents a `while`
     *        that is being invoked by the @link fixHeap(long int) @endlink method.
     *
     * The `while` loop has `2` stop conditions:
     *  @li there are no children to the `node` that is being iterated ( =
     *  the `node` that is being iterated is a `leaf`.
     *  @li the `node` that is being iterated is *not* `swappable` with each of
     *  its children.
     * @param currentIndex should be in between `0` and `(_logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @see fixHeap(long int)
     * @see fixHeapUpwards(long int)
     * @see Direction
     */
    void fixHeapWhile(long int currentIndex, Direction direction) {

        /* _array[currentIndex] is not `nullptr`. Thus, comparable. */
        while ((0 <= currentIndex) && (currentIndex < (_logicalSize / 2))) {

            /* Get the index that points to the `swappable` element. */
            long int indexOfSwappableChildOfCurrentRoot =
                    getIndexOfChildToSwapWithParent(_array, _logicalSize,
                                                    currentIndex * 2 + 1,
                                                    currentIndex * 2 + 2);
            if (_array[indexOfSwappableChildOfCurrentRoot] != nullptr) {

                /*
                 * There is a living entry.
                 * Compare by keys.
                 * `swap` the elements if needed, to maintain the validity of
                 * the heap as a `Heap`.
                 */
                if (predicateIsSwapNeeded(
                            *_array[currentIndex],
                            *_array[indexOfSwappableChildOfCurrentRoot])) {
                    my_algorithms::swap(_array, currentIndex,
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
                 * There is no entry to compare with.
                 * Thus, this `node` does not have children,
                 * and is actually a leaf.
                 */
                break;
            }
        }
    }

  private:
    /**
     * @note in case @p currentIndex is `0`, then the result will be `-1`.
     * @param currentIndex the index of the element to get its parent element
     *                     index.
     * @return the index of the parent element of the element which its index
     *         is the given @p currentIndex.
     */
    static long int getParentIndex(long int currentIndex) {
        return floor((double) (currentIndex - 1) / 2);
    }

  protected:
    /**
     * @see fixHeapWhile(long int, Direction)
     */
    virtual long int
    getIndexOfChildToSwapWithParent(Entry<K, V> **array, long int size,
                                    long int indexToElement1,
                                    long int indexToElement2) = 0;

  protected:
    /**
     * @see fixHeapWhile(long int, Direction)
     */
    virtual bool predicateIsSwapNeeded(Entry<K, V> element1,
                                       Entry<K, V> element2) = 0;

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     * @throws std::logic_error in case the heap is already full.
     */
    void insert(Entry<K, V> *elementToInsert) override {
        if (this->_physicalSize > this->_logicalSize) {

            /* If there is enough space in the _array. */
            insertWhenThereIsEnoughSpace(elementToInsert);
        } else {

            /* The heap is already full. Throw a message. */
            // std::string message;
            // message.append("The heap is already full, and contains ");
            // message.append(std::to_string(_physicalSize));
            // message.append(" elements.\n");

            throw std::logic_error(Constants::WRONG_INPUT);
        }
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when there is enough space in the heap to insert an
     *        additional @p elementToInsert element.
     *
     * @param elementToInsert is the element required to be inserted to the
     *                        heap.
     * @see insert(Entry<K, V> *)
     */
    void insertWhenThereIsEnoughSpace(Entry<K, V> *elementToInsert) {

        /* Add the `elementToInsert` as the `last` element in the _array. */
        this->_array[this->_logicalSize++] = elementToInsert;

        long int currentIndex = this->_logicalSize - 1;

        /*
         * Check upwards the heap, whether there is a need to `swap` the
         * elements according to the insertion, to ensure the heap is valid.
         * While there is at least `1` child in the _array.
         */
        while (0 < currentIndex) {

            /*
             * Beginning with the inserted element, compare each child to
             * its parent, to check if there is a need to `swap` between
             * them, in order to ensure validity of the heap, as a
             * `Heap`.
             */
            if (predicateIsSwapNeeded(*this->_array[(currentIndex - 1) / 2],
                                      *this->_array[currentIndex])) {
                my_algorithms::swap(this->_array, currentIndex,
                                    (currentIndex - 1) / 2);

                /* Step upwards to the parent of the element. */
                currentIndex = (currentIndex - 1) / 2;
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
    bool isEmpty() override { return this->_logicalSize; }

  public:
    void makeEmpty() override { this->_logicalSize = 0; }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Heap &heap) {
        return printThis(os, heap);
    }

  private:
    std::ostream &print(std::ostream &       os,
                        const HeapAdt<K, V> &heapAdt) const override {
        Heap &heap = (Heap &) heapAdt; // Force cast.
        return printThis(os, heap);
    }

  private:
    static std::ostream &printThis(std::ostream &os, const Heap<K, V> &heap) {
        os << "_array{\n";

        /* In case the _array is empty, print a message instead of elements. */
        if (heap._logicalSize == 0) {
            os << "The _array is empty."
               << "\n";
        }
        for (long int i = 0; i < heap._logicalSize; i++) {
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
