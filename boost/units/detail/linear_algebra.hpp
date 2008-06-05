// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_DETAIL_LINEAR_ALGEBRA_HPP
#define BOOST_UNITS_DETAIL_LINEAR_ALGEBRA_HPP

#include <boost/units/static_rational.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/units/dim.hpp>
#include <boost/units/dimensionless_type.hpp>
#include <boost/units/static_rational.hpp>
#include <boost/units/detail/dimension_list.hpp>
#include <boost/units/detail/sort.hpp>

namespace boost {

namespace units {

namespace detail {

// typedef list<rational> equation;

template<int N>
struct eliminate_from_pair_of_equations_impl;

template<class E1, class E2>
struct eliminate_from_pair_of_equations;

template<int N>
struct elimination_impl;

template<bool is_zero, bool element_is_last>
struct elimination_skip_leading_zeros_impl;

template<class Equation, class Vars>
struct substitute;

template<int N>
struct substitute_impl;

template<bool is_end>
struct solve_impl;

template<class T>
struct solve;

template<int N>
struct check_extra_equations_impl;

template<int N>
struct normalize_units_impl;

struct inconsistent {};

// eliminate_from_pair_of_equations takes a pair of
// equations and eliminates the first variable.
//
// equation eliminate_from_pair_of_equations(equation l1, equation l2) {
//     rational x1 = l1.front();
//     rational x2 = l2.front();
//     return(transform(pop_front(l1), pop_front(l2), _1 * x2 - _2 * x1));
// }

template<int N>
struct eliminate_from_pair_of_equations_impl {
    template<class Begin1, class Begin2, class X1, class X2>
    struct apply {
        typedef typename mpl::push_front<
            typename eliminate_from_pair_of_equations_impl<N - 1>::template apply<
                typename mpl::next<Begin1>::type,
                typename mpl::next<Begin2>::type,
                X1,
                X2
            >::type,
            typename mpl::minus<
                typename mpl::times<typename mpl::deref<Begin1>::type, X2>::type,
                typename mpl::times<typename mpl::deref<Begin2>::type, X1>::type
            >::type
        >::type type;
    };
};

template<>
struct eliminate_from_pair_of_equations_impl<0> {
    template<class Begin1, class Begin2, class X1, class X2>
    struct apply {
        typedef mpl::list0<> type;
    };
};

template<class E1, class E2>
struct eliminate_from_pair_of_equations {
    typedef typename mpl::begin<E1>::type begin1;
    typedef typename mpl::begin<E2>::type begin2;
    typedef typename eliminate_from_pair_of_equations_impl<mpl::size<E1>::value - 1>::template apply<
        typename mpl::next<begin1>::type,
        typename mpl::next<begin2>::type,
        typename mpl::deref<begin1>::type,
        typename mpl::deref<begin2>::type
    >::type type;
};

// Eliminates the first variable from a list of equations
// returns inconsistent if all its coefficients are 0.  Otherwise
// recursively calls solve to find the remaining variables
//
// list<rational> eliminate(list<equation> system) {
//     list<equation> result;
//     equation eliminate_against = null;
//     for_each(equation e : system) {
//         if(eliminate_against == null) {
//             if(e.front() == 0) {
//                 result = push_front(result, pop_front(e));
//             } else {
//                 eliminate_against = e;
//             }
//         } else {
//             result = push_back(result, eliminate_from_pair_of_equations(e,eliminate_against));
//         }
//     }
//     if(eliminate_against == null) {
//         return(inconsistent);
//     } else {
//         list<rational> solution = solve(result);
//         return(push_front(solution, substitute(eliminate_against,solution)));
//     }
// }

template<int N>
struct elimination_impl {
    template<class Begin, class Prev, class L>
    struct apply {
        typedef typename mpl::push_front<
            typename elimination_impl<N-1>::template apply<typename mpl::next<Begin>::type, Prev, L>::type,
            typename eliminate_from_pair_of_equations<typename mpl::deref<Begin>::type,Prev>::type
        >::type type;
    };
};

template<>
struct elimination_impl<0> {
    template<class Begin, class Prev, class L>
    struct apply {
        typedef L type;
    };
};

template<>
struct elimination_skip_leading_zeros_impl<true, true> {
    template<class Begin, int N, class L>
    struct apply {
        typedef inconsistent type;
    };
};

template<>
struct elimination_skip_leading_zeros_impl<true, false> {
    template<class Begin, int N, class L>
    struct apply {
        typedef typename mpl::next<Begin>::type next;
        typedef typename elimination_skip_leading_zeros_impl<
            boost::is_same<
                typename mpl::deref<
                    typename mpl::begin<typename mpl::deref<next>::type>::type
                >::type,
                static_rational<0>
            >::value,
            N == 2
        >::template apply<
            next,
            N-1,
            typename mpl::push_front<
                L,
                typename mpl::pop_front<typename mpl::deref<Begin>::type>::type
            >::type
        >::type type;
    };
};

template<class S>
struct combine_solutions {
    template<class Iterator>
    struct apply {
        typedef typename substitute<typename mpl::deref<Iterator>::type, S>::type x;
        typedef typename mpl::push_front<S, x>::type type;
    };
};

template<>
struct combine_solutions<inconsistent> {
    template<class Iterator>
    struct apply {
        typedef inconsistent type;
    };
};

template<>
struct elimination_skip_leading_zeros_impl<false, true> {
    template<class Begin, int N, class L>
    struct apply {
        typedef typename elimination_impl<N - 1>::template apply<
            typename mpl::next<Begin>::type,
            typename mpl::deref<Begin>::type,
            L
        >::type list_type;
        typedef typename solve<list_type>::type next;
        typedef typename combine_solutions<next>::template apply<Begin>::type type;
    };
};

template<>
struct elimination_skip_leading_zeros_impl<false, false> {
    template<class Begin, int N, class L>
    struct apply {
        typedef typename elimination_impl<N - 1>::template apply<
            typename mpl::next<Begin>::type,
            typename mpl::deref<Begin>::type,
            L
        >::type list_type;
        typedef typename solve<list_type>::type next;
        typedef typename combine_solutions<next>::template apply<Begin>::type type;
    };
};

// finds the vaue of the first variable given the
// values of all the other variables.
//
// rational substitute(equation e, list<rational> solutions) {
//     rational value = e.back();
//     for_each(rational x : solutions, rational a : pop_front(pop_back(e))) {
//         value -= a * x;
//     }
//     return(e.front() / value);
// }

template<int N>
struct substitute_impl {
    template<class Begin1, class Begin2>
    struct apply {
        typedef typename mpl::minus<
            typename substitute_impl<N-1>::template apply<
                typename mpl::next<Begin1>::type,
                typename mpl::next<Begin2>::type
            >::type,
            typename mpl::times<
                typename mpl::deref<Begin1>::type,
                typename mpl::deref<Begin2>::type
            >::type
        >::type type;
    };
};

template<>
struct substitute_impl<0> {
    template<class Begin1, class Begin2>
    struct apply {
        typedef typename mpl::deref<Begin1>::type type;
    };
};

template<class Equation, class Vars>
struct substitute {
    typedef typename mpl::begin<Equation>::type begin;
    typedef typename mpl::divides<
        typename substitute_impl<mpl::size<Vars>::value>::template apply<
            typename mpl::next<begin>::type,
            typename mpl::begin<Vars>::type
        >::type,
        typename mpl::deref<begin>::type
    >::type type;
};

template<>
struct solve_impl<true> {
    template<class T>
    struct apply {
        typedef mpl::list0<> type;
    };
};

// check_extra_equations verifies that the
// after all the variables have been eliminated
// the remaining equations are all 0=0.

template<class T>
struct check_extra_equations_func {
    template<class Begin, int N>
    struct apply {
        typedef inconsistent type;
    };
};

template<>
struct check_extra_equations_func<static_rational<0> > {
    template<class Begin, int N>
    struct apply {
        typedef typename check_extra_equations_impl<N - 1>::template apply<typename mpl::next<Begin>::type>::type type;
    };
};

template<int N>
struct check_extra_equations_impl {
    template<class Begin>
    struct apply {
        typedef typename check_extra_equations_func<
            typename mpl::deref<typename mpl::begin<typename mpl::deref<Begin>::type>::type>::type
        >::template apply<Begin, N>::type type;
    };
};

template<>
struct check_extra_equations_impl<0> {
    template<class Begin>
    struct apply {
        typedef mpl::list0<> type;
    };
};

template<bool is_end>
struct check_extra_equations;

template<>
struct check_extra_equations<true> {
    template<class T>
    struct apply {
        typedef typename check_extra_equations_impl<mpl::size<T>::value>::template apply<
            typename mpl::begin<T>::type
        >::type type;
    };
};

template<>
struct check_extra_equations<false> {
    template<class T>
    struct apply {
        typedef typename mpl::begin<T>::type begin;
        typedef typename elimination_skip_leading_zeros_impl<
            boost::is_same<
                typename mpl::deref<
                    typename mpl::begin<typename mpl::deref<begin>::type>::type
                >::type,
                static_rational<0>
            >::value,
            mpl::size<T>::value == 1
        >::template apply<
            begin,
            mpl::size<T>::value,
            mpl::list0<>
        >::type type;
    };
};

template<>
struct solve_impl<false> {
    template<class T>
    struct apply {
        typedef typename mpl::begin<T>::type begin;
        typedef typename check_extra_equations<
            mpl::size<typename mpl::deref<begin>::type>::value == 1
        >::template apply<
            T
        >::type type;
    };
};

// solve takes a list of equations and returns the solutions
// as a vector.  Each equation is interpreted as a sequence
// of coefficients with the last item being the value e.g.
// list<1, 2, 3> is 1 * x0 + 2 * x1 = 3

template<class T>
struct solve {
    typedef typename solve_impl<mpl::size<T>::value == 0>::template apply<T>::type type;
};

// find_base_dimensions takes a list of
// base_units and returns a sorted list
// of all the base_dimensions they use.
//
// list<base_dimension> find_base_dimensions(list<base_unit> l) {
//     set<base_dimension> dimensions;
//     for_each(base_unit unit : l) {
//         for_each(dim d : unit.dimension_type) {
//             dimensions = insert(dimensions, d.tag_type);
//         }
//     }
//     return(sort(dimensions, _1 > _2, front_inserter(list<base_dimension>())));
// }

template<int N>
struct find_base_dimensions_impl_impl {
    template<class Begin, class S>
    struct apply {
        typedef typename mpl::insert<
            typename find_base_dimensions_impl_impl<N-1>::template apply<
                typename mpl::next<Begin>::type,
                S
            >::type,
            typename mpl::deref<Begin>::type::tag_type
        >::type type;
    };
};

template<>
struct find_base_dimensions_impl_impl<0> {
    template<class Begin, class S>
    struct apply {
        typedef S type;
    };
};

template<int N>
struct find_base_dimensions_impl {
    template<class Begin>
    struct apply {
        typedef typename find_base_dimensions_impl_impl<mpl::size<typename mpl::deref<Begin>::type::dimension_type>::value>::template apply<
            typename mpl::begin<typename mpl::deref<Begin>::type::dimension_type>::type,
            typename find_base_dimensions_impl<N-1>::template apply<typename mpl::next<Begin>::type>::type
        >::type type;
    };
};

template<>
struct find_base_dimensions_impl<0> {
    template<class Begin>
    struct apply {
        typedef mpl::set0<> type;
    };
};

template<class T>
struct find_base_dimensions {
    typedef typename bubble_sort<
        typename find_base_dimensions_impl<
            mpl::size<T>::value
        >::template apply<typename mpl::begin<T>::type>::type
    >::type type;
};

// calculate_base_dimension_coefficients finds
// the coefficients corresponding to the first
// base_dimension in each of the dimension_lists.
// It returns two values.  The first result
// is a list of the coefficients.  The second
// is a list with all the incremented iterators.
// When we encounter a base_dimension that is
// missing from a dimension_list, we do not
// increment the iterator and we set the
// coefficient to zero.

template<bool has_dimension>
struct calculate_base_dimension_coefficients_func;

template<>
struct calculate_base_dimension_coefficients_func<true> {
    template<class T>
    struct apply {
        typedef typename mpl::deref<T>::type::value_type type;
        typedef typename mpl::next<T>::type next;
    };
};

template<>
struct calculate_base_dimension_coefficients_func<false> {
    template<class T>
    struct apply {
        typedef static_rational<0> type;
        typedef T next;
    };
};

// begins_with_dimension returns true iff its first
// parameter is a valid iterator which yields its
// second parameter when dereferenced.

template<class Iterator>
struct begins_with_dimension {
    template<class Dim>
    struct apply : 
        boost::is_same<
            Dim,
            typename mpl::deref<Iterator>::type::tag_type
        > {};
};

template<>
struct begins_with_dimension<dimensionless_type> {
    template<class Dim>
    struct apply : mpl::false_ {};
};

template<int N>
struct calculate_base_dimension_coefficients_impl {
    template<class BaseUnitDimensions,class Dim,class T>
    struct apply {
        typedef typename calculate_base_dimension_coefficients_func<
            begins_with_dimension<typename mpl::deref<BaseUnitDimensions>::type>::template apply<
                Dim
            >::value
        >::template apply<
            typename mpl::deref<BaseUnitDimensions>::type
        > result;
        typedef typename calculate_base_dimension_coefficients_impl<N-1>::template apply<
            typename mpl::next<BaseUnitDimensions>::type,
            Dim,
            typename mpl::push_front<T, typename result::type>::type
        > next_;
        typedef typename next_::type type;
        typedef typename mpl::push_front<typename next_::next, typename result::next>::type next;
    };
};

template<>
struct calculate_base_dimension_coefficients_impl<0> {
    template<class Begin, class BaseUnitDimensions, class T>
    struct apply {
        typedef T type;
        typedef mpl::list0<> next;
    };
};

// solve_for_base_dimension_impl computes the
// coefficients of each unit for all the base_dimensions.
// the inner lists are in reverse order.

template<int N>
struct get_equations_for_base_dimension_impl {
    template<class Begin, class Units>
    struct apply {
        typedef typename calculate_base_dimension_coefficients_impl<mpl::size<Units>::value>::template apply<
            typename mpl::begin<Units>::type,
            typename mpl::deref<Begin>::type,
            mpl::list0<>
        > x;
        typedef typename mpl::push_front<
            typename get_equations_for_base_dimension_impl<N-1>::template apply<
                typename mpl::next<Begin>::type,
                typename x::next
            >::type,
            typename x::type
        >::type type;
    };
};

template<>
struct get_equations_for_base_dimension_impl<0> {
    template<class Begin, class Units>
    struct apply {
        typedef mpl::list0<> type;
    };
};

// get_dimension_iterators_impl takes a list of base_units
// and returns a list of the begin iterators of their
// dimensions

template<int N>
struct get_dimension_iterators_impl {
    template<class Begin>
    struct apply {
        typedef typename mpl::push_front<
            typename get_dimension_iterators_impl<N-1>::template apply<typename mpl::next<Begin>::type>::type,
            typename mpl::begin<typename mpl::deref<Begin>::type::dimension_type>::type
        >::type type;
    };
};

template<>
struct get_dimension_iterators_impl<0> {
    template<class Begin>
    struct apply {
        typedef mpl::list0<> type;
    };
};

// prepare_equations takes the result of
// solve_for_base_dimension_impl and an index.
// it sets the equation at the index equal to
// one and all the others to zero.  In the process
// it reverses the inner lists thus yielding
// a matrix that can be passed to solve.

template<int N>
struct prepare_equations_impl {
    template<class Begin, int M>
    struct apply {
        typedef typename mpl::push_front<
            typename prepare_equations_impl<N-1>::template apply<typename mpl::next<Begin>::type, M - 1>::type,
            typename mpl::reverse<typename mpl::push_front<typename mpl::deref<Begin>::type, static_rational<(M == 0 ? 1 : 0)> >::type>::type
        >::type type;
    };
};

template<>
struct prepare_equations_impl<0> {
    template<class Begin, int M>
    struct apply {
        typedef mpl::list0<> type;
    };
};

// add_zeroes pushs N zeroes onto the
// front of a list.
//
// list<rational> add_zeroes(list<rational> l, int N) {
//     if(N == 0) {
//         return(l);
//     } else {
//         return(push_front(add_zeroes(l, N-1), 0));
//     }
// }

template<int N>
struct add_zeroes_impl {
    // If you get an error here and your base units are
    // in fact linearly independent, please report it.
    BOOST_MPL_ASSERT_MSG((N > 0), base_units_are_probably_not_linearly_independent, (void));
    template<class T>
    struct apply {
        typedef typename mpl::push_front<
            typename add_zeroes_impl<N-1>::template apply<T>::type,
            static_rational<0>
        >::type type;
    };
};

template<>
struct add_zeroes_impl<0> {
    template<class T>
    struct apply {
        typedef T type;
    };
};

// add_solutions takes a list of equations
// for the extra dummy units and a list
// of the values of all the regular units.
// It find the coefficients of all the dummy
// units and pushes them onto the begining
// of the list in reverse order (since the
// dummy equations are reversed).

template<int N>
struct add_solutions_impl {
    template<class Begin, class T, class Solution>
    struct apply {
        typedef typename add_solutions_impl<N-1>::template apply<
            typename mpl::next<Begin>::type,
            typename mpl::push_front<
                T,
                typename substitute_impl<mpl::size<Solution>::value>::template apply<
                    typename mpl::begin<typename mpl::deref<Begin>::type>::type,
                    typename mpl::begin<Solution>::type
                >::type
            >::type,
            Solution
        >::type type;
    };
};

template<>
struct add_solutions_impl<0> {
    template<class Begin, class T, class Solution>
    struct apply {
        typedef T type;
    };
};

// normalize_units finds the units corresponding
// to each base dimension.  The form of the result is
// a two dimensional list.  list<list<rational> >.
// each of the inner lists represents a single
// base dimension.  There may be extra units added
// to the front of the inner list if there are
// more base dimensions than base units.  The
// number such units is returned as a long called
// extra.  For example list<pound, foot> will yield
// list<list<0, 0, 1>,list<1, 0, 0>,list<1/2,-1/2,1/2> > meaning
//
//   length = 0 * mass + 0 * force + 1 * length
//   mass   = 1 * mass + 0 * force + 0 * length
//   time   = 1/2 * mass - 1/2 * force + 1/2 * length
//
// Why is there a dummy mass unit?  It isn't
// possible to represent three base dimensions
// with only two base units.  So we need some
// kind of dummy.  Why mass?  Well, a base
// unit of length doesn't help us since we
// already have one.  Mass is before time
// so we use mass.

// S is the solution for this particular base dimension.
// if the base dimension cannot be represented then
// solve will return inconsistent hence the two specializations.

template<class S>
struct normalize_units_func {
    template<class ReverseEquations, int M, class DimensionIterator, int N, int Extra, int I,class ExtraEquations>
    struct apply {
        // first add zeroes for all the extra units that
        // are not needed.
        typedef typename add_zeroes_impl<Extra-mpl::size<ExtraEquations>::value>::template apply<S>::type result1;
        // then find the values for the extra units that /are/ needed.
        typedef typename add_solutions_impl<mpl::size<ExtraEquations>::value>::template apply<
            typename mpl::begin<ExtraEquations>::type,
            result1,
            S
        >::type result;
        // recurse back to the primary loop putting
        // push_front outside since we wish to maintain
        // the original ordering of dimensions
        typedef typename mpl::push_front<
            typename normalize_units_impl<N-1>::template apply<
                // The coefficient are still the same
                // and we don't need to remove any equations
                ReverseEquations,
                // increment the number of equations that
                // need to be skipped when we add another
                // dummy unit.
                M+1,
                typename mpl::next<DimensionIterator>::type,
                Extra,
                // increment the number of dimensions we've seen
                I+1,
                // pass the equations for the dummy
                // units on without modification.
                ExtraEquations
            >::type,
            result
        >::type type;
    };
};

// handles the case when this base dimension
// cannot be represented with the base units
// and the dummies allready added.
template<>
struct normalize_units_func<inconsistent> {
    template<class ReverseEquations, int M, class DimensionIterator, int N, int Extra, int I, class ExtraEquations>
    struct apply {
        // Find the position that needs to be erased. (Since this
        // equation can always be adjusted by adjusting the
        // dummy unit we are adding now, independently of
        // other units, we don't need it anymore.)
        typedef typename mpl::advance_c<typename mpl::begin<ReverseEquations>::type, M>::type pos;
        // Continue with the main loop.
        typedef typename normalize_units_impl<N-1>::template apply<
            // Remove current_equation
            typename mpl::erase<
                ReverseEquations,
                pos
            >::type,
            M,
            typename mpl::next<DimensionIterator>::type,
            Extra,
            // Increment the number of dimensions we've seen
            I+1,
            // Add "current_equation == 0" to the list of equations
            // for the dummy units.  (For all base dimensions
            // except this the current dimension must sum to
            // zero.)
            typename mpl::push_front<
                ExtraEquations,
                // Remember it's backwards
                typename mpl::reverse<
                    typename mpl::push_front<typename mpl::deref<pos>::type, static_rational<0> >::type
                >::type
            >::type
        > next;
        // this dimension is (0, ..., 0, 1, 0, ..., 0)
        typedef typename mpl::push_front<
            typename add_zeroes_impl<N-1>::template apply<mpl::list0<> >::type,
            static_rational<1>
        >::type result1;
        typedef typename add_zeroes_impl<I>::template apply<result1>::type result;
        // Push the result onto the list.
        typedef typename mpl::push_front<typename next::type, result>::type type;
    };
};

template<int N>
struct normalize_units_impl {
    template<class ReverseEquations, int M, class DimensionIterator, int Extra, int I, class ExtraEquations>
    struct apply {
        typedef typename solve<
            typename prepare_equations_impl<
                mpl::size<ReverseEquations>::value
            >::template apply<
                typename mpl::begin<ReverseEquations>::type,
                M
            >::type
        >::type solution;
        typedef typename normalize_units_func<solution>::template apply<
            ReverseEquations,
            M,
            DimensionIterator,
            N,
            Extra,
            I,
            ExtraEquations
        >::type type;
    };
};

template<>
struct normalize_units_impl<0> {
    template<class ReverseEquations, int M, class DimensionIterator, int Extra, int I, class ExtraEquations>
    struct apply {
        typedef mpl::list0<> type;
    };
};

template<class T>
struct normalize_units {
    typedef typename find_base_dimensions<T>::type dimensions;
    typedef typename get_dimension_iterators_impl<mpl::size<T>::value>::template apply<typename mpl::begin<T>::type>::type iterators;
    typedef typename get_equations_for_base_dimension_impl<
        mpl::size<dimensions>::value
    >::template apply<
        typename mpl::begin<dimensions>::type,
        iterators
    >::type reverse_equations;
    static const long extra = mpl::size<reverse_equations>::value - mpl::size<T>::value;
    typedef typename normalize_units_impl<mpl::size<reverse_equations>::value>::template apply<
        reverse_equations,
        0,
        typename mpl::begin<dimensions>::type,
        extra,
        0,
        mpl::list0<>
    >::type type;
};

// expand_dimensions finds the exponents of
// a set of dimensions in a dimension_list.
// the second parameter is assumed to be
// a superset of the base_dimensions of
// the first parameter.
//
// list<rational> expand_dimensions(dimension_list, list<base_dimension>);

template<int N>
struct expand_dimensions {
    template<class Begin, class DimensionIterator>
    struct apply {
        typedef typename calculate_base_dimension_coefficients_func<
            begins_with_dimension<DimensionIterator>::template apply<typename mpl::deref<Begin>::type>::value
        >::template apply<DimensionIterator> result;
        typedef typename mpl::push_front<
            typename expand_dimensions<N-1>::template apply<typename mpl::next<Begin>::type, typename result::next>::type,
            typename result::type
        >::type type;
    };
};

template<>
struct expand_dimensions<0> {
    template<class Begin, class DimensionIterator>
    struct apply {
        typedef mpl::list0<> type;
    };
};

// multiply_add_units computes M x V
// where M is a matrix and V is a horizontal
// vector
//
// list<rational> multiply_add_units(list<list<rational> >, list<rational>);

template<int N>
struct multiply_add_units_impl {
    template<class Begin1, class Begin2 ,class X>
    struct apply {
        typedef typename mpl::push_front<
            typename multiply_add_units_impl<N-1>::template apply<
                typename mpl::next<Begin1>::type,
                typename mpl::next<Begin2>::type,
                X
            >::type,
            typename mpl::plus<
                typename mpl::times<
                    typename mpl::deref<Begin2>::type,
                    X
                >::type,
                typename mpl::deref<Begin1>::type
            >::type
        >::type type;
    };
};

template<>
struct multiply_add_units_impl<0> {
    template<class Begin1, class Begin2 ,class X>
    struct apply {
        typedef mpl::list0<> type;
    };
};

template<int N>
struct multiply_add_units {
    template<class Begin1, class Begin2>
    struct apply {
        typedef typename multiply_add_units_impl<
            mpl::size<typename mpl::deref<Begin2>::type>::value
        >::template apply<
            typename mpl::begin<
                typename multiply_add_units<N-1>::template apply<
                    typename mpl::next<Begin1>::type,
                    typename mpl::next<Begin2>::type
                >::type
            >::type,
            typename mpl::begin<typename mpl::deref<Begin2>::type>::type,
            typename mpl::deref<Begin1>::type
        >::type type;
    };
};

template<>
struct multiply_add_units<1> {
    template<class Begin1, class Begin2>
    struct apply {
        typedef typename add_zeroes_impl<
            mpl::size<typename mpl::deref<Begin2>::type>::value
        >::template apply<mpl::list0<> >::type type1;
        typedef typename multiply_add_units_impl<
            mpl::size<typename mpl::deref<Begin2>::type>::value
        >::template apply<
            typename mpl::begin<
                type1
            >::type,
            typename mpl::begin<typename mpl::deref<Begin2>::type>::type,
            typename mpl::deref<Begin1>::type
        >::type type;
    };
};


// strip_zeroes erases the first N elements of a list if
// they are all zero, otherwise returns inconsistent
//
// list strip_zeroes(list l, int N) {
//     if(N == 0) {
//         return(l);
//     } else if(l.front == 0) {
//         return(strip_zeroes(pop_front(l), N-1));
//     } else {
//         return(inconsistent);
//     }
// }

template<int N>
struct strip_zeroes_impl;

template<class T>
struct strip_zeroes_func {
    template<class L, int N>
    struct apply {
        typedef inconsistent type;
    };
};

template<>
struct strip_zeroes_func<static_rational<0> > {
    template<class L, int N>
    struct apply {
        typedef typename strip_zeroes_impl<N-1>::template apply<typename mpl::pop_front<L>::type>::type type;
    };
};

template<int N>
struct strip_zeroes_impl {
    template<class T>
    struct apply {
        typedef typename strip_zeroes_func<typename mpl::front<T>::type>::template apply<T, N>::type type;
    };
};

template<>
struct strip_zeroes_impl<0> {
    template<class T>
    struct apply {
        typedef T type;
    };
};

// Given a list of base_units, computes the
// exponents of each base unit for a given
// dimension.
//
// list<rational> calculate_base_unit_exponents(list<base_unit> units, dimension_list dimensions);
//
// What is the purpose of all this magic with
// base_dimensions? Can't we just solve the
// equations for the dimension directly?  Yes,
// we can, but remember that solving a
// system of linear equations is O(N^3).
// By normalizing the system we incur a
// high one time cost O(N^4), but for all
// solutions after the first it is O(N^2)
// In addition, the constant factor is
// good because everything is already set up.
// Since we expect a few systems to be
// used many times, the cost of creating
// a system is probably not significant.

template<class T>
struct is_base_dimension_unit {
    typedef mpl::false_ type;
    typedef void base_dimension_type;
};
template<class T>
struct is_base_dimension_unit<list<dim<T, static_rational<1> >, dimensionless_type> > {
    typedef mpl::true_ type;
    typedef T base_dimension_type;
};

template<int N>
struct is_simple_system_impl {
    template<class Begin, class Prev>
    struct apply {
        typedef is_base_dimension_unit<typename mpl::deref<Begin>::type::dimension_type> test;
        typedef mpl::and_<
            typename test::type,
            mpl::less<Prev, typename test::base_dimension_type>,
            typename is_simple_system_impl<N-1>::template apply<
                typename mpl::next<Begin>::type,
                typename test::base_dimension_type
            >
        > type;
        static const bool value = (type::value);
    };
};

template<>
struct is_simple_system_impl<0> {
    template<class Begin, class Prev>
    struct apply : mpl::true_ {
    };
};

template<class T>
struct is_simple_system {
    typedef typename mpl::begin<T>::type Begin;
    typedef is_base_dimension_unit<typename mpl::deref<Begin>::type::dimension_type> test;
    typedef typename mpl::and_<
        typename test::type,
        typename is_simple_system_impl<
            mpl::size<T>::value - 1
        >::template apply<
            typename mpl::next<Begin>::type,
            typename test::base_dimension_type
        >
    >::type type;
    static const bool value = type::value;
};

template<bool>
struct calculate_base_unit_exponents_impl;

template<>
struct calculate_base_unit_exponents_impl<true> {
    template<class T, class Dimensions>
    struct apply {
        typedef typename expand_dimensions<mpl::size<T>::value>::template apply<
            typename mpl::begin<typename find_base_dimensions<T>::type>::type,
            typename mpl::begin<Dimensions>::type
        >::type type;
    };
};

template<>
struct calculate_base_unit_exponents_impl<false> {
    template<class T, class Dimensions>
    struct apply {
        // find the units that correspond to each base dimension
        typedef normalize_units<T> base_solutions;
        // pad the dimension with zeroes so it can just be a
        // list of numbers, making the multiplication easy
        // e.g. if the arguments are list<pound, foot> and
        // list<mass,time^-2> then this step will
        // yield list<0,1,-2>
        typedef typename expand_dimensions<mpl::size<typename base_solutions::dimensions>::value>::template apply<
            typename mpl::begin<typename base_solutions::dimensions>::type,
            typename mpl::begin<Dimensions>::type
        >::type dimensions;
        // take the unit corresponding to each base unit
        // multiply each of its exponents by the exponent
        // of the base_dimension in the result and sum.
        typedef typename multiply_add_units<mpl::size<dimensions>::value>::template apply<
            typename mpl::begin<dimensions>::type,
            typename mpl::begin<typename base_solutions::type>::type
        >::type units;
        // Now, verify that the dummy units really
        // cancel out and remove them.
        typedef typename strip_zeroes_impl<base_solutions::extra>::template apply<units>::type type;
    };
};

template<class T, class Dimensions>
struct calculate_base_unit_exponents {
    typedef typename calculate_base_unit_exponents_impl<is_simple_system<T>::value>::template apply<T, Dimensions>::type type;
};

} // namespace detail

} // namespace units

} // namespace boost

#endif
