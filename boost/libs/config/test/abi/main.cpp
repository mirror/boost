//  (C) Copyright John Maddock 2003. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for the most recent version.

//
// before we do anything else, we need to mess with the compilers ABI:
// 
#ifdef _MSC_VER
#pragma pack(1)
#elif defined(__BORLANDC__)
#pragma option -Ve- -Vx- -a1 -b-
#endif
#include <stdio.h>
#include "abi_test.hpp"


int main()
{
   abi_test t;
   if((t.inline_one() != t.virtual_one()) || (t.inline_two() != t.virtual_two()))
   {
      fwrite("Failed ABI test", 1, 15, stdout);
      return -1;
   }
   return 0;
}