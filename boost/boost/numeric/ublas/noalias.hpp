//
// Copyright (c) 2004 Michael Stevens
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_UBLAS_NOALIAS_H
#define BOOST_UBLAS_NOALIAS_H

namespace boost { namespace numeric { namespace ublas {

    // Assignment proxy.
    // Provides temporary free assigment when LHS has no alias on RHS
    template<class C>
    class noalias_proxy:
        private nonassignable {
    public:
        typedef typename C::closure_type closure_type;

        BOOST_UBLAS_INLINE
        noalias_proxy (C& lval):
            nonassignable (), lval_ (lval) {}
        BOOST_UBLAS_INLINE
        noalias_proxy (const noalias_proxy& p):
            nonassignable (), lval_ (p.lval_) {}

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator= (const E& e) {
            lval_.assign (e);
            return lval_;
        }

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator+= (const E& e) {
            lval_.plus_assign (e);
            return lval_;
        }

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator-= (const E& e) {
            lval_.minus_assign (e);
            return lval_;
        }

    private:
        closure_type lval_;
    };

    // Improve syntax of effcient assignment where no aliases of LHS appear on the RHS
    //  noalias(lhs) = rhs_expression
    template <class C>
    BOOST_UBLAS_INLINE
    noalias_proxy<C> noalias (C& lvalue) {
        return noalias_proxy<C> (lvalue);
    }
    template <class C>
    BOOST_UBLAS_INLINE
    noalias_proxy<const C> noalias (const C& lvalue) {
        return noalias_proxy<const C> (lvalue);
    }

}}}

#endif
