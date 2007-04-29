///////////////////////////////////////////////////////////////////////////////
// matches.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace proto;

template<typename Grammar, typename Expr>
void assert_matches(Expr const &expr)
{
    BOOST_MPL_ASSERT((matches<Expr, Grammar>));
}

template<typename Grammar, typename Expr>
void assert_not_matches(Expr const &expr)
{
    BOOST_MPL_ASSERT_NOT((matches<Expr, Grammar>));
}

struct int_convertible
{
    int_convertible() {}
    operator int() const { return 0; }
};

struct Input
  : or_<
        right_shift< terminal< std::istream & >, _ >
      , right_shift< Input, _ >
    >
{};

struct Output
  : or_<
        left_shift< terminal< std::ostream & >, _ >
      , left_shift< Output, _ >
    >
{};

terminal< std::istream & >::type const cin_ = { std::cin };
terminal< std::ostream & >::type const cout_ = { std::cout };

struct Anything
  : or_<
        terminal<_>
      , nary_expr<_, vararg<Anything> >
    >
{};

void a_function() {}

struct MyCases
{
    template<typename Tag>
    struct case_
      : proto::not_<proto::_>
    {};
};

template<>
struct MyCases::case_<proto::tag::right_shift>
  : proto::_
{};

template<>
struct MyCases::case_<proto::tag::plus>
  : proto::_
{};

enum binary_representation_enum
{
    magnitude
  , two_complement
};

typedef
    mpl::integral_c<binary_representation_enum, magnitude>
magnitude_c;

typedef
    mpl::integral_c<binary_representation_enum, two_complement>
two_complement_c;

template<typename Type, typename Representation>
struct number
{};

struct NumberGrammar
  : proto::or_ <
        proto::terminal<number<proto::_, two_complement_c> >
      , proto::terminal<number<proto::_, magnitude_c> >
    >
{};


void test_matches()
{
    assert_matches< _ >( lit(1) );
    assert_matches< _ >( as_arg(1) );
    assert_matches< _ >( as_expr(1) );

    assert_matches< terminal<int> >( lit(1) );
    assert_matches< terminal<int> >( as_arg(1) );
    assert_matches< terminal<int> >( as_expr(1) );

    assert_not_matches< terminal<int> >( lit('a') );
    assert_not_matches< terminal<int> >( as_arg('a') );
    assert_not_matches< terminal<int> >( as_expr('a') );

    assert_matches< terminal<convertible_to<int> > >( lit('a') );
    assert_matches< terminal<convertible_to<int> > >( as_arg('a') );
    assert_matches< terminal<convertible_to<int> > >( as_expr('a') );

    assert_not_matches< terminal<int> >( lit((int_convertible())) );
    assert_not_matches< terminal<int> >( as_arg((int_convertible())) );
    assert_not_matches< terminal<int> >( as_expr((int_convertible())) );

    assert_matches< terminal<convertible_to<int> > >( lit((int_convertible())) );
    assert_matches< terminal<convertible_to<int> > >( as_arg((int_convertible())) );
    assert_matches< terminal<convertible_to<int> > >( as_expr((int_convertible())) );

    assert_matches< if_<is_same<proto::result_of::arg<mpl::_>, int> > >( lit(1) );
    assert_not_matches< if_<is_same<proto::result_of::arg<mpl::_>, int> > >( lit('a') );

    assert_matches<
        and_<
            terminal<_>
          , if_<is_same<proto::result_of::arg<mpl::_>, int> >
        >
    >( lit(1) );

    assert_not_matches<
        and_<
            terminal<_>
          , if_<is_same<proto::result_of::arg<mpl::_>, int> >
        >
    >( lit('a') );

    assert_matches< terminal<char const *> >( lit("hello") );
    assert_matches< terminal<char const *> >( as_arg("hello") );
    assert_matches< terminal<char const *> >( as_expr("hello") );

    assert_matches< terminal<char const (&)[6]> >( lit("hello") );
    assert_matches< terminal<char const (&)[6]> >( as_arg("hello") );
    assert_matches< terminal<char const (&)[6]> >( as_expr("hello") );

    assert_matches< terminal<char const (&)[N]> >( lit("hello") );
    assert_matches< terminal<char const (&)[N]> >( as_arg("hello") );
    assert_matches< terminal<char const (&)[N]> >( as_expr("hello") );

    assert_matches< terminal<std::string> >( lit(std::string("hello")) );
    assert_matches< terminal<std::string> >( as_arg(std::string("hello")) );
    assert_matches< terminal<std::string> >( as_expr(std::string("hello")) );

    assert_matches< terminal<std::basic_string<_> > >( lit(std::string("hello")) );
    assert_matches< terminal<std::basic_string<_> > >( as_arg(std::string("hello")) );
    assert_matches< terminal<std::basic_string<_> > >( as_expr(std::string("hello")) );

    assert_not_matches< terminal<std::basic_string<_> > >( lit(1) );
    assert_not_matches< terminal<std::basic_string<_> > >( as_arg(1) );
    assert_not_matches< terminal<std::basic_string<_> > >( as_expr(1) );

    assert_not_matches< terminal<std::basic_string<_,_,_> > >( lit(1) );
    assert_not_matches< terminal<std::basic_string<_,_,_> > >( as_arg(1) );
    assert_not_matches< terminal<std::basic_string<_,_,_> > >( as_expr(1) );

    assert_matches< terminal<std::basic_string<_> const & > >( lit(std::string("hello")) );
    assert_matches< terminal<std::basic_string<_> const & > >( as_arg(std::string("hello")) );
    assert_not_matches< terminal<std::basic_string<_> const & > >( as_expr(std::string("hello")) );

    assert_matches< terminal< void(&)() > >( lit(a_function) );
    assert_matches< terminal< void(&)() > >( as_arg(a_function) );
    assert_matches< terminal< void(&)() > >( as_expr(a_function) );

    assert_not_matches< terminal< void(*)() > >( lit(a_function) );
    assert_not_matches< terminal< void(*)() > >( as_arg(a_function) );
    assert_not_matches< terminal< void(*)() > >( as_expr(a_function) );

    assert_matches< terminal< convertible_to<void(*)()> > >( lit(a_function) );
    assert_matches< terminal< convertible_to<void(*)()> > >( as_arg(a_function) );
    assert_matches< terminal< convertible_to<void(*)()> > >( as_expr(a_function) );

    assert_matches< terminal< void(*)() > >( lit(&a_function) );
    assert_matches< terminal< void(*)() > >( as_arg(&a_function) );
    assert_matches< terminal< void(*)() > >( as_expr(&a_function) );

    assert_matches< terminal< void(* const &)() > >( lit(&a_function) );
    assert_matches< terminal< void(* const &)() > >( as_arg(&a_function) );
    assert_not_matches< terminal< void(* const &)() > >( as_expr(&a_function) );

    assert_matches<
        or_<
            if_<is_same<proto::result_of::arg<mpl::_>, char> >
          , if_<is_same<proto::result_of::arg<mpl::_>, int> >
        >
    >( lit(1) );

    assert_not_matches<
        or_<
            if_<is_same<proto::result_of::arg<mpl::_>, char> >
          , if_<is_same<proto::result_of::arg<mpl::_>, int> >
        >
    >( lit(1u) );

    assert_matches< Input >( cin_ >> 1 >> 2 >> 3 );
    assert_not_matches< Output >( cin_ >> 1 >> 2 >> 3 );

    assert_matches< Output >( cout_ << 1 << 2 << 3 );
    assert_not_matches< Input >( cout_ << 1 << 2 << 3 );

    assert_matches< function< terminal<int>, vararg< terminal<char> > > >( lit(1)('a','b','c','d') );
    assert_not_matches< function< terminal<int>, vararg< terminal<char> > > >( lit(1)('a','b','c',"d") );

    assert_matches< Anything >( cout_ << 1 << +lit('a') << lit(1)('a','b','c',"d") );

    assert_matches< proto::switch_<MyCases> >( lit(1) >> 'a' );
    assert_matches< proto::switch_<MyCases> >( lit(1) + 'a' );
    assert_not_matches< proto::switch_<MyCases> >( lit(1) << 'a' );

    number<int, two_complement_c> num;
    assert_matches<NumberGrammar>(proto::as_expr(num));
}

using namespace unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test proto::matches<>");

    test->add(BOOST_TEST_CASE(&test_matches));

    return test;
}
