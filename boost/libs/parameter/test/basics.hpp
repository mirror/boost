// Copyright David Abrahams, Daniel Wallin 2005. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BASICS_050424_HPP
#define BASICS_050424_HPP

#include <boost/static_assert.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/instance.hpp>

namespace test {

using namespace boost::parameter;

struct name_;
struct value_;
struct index_;
struct tester_;

namespace
{
#if !(BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
      || BOOST_WORKAROUND(__GNUC__, == 2)   \
      || defined(__APPLE_CC__) && BOOST_WORKAROUND (__GNUC__, <= 4))
  keyword<name_>& name = instance();
  keyword<value_>& value = instance();
  keyword<index_>& index = instance();
  keyword<tester_>& tester = instance();
#else
  keyword<name_>& name = keyword<name_>::get();
  keyword<value_>& value = keyword<value_>::get();
  keyword<index_>& index = keyword<index_>::get();
  keyword<tester_>& tester = keyword<tester_>::get();
#endif 

} // namespace unnamed

struct f_parameters // vc6 is happier with inheritance than with a typedef
  : parameters<
      tester_
    , name_
    , value_
    , index_
  >
{};

inline double value_default()
{
    return 666.222;
}

template <class T>
inline bool equal(T const& x, T const& y)
{
    return x == y;
}

inline bool equal(char const* s1, char const* s2)
{
    return !strcmp(s1,s2);
}

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
inline bool equal(char* s1, char* s2)
{
    return !strcmp(s1,s2);
}
#endif 

template <class Name, class Value, class Index>
struct values_t
{
    values_t(Name const& n, Value const& v, Index const& i)
      : n(n), v(v), i(i)
    {}

    template <class Name_, class Value_, class Index_>
    void operator()(Name_ const& n_, Value_ const& v_, Index_ const& i_) const
    {

        // Only VC and its emulators fail this; they seem to have
        // problems with deducing the constness of string literal
        // arrays.
#if defined(_MSC_VER)                                                   \
        && (BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 700)           \
            || BOOST_WORKAROUND(BOOST_MSVC, < 1310))                    \
            || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
# else 
        BOOST_STATIC_ASSERT((boost::is_same<Index,Index_>::value));
        BOOST_STATIC_ASSERT((boost::is_same<Value,Value_>::value));
        BOOST_STATIC_ASSERT((boost::is_same<Name,Name_>::value));
#endif
        assert(equal(n, n_));
        assert(equal(v, v_));
        assert(equal(i, i_));
    }

    Name const& n;
    Value const& v;
    Index const& i;
};

template <class Name, class Value, class Index>
inline values_t<Name,Value,Index>
values(Name const& n, Value const& v, Index const& i)
{
    return values_t<Name,Value,Index>(n,v,i);
}

} // namespace test

// GCC2 has a problem with char (&)[] deduction, so we'll cast string
// literals there.
#undef S
#if BOOST_WORKAROUND(__GNUC__, == 2) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
# define S(s) (char const*)s
#else
# define S(s) s
#endif

#endif // BASICS_050424_HPP

