// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETERS_031014_HPP
#define BOOST_PARAMETERS_031014_HPP

#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/iterator/detail/config_def.hpp>
#include <boost/python/detail/is_xxx.hpp>

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/default.hpp>
#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/config.hpp>

namespace boost {

template<class T> class reference_wrapper;

namespace parameter {

namespace aux { struct use_default {}; }

// These templates can be used to describe the treatment of particular
// named parameters for the purposes of overload elimination with
// SFINAE, by placing specializations in the parameters<...> list.  In
// order for a treated function to participate in overload resolution:
//
//   - all keyword tags wrapped in required<...> must have a matching
//     actual argument
//
//   - The actual argument type matched by every keyword tag
//     associated with a predicate must satisfy that predicate
//
// If a keyword k is specified without an optional<...> or
// required<...>, wrapper, it is treated as though optional<k> were
// specified.
//
template <class Tag, class Predicate = aux::use_default>
struct required
{
    typedef Tag key_type;
    typedef Predicate predicate;
};

template <class Tag, class Predicate = aux::use_default>
struct optional
{
    typedef Tag key_type;
    typedef Predicate predicate;
};

template <class Tag, class Predicate>
struct unnamed
{
    typedef Tag key_type;
    typedef Predicate predicate;
};

namespace aux {

  // Defines metafunctions, is_required, is_optional and is_unnamed, 
  // that identify required<...>, optional<...> and unnamed<> 
  // specializations.
  BOOST_PYTHON_IS_XXX_DEF(required, required, 2)
  BOOST_PYTHON_IS_XXX_DEF(optional, optional, 2)
  BOOST_PYTHON_IS_XXX_DEF(unnamed, unnamed, 2)

  //
  // key_type, has_default, and predicate --
  //
  // These metafunctions accept a ParameterSpec and extract the
  // keyword tag, whether or not a default is supplied for the
  // parameter, and the predicate that the corresponding actual
  // argument type is required match.
  //
  // a ParameterSpec is a specialization of either keyword<...>,
  // required<...> or optional<...>.
  //

  // helper for key_type<...>, below.
  template <class T>
  struct get_key_type
    : mpl::if_<
          is_unnamed<typename T::key_type>
        , get_key_type<typename T::key_type>
        , mpl::identity<typename T::key_type>
      >::type
  {};

  template <class T>
  struct key_type
    : mpl::eval_if<
          mpl::or_<
              is_optional<T>
            , is_required<T>
            , is_unnamed<T>
          >
        , get_key_type<T>
        , mpl::identity<T>
      >
  {
  };

  template <class T>
  struct has_default
    : mpl::not_<typename is_required<T>::type>
  {
  };

  // helper for get_predicate<...>, below
  template <class T>
  struct get_predicate_or_default
  {
      typedef T type;
  };

  template <>
  struct get_predicate_or_default<use_default>
  {
      typedef mpl::always<mpl::true_> type;
  };

  // helper for predicate<...>, below
  template <class T>
  struct get_predicate
    : mpl::if_<
          is_unnamed<typename T::key_type>
        , get_predicate<typename T::key_type>
        , get_predicate_or_default<typename T::predicate>
      >::type
  {};

  template <class T>
  struct predicate
    : mpl::eval_if<
         mpl::or_<
              is_optional<T>
            , is_required<T>
            , is_unnamed<T>
          >
        , get_predicate<T>
        , mpl::identity<mpl::always<mpl::true_> >
      >
  {
  };


  // Converts a ParameterSpec into a specialization of
  // parameter_requirements.  We need to do this in order to get the
  // key_type into the type in a way that can be conveniently matched
  // by a satisfies(...) member function in arg_list.
  template <class ParameterSpec>
  struct as_parameter_requirements
  {
      typedef parameter_requirements<
          typename key_type<ParameterSpec>::type
        , typename predicate<ParameterSpec>::type
        , typename has_default<ParameterSpec>::type
      > type;
  };

  // Labels Arg with default keyword tag from ParameterSpec 
  // if it is not already a tagged_argument
  template <class ParameterSpec, class Arg, class Unnamed>
  struct as_tagged_argument
    : mpl::eval_if<
          is_tagged_argument<Arg>
        , mpl::identity<Arg>
        , mpl::apply_wrap2<Unnamed, Arg, typename key_type<ParameterSpec>::type>
      >
  {};

#if BOOST_WORKAROUND(BOOST_MSVC, == 1200)  // ETI workaround
  template <>
  struct as_tagged_argument<int,int,int>
  {
      typedef int type;
  };
#endif

  // Returns mpl::true_ iff the given ParameterRequirements are
  // satisfied by ArgList.
  template <class ArgList, class ParameterRequirements>
  struct satisfies
  {
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
      // VC7.1 can't handle the sizeof() implementation below,
      // so we use this instead.
      typedef typename mpl::apply_wrap2<
          typename ArgList::binding
        , typename ParameterRequirements::keyword
        , void_
      >::type bound;

      typedef typename mpl::eval_if<
          is_same<bound, void_>
        , typename ParameterRequirements::has_default
        , mpl::apply1<
              typename ParameterRequirements::predicate
            , typename remove_reference<bound>::type
          >
      >::type type;
#else
      BOOST_STATIC_CONSTANT(
          bool, value = (
              sizeof(
                  aux::to_yesno(
                      ArgList::satisfies((ParameterRequirements*)0)
                  )
              ) == sizeof(yes_tag)
          )
      );

      typedef mpl::bool_<satisfies::value> type;
#endif
  };

  // Returns mpl::true_ if the requirements of the given ParameterSpec
  // are satisfied by ArgList.
  template <class ArgList, class ParameterSpec>
  struct satisfies_requirements_of
    : satisfies<
          ArgList
        , typename as_parameter_requirements<ParameterSpec>::type
      >
  {};

  // Helper for make_partial_arg_list, below.  Produce an arg_list
  // node for the given ParameterSpec and ArgumentType, whose tail is
  // determined by invoking the nullary metafunction TailFn.
  template <class ParameterSpec, class ArgumentType, class Unnamed, class TailFn>
  struct make_arg_list
  {
      typedef arg_list<
          typename as_tagged_argument<ParameterSpec,ArgumentType,Unnamed>::type
        , typename TailFn::type
      > type;
  };

  // Just like make_arg_list, except if ArgumentType is void_, the
  // result is empty_arg_list.  Used to build arg_lists whose length
  // depends on the number of non-default (void_) arguments passed to
  // a class template.
  template <
      class ParameterSpec
    , class ArgumentType
    , class Unnamed
    , class TailFn
  >
  struct make_partial_arg_list
    : mpl::eval_if<
          is_same<ArgumentType,void_>
        , mpl::identity<empty_arg_list>
        , make_arg_list<ParameterSpec, ArgumentType, Unnamed, TailFn>
      >
  {};

  // Generates:
  //
  //   make<
  //       parameter_spec#0, argument_type#0
  //     , make<
  //           parameter_spec#1, argument_type#1
  //         , ... mpl::identity<aux::empty_arg_list>
  //    ...>
  //   >
#define BOOST_PARAMETER_make_arg_list(z, n, names)      \
      BOOST_PP_SEQ_ELEM(0,names)<                       \
          BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1,names), n),  \
          BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(2,names), n),  \
          BOOST_PP_SEQ_ELEM(3,names),
  
#define BOOST_PARAMETER_right_angle(z, n, text)    >

#define BOOST_PARAMETER_build_arg_list(n, make, parameter_spec, argument_type, unnamed) \
  BOOST_PP_REPEAT(                                                                      \
      n, BOOST_PARAMETER_make_arg_list, (make)(parameter_spec)(argument_type)(unnamed)) \
  mpl::identity<aux::empty_arg_list>                                                    \
  BOOST_PP_REPEAT(n, BOOST_PARAMETER_right_angle, _)

  // Metafunctions used to determine if a ParameterSpec is
  // either unnamed<something, something> or
  // [required/optional]<unnamed<something, something> >

  template <class T>
  struct is_nested_unnamed_aux
    : is_unnamed<typename T::key_type>
  {};

  template <class T>
  struct is_nested_unnamed
    : mpl::if_<
          mpl::or_<
              is_optional<T>
            , is_required<T>
          >
        , is_nested_unnamed_aux<T>
        , mpl::false_
      >::type
  {};

  template <class T>
  struct is_unnamed_spec
    : mpl::or_<
          is_unnamed<T>
        , is_nested_unnamed<T>
      >
  {};

  // List of unnamed keywords with the associated predicate.
  template <class Keyword, class Predicate, class Tail>
  struct unnamed_list
  {
      // If the Predicate applies; tag the argument with
      // Keyword. Otherwise, try the tail.
      template <class Arg, class DefaultTag>
      struct apply
      {
          typedef typename mpl::eval_if<
              typename mpl::apply1<Predicate, Arg>::type
            , mpl::identity<tagged_argument<
                  Keyword
                , typename unwrap_cv_reference<Arg const>::type
              > >
            , mpl::apply_wrap2<Tail, Arg, DefaultTag>
          >::type type;
      };
  };

  // Terminates an unnamed_list<>.
  struct empty_unnamed_list
  {
      // Default case. No unnamed predicates matched the Arg.
      // Tag argument with the DefaultTag.
      template <class Arg, class DefaultTag>
      struct apply
      {
          typedef tagged_argument<
              DefaultTag
            , typename unwrap_cv_reference<Arg const>::type
          > type;
      };
  };

  template <class ParameterSpec, class TailFn>
  struct make_unnamed_list_aux
  {
      typedef typename mpl::if_<
          is_unnamed_spec<ParameterSpec>
        , unnamed_list<
              typename key_type<ParameterSpec>::type
            , typename predicate<ParameterSpec>::type
            , typename TailFn::type
          >
        , typename TailFn::type
      >::type type;
  };

  template <class ParameterSpec, class TailFn>
  struct make_unnamed_list
  {
      typedef typename mpl::eval_if<
          is_same<ParameterSpec, void_>
        , mpl::identity<empty_unnamed_list>
        , make_unnamed_list_aux<ParameterSpec, TailFn>
      >::type type;
  };

  // Generates:
  //
  //   make<
  //       parameter_spec#0
  //     , make<
  //           parameter_spec#1
  //         , make<
  //               parameter_spec#2
  //             , mpl::identity<mpl::vector0<> >
  //           >
  //       >
  //   >
  //
  
#define BOOST_PARAMETER_make_unnamed_list(z, n, names)  \
      BOOST_PP_SEQ_ELEM(0,names)<                       \
          BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1,names), n),

#define BOOST_PARAMETER_build_unnamed_list(n, make, parameter_spec)                 \
  BOOST_PP_REPEAT(                                                                  \
      n, BOOST_PARAMETER_make_unnamed_list, (make)(parameter_spec))                 \
  mpl::identity<aux::empty_unnamed_list>                                            \
  BOOST_PP_REPEAT(n, BOOST_PARAMETER_right_angle, _)

} // namespace aux

#define BOOST_PARAMETER_TEMPLATE_ARGS(z, n, text) class BOOST_PP_CAT(PS, n) = aux::void_

template<
     class PS0
   , BOOST_PP_ENUM_SHIFTED(BOOST_PARAMETER_MAX_ARITY, BOOST_PARAMETER_TEMPLATE_ARGS, _)
>
struct parameters
{
#undef BOOST_PARAMETER_TEMPLATE_ARGS

    typedef typename BOOST_PARAMETER_build_unnamed_list(
        BOOST_PARAMETER_MAX_ARITY
      , aux::make_unnamed_list
      , PS
    )::type unnamed_specs;

    // if the elements of NamedList match the criteria of overload
    // resolution, returns a type which can be constructed from
    // parameters.  Otherwise, this is not a valid metafunction (no nested
    // ::type).


#ifndef BOOST_NO_SFINAE
    // If NamedList satisfies the PS0, PS1, ..., this is a
    // metafunction returning parameters.  Otherwise it 
    // has no nested ::type.
    template <class NamedList>
    struct match_base
      : mpl::if_<
            // mpl::and_<
            //    aux::satisfies_requirements_of<NamedList,PS0>
            //  , mpl::and_<
            //       aux::satisfies_requirements_of<NamedList,PS1>...
            //           ..., mpl::true_
            // ...> >
            
# define BOOST_PARAMETER_satisfies(z, n, text)                                   \
            mpl::and_<                                                              \
                aux::satisfies_requirements_of<NamedList, BOOST_PP_CAT(PS, n)> ,
      
            BOOST_PP_REPEAT(BOOST_PARAMETER_MAX_ARITY, BOOST_PARAMETER_satisfies, _)
            mpl::true_
            BOOST_PP_REPEAT(BOOST_PARAMETER_MAX_ARITY, BOOST_PARAMETER_right_angle, _)

# undef BOOST_PARAMETER_satisfies

          , mpl::identity<
                parameters<BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, PS)>
            >
          , aux::void_
        >
    {};
#endif
    
    // Specializations are to be used as an optional argument to
    // eliminate overloads via SFINAE
    template<
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        // Borland simply can't handle default arguments in member
        // class templates.  People wishing to write portable code can
        // explicitly specify BOOST_PARAMETER_MAX_ARITY arguments
        BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, class A)
#else 
        BOOST_PP_ENUM_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY, class A, = aux::void_ BOOST_PP_INTERCEPT
        )
#endif            
    >
    struct match
# ifndef BOOST_NO_SFINAE
      : match_base<
            typename BOOST_PARAMETER_build_arg_list(
                BOOST_PARAMETER_MAX_ARITY, aux::make_partial_arg_list, PS, A, unnamed_specs
            )::type
        >::type
    {};
# else
    { 
        typedef parameters<
            BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, PS)
        > type; 
    };
# endif

    //
    // The function call operator is used to build an arg_list that
    // labels the positional parameters and maintains whatever other
    // tags may have been specified by the caller.
    //
    aux::empty_arg_list operator()() const
    {
       return aux::empty_arg_list();
    }

    template<class A0>
    typename
      aux::make_arg_list<PS0,A0,unnamed_specs, mpl::identity<aux::empty_arg_list> >
    ::type
    operator()( A0 const& a0) const
    {
        typedef typename
          aux::make_arg_list<PS0, A0, unnamed_specs, mpl::identity<aux::empty_arg_list> >
        ::type result_type;

        return result_type(
            a0
            // , void_(), void_(), void_() ...
            BOOST_PP_ENUM_TRAILING_PARAMS(
                BOOST_PP_SUB(BOOST_PARAMETER_MAX_ARITY, 1)
              , aux::void_() BOOST_PP_INTERCEPT)
        );
    }

    template<class A0, class A1>
    typename
      aux::make_arg_list<
          PS0,A0,unnamed_specs
        , aux::make_arg_list<
              PS1,A1,unnamed_specs
            , mpl::identity<aux::empty_arg_list>
          >
      >
    ::type
    operator()(A0 const& a0, A1 const& a1) const
    {
        typedef typename
          aux::make_arg_list<
              PS0,A0,unnamed_specs
            , aux::make_arg_list<
                  PS1,A1,unnamed_specs 
                , mpl::identity<aux::empty_arg_list>
              >
          >
        ::type result_type;


        return result_type(
            a0, a1
            // , void_(), void_() ...
            BOOST_PP_ENUM_TRAILING_PARAMS(
                BOOST_PP_SUB(BOOST_PARAMETER_MAX_ARITY, 2)
              , aux::void_() BOOST_PP_INTERCEPT)
        );
    }

    // Higher arities are handled by the preprocessor
#define BOOST_PP_ITERATION_PARAMS_1 (3,( \
        3,BOOST_PARAMETER_MAX_ARITY,<boost/parameter/aux_/overloads.hpp> \
    ))
#include BOOST_PP_ITERATE()
    
#undef BOOST_PARAMETER_build_arg_list
#undef BOOST_PARAMETER_make_arg_list
#undef BOOST_PARAMETER_right_angle

};

} // namespace parameter

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>
 
#endif // BOOST_PARAMETERS_031014_HPP

