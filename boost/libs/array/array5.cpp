/* simple example for using class array<>
 */
#include <iostream>
#include <boost/array.hpp>

template <typename T>
void test_static_size (const T& cont)
{
    int tmp[T::static_size];
    for (unsigned i=0; i<T::static_size; ++i) {
        tmp[i] = int(cont[i]);
    }
    for (unsigned i=0; i<T::static_size; ++i) {
        std::cout << tmp[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    // define special type name
    typedef boost::array<float,6> Array;

    // create and initialize an array
    const Array a = { { 42.42 } };

    // use some common STL container operations
    std::cout << "static_size: " << a.size() << std::endl;
    std::cout << "size:        " << a.size() << std::endl;
    std::cout << "empty:       " << std::boolalpha << a.empty() << std::endl;
    std::cout << "max_size:    " << a.max_size() << std::endl;
    std::cout << "front:       " << a.front() << std::endl;
    std::cout << "back:        " << a.back() << std::endl;
    std::cout << "[0]:         " << a[0] << std::endl;
    std::cout << "elems:       ";

    // iterate through all elements
    for (Array::const_iterator pos=a.begin(); pos<a.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
    test_static_size(a);

    // check copy constructor and assignment operator
    Array b(a);
    Array c;
    c = a;
    if (a==b && a==c) {
        std::cout << "copy construction and copy assignment are OK"
	          << std::endl;
    }
    else {
        std::cout << "copy construction and copy assignment are OK"
	          << std::endl;
    }

    typedef boost::array<double,6> DArray;
    typedef boost::array<int,6> IArray;
    IArray ia = { 1, 2, 3, 4, 5, 6 };
    DArray da;
    da = ia;
    da.assign(42);
    return 0;
}

