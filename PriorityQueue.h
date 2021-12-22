
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "DoublePointerMinHeapAndMaxHeapComponent.h"
#include "PriorityQueueAdt.h"

/**
 * @brief This *priority-queue* is implemented by four *Heaps*, and each of
 *        these Heaps' elements are *Entries* that are composed by a *key* and a *value*.
 *
 * @attention the `median()` is defined as the element that its priority is
 *            `ceil(n / 2)`.
 *
 * @tparam E The type of each element. **Must** be `comparable`.
 *           The *priority* of each element is based on this comparable `key`.
 * @see DoublePointerMinHeapAndMaxHeapComponent
 */
template<typename E> class PriorityQueue : public PriorityQueueAdt<E> {

    typedef ElementInMinHeapAndMaxHeap<E> EWrapper;

  private:
    static constexpr unsigned long SIZE = 100;

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<E> *_lessOrEqualToMedianDoubleHeap =
            nullptr;

  protected:
    DoublePointerMinHeapAndMaxHeapComponent<E> *_greaterThanMedianDoubleHeap =
            nullptr;

  public:
    explicit PriorityQueue(int physicalSizeOfEachHeap) {
        createDoubleHeapWithPhysicalSize(_lessOrEqualToMedianDoubleHeap,
                                         physicalSizeOfEachHeap);
        createDoubleHeapWithPhysicalSize(_greaterThanMedianDoubleHeap,
                                         physicalSizeOfEachHeap);
    }

  public:
    /**
     * @warning invoking this method does *not* initialize any field.
     *          So, if you decide to use this method, *you may not* invoke any
     *          of the methods in this class. Instead, you *must* invoke the
     *          `createEmpty()` method beforehand, and only then you are
     *          allowed to invoke the other methods in this class.
     *          @li This kind of implementation is served only because of a
     *          request given by the customer ( = the course lecturer).
     */
    PriorityQueue() {
        // createEmpty();
    }

  public:
    virtual ~PriorityQueue() { deleteThis(); }

  protected:
    void deleteThis() const {
        delete _lessOrEqualToMedianDoubleHeap;
        delete _greaterThanMedianDoubleHeap;
    }

  public:
    /**
     * @brief retrieve the element with the maximum priority in this
     *        data-structure.
     *        This is the root element from the
     *        `_greaterThanMedianDoubleHeap`'s maximum-heap.
     *
     * @return the element with the maximum priority in this data-structure.
     * @throws std::runtime_error in case there are no elements in the
     *         `_lessOrEqualToMedianDoubleHeap`'s maximum-heap.
     *         This happens when `getLogicalSize() <= 0`.
     * @see deleteMax()
     * @see maxEWrapper()
     */
    E *max() override {
        return maxEWrapper()->getUniqueElement()->getElement();
    }

  protected:
    EWrapper *maxEWrapper() {

        /*
         * DEVELOPER NOTE: retrieving the max in `_greaterThanMedianDoubleHeap`
         * will not work when `getLogicalSize() < 3`, so in that case return
         * the max in `_lessOrEqualToMedianDoubleHeap`.
         */
        return getLogicalSize() >= 3
                       ? _greaterThanMedianDoubleHeap->getMaxHeap()->getRoot()
                       : _lessOrEqualToMedianDoubleHeap->getMaxHeap()
                                 ->getRoot();
    }

  public:
    /**
     * @warning you will be able to access the value of the `return`ed
     *          element's pointer - but it will be **your responsibility to
     *          `delete`** the pointer afterwards.
     * @return the pointer of the *maximum priority* element in the
     *         data-structure - that is **your responsibility to `delete`
     *         from the heap** afterwards.
     * @see deleteMax(bool)
     */
    E *deleteMax() override { return deleteMax(false); }

  protected:
    /**
     * @param deleteFromHeap @warning
     *                       @note set this parameter to `true` in case
     *                       you want to `delete` the element from the heap -
     *                       but then, since the element will be `delete`d, you
     *                       *will not be able to access its value*.
     *                       @note set this parameter to `false` in case you
     *                       *do not* want to `delete` the element from the
     *                       heap - so you will be able to access the value of
     *                       the `return`ed element's pointer - but it will be
     *                       **your responsibility to `delete`** the pointer afterwards.
     * @return the pointer to the element with the maximum priority in this
     *         data-structure.
     * @see max()
     */
    E *deleteMax(bool deleteFromHeap) {
        EWrapper *eWrapper = maxEWrapper();
        eWrapper->getUniqueElement()->setNeedToDeleteElement(false);
        E *returnValue = eWrapper->getUniqueElement()->getElement();

        /*
         * Extract the element via MOVE.
         * `delete` the EWrapper which contains the `element` but not the
         * `element` itself.
         */
        if (getLogicalSize() >= 3) {
            _greaterThanMedianDoubleHeap
                    ->deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
                            0, deleteFromHeap);
            if (isLogicalSizeOdd()) {

                // Transfer the maximum from "less" to "greater".
                transferTheMaxElementFromLessToGreater();
            }
        } else {
            _lessOrEqualToMedianDoubleHeap
                    ->deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
                            0, deleteFromHeap);
        }

        if (deleteFromHeap) {
            delete returnValue;
            returnValue = nullptr;
        }
        return returnValue;
    }

  public:
    /**
     * @brief retrieve the element with the minimum priority in this
     *        data-structure.
     *        This is the root element from the
     *        `_lessOrEqualToMedianDoubleHeap`'s minimum-heap.
     *
     * @return the element with the minimum priority in this data-structure.
     * @throws std::runtime_error in case there are no elements in the
     *         `_lessOrEqualToMedianDoubleHeap`'s minimum-heap.
     *         This happens when `getLogicalSize() <= 0`.
     * @see deleteMin()
     * @see minEWrapper()
     */
    E *min() override {

        // DEVELOPER NOTE: this will always work when `getLogicalSize() > 0`
        return minEWrapper()->getUniqueElement()->getElement();
    }

  protected:
    EWrapper *minEWrapper() {

        // DEVELOPER NOTE: this will always work when `getLogicalSize() > 0`
        return _lessOrEqualToMedianDoubleHeap->getMinHeap()->getRoot();
    }

  public:
    /**
     * @warning you will be able to access the value of the `return`ed
     *          element's pointer - but it will be **your responsibility to
     *          `delete`** the pointer afterwards.
     * @return the pointer of the *minimum priority* element in the
     *         data-structure - that is **your responsibility to `delete`
     *         from the heap** afterwards.
     * @see deleteMin(bool)
     */
    E *deleteMin() override { return deleteMin(false); }

  protected:
    /**
     * @param deleteFromHeap @warning
     *                       @note set this parameter to `true` in case
     *                       you want to `delete` the element from the heap -
     *                       but then, since the element will be `delete`d, you
     *                       *will not be able to access its value*.
     *                       @note set this parameter to `false` in case you
     *                       *do not* want to `delete` the element from the
     *                       heap - so you will be able to access the value of
     *                       the `return`ed element's pointer - but it will be
     *                       **your responsibility to `delete`** the pointer afterwards.
     * @return the pointer to the element with the minimum priority in this
     *         data-structure.
     * @see min()
     */
    E *deleteMin(bool deleteFromHeap) {
        EWrapper *eWrapper = minEWrapper();
        eWrapper->getUniqueElement()->setNeedToDeleteElement(false);
        E *returnValue = eWrapper->getUniqueElement()->getElement();

        /*
         * Extract the element via MOVE.
         * `delete` the EWrapper which contains the `element` but not the
         * `element` itself.
         */
        if (getLogicalSize() >= 3) {
            _lessOrEqualToMedianDoubleHeap
                    ->deleteEWrapperFromBothHeapsViaIndexOfMinHeapElement(0,
                                                                          true);
            if (isLogicalSizeEven()) {

                // Transfer the minimum from "greater" to "less".
                transferTheMinElementFromGreaterToLess();
            }
        } else {
            _lessOrEqualToMedianDoubleHeap
                    ->deleteEWrapperFromBothHeapsViaIndexOfMinHeapElement(0,
                                                                          true);
        }

        if (deleteFromHeap) {
            delete returnValue;
            returnValue = nullptr;
        }
        return returnValue;
    }

  public:
    void createEmpty() override {
        createDoubleHeap(_lessOrEqualToMedianDoubleHeap);
        createDoubleHeap(_greaterThanMedianDoubleHeap);
    }

  protected:
    void
    createDoubleHeap(DoublePointerMinHeapAndMaxHeapComponent<E> *
                             &fieldOfDoublePointerMinHeapAndMaxHeapComponent) {
        auto *minHeap = new MinHeapWhenAlsoHavingMaxHeap<E>(SIZE);
        auto *maxHeap = new MaxHeapWhenAlsoHavingMinHeap<E>(SIZE);

        // Polymorphing `MinHeap` and `MaxHeap` through parameters.
        fieldOfDoublePointerMinHeapAndMaxHeapComponent =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(minHeap,
                                                               maxHeap);
    }

  protected:
    void createDoubleHeapWithPhysicalSize(
            DoublePointerMinHeapAndMaxHeapComponent<E> *
                    &     fieldOfDoublePointerMinHeapAndMaxHeapComponent,
            unsigned long physicalSize) {
        auto *minHeap = new MinHeapWhenAlsoHavingMaxHeap<E>(physicalSize);
        auto *maxHeap = new MaxHeapWhenAlsoHavingMinHeap<E>(physicalSize);

        // Polymorphing `MinHeap` and `MaxHeap` through parameters.
        fieldOfDoublePointerMinHeapAndMaxHeapComponent =
                new DoublePointerMinHeapAndMaxHeapComponent<E>(minHeap,
                                                               maxHeap);
    }

  public:
    void insert(E &&element) override {
        if (getLogicalSize() > 1) {
            if (isLogicalSizeEven()) {
                if (*median() < element) {

                    // Insert the given EWrapper to the "greater" heap.
                    _greaterThanMedianDoubleHeap->insertToBothHeaps(
                            (E &&) element);
                } else {
                    transferTheMaxElementFromLessToGreater();

                    // Insert the given EWrapper to the "less" heap.
                    _lessOrEqualToMedianDoubleHeap->insertToBothHeaps(
                            (E &&) element);
                }
            } else if (isLogicalSizeOdd()) {
                if (*median() < element) {
                    transferTheMinElementFromGreaterToLess();

                    // Insert the given EWrapper to the "greater" heap.
                    _greaterThanMedianDoubleHeap->insertToBothHeaps(
                            (E &&) element);
                } else {

                    // Insert the given EWrapper to the "less" heap.
                    _lessOrEqualToMedianDoubleHeap->insertToBothHeaps(
                            (E &&) element);
                }
            }
        } else {

            // Insert the given EWrapper to the "less" heap.
            _lessOrEqualToMedianDoubleHeap->insertToBothHeaps((E &&) element);
        }
    }

  protected:
    void transferTheMaxElementFromLessToGreater() const {
        transferElementFromLessDoubleHeapViaIndexOfMaxHeapToGreaterDoubleHeap(
                0);
    }

  private:
    void transferElementFromLessDoubleHeapViaIndexOfMaxHeapToGreaterDoubleHeap(
            unsigned long index) const {

        // Delete the `EWrapper` from both "less" heaps.
        EWrapper *eWrapperToTransferToGreater =
                _lessOrEqualToMedianDoubleHeap
                        ->deleteEWrapperFromBothHeapsViaIndexOfMaxHeapElement(
                                index, false);

        // Transfer it to both "greater" heaps.
        _greaterThanMedianDoubleHeap->insertToBothHeaps(
                eWrapperToTransferToGreater);
    }

  protected:
    void transferTheMinElementFromGreaterToLess() const {
        transferElementFromGreaterDoubleHeapViaIndexOfMinHeapToLessDoubleHeap(
                0);
    }

  private:
    void transferElementFromGreaterDoubleHeapViaIndexOfMinHeapToLessDoubleHeap(
            unsigned long index) const {

        // Delete the `EWrapper` from both "greater" heaps.
        EWrapper *eWrapperToTransferToLess =
                _greaterThanMedianDoubleHeap
                        ->deleteEWrapperFromBothHeapsViaIndexOfMinHeapElement(
                                index, false);

        // Transfer it to both "less" heaps.
        _lessOrEqualToMedianDoubleHeap->insertToBothHeaps(
                eWrapperToTransferToLess);
    }

  public:
    /**
     * @return the median priority element - defining the median as the
     *         element that its priority is `ceil(n / 2)`
     * @throws std::runtime_error in case there are no elements in the
     *         `_lessOrEqualToMedianDoubleHeap`'s maximum-heap.
     *          This happens when `getLogicalSize() <= 0`.
     */
    E *median() override {

        // DEVELOPER NOTE: this will always work when `getLogicalSize() > 0`
        return _lessOrEqualToMedianDoubleHeap->getMaxHeap()
                ->getRoot()
                ->getUniqueElement()
                ->getElement();
    }

  protected:
    long int getLogicalSize() {
        return _lessOrEqualToMedianDoubleHeap->getMaxHeap()->getLogicalSize() +
               _greaterThanMedianDoubleHeap->getMaxHeap()->getLogicalSize();
    }

  protected:
    bool isLogicalSizeEven() { return isEven(getLogicalSize()); }

  protected:
    static bool isEven(unsigned long number) { return number % 2 == 0; }

  protected:
    bool isLogicalSizeOdd() { return !isLogicalSizeEven(); }

  protected:
    static bool isOdd(unsigned long number) { return !isEven(number); }

  public:
    friend std::ostream &operator<<(std::ostream &       os,
                                    const PriorityQueue &priorityQueue) {
        priorityQueue.print(os);
        return os;
    }

  public:
    std::ostream &print(std::ostream &os) const override {
        return printThis(os, *this);
    }

  private:
    static std::ostream &printThis(std::ostream &          os,
                                   const PriorityQueue<E> &priorityQueue) {
        constexpr char *PRINT_WHEN_EMPTY = (char *) "empty.";

        os << "---------------------------- ";
        os << "_lessOrEqualToMedianDoubleHeap:";
        os << " ----------------------------" << std::endl;
        if (priorityQueue._lessOrEqualToMedianDoubleHeap->getMinHeap()
                    ->getLogicalSize()) {
            priorityQueue._lessOrEqualToMedianDoubleHeap->print(std::cout);
        } else {
            os << PRINT_WHEN_EMPTY << std::endl;
        }

        os << "---------------------------- ";
        os << "_greaterThanMedianDoubleHeap:";
        os << " ----------------------------" << std::endl;
        if (priorityQueue._greaterThanMedianDoubleHeap->getMinHeap()
                    ->getLogicalSize()) {
            priorityQueue._greaterThanMedianDoubleHeap->print(std::cout);
        } else {
            os << PRINT_WHEN_EMPTY << std::endl;
        }

        os << " ----------------------------------------"
              "--------------------------------------------"
           << std::endl;

        return os;
    }
};

#endif // PRIORITY_QUEUE_H
