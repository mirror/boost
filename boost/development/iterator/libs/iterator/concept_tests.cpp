#include <boost/iterator_concepts.hpp>
#include <boost/operators.hpp>

struct new_iterator
  : public boost::iterator<std::random_access_iterator_tag, int>,
    public boost::new_iterator_base
{
  typedef boost::random_access_iterator_tag traversal_category;
  typedef boost::mutable_lvalue_iterator_tag return_category;

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

struct bar { };
void foo(bar) { }

int
main()
{
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  boost::function_requires<
    boost_concepts::MutableLvalueIteratorConcept<int*> >();
  boost::function_requires<
    boost_concepts::RandomAccessIteratorConcept<int*> >();

  boost::function_requires<
    boost_concepts::ConstantLvalueIteratorConcept<const int*> >();
  boost::function_requires<
    boost_concepts::RandomAccessIteratorConcept<const int*> >();
#endif

  boost::function_requires<
    boost_concepts::MutableLvalueIteratorConcept<new_iterator> >();
  boost::function_requires<
    boost_concepts::RandomAccessIteratorConcept<new_iterator> >();

  boost::function_requires<
    boost_concepts::MutableLvalueIteratorConcept<old_iterator> >();
  boost::function_requires<
    boost_concepts::RandomAccessIteratorConcept<old_iterator> >();
  return 0;
}
