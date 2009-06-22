
//  (C) Copyright Thorsten Ottosen 2009. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"
#ifdef TEST_STD
#  include <type_traits>
#  include <boost/type_traits/type_with_alignment.hpp> // max_align and long_long_type
#else
#  include <boost/type_traits/alignment_of.hpp>
#  include <boost/type_traits/aligned_storage.hpp>
#  include <boost/type_traits/is_pod.hpp>
#endif


namespace
{
    template< unsigned N, unsigned Alignment >
    struct alignment_implementation1
    {
        boost::detail::aligned_storage::aligned_storage_imp<N,Alignment> type;
        const void* address() const { return this; }
    };
    
    template< unsigned N, unsigned Alignment >
    struct alignment_implementation2 : 
#ifndef __BORLANDC__
       private 
#else
       public
#endif
       boost::detail::aligned_storage::aligned_storage_imp<N,Alignment>
    {
        typedef boost::detail::aligned_storage::aligned_storage_imp<N,Alignment> type;
        const void* address() const { return static_cast<const type*>(this)->address(); }
    };
    
    template< unsigned N, class T >
    const void* get_address1()
    {
        alignment_implementation1<N*sizeof(T), tt::alignment_of<T>::value> imp1;
        return imp1.address();
    }

    template< unsigned N, class T >
    const void* get_address2()
    {
        alignment_implementation2<N*sizeof(T), tt::alignment_of<T>::value> imp2;
        return imp2.address();
    }

    template< class T >
    void check()
    {
        const void* addr1 = get_address1<0,T>();
        const void* addr2 = get_address2<0,T>();
        //
        // @remark: only the empty case differs
        //
        BOOST_CHECK( addr1 != addr2 );
        
        addr1 = get_address1<1,T>();
        addr2 = get_address2<1,T>();
        BOOST_CHECK( addr1 == addr2 );

        addr1 = get_address1<2,T>();
        addr2 = get_address2<2,T>();
        BOOST_CHECK( addr1 == addr2 );

        addr1 = get_address1<3,T>();
        addr2 = get_address2<3,T>();
        BOOST_CHECK( addr1 == addr2 );

        addr1 = get_address1<4,T>();
        addr2 = get_address2<4,T>();
        BOOST_CHECK( addr1 == addr2 );

        addr1 = get_address1<17,T>();
        addr2 = get_address2<17,T>();
        BOOST_CHECK( addr1 == addr2 );

        addr1 = get_address1<32,T>();
        addr2 = get_address2<32,T>();
        BOOST_CHECK( addr1 == addr2 );
    }
}

TT_TEST_BEGIN(type_with_empty_alignment_buffer)

check<char>();
check<short>();
check<int>();
check<long>();
check<float>();
check<double>();
check<long double>();

#ifdef BOOST_HAS_MS_INT64
check<__int64>();
#endif

check<int(*)(int)>();
check<int*>();
check<VB>();
check<VD>();
check<enum_UDT>();
check<mf2>();
check<POD_UDT>();
check<empty_UDT>();
check<union_UDT>();
check<boost::detail::max_align>();

TT_TEST_END









