//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This example enhances the arithmetic expression evaluator
// in calc2.cpp by using a proto transform to calculate the
// number of arguments an expression requires and using a 
// compile-time assert to guarantee that the right number of
// arguments are actually specified.

#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/proto/transform/apply.hpp>
using namespace boost;

// Will be used to define the placeholders _1 and _2
template<typename I> struct arg { typedef I arity; };

// A meta-function for getting a placeholder terminal's arity.
template<typename Arg>
struct arg_arity
{
    typedef typename Arg::arity type;
};

// A custom transform that fetches the arity of a placeholder terminal
template<typename Grammar>
struct placeholder_arity
  : Grammar
{
    template<typename Expr, typename, typename>
    struct apply
      : arg_arity<typename proto::result_of::arg<Expr>::type>
    {};

    //// If this transform had a runtime counterpart, it would look like this:
    //template<typename Expr, typename State, typename Visitor>
    //static typename apply<Expr, State, Visitor>::type 
    //call(Expr const &expr, State const &state, Visitor &visitor)
    //{
    //    ... do stuff ...
    //}
};

// A custom transforms for calculating the max arity of a calculator expression
template<typename Grammar>
struct max_arity
  : Grammar
{
    template<typename Expr, typename State, typename Visitor>
    struct apply
    {
        // Calculate the arity of the current expression.
        typedef typename Grammar::template apply<Expr, State, Visitor>::type arity;
        // The old maximum is passed along in the State parameter by
        // proto::transform::fold<> (see below). The new maximum is the
        // larger of the old maximum and the arity we just calculated.
        typedef typename mpl::max<arity, State>::type type;
    };

    // As with placeholder_arity<> above, placeholder_arity<> has no need
    // for a call() member function.
};

using proto::_;

// This grammar basically says that a calculator expression is one of:
//   - A placeholder terminal
//   - Some other terminal
//   - Some non-terminal whose children are calculator expressions
// In addition, it has transforms that say how to calculate the
// expression arity for each of the three cases.
struct CalculatorGrammar
  : proto::or_<
        // placeholders have a non-zero arity ...
        placeholder_arity< proto::terminal< arg<_> > >

        //// This accomplishes the same thing without the need to
        //// define a separate placeholder_arity<> transform, but
        //// is a little more cryptic.
        //proto::transform::apply1<
        //    proto::terminal< arg<_> >
        //  , arg_arity< proto::result_of::arg<mpl::_> >
        //>

        // Any other terminals have arity 0 ...
      , proto::transform::always< proto::terminal<_>, mpl::int_<0> >
        // For any non-terminals, find the arity of the children and
        // take the maximum. This is recursive.
      , proto::transform::fold<
            // This matches any non-terminal for which the children
            // are themselves calculator expressions.
            proto::nary_expr<_, proto::vararg< max_arity< CalculatorGrammar > > >

            //// This accomplishes the same thing without the need to
            //// define a separate max_arity<> transform, but is a little
            //// more cryptic.
            //proto::nary_expr<
            //    _
            //  , proto::vararg<
            //        // Here, mpl::_1 will be replaced with the result of applying
            //        // the CalculatorGrammar transform (i.e., the arity of the
            //        // child node), and mpl::_2 will be replaced with the State of
            //        // the transformation so far (i.e., the maximum arity found so
            //        // far).
            //        proto::transform::apply2<CalculatorGrammar, mpl::max<mpl::_1, mpl::_2> >
            //    >
            //>
        >
    >
{};

// Simple wrapper for calculating a calculator expression's arity.
// It specifies mpl::int_<0> as the initial state. The visitor, which
// is not used, is mpl::void_.
template<typename Expr>
struct calculator_arity
  : CalculatorGrammar::apply<Expr, mpl::int_<0>, mpl::void_>
{};

// For expressions in the calculator domain, operator()
// will be special; it will evaluate the expression.
struct calculator_domain;

// Define a calculator context, for evaluating arithmetic expressions
// (This is as before, in calc1.cpp and calc2.cpp)
struct calculator_context
  : proto::callable_context< calculator_context const >
{
    // The values bound to the placeholders
    double d[2];

    // The result of evaluating arithmetic expressions
    typedef double result_type;

    explicit calculator_context(double d1 = 0., double d2 = 0.)
    {
        d[0] = d1;
        d[1] = d2;
    }

    // Handle the evaluation of the placeholder terminals
    template<typename I>
    double operator()(proto::tag::terminal, arg<I>) const
    {
        return d[ I() - 1 ];
    }
};

// Wrap all calculator expressions in this type, which defines
// operator() to evaluate the expression.
template<typename Expr>
struct calculator_expression
  : proto::extends<Expr, calculator_expression<Expr>, calculator_domain>
{
    typedef
        proto::extends<Expr, calculator_expression<Expr>, calculator_domain>
    base_type;
    
    explicit calculator_expression(Expr const &expr = Expr())
      : base_type(expr)
    {}

    using base_type::operator=;

    // Override operator() to evaluate the expression
    double operator()() const
    {
        // Assert that the expression has arity 0
        BOOST_MPL_ASSERT_RELATION(0, ==, calculator_arity<Expr>::type::value);
        calculator_context const ctx;
        return proto::eval(*this, ctx);
    }

    double operator()(double d1) const
    {
        // Assert that the expression has arity 1
        BOOST_MPL_ASSERT_RELATION(1, ==, calculator_arity<Expr>::type::value);
        calculator_context const ctx(d1);
        return proto::eval(*this, ctx);
    }

    double operator()(double d1, double d2) const
    {
        // Assert that the expression has arity 2
        BOOST_MPL_ASSERT_RELATION(2, ==, calculator_arity<Expr>::type::value);
        calculator_context const ctx(d1, d2);
        return proto::eval(*this, ctx);
    }
};

// Tell proto how to generate expressions in the calculator_domain
struct calculator_domain
  : proto::domain<proto::generator<calculator_expression> >
{};

// Define some placeholders (notice they're wrapped in calculator_expression<>)
calculator_expression<proto::terminal< arg< mpl::int_<1> > >::type> const _1;
calculator_expression<proto::terminal< arg< mpl::int_<2> > >::type> const _2;

// Now, our arithmetic expressions are immediately executable function objects:
int main()
{
    // Displays "5"
    std::cout << (_1 + 2.0)( 3.0 ) << std::endl;

    // Displays "6"
    std::cout << ( _1 * _2 )( 3.0, 2.0 ) << std::endl;

    // Displays "1.5"
    std::cout << ( (_1 - _2) / _2 )( 3.0, 2.0 ) << std::endl;

    // This won't compile because the arity of the
    // expression doesn't match the number of arguments
    // ( (_1 - _2) / _2 )( 3.0 );

    return 0;
}
