#include <boost/numeric/ublas/storage_sparse.hpp>

int main () {
    using namespace boost::numeric::ublas;
    map_array<int, double> a (3);
    for (unsigned i = 0; i < a.size (); ++ i) {
        a [i] = i;
        std::cout << a [i] << std::endl;
    }
}

