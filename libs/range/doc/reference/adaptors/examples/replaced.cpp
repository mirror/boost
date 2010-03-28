#include <boost/range/adaptor/replaced.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    using namespace boost::adaptors;
    using namespace boost::assign;
    
    std::vector<int> input;
    input += 1,2,3,2,5,2,7,2,9;
    
    boost::copy(
        input | replaced(2, 10),
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

