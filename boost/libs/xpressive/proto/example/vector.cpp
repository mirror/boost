///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This is an example of using BOOST_PROTO_DEFINE_OPERATORS to proto-ify
// expressions using std::vector<>, a non-proto type. It is a port of the
// Vector example from PETE (http://www.codesourcery.com/pooma/download.html).

#include <vector>
#include <iostream>
#include <stdexcept>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/debug.hpp>
#include <boost/xpressive/proto/context.hpp>

using namespace boost;
using proto::_;

template<typename Expr>
struct VectorExpr;

// Here is an evaluation context that indexes into a std::vector
// expression and combines the result.
struct VectorSubscriptCtx
{
    VectorSubscriptCtx(std::size_t i)
      : i_(i)
    {}

    // Unless this is a vector terminal, use the
    // default evaluation context
    template<typename Expr, typename Arg = typename proto::result_of::arg<Expr>::type>
    struct eval
      : proto::default_eval<Expr, VectorSubscriptCtx const>
    {};

    // Index vector terminals with our subscript.
    template<typename Expr, typename T, typename A>
    struct eval<Expr, std::vector<T, A> >
    {
        typedef T result_type;

        T operator()(Expr &expr, VectorSubscriptCtx const &ctx) const
        {
            return proto::arg(expr)[ctx.i_];
        }
    };

    std::size_t i_;
};

// Here is an evaluation context that verifies that all the
// vectors in an expression have the same size.
struct VectorSizeCtx
  : proto::callable_context< VectorSizeCtx const >
{
    typedef int result_type;

    VectorSizeCtx(std::size_t size)
      : size_(size)
    {}

    // Index array terminals with our subscript. Everything
    // else will be handled by the default evaluation context.
    template<typename T, typename A>
    int operator()(proto::tag::terminal, std::vector<T, A> const &arr) const
    {
        if(this->size_ != arr.size())
        {
            throw std::invalid_argument("LHS and RHS are not compatible");
        }
        return 0; // not used
    }

    std::size_t size_;
};

// A grammar which matches all the assignment operators,
// so we can easily disable them.
struct AssignOps
  : proto::switch_<struct AssignOpsCases>
{};

// Here are the cases used by the switch_ above.
struct AssignOpsCases
{
    template<typename Tag, int D = 0> struct case_  : proto::not_<_> {};

    template<int D> struct case_< proto::tag::plus_assign, D >         : _ {};
    template<int D> struct case_< proto::tag::minus_assign, D >        : _ {};
    template<int D> struct case_< proto::tag::multilpies_assign, D >   : _ {};
    template<int D> struct case_< proto::tag::divides_assign, D >      : _ {};
    template<int D> struct case_< proto::tag::modulus_assign, D >      : _ {};
    template<int D> struct case_< proto::tag::shift_left_assign, D >   : _ {};
    template<int D> struct case_< proto::tag::shift_right_assign, D >  : _ {};
    template<int D> struct case_< proto::tag::bitwise_and_assign, D >  : _ {};
    template<int D> struct case_< proto::tag::bitwise_or_assign, D >   : _ {};
    template<int D> struct case_< proto::tag::bitwise_xor_assign, D >  : _ {};
};

// A vector grammar is a terminal or some op that is not an
// assignment op. (Assignment will be handles specially.)
struct VectorGrammar
  : proto::or_<
        proto::terminal<_>
      , proto::and_<proto::nary_expr<_, proto::vararg<VectorGrammar> >, proto::not_<AssignOps> >
    >
{};

// Expressions in the vector domain will be wrapped in VectorExpr<>
// and must conform to the VectorGrammar
struct VectorDomain
  : proto::domain<proto::generator<VectorExpr>, VectorGrammar>
{};

// Here is VectorExpr, which extends a proto expr type by
// giving it an operator[] which uses the VectorSubscriptCtx 
// to evaluate an expression with a given index.
template<typename Expr>
struct VectorExpr
  : proto::extends<Expr, VectorExpr<Expr>, VectorDomain>
{
    explicit VectorExpr(Expr const &expr)
      : proto::extends<Expr, VectorExpr<Expr>, VectorDomain>(expr)
    {}

    // Use the VectorSubscriptCtx to implement subscripting
    // of a Vector expression tree.
    typename proto::result_of::eval<Expr const, VectorSubscriptCtx const>::type
    operator []( std::size_t i ) const
    {
        VectorSubscriptCtx const ctx(i);
        return proto::eval(*this, ctx);
    }
};

// Define a trait type for detecting vector terminals, to
// be used by the BOOST_PROTO_DEFINE_OPERATORS macro below.
template<typename T>
struct IsVector
  : mpl::false_
{};

template<typename T, typename A>
struct IsVector<std::vector<T, A> >
  : mpl::true_
{};

namespace VectorOps
{
    // This defines all the overloads to make expressions involving
    // std::vector to build expression templates.
    BOOST_PROTO_DEFINE_OPERATORS(IsVector, VectorDomain)

    typedef VectorSubscriptCtx const CVectorSubscriptCtx;

    // Assign to a vector from some expression.
    template<typename T, typename A, typename Expr>
    std::vector<T, A> &assign(std::vector<T, A> &arr, Expr const &expr)
    {
        VectorSizeCtx const size(arr.size());
        proto::eval(proto::as_expr<VectorDomain>(expr), size); // will throw if the sizes don't match
        for(std::size_t i = 0; i < arr.size(); ++i)
        {
            arr[i] = proto::as_expr<VectorDomain>(expr)[i];
        }
        return arr;
    }

    // Add-assign to a vector from some expression.
    template<typename T, typename A, typename Expr>
    std::vector<T, A> &operator +=(std::vector<T, A> &arr, Expr const &expr)
    {
        VectorSizeCtx const size(arr.size());
        proto::eval(proto::as_expr<VectorDomain>(expr), size); // will throw if the sizes don't match
        for(std::size_t i = 0; i < arr.size(); ++i)
        {
            arr[i] += proto::as_expr<VectorDomain>(expr)[i];
        }
        return arr;
    }
}

int main()
{
    using namespace VectorOps;

    int i;
    const int n = 10;
    std::vector<int> a,b,c,d;
    std::vector<double> e(n);

    for (i = 0; i < n; ++i)
    {
        a.push_back(i);
        b.push_back(2*i);
        c.push_back(3*i);
        d.push_back(i);
    }

    VectorOps::assign(b, 2);
    VectorOps::assign(d, a + b * c);
    a += if_else(d < 30, b, c);

    VectorOps::assign(e, c);
    e += e - 4 / (c + 1);

    for (i = 0; i < n; ++i)
    {
        std::cout
            << " a(" << i << ") = " << a[i]
            << " b(" << i << ") = " << b[i]
            << " c(" << i << ") = " << c[i]
            << " d(" << i << ") = " << d[i]
            << " e(" << i << ") = " << e[i]
            << std::endl;
    }
}
