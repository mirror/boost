// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// 8 Mar 2001   Jeremy Siek
//     Initial checkin.

#include <boost/iterator_adaptors.hpp>
#include <boost/pending/iterator_tests.hpp>
#include <boost/static_assert.hpp>

class bar { };
void foo(bar) { }

int
main()
{
  using boost::dummyT;
  dummyT array[] = { dummyT(0), dummyT(1), dummyT(2), 
		     dummyT(3), dummyT(4), dummyT(5) };
  typedef boost::iterator_adaptor<dummyT*, 
    boost::default_iterator_policies, dummyT> my_iter;
  my_iter mi(array);

  {
    typedef boost::iterator_adaptor<my_iter, boost::default_iterator_policies,
      boost::iterator_traits_generator
      ::reference<dummyT>
      ::iterator_category<std::input_iterator_tag> > iter_type;

    BOOST_STATIC_ASSERT((boost::is_same<iter_type::iterator_category*,
       std::input_iterator_tag*>::value));

    BOOST_STATIC_ASSERT(( ! boost::is_convertible<iter_type::iterator_category*,
       std::forward_iterator_tag*>::value));

    iter_type i(mi);
    boost::input_iterator_test(i, dummyT(0), dummyT(1));
  }
  {
    typedef boost::iterator_adaptor<dummyT*,
      boost::default_iterator_policies,
      boost::iterator_traits_generator
        ::value_type<dummyT>
        ::reference<const dummyT&>
        ::pointer<const dummyT*> 
        ::iterator_category<std::forward_iterator_tag>
        ::difference_type<std::ptrdiff_t> > adaptor_type;

    adaptor_type i(array);

    boost::input_iterator_test(i, dummyT(0), dummyT(1));
    int zero = 0;
    if (zero) // don't do this, just make sure it compiles
      assert((*i).m_x == i->foo());      
  }

  return 0;
}
