#include <boost/numeric/ublas/storage.hpp>

int main () {
    using namespace boost::numeric::ublas;
    slice s (0, 1, 3);
    for (unsigned i = 0; i < s.size (); ++ i) {
        std::cout << s (i) << std::endl;
    }
}

