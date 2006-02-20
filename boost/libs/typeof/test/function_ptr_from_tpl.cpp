#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

void f()
{}

template<class T> 
class x
{
    BOOST_STATIC_ASSERT((
        boost::is_same<BOOST_TYPEOF_TPL(&f), void(*)()>::value
        ));
};
