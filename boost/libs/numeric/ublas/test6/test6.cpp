#ifdef BOOST_MSVC

#pragma warning (disable: 4355)
#pragma warning (disable: 4503)
#pragma warning (disable: 4786)

#endif

#include <iostream>

#include <boost/numeric/ublas/config.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "test6.hpp"

#ifdef BOOST_MSVC
// Standard new handler is not standard compliant.
#include <new.h>
int __cdecl std_new_handler (unsigned) {
    throw std::bad_alloc ();
}
#endif

int main () {
#ifdef BOOST_MSVC
    _set_new_handler (std_new_handler);
#endif
    test_vector ();
    test_matrix_vector ();
    test_matrix ();
    return 0;
}

