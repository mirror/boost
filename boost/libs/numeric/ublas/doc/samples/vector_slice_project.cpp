#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    vector<double> v (3);
    for (int i = 0; i < 3; ++ i)
        project (v, slice (0, 1, 3)) (i) = i;
    std::cout << project (v, slice (0, 1, 3)) << std::endl;
}

