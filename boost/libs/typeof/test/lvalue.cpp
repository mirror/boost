#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

struct x{};
BOOST_TYPEOF_REGISTER_TYPE(x)

x n;
const x cn = n;
x& rn = n;
const x& rcn = cn;
x f();
const x cf();
x& rf();
const x& rcf();

BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(n), x&>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cn), const x&>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rn), x&>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcn), const x&>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(f()), x>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rf()), x&>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcf()), const x&>::value));
BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cf()), const x&>::value));
