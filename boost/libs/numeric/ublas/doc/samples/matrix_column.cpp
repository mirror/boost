#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> m (3, 3);
    for (unsigned j = 0; j < m.size2 (); ++ j) {
        matrix_column<matrix<double> > mc (m, j);
        for (unsigned i = 0; i < mc.size (); ++ i)
            mc (i) = 3 * i + j;
        std::cout << mc << std::endl;
    }
}

