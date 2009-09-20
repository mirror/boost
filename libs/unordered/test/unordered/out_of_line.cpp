// Just a little test to see if out of line template methods are supported:

#include <boost/detail/lightweight_test.hpp>

template <class T>
struct foo {
    template <class U>
    bool bar(U x);
};

template <class T>
template <class U>
bool foo<T>::bar(U x) { return x ? true : false; }

int main() {
    foo<int> x;
    BOOST_TEST(x.bar(1));
    BOOST_TEST(!x.bar(0));
    
    return boost::report_errors();
}