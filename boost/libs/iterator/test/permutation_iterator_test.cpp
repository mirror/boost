// (C) Copyright Toon Knapen    2001.
// (C) Copyright Roland Richter 2003.
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

#include <boost/config.hpp>
#include <boost/test/minimal.hpp>

#include <boost/iterator/permutation_iterator.hpp>

#include <vector>
#include <list>

#include <algorithm>


void permutation_test()
{
  // Example taken from documentation of old permutation_iterator.
  typedef std::vector< int > element_range_type;
  typedef std::list< int > index_type;

  const int element_range_size = 10;
  const int index_size = 4;

  element_range_type elements( element_range_size );
  for( element_range_type::iterator el_it = elements.begin(); el_it != elements.end(); ++el_it )
    { *el_it = std::distance(elements.begin(), el_it); }

  index_type indices( index_size );
  for( index_type::iterator i_it = indices.begin(); i_it != indices.end(); ++i_it )
    { *i_it = element_range_size - index_size + std::distance(indices.begin(), i_it); }
  std::reverse( indices.begin(), indices.end() );

#ifdef BOOST_MSVC

  typedef boost::permutation_iterator< element_range_type::iterator
                                     , index_type::iterator
                                     , boost::use_default
                                     , boost::use_default
                                     , element_range_type::reference > permutation_type;

  permutation_type begin( elements.begin(), indices.begin() );
  permutation_type it = begin;
  permutation_type end( elements.begin(), indices.end() );

#else

  typedef boost::permutation_iterator< element_range_type::iterator, index_type::iterator > permutation_type;
  permutation_type begin = boost::make_permutation_iterator( elements.begin(), indices.begin() );
  permutation_type it = begin;
  permutation_type end = boost::make_permutation_iterator( elements.begin(), indices.end() );

#endif

  BOOST_CHECK( it == begin );
  BOOST_CHECK( it != end );

  BOOST_CHECK( std::distance( begin, end ) == index_size );

  for( index_type::iterator i_it = indices.begin(); it != end; ++i_it, ++it )
  {
    BOOST_CHECK( *it == elements[ *i_it ] );
  }

  it = begin;
  for( int i = 0; i < index_size ; i+=2, it+=2 ) 
  {
    index_type::iterator i_it = indices.begin(); std::advance( i_it, i );
    BOOST_CHECK( *it == elements[ *i_it ] );
  }


  it = begin + (index_size);
  BOOST_CHECK( it != begin );
  for( index_type::iterator i_it = --indices.end(); it-- != begin; --i_it ) 
  {
    BOOST_CHECK( *it == elements[ *i_it ] );
  }
  
  it = begin + (index_size - 1);
  for( int i = 0; i < index_size; i+=2, it-=2 ) 
  {
    index_type::iterator i_it = --indices.end(); std::advance( i_it, -i );
    BOOST_CHECK( *it == elements[ *i_it ] );
  }

}


int test_main(int, char *[])
{
  permutation_test();

  bool error_on_purpose = false;
  //BOOST_CHECK( error_on_purpose );

  return 0;
}
