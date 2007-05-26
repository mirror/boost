///////////////////////////////////////////////////////////////////////////////
// lambda.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <boost/version.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/next_prior.hpp>
#if BOOST_VERSION < 103500
# include <boost/spirit/fusion/sequence/at.hpp>
# include <boost/spirit/fusion/sequence/tuple.hpp>
namespace boost { namespace fusion { namespace result_of { using namespace meta; }}}
#else
# include <boost/fusion/tuple.hpp>
#endif
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/sstream.hpp>
#include <boost/typeof/std/ostream.hpp>
#include <boost/typeof/std/iostream.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

using namespace boost;

// Forward declaration of the lambda expression wrapper
template<typename T>
struct lambda;

struct lambda_domain
  : proto::domain<proto::pod_generator<lambda> >
{};

template<typename I>
struct placeholder
{
    typedef I arity;
};

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
{
    lambda_context(Tuple const &args)
      : args_(args)
    {}

    template<typename Expr, typename EnableIf = void>
    struct eval
      : proto::default_eval<Expr, lambda_context<Tuple> >
    {};

    template<typename Expr>
    struct eval<Expr, typename enable_if<proto::matches<Expr, proto::terminal<placeholder<_> > > >::type>
    {
        typedef typename proto::result_of::arg<Expr>::type::arity index;
        typedef typename fusion::result_of::at<Tuple, index>::type result_type;
        result_type operator()(Expr const &expr, lambda_context<Tuple> &ctx)
        {
#if BOOST_VERSION < 103500
            return fusion::at<index::value>(ctx.args_);
#else
            return fusion::at<index>(ctx.args_);
#endif
        }
    };

    Tuple args_;
};

// The lambda<> expression wrapper makes expressions polymorphic
// function objects
template<typename T>
struct lambda
{
    BOOST_PROTO_EXTENDS(T, lambda<T>, lambda_domain)
    BOOST_PROTO_EXTENDS_ASSIGN(T, lambda<T>, lambda_domain)
    BOOST_PROTO_EXTENDS_SUBSCRIPT(T, lambda<T>, lambda_domain)

    // Careful not to evaluate the return type of the nullary function
    // unless we have a nullary lambda!
    typedef typename mpl::eval_if<
        typename lambda_arity<T>::type
      , mpl::identity<void>
      , proto::result_of::eval<T const, lambda_context<fusion::tuple<> > >
    >::type nullary_type;

    // Define our operator() that evaluates the lambda expression.
    nullary_type operator()() const
    {
        fusion::tuple<> args;
        lambda_context<fusion::tuple<> > ctx(args);
        return proto::eval(*this, ctx);
    }

    template<typename A0>
    typename proto::result_of::eval<T const, lambda_context<fusion::tuple<A0 const &> > >::type
    operator()(A0 const &a0) const
    {
        fusion::tuple<A0 const &> args(a0);
        lambda_context<fusion::tuple<A0 const &> > ctx(args);
        return proto::eval(*this, ctx);
    }

    template<typename A0, typename A1>
    typename proto::result_of::eval<T const, lambda_context<fusion::tuple<A0 const &, A1 const &> > >::type
    operator()(A0 const &a0, A1 const &a1) const
    {
        fusion::tuple<A0 const &, A1 const &> args(a0, a1);
        lambda_context<fusion::tuple<A0 const &, A1 const &> > ctx(args);
        return proto::eval(*this, ctx);
    }
};

// Define some lambda placeholders
lambda<proto::terminal<placeholder<mpl::int_<0> > >::type> const _1 = {{}};
lambda<proto::terminal<placeholder<mpl::int_<1> > >::type> const _2 = {{}};

template<typename T>
lambda<typename proto::terminal<T>::type> const val(T const &t)
{
    lambda<typename proto::terminal<T>::type> that = {{t}};
    return that;
}

template<typename T>
lambda<typename proto::terminal<T &>::type> const var(T &t)
{
    lambda<typename proto::terminal<T &>::type> that = {{t}};
    return that;
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
