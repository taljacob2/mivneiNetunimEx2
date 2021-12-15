
#ifndef OBJECT_MAKER_H
#define OBJECT_MAKER_H

#include <string>

/**
 * @brief This class serves as the root class all classes.
 *
 * @li This class enables its sub-classes to use the `delete` operator when
 * they are *stack-allocated*, *without* causing a crash of
 * `Invalid free() / delete / delete[] / realloc()`.
 *
 * @author Tal Yacob.
 * @version 1.0.1
 */
class Object {

  private:
    bool onInitArbitraryField = onInit();

  private:
    bool onInit() {
        setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse();
        return false;
    }

  private:
    void
    setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse() {
        createdOnHeap       = createdOnHeapStatic;
        createdOnHeapStatic = false;
    }

  private:
    /**
     * @attention Initialized at the beginning of the constructor invocation.
     */
    bool createdOnHeap;

  private:
    static bool createdOnHeapStatic;

  private:
    bool isCreatedOnHeap() const { return createdOnHeap; }

  public:
    void *operator new(size_t sz) { operatorNewPrivate(sz); }

  private:
    static void *operatorNewPrivate(size_t sz) {
        createdOnHeapStatic = true;
        return ::operator new(sz);
    }

  protected:
    virtual void *invokeOperatorNew(size_t sz) { operatorNewPrivate(sz); }

  public:
    void operator delete(void *ptrToDelete) {
        operatorDeletePrivate(ptrToDelete);
    }

  private:
    static void *operatorDeletePrivate(void *ptrToDelete) {
        auto *obj = (Object *) ptrToDelete;
        if (obj->isCreatedOnHeap()) { ::operator delete(ptrToDelete); }
    }

  protected:
    virtual void invokeOperatorDelete(void *ptrToDelete) {
        operatorDeletePrivate(ptrToDelete);
    }
};

bool Object::createdOnHeapStatic = false;

#endif // OBJECT_MAKER_H
