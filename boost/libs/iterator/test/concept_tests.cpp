// (C) Copyright Jeremy Siek 2002. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/iterator/iterator_concepts.hpp>
#include <boost/operators.hpp>
#include <boost/static_assert.hpp> // remove
#include <boost/detail/workaround.hpp>
#include "static_assert_same.hpp" // remove

struct new_iterator
  : public boost::iterator< boost::iterator_tag<
    boost::writable_lvalue_iterator_tag
    , boost::random_access_traversal_tag>, int>
{
  int& operator*() const { return *m_x; }
  new_iterator& operator++() { return *this; }
  new_iterator operator++(int) { return *this; }
  new_iterator& operator--() { return *this; }
  new_iterator operator--(int) { return *this; }
  new_iterator& operator+=(std::ptrdiff_t) { return *this; }
  new_iterator operator+(std::ptrdiff_t) { return *this; }
  new_iterator& operator-=(std::ptrdiff_t) { return *this; }
  std::ptrdiff_t operator-(const new_iterator&) const { return 0; }
  new_iterator operator-(std::ptrdiff_t) const { return *this; }
  bool operator==(const new_iterator&) const { return false; }
  bool operator!=(const new_iterator&) const { return false; }
  bool operator<(const new_iterator&) const { return false; }
  int* m_x;
};
new_iterator operator+(std::ptrdiff_t, new_iterator x) { return x; }

struct old_iterator
  : public boost::iterator<std::random_access_iterator_tag, int>
{
  int& operator*() const { return *m_x; }
  old_iterator& operator++() { return *this; }
  old_iterator operator++(int) { return *this; }
  old_iterator& operator--() { return *this; }
  old_iterator operator--(int) { return *this; }
  old_iterator& operator+=(std::ptrdiff_t) { return *this; }
  old_iterator operator+(std::ptrdiff_t) { return *this; }
  old_iterator& operator-=(std::ptrdiff_t) { return *this; }
  old_iterator operator-(std::ptrdiff_t) const { return *this; }
  std::ptrdiff_t operator-(const old_iterator&) const { return 0; }
  bool operator==(const old_iterator&) const { return false; }
  bool operator!=(const old_iterator&) const { return false; }
  bool operator<(const old_iterator&) const { return false; }
  int* m_x;
};
old_iterator operator+(std::ptrdiff_t, old_iterator x) { return x; }

struct my_writable_lvalue_iterator_tag
{
    operator boost::writable_lvalue_iterator_tag() const;
};

struct my_single_pass_traversal_tag
{
    operator boost::single_pass_traversal_tag() const;
};

void test_tag_convertibility()
{
    // This set of tests is by no means complete.

    // Test that this is an input/output iterator
#if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
    {
        typedef boost::iterator_tag<
            boost::writable_lvalue_iterator_tag
          , boost::single_pass_traversal_tag
        > tag;
        
        BOOST_STATIC_ASSERT((
            boost::is_convertible<tag, std::output_iterator_tag>::value
        ));
        BOOST_STATIC_ASSERT((
            boost::is_convertible<tag, std::input_iterator_tag>::value
        ));
        BOOST_STATIC_ASSERT((
            !boost::is_convertible<tag, std::forward_iterator_tag>::value
        ));
    }

    // Test that it's possible to build new sub-tags without
    // derivation.  Convertibility should be enough
    {
        typedef boost::iterator_tag<
            my_writable_lvalue_iterator_tag
          , my_single_pass_traversal_tag
        > tag;
        
        BOOST_STATIC_ASSERT((
            boost::is_convertible<tag, std::output_iterator_tag>::value
        ));
        BOOST_STATIC_ASSERT((
            boost::is_convertible<tag, std::input_iterator_tag>::value
        ));
        BOOST_STATIC_ASSERT((
            !boost::is_convertible<tag, std::forward_iterator_tag>::value
        ));
    }

    // Test that a single-pass readable lvalue iterator is only an
    // input iterator.  Requires special case handling in
    // categories.hpp
    {
        typedef boost::iterator_tag<
            boost::readable_lvalue_iterator_tag
          , boost::single_pass_traversal_tag
        > tag;
        BOOST_STATIC_ASSERT((
            boost::is_convertible<tag, std::input_iterator_tag>::value
        ));
        BOOST_STATIC_ASSERT((
            !boost::is_convertible<tag, std::output_iterator_tag>::value
        ));
        BOOST_STATIC_ASSERT((
            !boost::is_convertible<tag, std::forward_iterator_tag>::value
        ));
    }
#endif 
}

int
main()
{
  test_tag_convertibility();
        
  typedef boost::iterator_tag< boost::writable_lvalue_iterator_tag, boost::random_access_traversal_tag > tag;

  // BOOST_STATIC_ASSERT((boost::detail::is_random_access_iterator<tag>::value));
  int test = static_assert_same<tag::access, boost::writable_lvalue_iterator_tag>::value;
  test = static_assert_same<tag::traversal, boost::random_access_traversal_tag>::value;

  // BOOST_STATIC_ASSERT((boost::detail::is_random_access_iterator<new_iterator::iterator_category>::value));
  test = static_assert_same<new_iterator::iterator_category::access, boost::writable_lvalue_iterator_tag>::value;
  test = static_assert_same<new_iterator::iterator_category::traversal, boost::random_access_traversal_tag>::value;

  typedef boost::traversal_category<new_iterator>::type traversal_category;

  //  BOOST_STATIC_ASSERT(boost::detail::has_traversal<new_iterator::iterator_category>::value);
  BOOST_STATIC_ASSERT(boost::detail::is_new_iterator_tag<new_iterator::iterator_category>::value);


  test = static_assert_same<traversal_category, boost::random_access_traversal_tag>::value;
  (void)test;

  boost::function_requires<
    boost_concepts::WritableLvalueIteratorConcept<int*> >();
  boost::function_requires<
    boost_concepts::RandomAccessTraversalConcept<int*> >();

  boost::function_requires<
    boost_concepts::ReadableLvalueIteratorConcept<const int*> >();
  boost::function_requires<
    boost_concepts::RandomAccessTraversalConcept<const int*> >();

  boost::function_requires<
    boost_concepts::WritableLvalueIteratorConcept<new_iterator> >();
  boost::function_requires<
    boost_concepts::RandomAccessTraversalConcept<new_iterator> >();

  boost::function_requires<
    boost_concepts::WritableLvalueIteratorConcept<old_iterator> >();
  boost::function_requires<
    boost_concepts::RandomAccessTraversalConcept<old_iterator> >();
  return 0;
}
