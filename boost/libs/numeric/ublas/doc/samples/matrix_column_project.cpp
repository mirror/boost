#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> m (3, 3);
    for (unsigned j = 0; j < m.size2 (); ++ j) {
        for (unsigned i = 0; i < m.size1 (); ++ i)
            column (m, j) (i) = 3 * i + j;
        std::cout << column (m, j) << std::endl;
    }
}

