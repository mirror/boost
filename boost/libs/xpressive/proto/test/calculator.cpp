///////////////////////////////////////////////////////////////////////////////
// calculator.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;

struct placeholder {};
proto::terminal<placeholder>::type const _1 = {{}};

struct calculator : proto::callable_context<calculator const>
{
    typedef int result_type;

    calculator(int i)
      : i_(i)
    {}

    int operator()(proto::tag::terminal, placeholder) const
    {
        return this->i_;
    }

    int operator()(proto::tag::terminal, int j) const
    {
        return j;
    }

    template<typename Left, typename Right>
    int operator()(proto::tag::add, Left const &left, Right const &right) const
    {
        return proto::eval(left, *this) + proto::eval(right, *this);
    }

    template<typename Left, typename Right>
    int operator()(proto::tag::subtract, Left const &left, Right const &right) const
    {
        return proto::eval(left, *this) - proto::eval(right, *this);
    }

    template<typename Left, typename Right>
    int operator()(proto::tag::multiply, Left const &left, Right const &right) const
    {
        return proto::eval(left, *this) * proto::eval(right, *this);
    }

    template<typename Left, typename Right>
    int operator()(proto::tag::divide, Left const &left, Right const &right) const
    {
        return proto::eval(left, *this) / proto::eval(right, *this);
    }

private:
    int i_;
};

template<typename Fun, typename Expr>
struct functor
{
    typedef typename proto::result_of::eval<Expr, Fun>::type result_type;

    functor(Expr const &expr)
      : expr_(expr)
    {}
    
    template<typename T>
    result_type operator()(T const &t) const
    {
        Fun fun(t);
        return proto::eval(this->expr_, fun);
    }

private:
    Expr const &expr_;
};

template<typename Fun, typename Expr>
functor<Fun, Expr> as(Expr const &expr)
{
    return functor<Fun, Expr>(expr);
}

void test_calculator()
{
    BOOST_CHECK_EQUAL(10, proto::eval(((_1 + 42)-3)/4, calculator(1)));
    BOOST_CHECK_EQUAL(11, proto::eval(((_1 + 42)-3)/4, calculator(5)));

    BOOST_CHECK_EQUAL(10, as<calculator>(((_1 + 42)-3)/4)(1));
    BOOST_CHECK_EQUAL(11, as<calculator>(((_1 + 42)-3)/4)(5));
}

using namespace unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test immediate evaluation of proto parse trees");

    test->add(BOOST_TEST_CASE(&test_calculator));

    return test;
}
