// Boost.Function library

// Copyright (C) 2001 Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
 
// For more information, see http://www.boost.org
 
// William Kempf, Jesse Jones and Karl Nelson were all very helpful in the
// design of this library.

#ifndef BOOST_FUNCTION_HPP
#define BOOST_FUNCTION_HPP

#include <boost/function/function_base.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/same_traits.hpp>
#include <boost/type_traits/transform_traits.hpp>
#include <boost/type_traits/ice.hpp>
#include <boost/function/function0.hpp>
#include <boost/function/function1.hpp>
#include <boost/function/function2.hpp>
#include <boost/function/function3.hpp>
#include <boost/function/function4.hpp>
#include <boost/function/function5.hpp>
#include <boost/function/function6.hpp>
#include <boost/function/function7.hpp>
#include <boost/function/function8.hpp>
#include <boost/function/function9.hpp>
#include <boost/function/function10.hpp>

namespace boost {
  namespace detail {
    namespace function {
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      template<typename Signature> 
      struct function_traits
      {
        typedef void result_type;
        typedef void arg1_type;
        typedef void arg2_type;
        typedef void arg3_type;
        typedef void arg4_type;
        typedef void arg5_type;
        typedef void arg6_type;
        typedef void arg7_type;
        typedef void arg8_type;
        typedef void arg9_type;
        typedef void arg10_type;
      };

      template<typename R>
      struct function_traits<R (*)(void)>
      {
        typedef R result_type;
        typedef unusable arg1_type;
        typedef unusable arg2_type;
        typedef unusable arg3_type;
        typedef unusable arg4_type;
        typedef unusable arg5_type;
        typedef unusable arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };
      
      template<typename R, typename T1>
      struct function_traits<R (*)(T1)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef unusable arg2_type;
        typedef unusable arg3_type;
        typedef unusable arg4_type;
        typedef unusable arg5_type;
        typedef unusable arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };
      
      template<typename R, typename T1, typename T2>
      struct function_traits<R (*)(T1, T2)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef unusable arg3_type;
        typedef unusable arg4_type;
        typedef unusable arg5_type;
        typedef unusable arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3>
      struct function_traits<R (*)(T1, T2, T3)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef unusable arg4_type;
        typedef unusable arg5_type;
        typedef unusable arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4>
      struct function_traits<R (*)(T1, T2, T3, T4)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef unusable arg5_type;
        typedef unusable arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5>
      struct function_traits<R (*)(T1, T2, T3, T4, T5)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef T5 arg5_type;
        typedef unusable arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6>
      struct function_traits<R (*)(T1, T2, T3, T4, T5, T6)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef T5 arg5_type;
        typedef T6 arg6_type;
        typedef unusable arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7>
      struct function_traits<R (*)(T1, T2, T3, T4, T5, T6, T7)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef T5 arg5_type;
        typedef T6 arg6_type;
        typedef T7 arg7_type;
        typedef unusable arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7, typename T8>
      struct function_traits<R (*)(T1, T2, T3, T4, T5, T6, T7, T8)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef T5 arg5_type;
        typedef T6 arg6_type;
        typedef T7 arg7_type;
        typedef T8 arg8_type;
        typedef unusable arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7, typename T8, typename T9>
      struct function_traits<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef T5 arg5_type;
        typedef T6 arg6_type;
        typedef T7 arg7_type;
        typedef T8 arg8_type;
        typedef T9 arg9_type;
        typedef unusable arg10_type;
      };

      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7, typename T8, typename T9,
               typename T10>
      struct function_traits<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
      {
        typedef R result_type;
        typedef T1 arg1_type;
        typedef T2 arg2_type;
        typedef T3 arg3_type;
        typedef T4 arg4_type;
        typedef T5 arg5_type;
        typedef T6 arg6_type;
        typedef T7 arg7_type;
        typedef T8 arg8_type;
        typedef T9 arg9_type;
        typedef T10 arg10_type;
      };
#endif

      // Choose the appropriate underlying implementation
      template<int Args> struct real_get_function_impl {};

      template<>
      struct real_get_function_impl<0>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function0<R, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<1>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function1<R, T1, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<2>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function2<R, T1, T2, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<3>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function3<R, T1, T2, T3, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<4>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function4<R, T1, T2, T3, T4, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<5>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function5<R, T1, T2, T3, T4, T5, Policy, Mixin, Allocator> 
          type;
        };
      };

      template<>
      struct real_get_function_impl<6>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function6<R, T1, T2, T3, T4, T5, T6, Policy, Mixin, Allocator>
          type;
        };
      };

      template<>
      struct real_get_function_impl<7>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function7<R, T1, T2, T3, T4, T5, T6, T7, Policy, Mixin, 
                            Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<8>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function8<R, T1, T2, T3, T4, T5, T6, T7, T8, Policy, Mixin, 
                            Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<9>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function9<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, Policy, 
                            Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<10>
      {
        template<
          typename R, 
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy,
          typename Mixin,
          typename Allocator
        >
        struct params
        {
          typedef function10<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, 
                             Policy, Mixin, Allocator> type;
        };
      };

      template<typename T1, typename T2>
      struct is_not_same
      {
  	    BOOST_STATIC_CONSTANT(bool, value = !(is_same<T1, T2>::value));
      };

      template<
        typename InR, 
        typename InT1, 
        typename InT2, 
        typename InT3, 
        typename InT4,
        typename InT5, 
        typename InT6, 
        typename InT7, 
        typename InT8, 
        typename InT9,
        typename InT10,
        typename InPolicy = empty_function_policy,
        typename InMixin = empty_function_mixin,
        typename InAllocator = std::allocator<function_base> 
      >
      class get_function_impl
      {
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef function_traits<typename add_pointer<InR>::type> traits;
      public:                       

        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::result_type,
                               InR>::type R;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg1_type,
                               InT1>::type T1;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg2_type,
                               InT2>::type T2;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg3_type,
                               InT3>::type T3;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg4_type,
                               InT4>::type T4;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg5_type,
                               InT5>::type T5;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg6_type,
                               InT6>::type T6;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg7_type,
                               InT7>::type T7;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg8_type,
                               InT8>::type T8;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg9_type,
                               InT9>::type T9;
        typedef typename ct_if<(is_function<InR>::value),
                               typename traits::arg10_type,
                               InT10>::type T10;        
        typedef typename ct_if<
	                   (type_traits::ice_and<
	                     (is_function<InR>::value),
			     (is_not_same<InT1, unusable>::value)
	                    >::value),
                           InT1,
                           InPolicy>::type Policy;

        typedef typename ct_if<
	                   (type_traits::ice_and<
	                     (is_function<InR>::value),
			     (is_not_same<InT2, unusable>::value)
	                    >::value),
                           InT2,
                           InMixin>::type Mixin;

        typedef typename ct_if<
	                   (type_traits::ice_and<
	                     (is_function<InR>::value),
			     (is_not_same<InT3, unusable>::value)
	                    >::value),
                           InT3,
                           InAllocator>::type Allocator;
#else
      public:                       
		typedef InR R;
		typedef InT1 T1;
		typedef InT2 T2;
		typedef InT3 T3;
		typedef InT4 T4;
		typedef InT5 T5;
		typedef InT6 T6;
		typedef InT7 T7;
		typedef InT8 T8;
		typedef InT9 T9;
		typedef InT10 T10;
		typedef InPolicy Policy;
		typedef InMixin Mixin;
		typedef InAllocator Allocator;
#endif
        typedef typename real_get_function_impl<
          (count_used_args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::value)
          >::template params<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, 
                             Policy, Mixin, Allocator>::type
        type;
      };

  template<
    typename InR, 
    typename InT1, 
    typename InT2, 
    typename InT3, 
    typename InT4,
    typename InT5, 
    typename InT6, 
    typename InT7, 
    typename InT8, 
    typename InT9,
    typename InT10,
    typename InMyPolicy = empty_function_policy,
    typename InMyMixin = empty_function_mixin,
    typename InMyAllocator = std::allocator<function_base> 
  >
  class function_traits_builder
  {
    typedef get_function_impl<InR, InT1, InT2, InT3, InT4, InT5, InT6, InT7, 
                              InT8, InT9, InT10, InMyPolicy, InMyMixin, 
                              InMyAllocator>
      impl;

    typedef typename impl::R MyR;
    typedef typename impl::T1 MyT1;
    typedef typename impl::T2 MyT2;
    typedef typename impl::T3 MyT3;
    typedef typename impl::T4 MyT4;
    typedef typename impl::T5 MyT5;
    typedef typename impl::T6 MyT6;
    typedef typename impl::T7 MyT7;
    typedef typename impl::T8 MyT8;
    typedef typename impl::T9 MyT9;
    typedef typename impl::T10 MyT10;
    typedef typename impl::Policy MyPolicy;
    typedef typename impl::Mixin MyMixin;
    typedef typename impl::Allocator MyAllocator;

  public:
    typedef typename impl::type type;
    typedef MyPolicy    policy_type;
    typedef MyMixin     mixin_type;
    typedef MyAllocator allocator_type;

#ifndef BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
    template<typename Policy>
    struct policy : 
        public function_traits_builder<MyR, MyT1, MyT2, MyT3, MyT4, MyT5, MyT6,
                                       MyT7, MyT8, MyT9, MyT10, Policy, 
                                       mixin_type, allocator_type> {};

    template<typename Mixin>
    struct mixin : 
        public function_traits_builder<MyR, MyT1, MyT2, MyT3, MyT4, MyT5, MyT6,
                                       MyT7, MyT8, MyT9, MyT10, policy_type, 
                                       Mixin, allocator_type> {};

    template<typename Allocator>
    struct allocator : 
        public function_traits_builder<MyR, MyT1, MyT2, MyT3, MyT4, MyT5, MyT6,
                                       MyT7, MyT8, MyT9, MyT10, policy_type, 
                                       mixin_type, Allocator> {};
#else
    template<typename Policy>
    struct policy 
    {
      typedef typename function_traits_builder<MyR, MyT1, MyT2, MyT3, MyT4, 
                                               MyT5, MyT6, MyT7, MyT8, MyT9, 
                                               MyT10, Policy, mixin_type, 
                                               allocator_type>::type
        type;
    };

    template<typename Mixin>
    struct mixin
    {
      typedef typename function_traits_builder<MyR, MyT1, MyT2, MyT3, MyT4, 
                                               MyT5, MyT6, MyT7, MyT8, MyT9, 
                                               MyT10, policy_type, Mixin,
                                               allocator_type>::type
        type;
    };

    template<typename Allocator>
    struct allocator
    {
      typedef typename function_traits_builder<MyR, MyT1, MyT2, MyT3, MyT4, 
                                               MyT5, MyT6, MyT7, MyT8, MyT9, 
                                               MyT10, policy_type, mixin_type,
                                               Allocator>::type
        type;
    };
#endif
  };

    } // end namespace function
  } // end namespace detail

  template<
    typename R, 
    typename T1 = detail::function::unusable, 
    typename T2 = detail::function::unusable,
    typename T3 = detail::function::unusable,
    typename T4 = detail::function::unusable,
    typename T5 = detail::function::unusable,
    typename T6 = detail::function::unusable,
    typename T7 = detail::function::unusable,
    typename T8 = detail::function::unusable,
    typename T9 = detail::function::unusable,
    typename T10 = detail::function::unusable
  >
  class function :
    public detail::function::get_function_impl<R, T1, T2, T3, T4, T5, T6, T7, 
                                               T8, T9, T10>::type,
    public detail::function::function_traits_builder<R, T1, T2, T3, T4, T5, T6,
                                                     T7, T8, T9, T10>
  {
    typedef typename detail::function::get_function_impl<R, T1, T2, T3, T4, T5,
                                                         T6, T7, T8, T9, T10
                                                         >::type 
      base_type;

  public:
    typedef typename base_type::policy_type policy_type;
    typedef typename base_type::mixin_type mixin_type;
    typedef typename base_type::allocator_type allocator_type;              
    typedef function self_type;                                     
                                                                            
    function() : base_type() {}                                     
                                                                            
    template<typename Functor>                                              
    function(Functor BOOST_FUNCTION_TARGET_FIX(const &) f) : base_type(f) {}
                      
    function(const self_type& f) : base_type(static_cast<const base_type&>(f)){}
         
    template<typename Functor>
    self_type& operator=(Functor BOOST_FUNCTION_TARGET_FIX(const &) f)
    {
      self_type(f).swap(*this);
      return *this;
    }

    self_type& operator=(const base_type& f)
    {
      self_type(f).swap(*this);
      return *this;
    }

    self_type& operator=(const self_type& f)
    {   
      self_type(f).swap(*this);
      return *this;
    }

    template<typename Functor>
    void set(Functor BOOST_FUNCTION_TARGET_FIX(const &) f)
    {
      int deprecated;
      self_type(f).swap(*this);
    }

    void set(const base_type& f)
    {
      int deprecated;
      self_type(f).swap(*this);
    }

    void set(const self_type& f)                             
    {
      int deprecated;
      self_type(f).swap(*this);
    }   
  };

  template<typename R,
           typename T1, 
           typename T2,
           typename T3,
           typename T4,
           typename T5,
           typename T6,
           typename T7,
           typename T8,
           typename T9,
           typename T10>
  inline void swap(function<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& f1,
                   function<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& f2)
  {
    f1.swap(f2);
  }
} // end namespace boost

#endif
