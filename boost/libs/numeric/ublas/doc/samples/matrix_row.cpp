#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> m (3, 3);
    for (unsigned i = 0; i < m.size1 (); ++ i) {
        matrix_row<matrix<double> > mr (m, i);
        for (unsigned j = 0; j < mr.size (); ++ j)
            mr (j) = 3 * i + j;
        std::cout << mr << std::endl;
    }
}

