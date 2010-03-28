#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

struct is_even
{
    bool operator()(int x) const { return x % 2 == 0; }
};

int main(int argc, const char* argv[])
{
    using namespace boost::assign;
    using namespace boost::adaptors;
    
    std::vector<int> input;
    input += 1,2,3,4,5,6,7,8,9;
    
    boost::copy(
        input | filtered(is_even()),
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

