/* example for using class array<>
 */
#include <algorithm>
#include <functional>
#include <boost/array.hpp>
#include "print.hpp"
using namespace std;
using namespace boost;

int main()
{
    // create and initialize array
    array<int,10> a = { { 1, 2, 3, 4, 5 } };

    PRINT_ELEMENTS(a);

    // modify elements directly
    for (unsigned i=0; i<a.size(); ++i) {
        ++a[i];
    }
    PRINT_ELEMENTS(a);

    // change order using an STL algorithm
    reverse(a.begin(),a.end());
    PRINT_ELEMENTS(a);

    // negate elements using STL framework
    transform(a.begin(),a.end(),    // source
              a.begin(),            // destination
              negate<int>());       // operation
    PRINT_ELEMENTS(a);
}

