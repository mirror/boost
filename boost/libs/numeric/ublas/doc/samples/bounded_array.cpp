#include <boost/numeric/ublas/storage.hpp>

int main () {
    using namespace boost::numeric::ublas;
    bounded_array<double, 3> a (3);
    for (unsigned i = 0; i < a.size (); ++ i) {
        a [i] = i;
        std::cout << a [i] << std::endl;
    }
}

