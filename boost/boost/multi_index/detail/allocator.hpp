/* Copyright Joaquín M López Muñoz 2003-2004. Use, modification, and
 * distribution are subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ALLOCATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_ALLOCATOR_HPP

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cstddef>
#include <new>

namespace boost{

namespace multi_index{

namespace detail{

/* allocator adaption layer */

namespace allocator{

/* Detects whether a given allocator is from old Dinkumware's stdlib,
 * which lacks rebind and uses an ugly _Charalloc memfun as a poor
 * replacement.
 * Note that it does not suffice to check the Boost.Config stdlib
 * macros, as the user might have passed a custom, compliant allocator.
 */

#if defined(BOOST_DINKUMWARE_STDLIB)&&defined(BOOST_NO_STD_ALLOCATOR)

template<typename Allocator>
struct dinkumware_defective_allocator
{
  BOOST_STATIC_CONSTANT(bool,
    value=(
      is_same<
        Allocator,
        std::allocator<BOOST_DEDUCED_TYPENAME Allocator::value_type>
      >::value));
};

#else

template<typename Allocator>
struct dinkumware_defective_allocator
{
  BOOST_STATIC_CONSTANT(bool,value=false);
};

#endif

/* allocator ops for Dinkumware's defective allocator */

template<typename Allocator,typename Type>
struct dinkumware_defective_allocator_ops
{
  typedef Allocator rebound_type;

  static Type* allocate(Allocator& al,typename Allocator::size_type n)
  {
    return static_cast<Type*>(
      static_cast<void*>(al._Charalloc(n*sizeof(Type))));
  }

  static void deallocate(Allocator& al,Type* p,typename Allocator::size_type n)
  {
    al.deallocate(p,n);
  }

  static void construct(Allocator&,Type* p,const Type& t)
  {
    new(static_cast<void*>(p))Type(t);
  }

  static void destroy(Allocator&,Type* p)
  {
    (static_cast<Type*>(p))->~Type();
  }
};

/* allocator ops for compliant allocators */

#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
/* Workaround for a problem in MSVC with dependent template typedefs
 * when doing rebinding of allocators.
 * Modeled after <boost/mpl/aux_/msvc_dtw.hpp> (thanks, Aleksey!)
 */

template<typename Allocator>
struct msvc_rebind
{
  template<bool> struct fake_allocator:Allocator{};
  template<> struct fake_allocator<true>
  {
    template<typename Typename> struct rebind{};
  };

  template<typename Type>
  struct result:
    fake_allocator<mpl::aux::msvc_never_true<Allocator>::value>::
      template rebind<Type>
  {
  };
};
#endif

template<typename Allocator,typename Type>
struct compliant_allocator_ops
{

#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
  typedef typename msvc_rebind<Allocator>::
    template result<Type>::other              rebound_type;
#else
  typedef typename Allocator::
    BOOST_NESTED_TEMPLATE rebind<Type>::other rebound_type;
#endif

  static Type* allocate(Allocator& al,typename Allocator::size_type n)
  {
    return al.allocate(n);
  }

  static void deallocate(Allocator& al,Type* p,typename Allocator::size_type n)
  {
    al.deallocate(p,n);
  }

  static void construct(Allocator& al,Type *p,const Type& t)
  {
    al.construct(p,t);
  }

  static void destroy(Allocator& al,Type* p)
  {
    al.destroy(p);
  }
};

template<typename Allocator,typename Type>
struct allocator_ops:
  mpl::if_c<
    dinkumware_defective_allocator<Allocator>::value,
    dinkumware_defective_allocator_ops<Allocator,Type>,
    compliant_allocator_ops<Allocator,Type>
  >::type
{
};

/* allocator ops front end */

template<typename Allocator,typename Type>
struct rebind_to
{
  typedef typename allocator_ops<Allocator,Type>::rebound_type type;
};

template<typename Type,typename Allocator>
Type* allocate(
  Allocator& al,typename Allocator::size_type n
  BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Type))
{
  return allocator_ops<Allocator,Type>::allocate(al,n);
}

template<typename Allocator,typename Type>
void deallocate(Allocator& al,Type* p,typename Allocator::size_type n)
{
  allocator_ops<Allocator,Type>::deallocate(al,p,n);
}

template<typename Allocator,typename Type>
void construct(Allocator& al,Type* p,const Type& t)
{
  allocator_ops<Allocator,Type>::construct(al,p,t);
}

template<typename Allocator,typename Type>
void destroy(Allocator& al,Type* p)
{
  allocator_ops<Allocator,Type>::destroy(al,p);
}

/* allocator-independent versions of construct and destroy */

template<typename Type>
void construct(void* p,const Type& t)
{
  new (p) Type(t);
}

template<typename Type>
void destroy(const Type* p)
{
  p->~Type();
}

} /* namespace multi_index::detail::allocator */

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
