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
#include <boost/numeric/ublas/io.hpp>

#include <boost/numeric/ublas/blas.hpp>

#include "test2.hpp"

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

    std::cout << "test_blas_1" << std::endl;

    std::cout << "float" << std::endl;
    test_blas_1<ublas::vector<float>, 3> () ();

    std::cout << "double" << std::endl;
    test_blas_1<ublas::vector<double>, 3> () ();

#ifdef USE_STD_COMPLEX
    std::cout << "std::complex<float>" << std::endl;
    test_blas_1<ublas::vector<std::complex<float> >, 3> () ();

    std::cout << "std::complex<double>" << std::endl;
    test_blas_1<ublas::vector<std::complex<double> >, 3> () ();
#endif

    std::cout << "test_blas_2" << std::endl;

    std::cout << "float" << std::endl;
    test_blas_2<ublas::vector<float>, ublas::matrix<float>, 3> () ();

    std::cout << "double" << std::endl;
    test_blas_2<ublas::vector<double>, ublas::matrix<double>, 3> () ();

#ifdef USE_STD_COMPLEX
    std::cout << "std::complex<float>" << std::endl;
    test_blas_2<ublas::vector<std::complex<float> >, ublas::matrix<std::complex<float> >, 3> () ();

    std::cout << "std::complex<double>" << std::endl;
    test_blas_2<ublas::vector<std::complex<double> >, ublas::matrix<std::complex<double> >, 3> () ();
#endif

    std::cout << "float" << std::endl;
    test_blas_3<ublas::matrix<float>, 3> () ();

    std::cout << "double" << std::endl;
    test_blas_3<ublas::matrix<double>, 3> () ();

#ifdef USE_STD_COMPLEX
    std::cout << "std::complex<float>" << std::endl;
    test_blas_3<ublas::matrix<std::complex<float> >, 3> () ();

    std::cout << "std::complex<double>" << std::endl;
    test_blas_3<ublas::matrix<std::complex<double> >, 3> () ();
#endif
    return 0;
}

