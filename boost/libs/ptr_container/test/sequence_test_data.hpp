 
#include "test_data.hpp"
#include <boost/range/iterator_range.hpp>
#include <boost/ptr_container/ptr_predicate.hpp>
#include <boost/bind.hpp>

template< typename C, typename B, typename T >
void reversible_container_test();

template< typename C, typename B, typename T >
void reversible_container_test()
{

    BOOST_MESSAGE( "starting reversible container test" ); 
    enum { max_cnt = 10, size = 100 };
    C  c;
    BOOST_CHECK( c.size() == 0 );
    c.push_back( new T );
    BOOST_CHECK( c.size() == 1 );
    
    const C c2( c.clone() );
    BOOST_CHECK( c2.size() == c.size() );
    
    C  c3( c.begin(), c.end() );
    BOOST_CHECK( c.size() == c3.size() );
    
    c.assign( c3.begin(), c3.end() );
    BOOST_CHECK( c.size() == c3.size() );
        
    c.assign( c3 );
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
    hide_warning(s);
    BOOST_DEDUCED_TYPENAME C::size_type s2                = c.max_size();
    hide_warning(s2);
    c.push_back( new T );
    bool b                                                = c.empty();
    BOOST_CHECK( !c.empty() );
    b                                                     = is_null( c.begin() );
    BOOST_CHECK( b == false );
    BOOST_DEDUCED_TYPENAME C::reference r                 = c.front();
    hide_warning(r);
    BOOST_DEDUCED_TYPENAME C::const_reference cr          = c2.front();
    hide_warning(cr);
    BOOST_DEDUCED_TYPENAME C::reference r2                = c.back();
    hide_warning(r2);
    BOOST_DEDUCED_TYPENAME C::const_reference cr2         = c2.back();
    hide_warning(cr2);
    BOOST_MESSAGE( "finished accessors test" ); 
    
    c.push_back( new T );

    c.pop_back(); 
    c.insert( c.end(), new T );

#ifdef BOOST_NO_SFINAE
#else
    c.insert( c.end(), c3 );
#endif    
    c3.insert( c3.end(), c.begin(), c.end() ); 
    c.erase( c.begin() );
    c3.erase( c3.begin(), c3.end() );
    BOOST_CHECK( c3.empty() );
    c.swap( c3 );
    BOOST_CHECK( !c3.empty() );
    c3.clear();
    BOOST_CHECK( c3.empty() );
    C c4;
    c4.swap(c3);
    swap(c4,c3);
    BOOST_MESSAGE( "finished modifiers test" ); 
             
    c.push_back( new T ); c.push_back( new T ); c.push_back( new T ); 
    typedef BOOST_DEDUCED_TYPENAME C::auto_type auto_type;
    
    auto_type ptr       = c.release( c.begin() );
    std::auto_ptr<C> ap = c.release();
    c                   = c2.clone();
    BOOST_CHECK( !c.empty() );
    auto_type ptr2      = c.replace(c.begin(), new T );
    BOOST_MESSAGE( "finished release/clone/replace test" ); 
                     
    c3.push_back( new T );
    c3.push_back( new T );
    c3.push_back( new T );
    c.transfer( c.begin(), c3.begin(), c3 );
    c.transfer( c.end(), c3.begin(), c3.end(), c3 );
#ifdef BOOST_NO_SFINAE
#else    
    c.transfer( c.end(), boost::make_iterator_range( c3 ), c3 );    
    BOOST_CHECK( c3.empty() );
    BOOST_CHECK( !c.empty() );
#endif    
    c3.transfer( c3.begin(), c );
    BOOST_CHECK( !c3.empty() );
    BOOST_CHECK( c.empty() );
    BOOST_MESSAGE( "finished transfer test" ); 

}

