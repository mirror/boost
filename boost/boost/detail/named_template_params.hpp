// (C) Copyright Jeremy Siek 2001. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#ifndef BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP
#define BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP

#include <boost/type_traits/conversion_traits.hpp>
#include <boost/type_traits/composite_traits.hpp> // for is_reference
#if defined(__BORLANDC__)
#include <boost/type_traits/ice.hpp>
#endif

namespace boost {
  namespace detail {
    
    struct default_argument { };

    struct dummy_default_gen {
      template <class Base, class Traits>
      struct bind {
        typedef default_argument type;
      };
    };

   // This class template is a workaround for MSVC.
   template <class Gen> struct default_generator {
     typedef detail::dummy_default_gen type;
   };

    template <class T> struct is_default { 
      enum { value = false };  
      typedef type_traits::no_type type;
    };
    template <> struct is_default<default_argument> { 
      enum { value = true }; 
      typedef type_traits::yes_type type;
    };

    struct choose_default {
      template <class Arg, class DefaultGen, class Base, class Traits>
      struct bind {
        typedef typename default_generator<DefaultGen>::type Gen;
        typedef typename Gen::template bind<Base,Traits>::type type;
      };
    };
    struct choose_arg {
      template <class Arg, class DefaultGen, class Base, class Traits>
      struct bind {
        typedef Arg type;
      };
    };

#if defined(__BORLANDC__)
    template <class UseDefault>
    struct choose_arg_or_default { typedef choose_arg type; };
    template <>
    struct choose_arg_or_default<type_traits::yes_type> {
      typedef choose_default type;
    };
#else
    template <bool UseDefault>
    struct choose_arg_or_default { typedef choose_arg type; };
    template <>
    struct choose_arg_or_default<true> {
      typedef choose_default type;
    };
#endif
    
    template <class Arg, class DefaultGen, class Base, class Traits>
    class resolve_default {
#if defined(__BORLANDC__)
      typedef typename choose_arg_or_default<typename is_default<Arg>::type>::type Selector;
#else
      // This usually works for Borland, but I'm seeing weird errors in
      // iterator_adaptor_test.cpp when using this method.
      enum { is_def = is_default<Arg>::value };
      typedef typename choose_arg_or_default<is_def>::type Selector;
#endif
    public:
      typedef typename Selector
        ::template bind<Arg, DefaultGen, Base, Traits>::type type;
    };

    // To differentiate an unnamed parameter from a traits generator
    // we use is_convertible<X, iter_traits_gen_base>.
    struct named_template_param_base { };

    template <class X>
    struct is_named_param_list {
      enum { value  = is_convertible<X, named_template_param_base>::value };
    };
    
    struct choose_named_params {
      template <class Prev> struct bind { typedef Prev type; };
    };
    struct choose_default_arg {
      template <class Prev> struct bind { 
        typedef detail::default_argument type;
      };
    };

    template <bool Named> struct choose_default_dispatch { };
    template <> struct choose_default_dispatch<true> {
      typedef choose_named_params type;
    };
    template <> struct choose_default_dispatch<false> {
      typedef choose_default_arg type;
    };


    template <class PreviousArg>
    struct choose_default_argument {
      enum { is_named = is_named_param_list<PreviousArg>::value };
      typedef typename choose_default_dispatch<is_named>::type Selector;
      typedef typename Selector::template bind<PreviousArg>::type type;
    };

    // This macro assumes that there is a class named default_##TYPE
    // defined before the application of the macro.  This class should
    // have a single member class template named "bind" with two
    // template parameters: the type of the class being created (e.g.,
    // the iterator_adaptor type when creating iterator adaptors) and
    // a traits class. The bind class should have a single typedef
    // named "type" that produces the default for TYPE.  See
    // boost/iterator_adaptors.hpp for an example usage.  Also,
    // applications of this macro must be placed in namespace
    // boost::detail.

#define BOOST_NAMED_TEMPLATE_PARAM(TYPE) \
    struct get_##TYPE##_from_named { \
      template <class Base, class NamedParams, class Traits> \
      struct bind { \
          typedef typename NamedParams::traits NamedTraits; \
          typedef typename NamedTraits::TYPE TYPE; \
          typedef typename resolve_default<TYPE, \
            default_##TYPE, Base, NamedTraits>::type type; \
      }; \
    }; \
    struct pass_thru_##TYPE { \
      template <class Base, class Arg, class Traits> struct bind { \
          typedef typename resolve_default<Arg, \
            default_##TYPE, Base, Traits>::type type; \
      };\
    }; \
    template <int NamedParam> \
    struct get_##TYPE##_dispatch { }; \
    template <> struct get_##TYPE##_dispatch<1> { \
      typedef get_##TYPE##_from_named type; \
    }; \
    template <> struct get_##TYPE##_dispatch<0> { \
      typedef pass_thru_##TYPE type; \
    }; \
    template <class Base, class X, class Traits>  \
    class get_##TYPE { \
      enum { is_named = is_named_param_list<X>::value }; \
      typedef typename get_##TYPE##_dispatch<is_named>::type Selector; \
    public: \
      typedef typename Selector::template bind<Base, X, Traits>::type type; \
    }; \
    template <> struct default_generator<default_##TYPE> { \
      typedef default_##TYPE type; \
    }

    
  } // namespace detail
} // namespace boost

#endif // BOOST_DETAIL_NAMED_TEMPLATE_PARAMS_HPP
