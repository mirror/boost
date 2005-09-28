#include <boost/typeof/typeof.hpp>

struct foo
{
    typedef BOOST_TYPEOF(1 + 2.5) type;
};

namespace
{
    typedef foo::type type;
}
