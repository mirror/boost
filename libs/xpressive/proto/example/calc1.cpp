//[ Calc1
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This is a simple example of how to build an arithmetic expression
// evaluator with placeholders.

#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
using namespace boost;

template<typename I> struct arg {};

// Define some placeholders
proto::terminal< arg< mpl::int_<1> > >::type const _1 = {{}};
proto::terminal< arg< mpl::int_<2> > >::type const _2 = {{}};

// Define a calculator context, for evaluating arithmetic expressions
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

template<typename Expr>
double evaluate( Expr const &expr, double d1 = 0., double d2 = 0. )
{
    // Create a calculator context with d1 and d2 substituted for _1 and _2
    calculator_context const ctx(d1, d2);

    // Evaluate the calculator expression with the calculator_context
    return proto::eval(expr, ctx);
}

int main()
{
    // Displays "5"
    std::cout << evaluate( _1 + 2.0, 3.0 ) << std::endl;

    // Displays "6"
    std::cout << evaluate( _1 * _2, 3.0, 2.0 ) << std::endl;

    // Displays "1.5"
    std::cout << evaluate( (_1 - _2) / _2, 3.0, 2.0 ) << std::endl;

    return 0;
}
//]
