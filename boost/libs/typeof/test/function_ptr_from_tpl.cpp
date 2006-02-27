#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

void f()
{}

template<class T> 
struct tpl
{
    typedef BOOST_TYPEOF_TPL(&f) type;
};

typedef void(*fun_type)();
 
BOOST_STATIC_ASSERT((boost::is_same<tpl<void>::type, fun_type>::value));
