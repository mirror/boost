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

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      template<bool GetIt, typename Traits> 
      struct get_arg1_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg1_type<true, Traits>
      {
        typedef typename Traits::arg1_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg2_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg2_type<true, Traits>
      {
        typedef typename Traits::arg2_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg3_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg3_type<true, Traits>
      {
        typedef typename Traits::arg3_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg4_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg4_type<true, Traits>
      {
        typedef typename Traits::arg4_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg5_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg5_type<true, Traits>
      {
        typedef typename Traits::arg5_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg6_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg6_type<true, Traits>
      {
        typedef typename Traits::arg6_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg7_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg7_type<true, Traits>
      {
        typedef typename Traits::arg7_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg8_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg8_type<true, Traits>
      {
        typedef typename Traits::arg8_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg9_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg9_type<true, Traits>
      {
        typedef typename Traits::arg9_type type;
      };

      template<bool GetIt, typename Traits> 
      struct get_arg10_type
      {
        typedef unusable type;
      };

      template<typename Traits> 
      struct get_arg10_type<true, Traits>
      {
        typedef typename Traits::arg10_type type;
      };

      template<bool IsFunction,
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
               typename InPolicy,
               typename InMixin,
               typename InAllocator>
      struct maybe_decode_function_args
      {
        // Not a function, so just map the types directly
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
      };

      template<typename InR, 
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
               typename InPolicy,
               typename InMixin,
               typename InAllocator>
      struct maybe_decode_function_args<true, InR, InT1, InT2, InT3, InT4,
                                        InT5, InT6, InT7, InT8, InT9, InT10,
                                        InPolicy, InMixin, InAllocator>
      {
        typedef function_traits<InR> traits;

        typedef typename traits::result_type R;
        typedef typename get_arg1_type<(traits::arity >= 1), traits>::type T1;
        typedef typename get_arg2_type<(traits::arity >= 2), traits>::type T2;
        typedef typename get_arg3_type<(traits::arity >= 3), traits>::type T3;
        typedef typename get_arg4_type<(traits::arity >= 4), traits>::type T4;
        typedef typename get_arg5_type<(traits::arity >= 5), traits>::type T5;
        typedef typename get_arg6_type<(traits::arity >= 6), traits>::type T6;
        typedef typename get_arg7_type<(traits::arity >= 7), traits>::type T7;
        typedef typename get_arg8_type<(traits::arity >= 8), traits>::type T8;
        typedef typename get_arg9_type<(traits::arity >= 9), traits>::type T9;
        typedef typename get_arg10_type<(traits::arity >= 10), traits>::type T10;
        typedef typename ct_if<(is_same<InT1, unusable>::value),
                               empty_function_policy,
                               InT1>::type Policy;
        typedef typename ct_if<(is_same<InT2, unusable>::value),
                               empty_function_mixin,
                               InT2>::type Mixin;
        typedef typename ct_if<(is_same<InT3, unusable>::value),
                               std::allocator<function_base>,
                               InT3>::type Allocator;
      };

#endif // ndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

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
        typedef maybe_decode_function_args<(is_function<InR>::value),
                                           InR, InT1, InT2, InT3, InT4, InT5,
                                           InT6, InT7, InT8, InT9, InT10,
                                           InPolicy, InMixin, InAllocator>
          decoder;
        typedef typename decoder::R R;
        typedef typename decoder::T1 T1;
        typedef typename decoder::T2 T2;
        typedef typename decoder::T3 T3;
        typedef typename decoder::T4 T4;
        typedef typename decoder::T5 T5;
        typedef typename decoder::T6 T6;
        typedef typename decoder::T7 T7;
        typedef typename decoder::T8 T8;
        typedef typename decoder::T9 T9;
        typedef typename decoder::T10 T10;
        typedef typename decoder::Policy Policy;
        typedef typename decoder::Mixin Mixin;
        typedef typename decoder::Allocator Allocator;
#else
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
#endif // def BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      public:                       
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
