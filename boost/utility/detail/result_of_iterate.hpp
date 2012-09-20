// Boost result_of library

//  Copyright Douglas Gregor 2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  Copyright Daniel Walker, Eric Niebler, Michel Morin 2008-2012.
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or
//  copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/utility
#if !defined(BOOST_PP_IS_ITERATING)
# error Boost result_of - do not include this file!
#endif

// CWPro8 requires an argument in a function type specialization
#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3002)) && BOOST_PP_ITERATION() == 0
# define BOOST_RESULT_OF_ARGS void
#else
# define BOOST_RESULT_OF_ARGS BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)
#endif

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of<F(BOOST_RESULT_OF_ARGS)>
    : mpl::if_<
          mpl::or_< is_pointer<F>, is_member_function_pointer<F> >
        , boost::detail::tr1_result_of_impl<
            typename remove_cv<F>::type, 
            typename remove_cv<F>::type(BOOST_RESULT_OF_ARGS), 
            (boost::detail::has_result_type<F>::value)>
        , boost::detail::tr1_result_of_impl<
            F,
            F(BOOST_RESULT_OF_ARGS), 
            (boost::detail::has_result_type<F>::value)> >::type { };
#endif

#ifdef BOOST_RESULT_OF_USE_DECLTYPE

// Uses declval following N3225 20.7.7.6 when F is not a pointer.
template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct result_of<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T))>
    : mpl::if_<
          is_member_function_pointer<F>
        , detail::tr1_result_of_impl<
            typename remove_cv<F>::type, 
            typename remove_cv<F>::type(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), false
          >
        , detail::cpp0x_result_of_impl<
              F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T))
          >
      >::type
{};

namespace detail {

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1700))

template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
class is_callable<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T))> {
    typedef char (&pass)[1];
    typedef char (&fail)[2];

    template<typename G BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
             BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename S)>
    struct sub {};
    template<typename S>
    struct stub {};

    template<typename G BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
             BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename S)>
    static pass test(sub<G BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
                         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),S)>
                   , stub<
                          decltype(
                              boost::declval<G>()(
                                  BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), boost::declval<S, >() BOOST_PP_INTERCEPT)
                              )
                          )
                      >* x = 0);
    static fail test(...);

public:
    const static bool value = sizeof(pass) == sizeof(test(sub<F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
                                                              BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)
                                                          >()));
    typedef typename boost::mpl::bool_<value>::type type;
};

template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct cpp0x_result_of_impl<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), true>
    : lazy_enable_if<
          is_callable<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T))>
        , cpp0x_result_of_impl<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), false>
      >
{};

template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct cpp0x_result_of_impl<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), false>
{
  typedef decltype(
    boost::declval<F>()(
      BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), boost::declval<T, >() BOOST_PP_INTERCEPT)
    )
  ) type;
};

#else // BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1700))

template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct cpp0x_result_of_impl<F(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), 
                            typename result_of_always_void<decltype(
                                boost::declval<F>()(
                                    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), boost::declval<T, >() BOOST_PP_INTERCEPT)
                                )
                            )>::type> {
  typedef decltype(
    boost::declval<F>()(
      BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), boost::declval<T, >() BOOST_PP_INTERCEPT)
    )
  ) type;
};

#endif // BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1700))

} // namespace detail 

#else // defined(BOOST_RESULT_OF_USE_DECLTYPE)

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
template<typename F BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct result_of<F(BOOST_RESULT_OF_ARGS)>
    : tr1_result_of<F(BOOST_RESULT_OF_ARGS)> { };
#endif

#endif // defined(BOOST_RESULT_OF_USE_DECLTYPE)

#undef BOOST_RESULT_OF_ARGS

#if BOOST_PP_ITERATION() >= 1 

namespace detail {

template<typename R,  typename FArgs BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of_impl<R (*)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), FArgs, false>
{
  typedef R type;
};

template<typename R,  typename FArgs BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of_impl<R (&)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),T)), FArgs, false>
{
  typedef R type;
};

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
template<typename R, typename FArgs BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of_impl<R (T0::*)
                     (BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_ITERATION(),T)),
                 FArgs, false>
{
  typedef R type;
};

template<typename R, typename FArgs BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of_impl<R (T0::*)
                     (BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_ITERATION(),T))
                     const,
                 FArgs, false>
{
  typedef R type;
};

template<typename R, typename FArgs BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of_impl<R (T0::*)
                     (BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_ITERATION(),T))
                     volatile,
                 FArgs, false>
{
  typedef R type;
};

template<typename R, typename FArgs BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
         BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(),typename T)>
struct tr1_result_of_impl<R (T0::*)
                     (BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_ITERATION(),T))
                     const volatile,
                 FArgs, false>
{
  typedef R type;
};
#endif

}
#endif
