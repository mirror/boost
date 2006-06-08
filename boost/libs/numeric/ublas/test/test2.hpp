//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Permission to use, copy, modify, distribute and sell this software
//  and its documentation for any purpose is hereby granted without fee,
//  provided that the above copyright notice appear in all copies and
//  that both that copyright notice and this permission notice appear
//  in supporting documentation.  The authors make no representations
//  about the suitability of this software for any purpose.
//  It is provided "as is" without express or implied warranty.
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef TEST2_H
#define TEST2_H

#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/blas.hpp>

namespace ublas = boost::numeric::ublas;

#include "common/init.hpp"

template<class V, int N>
struct test_blas_1 {
    typedef typename V::value_type value_type;
    typedef typename ublas::type_traits<value_type>::real_type real_type;

    void test ();
};

template<class V, class M, int N>
struct test_blas_2 {
    typedef typename V::value_type value_type;

    void test ();
};

template<class M, int N>
struct test_blas_3 {
    typedef typename M::value_type value_type;

    void test ();
};


#endif
