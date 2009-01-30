
#line 1173 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>
#include <iostream>
using namespace boost::parameter;
#line 1162 "../../../../libs/parameter/doc/index.rst"
BOOST_PARAMETER_NAME(arg1)

struct somebody
{
    BOOST_PARAMETER_MEMBER_FUNCTION(
        (void), static f, tag, (optional (arg1,(int),0)))
    {
        std::cout << arg1 << std::endl;
    }
};
