// (C) Copyright Jeremy Siek 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_CONCEPTS_HPP
#define BOOST_ITERATOR_CONCEPTS_HPP

//  Revision History
//  26 Apr 2003 thw
//       Adapted to new iterator concepts
//  22 Nov 2002 Thomas Witt
//       Added interoperable concept.

#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_categories.hpp>

// Use boost::detail::iterator_traits to work around some MSVC/Dinkumware problems.
#include <boost/detail/iterator.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>

#include <boost/static_assert.hpp>

// Use boost/limits to work around missing limits headers on some compilers
#include <boost/limits.hpp>
#include <boost/config.hpp>

#include <algorithm>

namespace boost_concepts
{
  // Used a different namespace here (instead of "boost") so that the
  // concept descriptions do not take for granted the names in
  // namespace boost.

  //===========================================================================
  // Iterator Access Concepts

  template <typename Iterator>
  struct ReadableIteratorConcept
    : boost::AssignableConcept<Iterator>
    , boost::CopyConstructibleConcept<Iterator>

  {
      typedef BOOST_DEDUCED_TYPENAME boost::detail::iterator_traits<Iterator>::value_type value_type;
      typedef BOOST_DEDUCED_TYPENAME boost::detail::iterator_traits<Iterator>::reference reference;

      ~ReadableIteratorConcept()
      {

          value_type v = *i;
          boost::ignore_unused_variable_warning(v);
      }
  private:
      Iterator i;
  };
  
  template <
      typename Iterator
    , typename ValueType = BOOST_DEDUCED_TYPENAME boost::detail::iterator_traits<Iterator>::value_type
  >
  struct WritableIteratorConcept
    : boost::CopyConstructibleConcept<Iterator>
  {
      ~WritableIteratorConcept()
      {
          *i = v;
      }
  private:
      ValueType v;
      Iterator i;
  };
  
  template <typename Iterator>
  struct SwappableIteratorConcept
  {
      ~SwappableIteratorConcept()
      {
          std::iter_swap(i1, i2);
      }
  private:
      Iterator i1;
      Iterator i2;
  };

  template <typename Iterator>
  struct LvalueIteratorConcept
  {
      typedef typename boost::detail::iterator_traits<Iterator>::value_type value_type;
      
      ~LvalueIteratorConcept()
      {
        value_type& r = const_cast<value_type&>(*i);
        boost::ignore_unused_variable_warning(r);
      }
  private:
      Iterator i;
  };

  
  //===========================================================================
  // Iterator Traversal Concepts

  template <typename Iterator>
  struct IncrementableIteratorConcept
    : boost::AssignableConcept<Iterator>
    , boost::CopyConstructibleConcept<Iterator>
  {
      typedef typename boost::iterator_traversal<Iterator>::type traversal_category;

      ~IncrementableIteratorConcept()
      {
          BOOST_CONCEPT_ASSERT((
            boost::ConvertibleConcept<
                traversal_category
              , boost::incrementable_traversal_tag
            >));

          ++i;
          (void)i++;
      }
  private:
      Iterator i;
  };

  template <typename Iterator>
  struct SinglePassIteratorConcept
    : IncrementableIteratorConcept<Iterator>
    , boost::EqualityComparableConcept<Iterator>

  {
      ~SinglePassIteratorConcept()
      {
          BOOST_CONCEPT_ASSERT((
              boost::ConvertibleConcept<
                 BOOST_DEDUCED_TYPENAME SinglePassIteratorConcept::traversal_category
               , boost::single_pass_traversal_tag
              > ));
      }
  };

  template <typename Iterator>
  struct ForwardTraversalConcept
    : SinglePassIteratorConcept<Iterator>
    , boost::DefaultConstructibleConcept<Iterator>
  {
      typedef typename boost::detail::iterator_traits<Iterator>::difference_type difference_type;
      
      ~ForwardTraversalConcept()
      {
          BOOST_MPL_ASSERT((boost::is_integral<difference_type>));
          BOOST_MPL_ASSERT_RELATION(std::numeric_limits<difference_type>::is_signed, ==, true);
          
          BOOST_CONCEPT_ASSERT((
              boost::ConvertibleConcept<
                 BOOST_DEDUCED_TYPENAME ForwardTraversalConcept::traversal_category
               , boost::forward_traversal_tag
              > ));
    }
  };
  
  template <typename Iterator>
  struct BidirectionalTraversalConcept
    : ForwardTraversalConcept<Iterator>
  {
      ~BidirectionalTraversalConcept()
      {
          BOOST_CONCEPT_ASSERT((
              boost::ConvertibleConcept<
                 BOOST_DEDUCED_TYPENAME BidirectionalTraversalConcept::traversal_category
               , boost::bidirectional_traversal_tag
              > ));
          
          --i;
          (void)i--;
      }
   private:
      Iterator i;
  };

  template <typename Iterator>
  struct RandomAccessTraversalConcept
    : BidirectionalTraversalConcept<Iterator>
  {
   public:
      ~RandomAccessTraversalConcept()
      {
          BOOST_CONCEPT_ASSERT((
              boost::ConvertibleConcept<
                 BOOST_DEDUCED_TYPENAME RandomAccessTraversalConcept::traversal_category
               , boost::random_access_traversal_tag
              > ));
          
          i += n;
          i = i + n;
          i = n + i;
          i -= n;
          i = i - n;
          n = i - j;
      }
      
   private:
      typename BidirectionalTraversalConcept<Iterator>::difference_type n;
      Iterator i, j;
  };

  //===========================================================================
  // Iterator Interoperability Concept

  namespace detail
  {
    template <typename Iterator1, typename Iterator2>
    void interop_single_pass_constraints(Iterator1 const& i1, Iterator2 const& i2)
    {
        bool b;
        b = i1 == i2;
        b = i1 != i2;

        b = i2 == i1;
        b = i2 != i1;
        boost::ignore_unused_variable_warning(b);
    }

    template <typename Iterator1, typename Iterator2>
    void interop_rand_access_constraints(
        Iterator1 const& i1, Iterator2 const& i2,
        boost::random_access_traversal_tag, boost::random_access_traversal_tag)
    {
        bool b;
        typename boost::detail::iterator_traits<Iterator2>::difference_type n;
        b = i1 <  i2;
        b = i1 <= i2;
        b = i1 >  i2;
        b = i1 >= i2;
        n = i1 -  i2;

        b = i2 <  i1;
        b = i2 <= i1;
        b = i2 >  i1;
        b = i2 >= i1;
        n = i2 -  i1;
        boost::ignore_unused_variable_warning(b);
        boost::ignore_unused_variable_warning(n);
    }

    template <typename Iterator1, typename Iterator2>
    void interop_rand_access_constraints(
        Iterator1 const&, Iterator2 const&,
        boost::single_pass_traversal_tag, boost::single_pass_traversal_tag)
    { }

  } // namespace detail

  template <typename Iterator, typename ConstIterator>
  struct InteroperableIteratorConcept
  {
   private:
      typedef typename boost::detail::pure_traversal_tag<
          typename boost::iterator_traversal<
              Iterator
          >::type
      >::type traversal_category;

      typedef typename boost::detail::pure_traversal_tag<
          typename boost::iterator_traversal<
              ConstIterator
          >::type
      >::type const_traversal_category;
      
  public:
      ~InteroperableIteratorConcept()
      {
          BOOST_CONCEPT_ASSERT((SinglePassIteratorConcept<Iterator>));
          BOOST_CONCEPT_ASSERT((SinglePassIteratorConcept<ConstIterator>));

          detail::interop_single_pass_constraints(i, ci);
          detail::interop_rand_access_constraints(i, ci, traversal_category(), const_traversal_category());

          ci = i;
      }
      
   private:
      Iterator      i;
      ConstIterator ci;
  };

} // namespace boost_concepts


#endif // BOOST_ITERATOR_CONCEPTS_HPP
