//  (C) Copyright John Maddock 2003. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for the most recent version.

#include "link_test.hpp"

int main()
{
   return check_options(dyn_link, dyn_rtl, has_threads, debug, stl_debug) ? 0 : -1;
}

