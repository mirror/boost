//  Test boost/pending/iterator_adaptors.hpp

//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

// Revision History
// 21 Jan 01 Initial version (Jeremy Siek)

#include <list>
#include <boost/config.hpp>
#include <boost/pending/iterator_adaptors.hpp>
#include <boost/detail/iterator.hpp>

int main()
{
  typedef boost::iterator_adaptor<int*, boost::default_iterator_policies,
    boost::iterator<std::bidirectional_iterator_tag, int> > adaptor_type;
  
  adaptor_type i;
  i += 4;
  return 0;
}
