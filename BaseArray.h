
#ifndef BASE_ARRAY_H
#define BASE_ARRAY_H

#include "Unique.h"
#include <functional>
#include <iostream>

/**
 * @brief This class wraps an array of a *constant size*, and `delete`s it on
 *        destruction.
 *
 * Use this class instead of the old fashioned way:
 * @code
 * CLASS_TYPE *classTypeArray = new CLASS_TYPE [someDynamicSize];
 * @endcode
 * to *avoid* concerning yourself with the need to `delete` the allocated
 * array afterwards.
 * @tparam E the type of `element` in the array.
 *
 * @version 1.0.3
 */
template<typename E> class BaseArray {

  protected:
    static constexpr char *PHYSICAL_SIZE_MESSAGE =
            (char *) "BaseArray: `physicalSize` must be at least `1`.";

  protected:
    static constexpr char *OUT_OF_RANGE_MESSAGE =
            (char *) "BaseArray: out of range.";

  protected:
    static constexpr char *SIZE_OUT_OF_RANGE_MESSAGE =
            (char *) "BaseArray: size is out of range.";

  protected:
    static constexpr char *ELEMENT_IS_NULL_MESSAGE =
            (char *) "BaseArray: Element is `nullptr`.";

  protected:
    Unique<E> **_array = nullptr;

  protected:
    unsigned long _physicalSize = 100;

  public:
    unsigned long size() const { return _physicalSize; }

  public:
    explicit BaseArray(unsigned long physicalSize) {
        if (physicalSize < 1) {
            throw std::invalid_argument(PHYSICAL_SIZE_MESSAGE);
        }
        _physicalSize = physicalSize;
        _array        = new Unique<E> *[_physicalSize];
        initUniqueArray(_array, _physicalSize);
    }

  protected:
    static void initUniqueArray(Unique<E> **&array, unsigned long size) {
        for (unsigned long i = 0; i < size; i++) {
            array[i] = new Unique<E>(nullptr);
        }
    }

  public:
    BaseArray(const BaseArray &other) { *this = other; }

  public:
    BaseArray(BaseArray &&other) noexcept { *this = std::move(other); }

  public:
    virtual ~BaseArray() { deleteThis(); }

  protected:
    void deleteThis() { deleteUniqueArray(_array, _physicalSize); }

  protected:
    static void deleteUniqueArray(Unique<E> **&array, unsigned long size) {
        for (unsigned long i = 0; i < size; i++) { delete array[i]; }
        delete[] array;
    }

  public:
    /**
     * @warning in case the element you are trying to get was originally a
     *          `rvalue`, you will get the *one and only* reference to that element,
     *          and `this` array won't have access to it anymore.
     *          Thus, in case you need the reference to this element more than
     *          once, you **must catch** the return value of this method,
     *          or else nobody will have a reference for this element anymore,
     *          and it will be destroyed.
     *          @note as said before, in case the element you are trying to get
     *                was originally a `rvalue`, you will get the *one and only* reference to
     *                this element - and then, `this` array will replace its
     *                presence with `nullptr` (to mark it as "deleted").
     */
    virtual E *getElement(unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        E *element = _array[index]->getElement(); // Shallow copy pointer.

        if (_array[index]->isNeedToDeleteElement()) {
            delete _array[index]; // Delete the old unique pointer.
            _array[index] = new Unique<E>(nullptr);
        }

        return element;
    }

  public:
    /**
     * @param isAnonymous in case the element as an "inline anonymous heap
     *                    allocated lvalue" then, you should set the
     *                    @p isAnonymous to `true`. And that way, `this` array
     *                    will know to `delete` it after its use automatically.
     */
    virtual void setElement(E *element, unsigned long index, bool isAnonymous) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        auto *unique = new Unique<E>(element);
        if (isAnonymous) { unique->setNeedToDeleteElement(true); }

        // Delete old element.
        delete this->_array[index];

        this->_array[index] = unique;
    }

  public:
    virtual void setElement(E &&element, unsigned long index) {
        if (isOutOfRange(index)) {
            throw std::out_of_range(OUT_OF_RANGE_MESSAGE);
        }

        auto *unique        = new Unique<E>((E &&) element);

        // Delete old element.
        delete this->_array[index];

        this->_array[index] = unique;
    }

  public:
    virtual E *deleteElement(unsigned long index) {
        Unique<E> *uniqueDeleted  = _array[index];
        E *        elementDeleted = uniqueDeleted->getElement();
        if (!uniqueDeleted->isNeedToDeleteElement()) {
            uniqueDeleted = nullptr;
        }
        return elementDeleted;
    }

  public:
    /**
     * @brief This method will *invoke* the given @p callBack function on
     *        each element in the array.
     *
     * For example:
     * @code
     *    BaseArray<std::string> baseArray(3);
     *    baseArray.setElement("32", 0);
     *    baseArray.setElement("455", 1);
     *    baseArray.setElement("7678", 2);
     *    std::cout << baseArray << std::endl;
     *
     *    baseArray.forEach([&baseArray](auto *s) { *s = s->substr(0, 1); });
     *    // You may also use the explicit option of:
     *    // baseArray.forEach([&baseArray](std::string *s) { *s = s->substr(0, 1); });
     *
     *    std::cout << baseArray << std::endl;
     * @endcode
     * will result with the output of:
     * @code
     * [32 ,455 ,7678]
     * [3 ,4 ,7]
     * @endcode
     *
     * @param callBack a `void` function that each element in the array will
     *                 be invoked with.
     *                  @note You are suggested to use a "lambda" function
     *                        for this function - so that it will be quicker
     *                        for you to use this method.
     * @return `this` object. So that you may "chain" this method with another.
     */
    virtual BaseArray<E> &forEach(const std::function<void(E *)> &callBack,
                                  unsigned long sizeToIterateOnTo = 0) {
        unsigned long sizeToIterateOnToDynamic =
                getSizeToIterateOnToDynamic(sizeToIterateOnTo);

        for (unsigned long i = 0; i < sizeToIterateOnToDynamic; i++) {
            callBack(this->_array[i]->getElement());
        }

        return *this;
    }

  public:
    /**
     * @brief This method will *filter* out from the array the elements that
     *        do not return `true` the given @p predicate function.
     *
     * @note in case all of the array got filtered out, then this method will
     *       return an array of physicalSize of `1` with `nullptr` as its
     *       first element.
     *
     * For example:
     * @code
     * BaseArray<std::string> baseArray(3);
     * std::cout << baseArray << std::endl;
     * baseArray.filter([&baseArray](auto *s) { return s != nullptr; });
     * // You may also use the explicit option of:
     * // baseArray.filter([&baseArray](std::string *s) { return s != nullptr; });
     * std::cout << baseArray << std::endl;
     * @endcode
     * will result with the output of:
     * @code
     * [nullptr ,nullptr ,nullptr]
     * [nullptr]
     * @endcode
     *
     * @param predicate a `bool` function such that only the elements that
     *                  are returning `true` to this @p predicate function
     *                  would remain in the array. The others would be
     *                  `deleted` from the array.
     *                  @note You are suggested to use a "lambda" function
     *                        for this function - so that it will be quicker
     *                        for you to use this method.
     * @return `this` object. So that you may "chain" this method with another.
     */
    virtual BaseArray<E> &filter(const std::function<bool(E *)> &predicate,
                                 unsigned long sizeToIterateOnTo = 0) {
        unsigned long sizeToIterateOnToDynamic =
                getSizeToIterateOnToDynamic(sizeToIterateOnTo);

        unsigned long newArrayPhysicalSize = 0;

        /*
         * Must iterate over the array twice.
         * The `for-loops`' content is:
         * 1. Count the `newArraySize`.
         * 2. - `insert` the elements that are `true` with the predicate
         *      given to `newArray`.
         */
        for (unsigned long i = 0; i < sizeToIterateOnToDynamic; i++) {
            if (predicate(this->_array[i]->getElement())) {
                newArrayPhysicalSize++;
            }
        }

        if (!newArrayPhysicalSize) { newArrayPhysicalSize = 1; }

        Unique<E> **newArray = new Unique<E> *[newArrayPhysicalSize];
        initUniqueArray(newArray, newArrayPhysicalSize);

        copyArraysBasedOnPredicate(predicate, newArray);

        this->deleteThis();
        this->_array        = newArray;
        this->_physicalSize = newArrayPhysicalSize;
        return *this;
    }

  protected:
    void copyArraysBasedOnPredicate(const std::function<bool(E *)> &predicate,
                                    Unique<E> **                    newArray) {
        for (unsigned long i = 0; i < _physicalSize; i++) {
            E *element = _array[i]->getElement();
            if (predicate(element)) {

                /*
                 * - If element is originally a "lvalue", then shallow-copy the
                 *   pointer.
                 * - else if the element is originally a "rvalue", then
                 *   deep-copy the pointer.
                 */
                if (!_array[i]->isNeedToDeleteElement()) {

                    // Shallow-Copy the pointer within unique.
                    newArray[i] = _array[i];
                } else if (_array[i]->isNeedToDeleteElement()) {

                    // Deep-Copy the pointer within unique.
                    newArray[i] = new Unique<E>(*_array[i]);
                }
                continue;
            }
        }
    }

  public:
    /**
     * @brief This method will *map* out another `Array` from `this` array.
     *
     * For exmaple:
     * @code
     *    class ObjectTest {
     *
     *      private:
     *        int _arbitraryInt = 0;
     *
     *      public:
     *        explicit ObjectTest(int arbitraryInt) { _arbitraryInt = arbitraryInt; }
     *
     *      public:
     *        friend std::ostream &operator<<(std::ostream &    os,
     *                                        const ObjectTest &object) {
     *            os << "_arbitraryInt: " << object._arbitraryInt;
     *            return os;
     *        }
     *    };
     *
     * // ------------------------------------------------
     *
     *    BaseArray<std::string> baseArray(3);
     *    baseArray.setElement("32", 0);
     *    baseArray.setElement("455", 1);
     *    baseArray.setElement("7678", 2);
     *    std::cout << baseArray << std::endl;
     *
     *    auto mappedBaseArray = baseArray.map<ObjectTest>(
     *            [&baseArray](std::string *s) {
     *                return new ObjectTest(std::atoi(s->c_str()));
     *            },
     *            true);
     *    std::cout << mappedBaseArray << std::endl;
     * @endcode
     * will result with the output of:
     * @code
     * [32 ,455 ,7678]
     * [_arbitraryInt: 32 ,_arbitraryInt: 455 ,_arbitraryInt: 7678]
     * @endcode
     *
     * @tparam E2 the type of `element`s in the returned `Array`.
     * @param mapFunction a `E2`-return-type function that each element in
     *                    the array will be invoked with, and *maps* that element
     *                    to another object of type `E2`.
     *                    Afterwards, the elements in `this` array would be
     *                    `deleted` from the array.
     *                    @note You are suggested to use a "lambda" function
     *                          for this function - so that it will be
     *                          quicker for you to use this method.
     * @param sizeToIterateOnTo you may pick a different size to-iterate on the
     *                      array. The default size is its physical size, so
     *                      it will iterate on all of it.
     * @return the array of type `E2` mapped by `this` array. This way, you
     *         may also "chain" this method with another.
     */
    template<typename E2>
    BaseArray<E2> map(const std::function<E2 *(E *)> &mapFunction,
                      bool                            isAnonymous       = false,
                      unsigned long                   sizeToIterateOnTo = 0) {
        unsigned long sizeToIterateOnToDynamic =
                getSizeToIterateOnToDynamic(sizeToIterateOnTo);

        /*
         * Must iterate over the array once.
         * The `for-loop`'s content is:
         * - `insert` the new mapped-elements to `newArray`.
         */
        BaseArray<E2> e2Array(sizeToIterateOnToDynamic);
        for (unsigned long i = 0; i < sizeToIterateOnToDynamic; i++) {
            E *element = this->_array[i]->getElement();
            e2Array.setElement(mapFunction(element), i, isAnonymous);
        }

        return e2Array;
    }

  public:
    // FIXME: need to fix.
    //  this doesn't work for example with: `std::string` "map &&" to `int`
    /**
     * @brief This method will *map* out another `Array` from `this` array.
     *
     * @tparam E2 the type of `element`s in the returned `Array`.
     * @param mapFunction a `E2`-return-type function that each element in
     *                    the array will be invoked with, and *maps* that element
     *                    to another object of type `E2`.
     *                    Afterwards, the elements in `this` array would be
     *                    `deleted` from the array.
     *                    @note You are suggested to use a "lambda" function
     *                          for this function - so that it will be
     *                          quicker for you to use this method.
     * @param sizeToIterateOnTo you may pick a different size to-iterate on the
     *                      array. The default size is its physical size, so
     *                      it will iterate on all of it.
     * @return the array of type `E2` mapped by `this` array. This way, you
     *         may also "chain" this method with another.
     */
    template<typename E2>
    BaseArray<E2> map(const std::function<E2 && (E *)> &mapFunction,
                      unsigned long                     sizeToIterateOnTo = 0) {
        unsigned long sizeToIterateOnToDynamic =
                getSizeToIterateOnToDynamic(sizeToIterateOnTo);

        /*
         * Must iterate over the array once.
         * The `for-loop`'s content is:
         * - `insert` the new mapped-elements to `newArray`.
         */
        BaseArray<E2> e2Array(sizeToIterateOnToDynamic);
        for (unsigned long i = 0; i < sizeToIterateOnToDynamic; i++) {
            E *element = this->_array[i]->getElement();
            e2Array.setElement(mapFunction(element), i);
        }

        return e2Array;
    }

  private:
    unsigned long getSizeToIterateOnToDynamic(unsigned long sizeToIterateOnTo) {
        unsigned long sizeToIterateOnToDynamic = this->_physicalSize;
        if (sizeToIterateOnTo) {
            if (this->isOutOfRange(sizeToIterateOnTo - 1)) {
                std::string msg = (char *) this->SIZE_OUT_OF_RANGE_MESSAGE;
                std::string msg2 =
                        (char *) "You picked a size that is larger than the "
                                 "current `physicalSize` of :" +
                        this->_physicalSize;
                throw std::out_of_range(msg + " " + msg2);
            }
            sizeToIterateOnToDynamic = sizeToIterateOnTo;
        }
        return sizeToIterateOnToDynamic;
    }

  public:
    /**
     * @brief Shallow-Copying `this` object.
     * @return a shallow-copy of `this` object.
     */
    BaseArray<E> &copy() {
        BaseArray<E> copyArray(_physicalSize);
        for (unsigned long i = 0; i < _physicalSize; i++) {
            copyArray._array[i] = _array[i]; // Shallow-Copy the reference.
        }

        return copyArray;
    }

  protected:
    virtual bool isOutOfRange(unsigned long index) {

        // `_physicalSize` *must* be at least 1.
        return !((0 <= index) && (index < _physicalSize));
    }

  protected:
    void assertNotNull(E *element) {
        if (element == nullptr) {
            std::string msg = (char *) ELEMENT_IS_NULL_MESSAGE;
            std::string msg2 =
                    (char *) "Use the `getElement(unsigned long)`"
                             " method to retrieve it, instead of this"
                             " method.";
            throw std::runtime_error(msg + " " + msg2);
        }
    }

  public:
    BaseArray &operator=(const BaseArray &other) {

        // Guard self assignment
        if (this == &other) { return *this; }

        // Free the existing resource.
        deleteThis();

        // Copy the data pointer and its size from the source object.
        this->_physicalSize = other._physicalSize;
        for (unsigned long i = 0; i < _physicalSize; i++) {
            _array[i] = other._array[i]; // Shallow-Copy the reference.
        }

        return *this;
    }

  public:
    BaseArray &operator=(BaseArray &&other) noexcept {

        // Guard self assignment
        if (this != &other) {

            // Free the existing resource.
            deleteThis();

            // Copy the data pointer and its size from the source object.
            this->_physicalSize = other._physicalSize;
            for (unsigned long i = 0; i < _physicalSize; i++) {
                _array[i] = other._array[i]; // Shallow-Copy the reference.
            }

            /*
             * Release the data pointer from the source object so that
             * the destructor does not free the memory multiple times.
             */
            other._physicalSize = 0;
            other._array        = nullptr;
        }
        return *this;
    }

  public:
    friend std::ostream &operator<<(std::ostream &os, const BaseArray &array) {
        return print(os, array);
    }

  private:
    /**
     * @note This method is `nullptr` resistant - Instead of crashing, it prints
     *       "nullptr".
     */
    static std::ostream &print(std::ostream &os, const BaseArray &array) {
        os << '[';
        if (array._physicalSize) {
            printElement(os, (array._array[0])->getElement());
        }
        for (unsigned long i = 1; i < array._physicalSize; i++) {
            os << " ,";
            printElement(os, (array._array[i])->getElement());
        }
        os << ']';
        return os;
    }

  protected:
    static void printElement(std::ostream &os, E *element) {
        if (element == nullptr) {
            os << "nullptr";
        } else {
            os << *element;
        }
    }
};

#endif // BASE_ARRAY_H
