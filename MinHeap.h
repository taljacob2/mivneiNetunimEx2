
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "MinHeapADT.h"
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
 */
template<typename K, typename V> class MinHeap : public MinHeapADT<K, V> {
  private:
    /**
     * Array of pointers to **lvalue `Entries`** that serve as `elements`.
     * Initialized to `nullptr`.
     */
    Entry<K, V> **array = nullptr;

  private:
    /// The *physical-size* of the *array*. Initialized to `0`.
    long int physicalSize = 0;

  private:
    /// The *logical-size* of the *array*. Initialized to `0`.
    long int logicalSize = 0;

  public:
    /**
     * @brief Constructor, initializes the *array*.
     *
     * Builds a **Minimum-Heap** by giving an @p arrayToBuildFrom of
     * **lvalue `Entries`** as a parameter. Done by invoking the
     * @link buildHeap @endlink method.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     * @see buildHeap
     */
    explicit MinHeap(Entry<K, V> *arrayToBuildFrom,
                     long int     sizeOfArrayToBuildFrom) {
        buildHeap(arrayToBuildFrom, sizeOfArrayToBuildFrom);
    }

  public:
    /**
     * @brief Constructor, sets the `physicalSize` of the *array* to be @p
     *        physicalSize.
     *
     * @note the content of the *array* remains empty.
     * @param physicalSize set the `physicalSize` of the array to be this size.
     */
    explicit MinHeap(long int physicalSize) {
        this->physicalSize = physicalSize;
        array              = new Entry<K, V> *[physicalSize];
    }

  public:
    MinHeap() = default;

  public:
    virtual ~MinHeap() { delete[] array; }

  public:
    /**
     * @brief Deletes the *minimal element* from the heap, and returns it.
     *
     * @note After removing the *minimal element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap afterwards.
     * @attention in case the `logicalSize` of the *array* is 0,
     *            this method returns `null_ptr`.
     * @return the *minimal element* removed from the heap.
     * @throws std::logic_error in case the heap is already empty.
     * @see fixHeap(long int)
     */
    Entry<K, V> *deleteMin() override { return deleteMin(true); }

  public:
    /**
     * @brief Deletes the *minimal element* from the heap, and returns it.
     * @deprecated Caution when setting @p fixHeapAfterDeletion to `false`.
     *
     * @note After removing the *minimal element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap
     *       afterwards - only if the @p fixHeapAfterDeletion parameter is `true`.
     * @attention in case the `logicalSize` of the *array* is 0,
     *            this method returns `null_ptr`.
     * @param fixHeapAfterDeletion determines if the method will call the
     *                             *fixHeap(0)* method, after deletion, to
     *                             ensure that the heap is still valid.
     * @return the *minimal element* removed from the heap.
     * @throws std::logic_error in case the heap is already empty.
     * @see fixHeap(long int)
     */
    Entry<K, V> *deleteMin(bool fixHeapAfterDeletion) {

        /* Save the value of `array[0]` to return in the end of the method. */
        Entry<K, V> *returnElement = array[0];

        if (logicalSize >= 2) {
            deleteMinWhenThereAreTwoOrMoreElements(fixHeapAfterDeletion);
        } else if (logicalSize > 0) {

            /* Delete `array[0]` manually. */
            array[0] = nullptr;

            /* Decrease the `logicalSize` of the array by `1`. */
            logicalSize--;
        } else {

            /* `logicalSize` is 0. */
            // throw std::logic_error("You have tried to delete an element from "
            //                        "an empty heap.\n");
            throw std::logic_error("wrong input");
        }
        return returnElement;
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when there are `2` or more elements in the heap.
     *
     * @note After removing the *minimal element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap
     *       afterwards - only if the @p fixHeapAfterDeletion parameter is `true`.
     * @param fixHeapAfterDeletion determines if the method will call the
     *                             *fixHeap(0)* method, after deletion, to
     *                             ensure that the heap is still valid.
     * @see deleteMin()
     * @see fixHeap(long int)
     */
    void deleteMinWhenThereAreTwoOrMoreElements(bool fixHeapAfterDeletion) {

        /*
         * There are at least `2` elements in the heap,
         * so we are able to delete an element.
         */

        /* Set the `first` element in the array to be the `last` element. */
        array[0] = array[logicalSize - 1];

        /* Set the `last` element to be `nullptr`. */
        array[logicalSize - 1] = nullptr;

        /*
         * Decrease the `logicalSize` of the array by `1`,
         * before invoking `fixHeap(0)`.
         */
        logicalSize--;

        /*
         * After deletion,
         * invoke `fixHeap(0)` to fix the heap.
         */
        if (fixHeapAfterDeletion) { fixHeap(0); }
    }

  public:
    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     * @throws std::logic_error in case the heap is already full.
     */
    void insert(Entry<K, V> *elementToInsert) override {
        if (physicalSize > logicalSize) {

            /* If there is enough space in the array. */
            insertWhenThereIsEnoughSpace(elementToInsert);
        } else {

            /* The heap is already full. Throw a message. */
            // std::string message;
            // message.append("The heap is already full, and contains ");
            // message.append(std::to_string(physicalSize));
            // message.append(" elements.\n");

            throw std::logic_error("wrong input");
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

        /* Add the `elementToInsert` as the `last` element in the array. */
        array[logicalSize++] = elementToInsert;

        long int currentIndex = logicalSize - 1;

        /*
         * Check upwards the heap, whether there is a need to `swap` the
         * elements according to the insertion, to ensure the heap is valid.
         * While there is at least `1` child in the array.
         */
        while (0 < currentIndex) {

            /*
             * Beginning with the inserted element, compare each child to
             * its parent, to check if there is a need to `swap` between
             * them, in order to ensure validity of the heap, as a
             * `Minimum-Heap`.
             */
            if (*array[currentIndex] < *array[(currentIndex - 1) / 2]) {
                my_algorithms::swap(array, currentIndex,
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
     * @brief This method handles a heap that is *valid* from the root downwards
     *        until the `indexToFixFrom`, which from there and on downwards,
     *        the heap is *invalid* - means: that the `node` in the
     *        `indexToFixFrom` is no smaller than both of its children.
     *        The method ensures to *correct* the heap by *fixing* its
     *        validity - means, checking that each `node` is smaller than
     *        both of its children.
     *
     * @param indexToFixFrom the method fixes the heap from this index
     *                       downwards until the leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       smaller than both of its children, or when the root is a leaf.
     * @attention there is no use to give @p indexToFixFrom that is larger
     *            than `(logicalSize / 2)`, because indexes larger than
     *            `(logicalSize / 2)` point to leaf `node`s, thus the method
     *            will have no effect, as explained earlier.
     * @throws std::out_of_range in case the index provided is out of range.
     */
    void fixHeap(long int indexToFixFrom) override {

        /* Check that `indexToFixFrom` is a legal index. */
        if ((indexToFixFrom < 0) || (logicalSize <= indexToFixFrom)) {

            /* The `indexToFixFrom` is out of range. Throw a message. */
            // std::string message;
            // message.append("The index provided is out of range. There are ");
            // message.append(std::to_string(logicalSize));
            // message.append(" elements in the heap.\n");

            throw std::out_of_range("wrong input");
        }
        fixHeapLegalIndex(indexToFixFrom);
    }

  private:
    /**
     * @brief This method is a *private* method, that represents the
     *        case when the provided @p currentIndex is a legal index.
     *        This method is being invoked by the @link fixHeap(long int)
     *        @endlink method.
     *
     * @param currentIndex has been checked as a legal index. should be
     *                     in between `0` and `(logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @see fixHeap(long int)
     */
    void fixHeapLegalIndex(long int indexToFixFrom) {

        /*
         * `currentIndex` should be in between `0` and `(logicalSize / 2)`.
         *
         * Note: the `almost last` level has `(logicalSize / 2)` `nodes`.
         * Attention: there is no use to give `indexToFixFrom` that is larger
         *            than `(logicalSize / 2)`.
         */
        long int currentIndex = indexToFixFrom;
        if (array[currentIndex] == nullptr) {

            /*
             * The `indexToFixFrom` is out of range. Throw a message.
             * Note: should not be happening here, thanks to already checked
             * scenario.
             */
            // std::string message;
            // message.append(
            //         "The index provided is out of range. The element "
            //         "you have provided is `nullptr`. Thus, in-comparable.\n");

            throw std::out_of_range("wrong input");
        }

        /* array[currentIndex] is not `nullptr`. Thus, comparable. */
        fixHeapWhile(currentIndex);
    }

  private:
    /**
     * @brief This method is a *private* method, that represents a `while`
     *        that is being invoked by the @link fixHeap(long int) @endlink method.
     *
     * The `while` loop has `2` stop conditions:
     *  @li there are no children to the `node` that is being iterated ( =
     *  the `node` that is being iterated is a `leaf`.
     *  @li the `node` that is being iterated is *not* smaller than each of
     *  its children.
     * @param currentIndex should be in between `0` and `(logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @see fixHeap(long int)
     */
    void fixHeapWhile(long int currentIndex) {

        /* array[currentIndex] is not `nullptr`. Thus, comparable. */
        while ((0 <= currentIndex) && (currentIndex < (logicalSize / 2))) {

            /* Get the index that points to the `minimal` element. */
            long int indexOfMinimalChildOfCurrentRoot =
                    my_algorithms::min(array, logicalSize, currentIndex * 2 + 1,
                                       currentIndex * 2 + 2);
            if (array[indexOfMinimalChildOfCurrentRoot] != nullptr) {

                /*
                 * There is a living entry.
                 * Compare by keys.
                 * `swap` the elements if needed, to maintain the validity of
                 * the heap as a `Minimum-Heap`.
                 */
                if (*array[currentIndex] >
                    *array[indexOfMinimalChildOfCurrentRoot]) {
                    my_algorithms::swap(array, currentIndex,
                                        indexOfMinimalChildOfCurrentRoot);

                    /*
                     * Set the updated iterator index to the replaced index.
                     * Note: this enlarges the index.
                     */
                    currentIndex = indexOfMinimalChildOfCurrentRoot;
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

  public:
    /**
     * @brief Builds a **Minimum-Heap** by giving an @p arrayToBuildFrom of
     *        **lvalue `Entries`** as a parameter.
     *
     * Done by making an array of pointers to the elements given in the @p
     * arrayToBuildFrom.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     * @note In case there is already an `allocated` `array` in this heap,
     *       this method ensures to `delete []` it *before* handling the
     *       building process.
     * @attention the `Entries` elements in the @p arrayToBuildFrom must be
     *            **lvalues**.
     */
    void buildHeap(Entry<K, V> *arrayToBuildFrom,
                   long int     sizeOfArrayToBuildFrom) override {

        /* Delete the old array if there is any. */
        delete[] array;

        /* Initialize a `new` empty array of pointers to elements given. */
        physicalSize = sizeOfArrayToBuildFrom;
        logicalSize  = sizeOfArrayToBuildFrom;
        array        = new Entry<K, V> *[sizeOfArrayToBuildFrom];
        for (long int i = 0; i < sizeOfArrayToBuildFrom; i++) {
            array[i] = &arrayToBuildFrom[i];
        }

        /*
         * `currentIndex` should be in between `0` and `(logicalSize / 2)`.
         * Note: the almost last level has `(logicalSize / 2)` `nodes`.
         */
        long int lastIndex = logicalSize - 1;
        for (long int currentIndex = (lastIndex - 1) / 2; currentIndex >= 0;
             currentIndex--) {
            fixHeap(currentIndex);
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
    bool isEmpty() override { return logicalSize; }

  public:
    void makeEmpty() override { logicalSize = 0; }

  public:
    friend std::ostream &operator<<(std::ostream &os, const MinHeap &heap) {
        os << "array{\n";

        /* In case the array is empty, print a message instead of elements. */
        if (heap.logicalSize == 0) {
            os << "The array is empty."
               << "\n";
        }
        for (long int i = 0; i < heap.logicalSize; i++) {
            os << *heap.array[i] << ";";
            os << "\n";
        }
        os << "}; ";

        os << "logicalSize: " << heap.logicalSize
           << ", physicalSize: " << heap.physicalSize << ";"
           << "\n";
        return os;
    }
};

#endif // MIN_HEAP_H
