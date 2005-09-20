#include "test.hpp"
#include <boost/noncopyable.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

struct x : boost::noncopyable
{
    void foo() {}
    void bar() const {}
};

BOOST_TYPEOF_REGISTER_TYPE(x)

x& make_ref()
{
    static x result;
    return result;
}

const x& make_const_ref()
{
    static x result;
    return result;
}

void foo()
{
    BOOST_AUTO(& v1, make_ref());
    v1.foo();

    BOOST_AUTO(const& v2, make_const_ref());
    v2.bar();
}
