//  (C) Copyright John Maddock 2003. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for the most recent version.


#define BOOST_CONFIG_SOURCE

#include "link_test.hpp"

bool BOOST_CONFIG_DECL check_options(
                   bool m_dyn_link,
                   bool m_dyn_rtl,
                   bool m_has_threads,
                   bool m_debug,
                   bool m_stlp_debug)
{
   return (m_dyn_link == dyn_link) 
      && (m_dyn_rtl == dyn_rtl)
      && (m_has_threads == has_threads)
      && (m_debug == debug)
      && (m_stlp_debug == stl_debug);
}
