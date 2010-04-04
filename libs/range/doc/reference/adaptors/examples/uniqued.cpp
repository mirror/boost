#include <boost/range/adaptor/uniqued.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    using namespace boost::assign;
    using namespace boost::adaptors;
    
    std::vector<int> input;
    input += 1,1,2,2,2,3,4,5,6;
    
    boost::copy(
        input | uniqued,
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

