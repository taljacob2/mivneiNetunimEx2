
#ifndef POLYMORPH_H
#define POLYMORPH_H

template<typename SUBCLASS> class Pointer {

  private:
    SUBCLASS *_subclass = nullptr;

  public:
    Pointer(const SUBCLASS &subclass) {
        _subclass = convertReferenceToPointer(subclass);
    }

  public:
    virtual ~Pointer() {
        // delete _subclass; // TODO: debug
    }

  public:
    SUBCLASS *getSubclass() const { return _subclass; }

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
    static SUBCLASS *moveLocalAllocatedToHeap(const E &element) {
        E *pElement = new E(element);
        return pElement;
    }
};

#endif // POLYMORPH_H
