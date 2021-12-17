
#ifndef POINTER_H
#define POINTER_H

class Pointer {

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
};

#endif // POINTER_H
