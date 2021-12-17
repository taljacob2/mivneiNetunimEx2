
#ifndef POLYMORPHER_H
#define POLYMORPHER_H

class Polymorpher {

  public:
    /**
     * For example:
     * @code
     * auto  minHeap = MinHeap<int, std::string>(1);
     * auto &heap    = Polymorpher::polymorphLValue<HeapAdt<int, std::string>,
     *                                           MinHeap<int, std::string>>(
     *         minHeap);
     * @endcode
     */
    template<typename BASE_CLASS, typename SUB_CLASS>
    static BASE_CLASS &polymorphLValue(SUB_CLASS &subClass) {
        return (BASE_CLASS &) subClass;
    }
};

#endif // POLYMORPHER_H
