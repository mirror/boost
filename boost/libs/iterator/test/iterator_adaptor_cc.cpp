#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/concept_check.hpp>
#include <boost/cstdlib.hpp>
#include <list>

int main()
{
  {
    typedef boost::reverse_iterator<int*>       rev_iter;
    typedef boost::reverse_iterator<int const*> c_rev_iter;

    boost::function_requires< boost_concepts::WritableLvalueIteratorConcept<rev_iter> >();
    boost::function_requires< boost_concepts::RandomAccessTraversalConcept<rev_iter> >();
    boost::function_requires< boost::RandomAccessIteratorConcept<rev_iter> >();
    boost::function_requires< boost_concepts::InteroperableConcept<rev_iter, c_rev_iter> >();
  }
  {
    typedef boost::reverse_iterator<std::list<int>::iterator>       rev_iter;
    typedef boost::reverse_iterator<std::list<int>::const_iterator> c_rev_iter;

    boost::function_requires< boost_concepts::ReadableLvalueIteratorConcept<c_rev_iter> >();
    boost::function_requires< boost_concepts::BidirectionalTraversalConcept<c_rev_iter> >();
    boost::function_requires< boost::BidirectionalIteratorConcept<c_rev_iter> >();
    boost::function_requires< boost_concepts::InteroperableConcept<rev_iter, c_rev_iter> >();
  }

  return boost::exit_success;
}
