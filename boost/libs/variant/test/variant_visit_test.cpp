//-----------------------------------------------------------------------------
// boost-libs variant/test/variant_visit_test.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/variant/variant.hpp"
#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"
#include "boost/test/minimal.hpp"

#include "boost/mpl/bool.hpp"
#include "boost/mpl/and.hpp"
#include "boost/type_traits/is_same.hpp"

struct udt1
{
};

struct udt2
{
};

template <typename T>
class unary_check_content_type
    : public boost::static_visitor<bool>
{
public:

    // not recommended design, but simplifies workarounds:

    template <typename U>
    bool operator()(const U&) const
    {
        return ::boost::is_same<T,U>::value;
    }

};

template <typename T1, typename T2>
class binary_check_content_type
    : public boost::static_visitor<bool>
{
public:

    // not recommended design, but simplifies workarounds:

    template <typename U1, typename U2>
    bool operator()(const U1&, const U2&) const
    {
        return ::boost::mpl::and_<
              boost::is_same<T1,U1>
            , boost::is_same<T2,U2>
            >::value;
    }

};

int test_main(int , char* [])
{
    typedef boost::variant<udt1,udt2> var_t;
    udt1 u1;
    var_t var1(u1);
    udt2 u2;
    var_t var2(u2);

    //
    // unary tests
    //

    typedef unary_check_content_type<udt1> check1_t;
    typedef unary_check_content_type<udt2> check2_t;

    check1_t check1;
    const check1_t& check1_const = check1;
    BOOST_CHECK( boost::apply_visitor(check1, var1) );
    BOOST_CHECK( boost::apply_visitor(check1_const, var1) );
    BOOST_CHECK( boost::apply_visitor(check1_t(), var1) );

    check2_t check2;
    const check2_t& check2_const = check2;
    BOOST_CHECK( boost::apply_visitor(check2, var2) );
    BOOST_CHECK( boost::apply_visitor(check2_const, var2) );
    BOOST_CHECK( boost::apply_visitor(check2_t(), var2) );

    //
    // binary tests
    //

    typedef binary_check_content_type<udt1,udt2> check12_t;
    typedef binary_check_content_type<udt2,udt1> check21_t;

    check12_t check12;
    const check12_t& check12_const = check12;
    BOOST_CHECK( boost::apply_visitor(check12, var1, var2) );
    BOOST_CHECK( boost::apply_visitor(check12_const, var1, var2) );
    BOOST_CHECK( boost::apply_visitor(check12_t(), var1, var2) );

    check21_t check21;
    const check21_t& check21_const = check21;
    BOOST_CHECK( boost::apply_visitor(check21, var2, var1) );
    BOOST_CHECK( boost::apply_visitor(check21_const, var2, var1) );
    BOOST_CHECK( boost::apply_visitor(check21_t(), var2, var1) );

    //
    // delayed tests
    //

    BOOST_CHECK( boost::apply_visitor(check1)(var1) );
    BOOST_CHECK( boost::apply_visitor(check1_const)(var1) );

    BOOST_CHECK( boost::apply_visitor(check2)(var2) );
    BOOST_CHECK( boost::apply_visitor(check2_const)(var2) );

    BOOST_CHECK( boost::apply_visitor(check12)(var1, var2) );
    BOOST_CHECK( boost::apply_visitor(check12_const)(var1, var2) );

    BOOST_CHECK( boost::apply_visitor(check21)(var2, var1) );
    BOOST_CHECK( boost::apply_visitor(check21_const)(var2, var1) );

    return boost::exit_success;
}
