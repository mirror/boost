//  (C) Copyright John Maddock 2003. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for the most recent version.


#include "abi_test.hpp"


char abi_test::virtual_one()const
{ 
   return c; 
}

boost::int32_t abi_test::virtual_two()const
{ 
   return i; 
}

abi_test::abi_test()
{
   c = 0x12;
   i = 0x5678;
}
