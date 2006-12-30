///////////////////////////////////////////////////////////////////////////////
// lambda.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/tuple.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

using namespace boost;

struct lambda_domain {};
template<int I> struct placeholder {};

template<typename Tuple>
struct lambda_context;

template<typename Tuple>
struct lambda_context_result
{
    typedef lambda_context<Tuple> ctx_type;

    template<typename Sig>
    struct result;

    template<typename This, typename Arg>
    struct result<This(proto::tag::terminal, Arg)>
    {
        typedef Arg type;
    };

    template<typename This, int I>
    struct result<This(proto::tag::terminal, placeholder<I>)>
    {
        typedef typename fusion::result_of::value_at_c<Tuple, I>::type type;
    };

#define BIN_OP_RESULT(Left, Op, Right)\
    typedef typename proto::meta::eval<Left, ctx_type>::type left_type;\
    typedef typename proto::meta::eval<Right, ctx_type>::type right_type;\
    typedef BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (*(left_type*)0) Op (*(right_type*)0))\
    typedef typename nested::type type\
    /**/

    template<typename This, typename Left, typename Right>
    struct result<This(proto::tag::add, Left, Right)>
    {
        BIN_OP_RESULT(Left, +, Right);
    };

    template<typename This, typename Left, typename Right>
    struct result<This(proto::tag::subtract, Left, Right)>
    {
        BIN_OP_RESULT(Left, -, Right);
    };

    template<typename This, typename Left, typename Right>
    struct result<This(proto::tag::multiply, Left, Right)>
    {
        BIN_OP_RESULT(Left, *, Right);
    };

    template<typename This, typename Left, typename Right>
    struct result<This(proto::tag::divide, Left, Right)>
    {
        BIN_OP_RESULT(Left, /, Right);
    };
};

template<typename Tuple>
struct lambda_context
  : lambda_context_result<Tuple>
{
    typedef lambda_context<Tuple> this_type;

    lambda_context(Tuple const &args)
      : args_(args)
    {}

    template<typename Arg>
    Arg const &
    operator()(proto::tag::terminal, Arg const &arg)
    {
        return arg;
    }

    template<int I>
    typename fusion::result_of::at_c<Tuple, I>::type
    operator()(proto::tag::terminal, placeholder<I>)
    {
        return fusion::get<I>(this->args_);
    }

    template<typename Left, typename Right>
    typename result_of<this_type(proto::tag::add, Left, Right)>::type
    operator()(proto::tag::add, Left const &left, Right const &right)
    {
        return left.eval(*this) + right.eval(*this);
    }

    template<typename Left, typename Right>
    typename result_of<this_type(proto::tag::subtract, Left, Right)>::type
    operator()(proto::tag::subtract, Left const &left, Right const &right)
    {
        return left.eval(*this) - right.eval(*this);
    }

    template<typename Left, typename Right>
    typename result_of<this_type(proto::tag::multiply, Left, Right)>::type
    operator()(proto::tag::multiply, Left const &left, Right const &right)
    {
        return left.eval(*this) * right.eval(*this);
    }

    template<typename Left, typename Right>
    typename result_of<this_type(proto::tag::divide, Left, Right)>::type
    operator()(proto::tag::divide, Left const &left, Right const &right)
    {
        return left.eval(*this) / right.eval(*this);
    }

private:
    Tuple args_;
};

template<typename T>
struct lambda
  : proto::extends<T, lambda<T>, lambda_domain>
{
    typedef proto::extends<T, lambda<T>, lambda_domain> base_type;
    
    lambda()
      : base_type()
    {}

    lambda(T const &t)
      : base_type(t)
    {}

    using base_type::operator =;

    // hide base_type::operator() by defining our own which
    // evaluates the lambda expression.
    template<typename A0>
    typename proto::meta::eval<T, lambda_context<fusion::tuple<A0> > >::type
    operator()(A0 const &a0) const
    {
        lambda_context<fusion::tuple<A0> > ctx(fusion::make_tuple(a0));
        return this->eval(ctx);
    }

    template<typename A0, typename A1>
    typename proto::meta::eval<T, lambda_context<fusion::tuple<A0, A1> > >::type
    operator()(A0 const &a0, A1 const &a1) const
    {
        lambda_context<fusion::tuple<A0, A1> > ctx(fusion::make_tuple(a0, a1));
        return this->eval(ctx);
    }
};

namespace boost { namespace proto { namespace meta
{
    template<typename Expr, typename Tag>
    struct generate<lambda_domain, Expr, Tag>
    {
        typedef lambda<Expr> type;
        static type make(Expr const &expr)
        {
            return lambda<Expr>(expr);
        }
    };
}}}

lambda<proto::meta::terminal<placeholder<0> >::type> const _1;
lambda<proto::meta::terminal<placeholder<1> >::type> const _2;

void test_lambda()
{
    BOOST_CHECK_EQUAL(11, ( (_1 + 2) / 4 )(42));
    BOOST_CHECK_CLOSE(2.58, ( (4 - _2) * 3 )(42, 3.14), 0.1);
}

using namespace unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test expression template domains");

    test->add(BOOST_TEST_CASE(&test_lambda));

    return test;
}
