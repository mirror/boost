#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    identity_matrix<double> m (3);
    std::cout << m << std::endl;
}

