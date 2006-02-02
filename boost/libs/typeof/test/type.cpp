#include <boost/typeof/typeof.hpp>

namespace boost { namespace type_of {
    template<class T, class U> 
    struct test_wrapper{};
}}

namespace boost { namespace type_of { namespace { 

    template<class V , class P0 , class P1 > 
    struct encode_template_impl<V,boost::type_of::test_wrapper<  P0 , P1> > 
        : push_back<V, mpl::size_t<5 * 0x10000 + 33> > 
    { }; 
    template<class Iter> 
    struct decode_template_impl<mpl::size_t<5 * 0x10000 + 33>, Iter> 
    { 
        typedef int P0; 
        typedef int P1; 
        typedef boost::type_of::test_wrapper< int , int > type; 
        typedef Iter iter; 
    }; 
    template<class V , class P0 , class P1 > 
    struct encode_type_impl<V, boost::type_of::test_wrapper< P0 , P1> > 
    { 
        typedef typename push_back<V, boost::mpl::size_t<5 * 0x10000 + 33> >::type V0; 
        typedef typename encode_type< V0, P0 >::type V1; 
        typedef typename encode_type< V1, P1 >::type V2;   
        typedef V2 type; 
    }; 
    template<class Iter> 
    struct decode_type_impl<boost::mpl::size_t<5 * 0x10000 + 33>, Iter> 
    { 
        typedef Iter iter0; 
        typedef decode_type< iter0 > d0; 
        typedef typename d0::type P0; 
        typedef typename d0::iter iter1; 
        typedef decode_type< iter1 > d1; 
        typedef typename d1::type P1; 
        typedef typename d1::iter iter2;   
        typedef boost::type_of::test_wrapper< P0 , P1> type; 
        typedef iter2 iter; 
    }; 
}}}


/*
#include "test.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

struct A;
BOOST_TYPEOF_REGISTER_TYPE(A)

BOOST_STATIC_ASSERT(boost::type_of::test<A>::value);
*/
