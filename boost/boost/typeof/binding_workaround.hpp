#ifndef BOOST_TYPEOF_BINDING_WORKAROUND_HPP_INCLUDED
#define BOOST_TYPEOF_BINDING_WORKAROUND_HPP_INCLUDED

// workarounds related to inability to bind to const T& 

/* 
MSVC 7.1-, from inside a template,
can't bind a function pointer to const T& 
*/

#if BOOST_WORKAROUND(BOOST_MSVC,==1310) && defined(BOOST_TYPEOF_EMULATION)

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/detail/workaround.hpp>

namespace boost { namespace type_of {

    template<class T> 
        sizer<typename encode_type<BOOST_TYPEOF_VECTOR(0)<>, T*>::type> encode(T*, 
        typename enable_if<typename is_function<T>::type>::type* = 0);

}}

#elif BOOST_WORKAROUND(BOOST_MSVC,<=1310) && defined(BOOST_TYPEOF_NATIVE)

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/detail/workaround.hpp>

namespace boost { namespace type_of {

    template<typename T>
        char (*encode_start(T*, 
        typename enable_if<typename is_function<T>::type>::type* = 0))[encode_type<T*>::value];

}}

#endif

//

#endif//BOOST_TYPEOF_BINDING_WORKAROUND_HPP_INCLUDED
