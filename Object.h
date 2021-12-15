
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

/**
 * @brief This class serves as the root of all classes.
 *
 * @li This class enables the use of the `onInit()` method, which is being
 * invoked **before the constructor** and enables *lifecycle* to `this` object.
 * @li This class enables its sub-classes to use the `delete` operator when
 * they are *stack-allocated*, *without* causing a crash of
 * `Invalid free() / delete / delete[] / realloc()`.
 *
 * @author Tal Yacob.
 * @version 1.0.1
 */
class Object {

  private:

    /**
     * This arbitrary field is the responsible of the invocation of the
     * `onInit()` method. Because fields are being initialized **before** the
     * constructor, it makes sense to `inject` or `initialize` `this` object
     * here, on the `onInit()` method. This option, enables the thinking and
     * implementation of *lifecycle* solutions to this object.
     */
    bool onInitArbitraryField = onInit();

  protected:
    /**
     * @brief This special method is being invoked **before the constructor**.
     *
     * @li You may initialize this object here if you wish not to be
     * concerned of implementing your initializations across all the
     * constructors you would create in the future.
     * And instead prefer implementing them only once.
     *
     * @attention You may `override` this method to **add** your custom
     *            initializations *"onInit"* to this method, but make sure
     *            to still call this `base` `onInit` method, and also make
     *            sure to return an arbitrary `bool` value.
     *
     * @return an arbitrary value, just to force the invocation of this method.
     *         In this case, an arbitrary `bool` value.
     *         For example:
     *         @code
     *             protected:
     *               bool onInit() override {
     *                   Object::onInit();
     *
     *                   // Add your implementation here...
     *
     *                   return false;
     *               }
     *         @endcode
     */
    virtual bool onInit() {
        setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse();
        return false; // Arbitrary value to return.
    }

  private:
    void
    /**
     * @brief This method is invoked in the `onInit()` method, and serves for
     *        the `new` and `delete` operators.
     *
     * @li This method sets `createdOnHeap` to `createdOnHeapStatic`, so that
     * `createdOnHeap` would be updated for the current status of wether
     * `this` object was created with the `new` operator or not.
     * @li Afterwards, this method resets `createdOnHeapStatic` to `false`,
     * so that it will be ready for the next creation of `this` type of object.
     */
    setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse() {
        createdOnHeap       = createdOnHeapStatic;
        createdOnHeapStatic = false;
    }

  private:
    /**
     * @attention This field gets initialized before the constructor is being
     *            invoked, with the `onInit` method.
     * @see setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse()
     * @see onInit()
     */
    bool createdOnHeap;

  private:
    /**
     * This field tells if `this` objects was created by the `new` operator
     * or not. It is set to `true` by the `operatorNewPrivate` method when
     * the `new` operator was used to create `this` object, and it is set to
     * `false` by the `onInit` method before the constructor when `this` object
     * is created.
     *
     * @attention This field gets initialized before the constructor is being
     *            invoked, with the `onInit` method.
     * @see setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse()
     * @see onInit()
     */
    static bool createdOnHeapStatic;

  private:
    bool isCreatedOnHeap() const { return createdOnHeap; }

    /* --------------- operator `new` --------------- */

  public:

    /**
     * @brief This `public static` `new` operator is using a `private static`
     *        method for its body.
     *
     * @note This method is **not virtual**, and because of that it requires
     *       the use of `operatorNewPrivate(size_t)` and
     *       `invokeOperatorNew(size_t)` methods.
     * @see operatorNewPrivate(size_t)
     * @see invokeOperatorNew(size_t)
     */
    void *operator new(size_t sz) { operatorNewPrivate(sz); }

  private:
    /**
     * @brief This `private static` method is the *body* of the operator
     *        `new` method, and is being invoked too by the
     *        `invokeOperatorNew(size_t)` method **virtually**.
     *
     * @see invokeOperatorNew(size_t)
     */
    static void *operatorNewPrivate(size_t sz) {
        createdOnHeapStatic = true;
        return ::operator new(sz);
    }

  protected:
    /**
     * @brief This `protected` method is using the *body* of the operator
     *        `new` method, and is invoked by the sub-classes of this class
     *        **virtually** and naturally with the `new` operator itself.
     *
     * @see operatorNewPrivate(size_t)
     */
    virtual void *invokeOperatorNew(size_t sz) { operatorNewPrivate(sz); }

    /* --------------- operator `delete` --------------- */

  public:
    /**
     * @brief This `public static` `delete` operator is using a `private
     *        static` method for its body.
     *
     * @note This method is **not virtual**, and because of that it requires
     *       the use of `operatorDeletePrivate(void *)` and
     *       `invokeOperatorDelete(void *)` methods.
     * @see operatorDeletePrivate(void *)
     * @see invokeOperatorDelete(void *)
     */
    void operator delete(void *ptrToDelete) {
        operatorDeletePrivate(ptrToDelete);
    }

  private:
    /**
     * @brief This `private static` method is the *body* of the operator
     *        `delete` method, and is being invoked too by the
     *        `invokeOperatorDelete(void *)` method **virtually**.
     *
     * @see invokeOperatorDelete(void *)
     */
    static void *operatorDeletePrivate(void *ptrToDelete) {
        auto *obj = (Object *) ptrToDelete;
        if (obj->isCreatedOnHeap()) { ::operator delete(ptrToDelete); }
    }

  protected:
    /**
     * @brief This `protected` method is using the *body* of the operator
     *        `delete` method, and is invoked by the sub-classes of this class
     *        **virtually** and naturally with the `delete` operator itself.
     *
     * @see operatorDeletePrivate(void *)
     */
    virtual void invokeOperatorDelete(void *ptrToDelete) {
        operatorDeletePrivate(ptrToDelete);
    }
};

/**
 * @see Object::createdOnHeapStatic
 */
bool Object::createdOnHeapStatic = false;

#endif // OBJECT_H
