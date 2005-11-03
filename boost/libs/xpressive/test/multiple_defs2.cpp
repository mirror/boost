#include <boost/xpressive/xpressive.hpp>

int f()
{
    using namespace boost::xpressive;
    sregex srx = +_;
    sregex drx = sregex::compile(".+");

    return 0;
}
