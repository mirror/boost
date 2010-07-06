#include <boost/functional/hash.hpp>
#include <boost/shared_ptr.hpp>

// This should obviously pass if shared_ptr ever supports Boost.Hash.

int main() {
    boost::hash<boost::shared_ptr<int> > hash;
    boost::shared_ptr<int> x(new int(10));
    
    hash(x);
}