#include <boost/numeric/ublas/storage.hpp>

int main () {
    using namespace boost::numeric::ublas;
    range r (0, 3);
    for (unsigned i = 0; i < r.size (); ++ i) {
        std::cout << r (i) << std::endl;
    }
}

