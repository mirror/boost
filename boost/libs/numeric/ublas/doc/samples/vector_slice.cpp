#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    vector<double> v (3);
    vector_slice<vector<double> > vs (v, slice (0, 1, 3));
    for (unsigned i = 0; i < vs.size (); ++ i)
        vs (i) = i;
    std::cout << vs << std::endl;
}

