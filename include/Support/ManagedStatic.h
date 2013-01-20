//===- ManagedStatic.h ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MANAGED_STATIC_H
#define LUBA_MANAGED_STATIC_H
#include <cstddef>

namespace luba {

template<class C>
void* object_creator() {
  return new C();
}

template<typename T> struct object_deleter {
  static void call(void * Ptr) { delete (T*)Ptr; }
};

/// ManagedStaticBase - Common base class for ManagedStatic instances.
class ManagedStaticBase
{
protected:
  typedef void (*DeleterFuncType)(void*);

protected:
  // This should only be used as a static variable, which guarantees that this
  // will be zero initialized.
  mutable void* m_Ptr;
  mutable DeleterFuncType m_pDeleter;
  mutable const ManagedStaticBase* m_pNext;

  void RegisterManagedStatic(void *(*creator)(), void (*deleter)(void*)) const;

public:
  bool isConstructed() const { return (NULL != m_Ptr); }

  void destroy() const;
};

template<class C>
class ManagedStatic : public ManagedStaticBase
{
public:

  // Accessors.
  C &operator*() {
    void* tmp = m_Ptr;
    if (NULL == tmp)
      RegisterManagedStatic(object_creator<C>, object_deleter<C>::call);
    return *static_cast<C*>(m_Ptr);
  }

  const C &operator*() const {
    void* tmp = m_Ptr;
    if (NULL == tmp)
      RegisterManagedStatic(object_creator<C>, object_deleter<C>::call);
    return *static_cast<C*>(m_Ptr);
  }

  C *operator->() {
    void* tmp = m_Ptr;
    if (NULL == tmp)
      RegisterManagedStatic(object_creator<C>, object_deleter<C>::call);

    return static_cast<C*>(m_Ptr);
  }

  const C *operator->() const {
    void* tmp = m_Ptr;
    if (NULL == tmp)
      RegisterManagedStatic(object_creator<C>, object_deleter<C>::call);

    return static_cast<C*>(m_Ptr);
  }
};

/// shutdown - Deallocate and destroy all ManagedStatic variables.
void Shutdown();

} // namespace of luba

#endif
