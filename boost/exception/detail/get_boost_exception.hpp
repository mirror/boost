//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_B9A8291074CA11DD94BFC77156D89593
#define UUID_B9A8291074CA11DD94BFC77156D89593

#include <boost/exception/exception.hpp>

namespace
boost
    {
    namespace
    exception_detail
        {
#ifdef BOOST_NO_RTTI
        template <class T>
        exception const *
        get_boost_exception( T const * )
            {
            try
                {
                throw;
                }
            catch(
            exception & x )
                {
                return &x;
                }
            catch(...)
                {
                return 0;
                }
            }
#else
        template <class T>
        exception const *
        get_boost_exception( T const * x )
            {
            return dynamic_cast<exception const *>(x);
            }
#endif
        }
    }

#endif
