#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    banded_matrix<double> m (3, 3, 1, 1);
    for (signed i = 0; i < signed (m.size1 ()); ++ i)
        for (signed j = std::max (i - 1, 0); j < std::min (i + 2, signed (m.size2 ())); ++ j)
            m (i, j) = 3 * i + j;
    std::cout << m << std::endl;
}

