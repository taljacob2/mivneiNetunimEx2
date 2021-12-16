
#ifndef ARRAY_H
#define ARRAY_H

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
    E *_array = nullptr;

  private:
    unsigned long _size = 0;

  public:
    unsigned long getSize() const { return _size; }

  public:
    E &operator[](unsigned long i) { return _array[i]; }

  public:
    explicit Array(unsigned long size) {
        _size  = size;
        _array = new E[_size];
    }

  public:
    virtual ~Array() { delete[] _array; }
};

#endif // ARRAY_H
