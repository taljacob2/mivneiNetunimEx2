
#ifndef POLYMORPHER_H
#define POLYMORPHER_H

template<typename BASE_CLASS, typename SUB_CLASS>
class Polymorpher {

  public:
    /**
     * For example:
     * @code
     * auto minHeap = MinHeap<int, std::string>(1);
     * HeapAdt<int, std::string> &heap =
     *         Polymorpher::polymorph<HeapAdt<int, std::string>,
     *                 MinHeap<int, std::string>>(minHeap);
     * @endcode
     */
    static BASE_CLASS &polymorph(const SUB_CLASS &subClass) {
        return (BASE_CLASS &) subClass;
    }
};

#endif // POLYMORPHER_H
