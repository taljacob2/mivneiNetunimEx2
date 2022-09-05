
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

/**
 * @brief This class may serve as the root of all classes, because it gives
 *        them more functionality and stability.
 *
 * @li This class enables the use of the `onInit()` method, which is being
 * invoked **before the constructor** and enables *lifecycle* to `this` object.
 * @li This class enables its sub-classes to use the `delete` operator
 * even-though they are *stack-allocated*, *without* causing a crash of
 * `Invalid free() / delete / delete[] / realloc()`.
 * That means, for example, that you may allocate the sub-class
 * dynamically with the `new` operator in an *inline-anonymous* way for
 * *inserting* it to a *data-structure* of some sort,
 * and then "trust" that *data-structure* to `delete` this sub-class when it
 * decides to, with the `delete` operator - without that *data-structure*
 * knowing whether the sub-class was allocated via the stack or via the heap.
 * > For example, if `Entry` is a sub-class of `Object`, and `priorityQueue`'s
 * > destructor would in the future `delete` its `Entry`s with the `delete`
 * > operator:
 * > @code
 * > priorityQueue->insert(new Entry<int, std::string>(4, "yes"));
 * > @endcode
 *
 * **Flowchart Logic Explained:**
 * 
 * 0. We set a static variable named `Object::createdOnHeapStatic`, which its
 *    default value is set to `false`.
 * 
 * ----- The user calls the operator `new` to allocate a `new Object` on the heap ------
 * 
 * 1. `operator new` allocates the `Object` on heap memory.
 * 2. `operator new` changes `Object::createdOnHeapStatic` to `true`.
 * 
 * ----- Object creation begins ( = "lifecycle"): ------
 * 
 * 3. `this->onInit()` copies the value from `Object::createdOnHeapStatic` and
 *    sets it to `this->createdOnHeap`
 * 4. `this->onInit()` resets the value of `Object::createdOnHeapStatic` to
 *    `false` as the default value for the next Object creation.
 * 5. (Constructor is called here...)
 * 6. Other interfaces can check if the Object was allocated on heap by
 *    checking the value of `this->createdOnHeap`.
 * 
 * ----- The user calls the operator `delete`, may it be on purpose or by mistake ------
 * 
 * The `delete` operator now has an updated logic, that checks
 * `this->createdOnHeap` to indicate whether it is required to delete the
 * Object from the heap or not:
 * @code
 * if (obj->isCreatedOnHeap()) { ::operator delete(ptrToDelete); }
 * @endcode
 * 
 * Thus, the user doesn't really need to know whether the Object was originally
 * allocated on the heap or not. So now, it is possible to call the `delete`
 * operator on any Object, even if it may be *stack-allocated* - and *without*
 * causing a crash of `Invalid free() / delete / delete[] / realloc()`.
 * 
 * @version 1.0.2
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
     *            initializations to this method, but make sure
     *            to still call this `base` `onInit()` method, and also make
     *            sure to return an arbitrary `bool` value.
     *            For example:
     *            @code
     *                protected:
     *                  bool onInit() override {
     *                      Object::onInit();
     *
     *                      // Add your implementation here...
     *
     *                      return false;
     *                  }
     *            @endcode
     *
     * @return an arbitrary value, just to force the invocation of this method.
     *         In this case, an arbitrary `bool` value.
     */
    virtual bool onInit() {
        setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse();
        return false; // Arbitrary value to return.
    }

  private:
    /**
     * @brief This method is invoked in the `onInit()` method, and serves for
     *        the `new` and `delete` operators.
     *
     * @li This method sets `createdOnHeap` to `createdOnHeapStatic`, so that
     * `createdOnHeap` would be updated for the current status of whether
     * `this` object was created with the `new` operator or not.
     * @li Afterwards, this method resets `createdOnHeapStatic` to `false`,
     * so that it will be ready for the next creation of `this` type of object.
     */
    void
    setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse() {
        createdOnHeap       = createdOnHeapStatic;
        createdOnHeapStatic = false;
    }

  private:
    /**
     * This field indicates whether `this` object was created via the `new`
     * operator ( = on heap), or via the stack.
     *
     * @attention This field gets initialized before the constructor is being
     *            invoked, with the `onInit()` method.
     * @see setCreatedOnHeapToCreatedOnHeapStaticAndSetCreatedOnHeapStaticToFalse()
     * @see onInit()
     */
    bool createdOnHeap;

  private:
    /**
     * This field tells if `this` objects was created by the `new` operator
     * or not. It is set to `true` by the `operatorNewPrivate` method when
     * the `new` operator was used to create `this` object, and it is set to
     * `false` by the `onInit()` method before the constructor when `this`
     * object is created.
     *
     * @attention This field gets initialized before the constructor is being
     *            invoked, with the `onInit()` method.
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
    void *operator new(size_t sz) { return operatorNewPrivate(sz); }

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
    virtual void *invokeOperatorNew(size_t sz) {
        return operatorNewPrivate(sz);
    }

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
    static void operatorDeletePrivate(void *ptrToDelete) {
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
