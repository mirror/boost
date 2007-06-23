///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This is a simple example using proto::extends to extend a terminal type with
// additional behaviors, and using custom contexts and proto::eval for
// evaluating expressions. It is a port of the Vec3 example
// from PETE (http://www.codesourcery.com/pooma/download.html).

#include <iostream>
#include <functional>
#include <boost/mpl/int.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/proto_typeof.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/proto/transform/function.hpp>
using namespace boost::proto;
namespace mpl = boost::mpl;

// Here is an evaluation context that indexes into a Vec3
// expression, and combines the result.
struct Vec3SubscriptCtx
  : callable_context< Vec3SubscriptCtx const >
{
    typedef int result_type;

    Vec3SubscriptCtx(int i)
      : i_(i)
    {}

    // Index array terminals with our subscript. Everything
    // else will be handled by the default evaluation context.
    int operator()(tag::terminal, int const (&arr)[3]) const
    {
        return arr[this->i_];
    }

    int i_;
};

// This transform counts the number of int[3] terminals in an expression.
// It accumulates a runtime value, rather than computing a compile-time
// value, just to demonstrate the use of the std::plus<> function object
// as a transform.
struct CountLeaves
  : or_<
        // match a Vec3 terminal, return 1
        transform::always<terminal<int[3]>, mpl::int_<1> >
        // match a terminal, return int() (which is 0)
      , transform::always<terminal<_>, int>
        // fold everything else, using std::plus<> to add
        // the leaf count of each child to the accumulated state.
      , transform::fold<
            nary_expr<_, vararg<transform::function2<CountLeaves, std::plus<int> > > >
          , int // initial state of the fold is int() (which is 0)
        >
    >
{};

// Here is the Vec3 struct, which is a vector of 3 integers.
struct Vec3
  : extends<terminal<int[3]>::type, Vec3>
{
    explicit Vec3(int i=0, int j=0, int k=0)
    {
        (*this)[0] = i;
        (*this)[1] = j;
        (*this)[2] = k;
    }

    int &operator[](int i)
    {
        return arg(*this)[i];
    }

    int const &operator[](int i) const
    {
        return arg(*this)[i];
    }

    // Here we define a operator= for Vec3 terminals that
    // takes a Vec3 expression.
    template< typename Expr >
    Vec3 &operator =(Expr const & expr)
    {
        typedef Vec3SubscriptCtx const CVec3SubscriptCtx;
        (*this)[0] = eval(as_expr(expr), CVec3SubscriptCtx(0));
        (*this)[1] = eval(as_expr(expr), CVec3SubscriptCtx(1));
        (*this)[2] = eval(as_expr(expr), CVec3SubscriptCtx(2));
        return *this;
    }

    void print() const
    {
        std::cout << '{' << (*this)[0]
                  << ", " << (*this)[1]
                  << ", " << (*this)[2]
                  << '}' << std::endl;
    }
};

// The count_leaves() function uses the CountLeaves transform and
// to count the number of leaves in an expression.
template<typename Expr>
int count_leaves(Expr const &expr)
{
    int i = 0;
    return CountLeaves::call(expr, i, i);
}

int main()
{
    Vec3 a, b, c;

    c = 4;

    b[0] = -1;
    b[1] = -2;
    b[2] = -3;

    a = b + c;

    a.print();

    Vec3 d;
    BOOST_PROTO_AUTO(expr1, b + c);
    d = expr1;
    d.print();

    int num = count_leaves(expr1);
    std::cout << num << std::endl;

    BOOST_PROTO_AUTO(expr2, b + 3 * c);
    num = count_leaves(expr2);
    std::cout << num << std::endl;

    BOOST_PROTO_AUTO(expr3, b + c * d);
    num = count_leaves(expr3);
    std::cout << num << std::endl;

    return 0;
}

