
#include "test_data.hpp"
#include <boost/ptr_container/exception.hpp>
#include <boost/range/sub_range.hpp>

template< typename C, typename B, typename T >
void ptr_set_test();

template< typename C, typename B, typename T >
void ptr_set_test()
{   
    using namespace boost;
    
    BOOST_MESSAGE( "starting associative container test" ); 
    enum { max_cnt = 10, size = 100 };
    C  c;
    BOOST_CHECK( c.size() == 0 );
    
    const C c2( c.begin(), c.end() );
    BOOST_CHECK( c.size() == c2.size() );
    
    C c3;
    
    BOOST_MESSAGE( "finished construction test" ); 
                 
    BOOST_DEDUCED_TYPENAME C::allocator_type alloc        = c.get_allocator();
    BOOST_DEDUCED_TYPENAME C::iterator i                  = c.begin();
    BOOST_DEDUCED_TYPENAME C::const_iterator ci           = c2.begin();
    BOOST_DEDUCED_TYPENAME C::iterator i2                 = c.end();
    BOOST_DEDUCED_TYPENAME C::const_iterator ci2          = c2.begin();
    BOOST_DEDUCED_TYPENAME C::reverse_iterator ri         = c.rbegin();
    BOOST_DEDUCED_TYPENAME C::const_reverse_iterator cri  = c2.rbegin();
    BOOST_DEDUCED_TYPENAME C::reverse_iterator rv2        = c.rend();
    BOOST_DEDUCED_TYPENAME C::const_reverse_iterator cvr2 = c2.rend();
                             
    BOOST_DEDUCED_TYPENAME C::ptr_iterator ptr_i                  = c.ptr_begin();
    BOOST_DEDUCED_TYPENAME C::ptr_const_iterator ptr_ci           = c2.ptr_begin();
    BOOST_DEDUCED_TYPENAME C::ptr_iterator ptr_i2                 = c.ptr_end();
    BOOST_DEDUCED_TYPENAME C::ptr_const_iterator ptr_ci2          = c2.ptr_begin();
    BOOST_DEDUCED_TYPENAME C::ptr_reverse_iterator ptr_ri         = c.ptr_rbegin();
    BOOST_DEDUCED_TYPENAME C::ptr_const_reverse_iterator ptr_cri  = c2.ptr_rbegin();
    BOOST_DEDUCED_TYPENAME C::ptr_reverse_iterator ptr_rv2        = c.ptr_rend();
    BOOST_DEDUCED_TYPENAME C::ptr_const_reverse_iterator ptr_cvr2 = c2.ptr_rend();
        
    BOOST_MESSAGE( "finished iterator test" ); 
   
    BOOST_DEDUCED_TYPENAME C::size_type s                 = c.size();
    BOOST_DEDUCED_TYPENAME C::size_type s2                = c.max_size();
    BOOST_CHECK_EQUAL( c.size(), s );
    bool b                                                = c.empty();
    BOOST_MESSAGE( "finished accessors test" ); 
    
    T* t = new T;
    c.insert( c.end(), t );    
//    c.insert( c.end(), T() ); 
    c.insert( new T ); 
    c3.insert( c.begin(), c.end() ); 
    c.erase( c.begin() );
    c3.erase( c3.begin(), c3.end() );
    
    BOOST_CHECK( c3.empty() );
    c.swap( c3 );
    BOOST_CHECK( !c3.empty() );
    c3.clear();
    BOOST_CHECK( c3.empty() );
    BOOST_MESSAGE( "finished modifiers test" ); 
             
    c.insert( c.end(), new T );
    typename C::auto_type ptr2  = c.release( c.begin() );
    std::auto_ptr<C> ap         = c.release();
    c                           = c2.clone();
    BOOST_MESSAGE( "finished release/clone test" ); 

    c3.insert( new T );
    c3.insert( new T );
    BOOST_CHECK_EQUAL( c3.size(), 2u );
    c.transfer( c3.begin(), c3 );
    BOOST_CHECK( c3.empty() == false );
    c.transfer( c3.begin(), c3.end(), c3 );
    BOOST_CHECK( c3.empty() );
    BOOST_CHECK( !c.empty() );
    c3.transfer( c );
    BOOST_CHECK( !c3.empty() );
    BOOST_CHECK( c.empty() );
    BOOST_MESSAGE( "finished transfer test" );         
  
    C c4;
    c4.swap(c3);
    swap(c4,c3); 
    BOOST_MESSAGE( "finished set/map interface test" );         
    
    sub_range<C>        sub;
    sub_range<const C> csub;
    
    i  = c.find( T() );
    ci = c2.find( T() );
    c2.count( T() );
    i  = c.lower_bound( T() );
    ci = c2.lower_bound( T() );
    i  = c.upper_bound( T() );
    ci = c2.upper_bound( T() );
    sub  = c.equal_range( T() );
    csub = c2.equal_range( T() );         

    //BOOST_CHECK_THROW( c.at( T() ), bad_ptr_container_operation );
    //BOOST_CHECK_THROW( c2.at( T() ), bad_ptr_container_operation );

    try
    {
        c.at( T() );
    }
    catch( const bad_ptr_container_operation& )
    { }

    try
    {
        c2.at( T() );
    }
    catch( const bad_ptr_container_operation& )
    { }

    
    BOOST_MESSAGE( "finished algorithms interface test" );         
}

