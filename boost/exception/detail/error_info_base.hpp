//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_CE6983AC753411DDA764247956D89593
#define UUID_CE6983AC753411DDA764247956D89593

#include <boost/detail/workaround.hpp>
#include <string>

namespace
boost
    {
    namespace
    exception_detail
        {
        class
        error_info_base
            {
            public:

            virtual char const * tag_typeid_name() const = 0;
            virtual std::string value_as_string() const = 0;

            protected:

#if BOOST_WORKAROUND( __GNUC__, BOOST_TESTED_AT(4) )
virtual //Disable bogus GCC warning.
#endif
            ~error_info_base()
                {
                }
            };
        }
    }

#endif
