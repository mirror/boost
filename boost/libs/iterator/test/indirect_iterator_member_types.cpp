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
#include <boost/type_traits/same_traits.hpp>

struct zow { };

struct my_ptr {
  typedef zow value_type;
  typedef const zow& reference;
  typedef const zow* pointer;
  typedef void difference_type;
  typedef boost::no_traversal_tag iterator_category;
};

int main()
{
  {
    typedef boost::indirect_iterator<int**> Iter;
    BOOST_STATIC_ASSERT((boost::is_same<Iter::value_type, int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<Iter::reference, int&>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::pointer, int*>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::difference_type, std::ptrdiff_t>::value));
    
    BOOST_STATIC_ASSERT((boost::is_convertible<Iter::iterator_category,
			 std::random_access_iterator_tag>::value));
    BOOST_STATIC_ASSERT((boost::is_convertible<boost::iterator_traversal<Iter>::type,
			 boost::random_access_traversal_tag>::value));
  }
  {
    typedef boost::indirect_iterator<int const**> Iter;
    BOOST_STATIC_ASSERT((boost::is_same<Iter::value_type, int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<Iter::reference, const int&>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::pointer, const int*>::value));  
  }
  {
    typedef boost::indirect_iterator<int**, int> Iter;
    BOOST_STATIC_ASSERT((boost::is_same<Iter::value_type, int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<Iter::reference, int&>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::pointer, int*>::value));  
  }
  {
    typedef boost::indirect_iterator<int**, const int> Iter;
    BOOST_STATIC_ASSERT((boost::is_same<Iter::value_type, int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<Iter::reference, const int&>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::pointer, const int*>::value));  
  }
  {
    typedef boost::indirect_iterator<my_ptr*> Iter;
    BOOST_STATIC_ASSERT((boost::is_same<Iter::value_type, zow>::value));
    BOOST_STATIC_ASSERT((boost::is_same<Iter::reference, const zow&>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::pointer, const zow*>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::difference_type, std::ptrdiff_t>::value));
    
    BOOST_STATIC_ASSERT((boost::is_convertible<Iter::iterator_category,
			 std::random_access_iterator_tag>::value));
    BOOST_STATIC_ASSERT((boost::is_convertible<boost::iterator_traversal<Iter>::type,
			 boost::random_access_traversal_tag>::value));
  }
  {
    typedef boost::indirect_iterator<char**, int, std::random_access_iterator_tag, long&, short> Iter;
    BOOST_STATIC_ASSERT((boost::is_same<Iter::value_type, int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<Iter::reference, long&>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::pointer, int*>::value));  
    BOOST_STATIC_ASSERT((boost::is_same<Iter::difference_type, short>::value));  
  }
}
