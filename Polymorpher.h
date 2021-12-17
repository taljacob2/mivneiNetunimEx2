
#ifndef POLYMORPHER_H
#define POLYMORPHER_H

class Polymorpher {

  public:
    template<typename E>
    /**
     * @todo `delete` `element`.
     */
    static E *convertReferenceToPointer(const E &element) {

        /*
         * IMPORTANT: Polymorphic use.
         * A "pointer ( = *)" is the parent-class of a "reference ( = &)".
         */
        E *pElement = moveLocalAllocatedToHeap(element);
        return pElement;
    }

  private:
    template<typename E>
    /**
     * @todo `delete` `element`.
     */
    static E *moveLocalAllocatedToHeap(const E &element) {
        E *pElement = new E(element);
        return pElement;
    }

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
    template<typename BASE_CLASS, typename SUB_CLASS>
    static BASE_CLASS &polymorph(const SUB_CLASS &subClass) {
        return (BASE_CLASS &) subClass;
    }
};

#endif // POLYMORPHER_H
