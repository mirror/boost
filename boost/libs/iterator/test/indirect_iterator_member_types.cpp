//  (C) Copyright Jeremy Siek 2004. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  Revision History
//  03 Jan 2004   Jeremy Siek
//       First draft.


#include <boost/config.hpp>
#include <iostream>

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/static_assert.hpp>
#include "static_assert_same.hpp"
#include <boost/type_traits/same_traits.hpp>

struct zow { };

struct my_ptr {
  typedef zow const element_type;
//  typedef const zow& reference;
//  typedef const zow* pointer;
//  typedef void difference_type;
//  typedef boost::no_traversal_tag iterator_category;
};

BOOST_TT_BROKEN_COMPILER_SPEC(my_ptr)
BOOST_TT_BROKEN_COMPILER_SPEC(zow)

#ifndef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
    
# define STATIC_ASSERT_SAME_POINTER(P1, P2)                         \
    STATIC_ASSERT_SAME(                                             \
        boost::remove_const<boost::remove_pointer<P1>::type>::type  \
      , boost::remove_const<boost::remove_pointer<P2>::type>::type  \
    )

#else
    
# define STATIC_ASSERT_SAME_POINTER(P1, P2) STATIC_ASSERT_SAME(P1,P2)
    
#endif
    
int main()
{
  {
    typedef boost::indirect_iterator<int**> Iter;
    STATIC_ASSERT_SAME(Iter::value_type, int);
    STATIC_ASSERT_SAME(Iter::reference, int&);  
    STATIC_ASSERT_SAME_POINTER(Iter::pointer, int*);  
    STATIC_ASSERT_SAME(Iter::difference_type, std::ptrdiff_t);
    
    BOOST_STATIC_ASSERT((boost::is_convertible<Iter::iterator_category,
			 std::random_access_iterator_tag>::value));
    BOOST_STATIC_ASSERT((boost::is_convertible<boost::iterator_traversal<Iter>::type,
			 boost::random_access_traversal_tag>::value));
  }
  {
    typedef boost::indirect_iterator<int const**> Iter;
    STATIC_ASSERT_SAME(Iter::value_type, int);
    STATIC_ASSERT_SAME(Iter::reference, const int&);
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))  // Borland drops const all over the place
    STATIC_ASSERT_SAME_POINTER(Iter::pointer, const int*);
#endif 
  }
  {
    typedef boost::indirect_iterator<int**, int> Iter;
    STATIC_ASSERT_SAME(Iter::value_type, int);
    STATIC_ASSERT_SAME(Iter::reference, int&);  
    STATIC_ASSERT_SAME_POINTER(Iter::pointer, int*);  
  }
  {
    typedef boost::indirect_iterator<int**, const int> Iter;
    STATIC_ASSERT_SAME(Iter::value_type, int);
    STATIC_ASSERT_SAME(Iter::reference, const int&);  
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))  // Borland drops const all over the place
    STATIC_ASSERT_SAME_POINTER(Iter::pointer, const int*);
#endif 
  }
  {
    typedef boost::indirect_iterator<my_ptr*> Iter;
    STATIC_ASSERT_SAME(Iter::value_type, zow);
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))  // Borland drops const all over the place
    STATIC_ASSERT_SAME(Iter::reference, const zow&);
    STATIC_ASSERT_SAME_POINTER(Iter::pointer, const zow*);  
#endif 
    STATIC_ASSERT_SAME(Iter::difference_type, std::ptrdiff_t);
    
    BOOST_STATIC_ASSERT((boost::is_convertible<Iter::iterator_category,
			 std::random_access_iterator_tag>::value));
    BOOST_STATIC_ASSERT((boost::is_convertible<boost::iterator_traversal<Iter>::type,
			 boost::random_access_traversal_tag>::value));
  }
  {
    typedef boost::indirect_iterator<char**, int, std::random_access_iterator_tag, long&, short> Iter;
    STATIC_ASSERT_SAME(Iter::value_type, int);
    STATIC_ASSERT_SAME(Iter::reference, long&);  
    STATIC_ASSERT_SAME_POINTER(Iter::pointer, int*);  
    STATIC_ASSERT_SAME(Iter::difference_type, short);  
  }
  return 0;
}
