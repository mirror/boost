///////////////////////////////////////////////////////////////////////////////
// lambda.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

using namespace boost;

struct lambda_domain {};
template<typename I> struct placeholder { typedef I arity; };

// Some custom transforms for calculating the max arity of a lambda expression
template<typename Grammar>
struct max_arity
  : Grammar
{
    template<typename Expr, typename State, typename Visitor>
    struct apply
    {
        typedef typename Grammar::template apply<Expr, State, Visitor>::type arity;
        typedef typename mpl::max<arity, State>::type type;
    };
};

template<typename Grammar>
struct placeholder_arity
  : Grammar
{
    template<typename Expr, typename, typename>
    struct apply
      : mpl::next<typename proto::result_of::arg<Expr>::type::arity>
    {};
};

using proto::_;

// The lambda grammar, with the transforms for calculating the max arity
struct LambdaGrammar
  : proto::or_<
        placeholder_arity< proto::terminal< placeholder<_> > >
      , proto::trans::always< proto::terminal<_>, mpl::int_<0> >
      , proto::trans::fold<
            proto::nary_expr<_, proto::vararg< max_arity< LambdaGrammar > > >
        >
    >
{};

// simple wrapper for calculating a lambda expression's arity.
template<typename Expr>
struct lambda_arity
  : LambdaGrammar::apply<Expr, mpl::int_<0>, mpl::void_>
{};

// The lambda context is the same as the default context 
// with the addition of special handling for lambda placeholders
template<typename Tuple>
struct lambda_context
  : proto::context<lambda_context<Tuple> >
{
    typedef lambda_context<Tuple> this_type;

    template<typename Sig>
    struct result
      : proto::context<lambda_context<Tuple> >::template result<Sig>
    {};

    template<typename This, typename I>
    struct result<This(proto::tag::terminal, placeholder<I> const &)>
    {
        typedef typename fusion::result_of::at<Tuple, I>::type type;
    };

    lambda_context(Tuple const &args)
      : args_(args)
    {}

    using proto::context<lambda_context<Tuple> >::operator();

    template<typename I>
    typename fusion::result_of::at<Tuple, I>::type
    operator()(proto::tag::terminal, placeholder<I> const &)
    {
        return fusion::at<I>(this->args_);
    }

private:
    Tuple args_;
};

// The lambda<> expression wrapper makes expressions polymorphic
// function objects
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

    // This is needed because by default, the compiler-generated
    // assignment operator hides the operator= defined in our base class.
    using base_type::operator =;

    // Careful not to evaluate the return type of the nullary function
    // unless we have a nullary lambda!
    typedef typename mpl::eval_if<
        typename lambda_arity<T>::type
      , mpl::identity<void>
      , proto::result_of::eval<T, lambda_context<fusion::tuple<> > >
    >::type nullary_type;

    nullary_type operator()() const
    {
        fusion::tuple<> args;
        lambda_context<fusion::tuple<> > ctx(args);
        return this->eval(ctx);
    }

    // hide base_type::operator() by defining our own which
    // evaluates the lambda expression.
    template<typename A0>
    typename proto::result_of::eval<T, lambda_context<fusion::tuple<A0 const &> > >::type
    operator()(A0 const &a0) const
    {
        fusion::tuple<A0 const &> args(a0);
        lambda_context<fusion::tuple<A0 const &> > ctx(args);
        return this->eval(ctx);
    }

    template<typename A0, typename A1>
    typename proto::result_of::eval<T, lambda_context<fusion::tuple<A0 const &, A1 const &> > >::type
    operator()(A0 const &a0, A1 const &a1) const
    {
        fusion::tuple<A0 const &, A1 const &> args(a0, a1);
        lambda_context<fusion::tuple<A0 const &, A1 const &> > ctx(args);
        return this->eval(ctx);
    }
};

namespace boost { namespace proto
{
    // This causes expressions in the lambda domain to
    // be wrapped in a lambda<> expression wrapper.
    template<typename Expr, typename Tag>
    struct generate<lambda_domain, Expr, Tag>
    {
        typedef lambda<Expr> type;

        static type make(Expr const &expr)
        {
            return lambda<Expr>(expr);
        }
    };
}}

// Define some lambda placeholders
lambda<proto::terminal<placeholder<mpl::int_<0> > >::type> const _1;
lambda<proto::terminal<placeholder<mpl::int_<1> > >::type> const _2;

template<typename T>
lambda<typename proto::terminal<T>::type> const val(T const &t)
{
    return proto::terminal<T>::type::make(t);
}

template<typename T>
lambda<typename proto::terminal<T &>::type> const var(T &t)
{
    return proto::terminal<T &>::type::make(t);
}

void test_lambda()
{
    BOOST_CHECK_EQUAL(11, ( (_1 + 2) / 4 )(42));
    BOOST_CHECK_EQUAL(-11, ( (-(_1 + 2)) / 4 )(42));
    BOOST_CHECK_CLOSE(2.58, ( (4 - _2) * 3 )(42, 3.14), 0.1);

    // check non-const ref terminals
    std::stringstream sout;
    (sout << _1 << " -- " << _2)(42, "Life, the Universe and Everything!");
    BOOST_CHECK_EQUAL("42 -- Life, the Universe and Everything!", sout.str());

    // check nullary lambdas
    BOOST_CHECK_EQUAL(3, (val(1) + val(2))());

    // check array indexing for kicks
    int integers[5] = {0};
    (var(integers)[2] = 2)();
    (var(integers)[_1] = _1)(3);
    BOOST_CHECK_EQUAL(2, integers[2]);
    BOOST_CHECK_EQUAL(3, integers[3]);
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
