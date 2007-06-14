///////////////////////////////////////////////////////////////////////////////
// matches.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/mpl/min_max.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/proto/transform/branch.hpp>
#include <boost/xpressive/proto/transform/list.hpp>
#include <boost/xpressive/proto/transform/construct.hpp>
#include <boost/xpressive/proto/transform/fold_to_list.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost::proto;
namespace mpl = boost::mpl;
namespace fusion = boost::fusion;

struct placeholder1 {};
struct placeholder2 {};

namespace test1
{
//[ CalculatorGrammar
    using namespace boost::proto;

    /*<< A Calculator expression is ... >>*/
    struct CalculatorGrammar
      : or_<
            /*<< placeholder1, or ... >>*/
            terminal< placeholder1 >
          /*<< placeholder2, or ... >>*/
          , terminal< placeholder2 >
          /*<< some other terminal, or ... >>*/
          , terminal< _ >
          /*<< a unary expression where the operand is a calculator expression, or ... >>*/
          , unary_expr< _, CalculatorGrammar >
          /*<< a binary expression where the operands are calculator expressions, or ... >>*/
          , binary_expr< _, CalculatorGrammar, CalculatorGrammar >
        >
    {};
//]
}

//[ binary_max
// A custom transform that returns the arity of a binary
// calculator expression by finding the maximum of the
// arities of the two children expressions.
/*<< All transforms take a Grammar as a template parameter. >>*/
template<typename Grammar>
struct binary_max
  /*<< All transforms must inherit from the `Grammar`, so that the transform
  IS-A `Grammar`, and matches the same expressions that `Grammar` does. >>*/
  : Grammar
{
    template<typename Expr, typename State, typename Visitor>
    /*<< Transforms have a nested `apply<>` for calculating their return type. >>*/
    struct apply
    {
        /*<< Apply `Grammar`'s transform. This is what makes it possible to chain transforms. >>*/
        typedef typename mpl::apply_wrap3<Grammar, Expr, State, Visitor>::type expr_type;
        /*<< After applying `Grammar`'s transform, the children expressions have been
        replaced with their arities. >>*/
        typedef typename result_of::left<expr_type>::type left_arity;
        typedef typename result_of::right<expr_type>::type right_arity;
        /*<< The return type is the maximum of the children's arities. >>*/
        typedef typename mpl::max<left_arity, right_arity>::type type;
    };

    template<typename Expr, typename State, typename Visitor>
    static typename apply<Expr, State, Visitor>::type
    /*<< Transforms have a nested `call()` member function. >>*/
    call(Expr const &, State const &, Visitor &)
    {
        /*<< Usually, the `call()` member function invokes the `Grammar`'s `call()` function,
        as `Grammar::call(expr,state,visitor)`, but this transform doesn't have an interesting
        runtime counterpart, so just return a default-constructed object of the correct type. >>*/
        return typename apply<Expr, State, Visitor>::type();
    }
};
//]

terminal< placeholder1 >::type const _1 = {{}};
terminal< placeholder2 >::type const _2 = {{}};

//[ CalculatorArityGrammar
struct CalculatorGrammar
  : or_<
        transform::always< terminal< placeholder1 >, mpl::int_<1> >
      , transform::always< terminal< placeholder2 >, mpl::int_<2> >
      , transform::always< terminal< _ >, mpl::int_<0> >
      , transform::arg< unary_expr< _, CalculatorGrammar > >
      , binary_max< binary_expr< _, CalculatorGrammar, CalculatorGrammar > >
    >
{};
//]

//[ AsArgList
// This transform matches function invocations such as foo(1,'a',"b")
// and transforms them into Fusion cons lists of their arguments. In this
// case, the result would be cons(1, cons('a', cons("b", nil()))).
struct ArgsAsList
 /*<< Use a `branch<>` transform to use `fusion::nil` as the initial
 state of this transformation. >>*/
 : transform::branch<
     /*<< Use a `reverse_fold<>` transform to iterate over the children
     of this node in reverse order, building a fusion list from back to
     front. >>*/
     transform::reverse_fold<
       /*<< The `Grammar` we're matching is a function invocation. >>*/
       function<
         /*<< The first child expression of a `function<>` node is the
         function being invoked. We don't want that in our list, so use
         the `state<>` transform to effectively skip it. (Recall that
         we're building a list in the state parameter, and that the 
         `state<>` transform just returns the state unmodified. So this
         says to match a `terminal<>` but to not add it to the list.) >>*/
         transform::state<terminal<_> >
       /*<< We use `vararg<>` here because the function expression we're
       matching can have an arbitrary number of arguments. >>*/
       , vararg<
           /*<< The `list<>` transform puts the rest of the function
           arguments in a fusion cons list. >>*/
           transform::list<
             /*<< The arguments to the function are terminals.
             Extract the argument from each terminal before putting
             them into the list. >>*/
             transform::arg<terminal<_> >
           >
         >
       >
     >
   /*<< Here is the initial state used by this transform. >>*/
   , fusion::nil
   >
{};
//]

//[ FoldTreeToList
// This grammar describes what counts as the terminals in expressions
// of the form (_1=1,'a',"b"), which will be flattened using
// reverse_fold_tree<> below.
struct Terminals
  : or_<
        transform::arg<transform::right<assign<_, terminal<_> > > >
      , transform::arg<terminal<_> >
    >
{};

// This transform matches expressions of the form (_1=1,'a',"b")
// (note the use of the comma operator) and transforms it into a
// Fusion cons list of their arguments. In this case, the result
// would be cons(1, cons('a', cons("b", nil()))).
struct FoldTreeToList
  /*<< Fold all terminals that are separated by commas into a Fusion cons list. >>*/
  : transform::reverse_fold_tree<tag::comma, transform::list<Terminals>, fusion::nil>
{};
//]

//[ Promote
// This transform finds all float terminals in an expression and promotes
// them to doubles.
struct Promote
  : or_<
        /*<< Match a `terminal<float>`, then construct a `terminal<double>` with the `float`. >>*/
        transform::construct<terminal<float>, terminal<double>(transform::arg<_>) >
      , terminal<_>
      /*<< `nary_expr<>` has a pass-through transform which will transform each child
      sub-expression using the `Promote` transform. >>*/
      , nary_expr<_, vararg<Promote> >
    >
{};
//]

void test_examples()
{

    //[ CalculatorArityTest
    int i = 0; // not used, dummy state and visitor parameter

    std::cout << CalculatorGrammar::call( lit(100) * 200, i, i) << '\n';
    std::cout << CalculatorGrammar::call( (_1 - _1) / _1 * 100, i, i) << '\n';
    std::cout << CalculatorGrammar::call( (_2 - _1) / _2 * 100, i, i) << '\n';
    //]

    BOOST_CHECK_EQUAL(0, CalculatorGrammar::call( lit(100) * 200, i, i));
    BOOST_CHECK_EQUAL(1, CalculatorGrammar::call( (_1 - _1) / _1 * 100, i, i));
    BOOST_CHECK_EQUAL(2, CalculatorGrammar::call( (_2 - _1) / _2 * 100, i, i));

    using boost::fusion::cons;
    using boost::fusion::nil;
    cons<int, cons<char, cons<char const (&)[2]> > > args(ArgsAsList::call( _1(1, 'a', "b"), i, i ));
    BOOST_CHECK_EQUAL(args.car, 1);
    BOOST_CHECK_EQUAL(args.cdr.car, 'a');
    BOOST_CHECK_EQUAL(args.cdr.cdr.car, std::string("b"));

    cons<int, cons<char, cons<char const (&)[2]> > > lst(FoldTreeToList::call( (_1 = 1, 'a', "b"), i, i ));
    BOOST_CHECK_EQUAL(lst.car, 1);
    BOOST_CHECK_EQUAL(lst.cdr.car, 'a');
    BOOST_CHECK_EQUAL(lst.cdr.cdr.car, std::string("b"));

    plus<
        terminal<double>::type
      , terminal<double>::type
    >::type p = Promote::call( lit(1.f) + 2.f, i, i );
}


using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test examples from the documentation");

    test->add(BOOST_TEST_CASE(&test_examples));

    return test;
}
