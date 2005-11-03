#include <boost/xpressive/xpressive.hpp>
extern int f();
int main()
{
    using namespace boost::xpressive;
    sregex srx = +_;
    sregex drx = sregex::compile(".+");
    return f();
}
