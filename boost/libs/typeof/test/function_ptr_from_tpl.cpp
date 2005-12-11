#include <boost/typeof/typeof.hpp>

void f()
{}

template<class T> 
class x
{
   typedef BOOST_TYPEOF(&::f) type;
};
