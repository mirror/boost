//  Boost safe_bool_testable test program  -----------------------------------//

//  (C) Copyright Daniel Frey 2003. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  30 Jul 03  Initial version (Daniel Frey)

#include <boost/operators.hpp>

namespace
{
    struct X
        : private boost::bool_testable< X >
    {
        operator bool() const
        {
            return true;
        }
    };
}

int main()
{
    X x;

    int i = x; // Should cause compile time error

    i = i; // Surpress warnings which has nothing to do with the test

    return 0;
}   // main
