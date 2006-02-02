//#undef BOOST_TYPEOF_COMPLIANT
#include <boost/typeof/typeof.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/function_traits.hpp>

namespace boost { namespace type_of {

#ifdef BOOST_TYPEOF_EMULATION

    template<class T> 
    typename enable_if<
        is_function<T>, 
        sizer<typename encode_type<BOOST_TYPEOF_VECTOR(0)<>, T*>::type>
    >::type encode(T*);

#else

    template<typename T>
    char (*encode_start(T*))[encode_type<T*>::value];

#endif

}}

void f()
{}

template<class T> 
class x
{
   typedef BOOST_TYPEOF(&::f) type;
};
