#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    vector<double> v (3);
    vector_range<vector<double> > vr (v, range (0, 3));
    for (unsigned i = 0; i < vr.size (); ++ i)
        vr (i) = i;
    std::cout << vr << std::endl;
}

