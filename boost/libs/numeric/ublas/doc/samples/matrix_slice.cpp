#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> m (3, 3);
    matrix_slice<matrix<double> > ms (m, slice (0, 1, 3), slice (0, 1, 3));
    for (unsigned i = 0; i < ms.size1 (); ++ i)
        for (unsigned j = 0; j < ms.size2 (); ++ j)
            ms (i, j) = 3 * i + j;
    std::cout << ms << std::endl;
}

