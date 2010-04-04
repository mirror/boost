#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main(int argc, const char* argv[])
{
    using namespace boost::assign;
    using namespace boost::adaptors;
    
    std::map<int, int> input;
    for (int i = 0; i < 10; ++i)
        input.insert(std::make_pair(i, i * 10));
        
    boost::copy(
        input | map_values,
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

