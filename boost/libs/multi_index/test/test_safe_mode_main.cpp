/* Boost.MultiIndex test for safe mode.
 *
 * Copyright Joaquín M López Muñoz 2003-2004. Use, modification, and
 * distribution are subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include <boost/test/included/test_exec_monitor.hpp>
#include "test_safe_mode.hpp"

int test_main(int,char *[])
{
  test_safe_mode();
  return 0;
}

