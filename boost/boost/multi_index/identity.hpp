/* Copyright Joaquín M López Muñoz 2003-2004. Use, modification, and
 * distribution are subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_IDENTITY_HPP
#define BOOST_MULTI_INDEX_IDENTITY_HPP

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/identity_fwd.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost{

template<class Type> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* identity is a do-nothing key extractor that returns the [const] Type&
 * object passed.
 * Additionally, identity is overloaded to support referece_wrappers
 * of Type and "chained pointers" to Type's. By chained pointer to Type we
 * mean a  type  P such that, given a p of type P
 *   *...n...*x is convertible to Type&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. Type** or auto_ptr<Type*>.)
 */

/* NB. Some overloads of operator() have an extra dummy parameter int=0.
 * This is so because MSVC++ 6.0 otherwise *incorrectly* regards these
 * overloads as specializations of a previous member function template.
 * Left for all compilers as it does no harm.
 */

template<typename Type>
struct const_identity_base
{
  typedef Type result_type;

  template<typename ChainedPtr>
  Type& operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(
    const reference_wrapper<typename remove_const<Type>::type>& x)const
  { 
    return x.get();
  }
};

template<typename Type>
struct non_const_identity_base
{
  typedef Type result_type;

  /* templatized for pointer-like types */
  
  template<typename ChainedPtr>
  Type& operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  const Type& operator()(const Type& x,int=0)const
  {
    return x;
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  const Type& operator()(const reference_wrapper<const Type>& x,int=0)const
  { 
    return x.get();
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }
};

} /* namespace multi_index::detail */

template<class Type>
struct identity:
  mpl::if_c<
    is_const<Type>::value,
    detail::const_identity_base<Type>,detail::non_const_identity_base<Type>
  >::type
{
};

} /* namespace multi_index */

} /* namespace boost */

#endif
