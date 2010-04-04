#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    using namespace boost::adaptors;
    
    std::vector<boost::shared_ptr<int> > input;
    
    for (int i = 0; i < 10; ++i)
        input.push_back(boost::shared_ptr<int>(new int(i)));
        
    boost::copy(
        input | indirected,
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

