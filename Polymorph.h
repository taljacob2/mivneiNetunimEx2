
#ifndef POLYMORPH_H
#define POLYMORPH_H

template<typename SUBCLASS> class Polymorh {

  private:
    SUBCLASS *_subclass = nullptr;

  public:
    Polymorh(const SUBCLASS &subclass) {
        _subclass = convertReferenceToPointer(subclass);
    }

  public:
    virtual ~Polymorh() { delete _subclass; }

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
