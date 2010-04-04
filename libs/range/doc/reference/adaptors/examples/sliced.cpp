#include <boost/range/adaptor/sliced.hpp>
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
    input += 1,2,3,4,5,6,7,8,9;
    
    boost::copy(
        input | sliced(2, 5),
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

