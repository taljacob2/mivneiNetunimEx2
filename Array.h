
#ifndef ARRAY_H
#define ARRAY_H

#include <functional>

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
 * @version 1.0
 */
template<typename E> class Array {

  private:
    E **_array = nullptr;

  private:
    unsigned long _size = 0;

  public:
    unsigned long getSize() const { return _size; }

  public:
    explicit Array(unsigned long size) {
        _size  = size;
        _array = new E *[_size];
    }

  public:
    virtual ~Array() { delete[] _array; }

  public:
    E &operator[](unsigned long i) { return _array[i]; }

  public:
    const E &operator[](unsigned long i) const { return _array[i]; }

  public:
    void forEach(const std::function<void(E &)> &callBack) {
        for (int i = 0; i < _size; i++) { callBack(_array[i]); }
    }

  public:
    Array<E> &filter(const std::function<bool(E &)> &predicate,
                     bool                            deleteFilteredElements) {
        unsigned long newArraySize = 0;

        /*
         * Must iterate over the array twice.
         * The `for-loops`' content is:
         * 1. Count the `newArraySize`.
         * 2. - `insert` the elements that are `true` with the predicate
         *      given to `newArray`.
         *    - `delete` elements that are `false` with the predicate
         *      given from `_array`.
         */
        forEach([&newArraySize, predicate](E &e) {
            if (predicate(e)) { newArraySize++; }
        });

        E **newArray = new E *[newArraySize];

        for (int i = 0; i < _size; i++) {
            E *element = _array[i];

            if (predicate(element)) {
                newArray[i] = element;
                continue;
            }

            /**
             * This element should be filtered out from the array.
             * `delete` the element if the user required to.
             */
            if (deleteFilteredElements) { delete element; }
        }

        update(newArraySize, newArray);
        return this;
    }

  private:
    /**
     * @brief Update the fields of `this` object.
     * @param newArraySize .
     * @param newArray .
     */
    void update(unsigned long newArraySize, E **newArray) {
        delete[] _array;
        _array = newArray;
        _size  = newArraySize;
    }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Array &array) {


        os << "_array: " << array._array << " _size: " << array._size;
        return os;
    }
};

#endif // ARRAY_H
