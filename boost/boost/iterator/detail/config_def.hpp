// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// no include guard multiple inclusion intended

//
// This is a temporary workaround until the bulk of this is
// available in boost config.
// 23/02/03 thw
//

#include <boost/config.hpp> // for prior
#include <boost/detail/workaround.hpp>

#define BOOST_ITERATOR_CONFIG_DEF // if you get an error here, you have nested config_def #inclusion.

#if BOOST_WORKAROUND(BOOST_MSVC,  <= 1300)                      \
 || BOOST_WORKAROUND(__GNUC__, <= 2 && __GNUC_MINOR__ <= 95)    \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3000)                     \
 || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
#  define BOOST_NO_SFINAE // "Substitution Failure Is Not An Error not implemented"

#  if 0  // test code
    template <bool x>
    struct bar
    {
        typedef int type;
    };

    template <>
    struct bar<false>
    {
    };


    template <class T>
    struct foo : bar<(sizeof(T) == 1)>
    {
    };

    template <class T>
    char* f(int, typename foo<T>::type = 0) { return 0; }

    template <class T>
    int f(...) { return 0; }

    char* x = f<char>(0);
    int y = f<char[2]>(0);

    int main()
    {
        return 0;
    }
#  endif

#endif

#if BOOST_WORKAROUND(__MWERKS__, <=0x2407)
#  define BOOST_NO_IS_CONVERTIBLE // "is_convertible doesn't work for simple types"
#endif

#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(3)) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
#  define BOOST_NO_IS_CONVERTIBLE_TEMPLATE // The following program fails to compile:

#  if 0 // test code
    template <class T>
    struct foo
    {
        foo(T);

        template <class U>
        foo(foo<U> const& other) : p(other.p) { }

        T p;
    };

    bool x = boost::is_convertible<foo<int const*>, foo<int*> >::value;
#  endif

#endif

#if BOOST_WORKAROUND(__GNUC__, == 2 && __GNUC_MINOR__ == 95)    \
  || BOOST_WORKAROUND(__MWERKS__, <= 0x2407)                    \
  || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
# define BOOST_ITERATOR_NO_MPL_AUX_HAS_XXX  // "MPL's has_xxx facility doesn't work"
#endif 

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_IS_CONVERTIBLE) || defined(BOOST_NO_IS_CONVERTIBLE_TEMPLATE)
# define BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
#endif 

# if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#  define BOOST_ARG_DEPENDENT_TYPENAME typename
# else
#  define BOOST_ARG_DEPENDENT_TYPENAME
# endif

// no include guard multiple inclusion intended
