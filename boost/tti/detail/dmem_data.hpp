
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_MEM_DATA_HPP)
#define BOOST_TTI_DETAIL_MEM_DATA_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/function_types/components.hpp>
#include <boost/function_types/is_member_object_pointer.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/detail/ddeftype.hpp>
#include <boost/tti/detail/dftclass.hpp>
#include <boost/tti/gen/namespace_gen.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(BOOST_MSVC) || (BOOST_WORKAROUND(BOOST_GCC, >= 40400) && BOOST_WORKAROUND(BOOST_GCC, < 40600))

#define BOOST_TTI_DETAIL_TRAIT_HAS_MEMBER_DATA(trait,name) \
  template<class T,class C> \
  struct BOOST_PP_CAT(trait,_detail_hmd) \
    { \
    template<class> \
    struct return_of; \
    \
    template<class R,class IC> \
    struct return_of<R IC::*> \
      { \
      typedef R type; \
      }; \
    \
    template<bool,typename U> \
    struct menable_if; \
    \
    template<typename U> \
    struct menable_if<true,U> \
      { \
      typedef U type; \
      }; \
    \
    template<typename U,typename V> \
    static ::boost::type_traits::yes_type check2(V U::*); \
    \
    template<typename U,typename V> \
    static ::boost::type_traits::no_type check2(U); \
    \
    template<typename U,typename V> \
    static typename \
      menable_if \
        < \
        sizeof(check2<U,V>(&U::name))==sizeof(::boost::type_traits::yes_type), \
        ::boost::type_traits::yes_type \
        > \
      ::type \
    has_matching_member(int); \
    \
    template<typename U,typename V> \
    static ::boost::type_traits::no_type has_matching_member(...); \
    \
    template<class U,class V> \
    struct ttc_md \
      { \
      typedef boost::mpl::bool_<sizeof(has_matching_member<V,typename return_of<U>::type>(0))==sizeof(::boost::type_traits::yes_type)> type; \
      }; \
    \
    typedef typename ttc_md<T,C>::type type; \
    \
    BOOST_STATIC_CONSTANT(bool,value=type::value); \
    \
    }; \
/**/

#else // !defined(BOOST_MSVC)

#include <boost/tti/detail/dmem_fun.hpp>

#define BOOST_TTI_DETAIL_TRAIT_HAS_MEMBER_DATA(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_TYPES_MEMBER_FUNCTION(trait,name) \
  template<class T,class C> \
  struct BOOST_PP_CAT(trait,_detail_hmd) : \
    BOOST_PP_CAT(trait,_detail_types)<T,C> \
    { \
    }; \
/**/

#endif // defined(BOOST_MSVC)

namespace boost
  {
  namespace tti
    {
    namespace detail
      {
      
      template<class T,class R>
      struct ptmd
        {
        typedef R T::* type;
        };
        
      template<class T>
      struct dmem_check_ptmd :
        boost::mpl::identity<T>
        {
        BOOST_MPL_ASSERT((boost::function_types::is_member_object_pointer<T>));
        };
        
      template<class T>
      struct dmem_check_ptec :
        BOOST_TTI_NAMESPACE::detail::class_type<T>
        {
        BOOST_MPL_ASSERT((boost::function_types::is_member_object_pointer<T>));
        };
        
      template<class T,class T2>
      struct dmem_get_type :
        boost::mpl::eval_if
          <
          boost::is_same<T2,BOOST_TTI_NAMESPACE::detail::deftype>,
          BOOST_TTI_NAMESPACE::detail::dmem_check_ptmd<T>,
          BOOST_TTI_NAMESPACE::detail::ptmd<T,T2>
          >
        {
        };
        
      template<class T,class T2>
      struct dmem_get_enclosing :
        boost::mpl::eval_if
          <
          boost::is_same<T2,BOOST_TTI_NAMESPACE::detail::deftype>,
          BOOST_TTI_NAMESPACE::detail::dmem_check_ptec<T>,
          boost::mpl::identity<T>
          >
        {
        };
        
      }
    }
  }
  
#endif // BOOST_TTI_DETAIL_MEM_DATA_HPP
