
#ifndef POLYMORPH_H
#define POLYMORPH_H

template<typename T> class Pointer {

  private:
    T *_pointer = nullptr;

  public:
    Pointer(const T &instance) {
        _pointer = convertReferenceToPointer(instance);
    }

  public:
    virtual ~Pointer() {
        // delete _pointer; // TODO: debug
    }

  public:
    T *getPointer() const { return _pointer; }

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

#endif // POLYMORPH_H
