#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> m1 (3, 3), m2 (3, 3);
    for (unsigned i = 0; i < std::min (m1.size1 (), m2.size1 ()); ++ i)
        for (unsigned j = 0; j <= i; ++ j)
            m1 (i, j) = m2 (i, j) = 3 * i + j + 1;

    std::cout << solve (m1, m2, lower_tag ()) << std::endl;
}

