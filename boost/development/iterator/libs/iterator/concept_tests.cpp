#include <boost/iterator_concepts.hpp>

int
main()
{
  boost::function_requires< 
    boost_concepts::MutableLvalueRandomAccessIteratorConcept<int*> >();

  boost::function_requires< 
    boost_concepts::ConstantLvalueRandomAccessIteratorConcept<const int*> >();

  return 0;
}
