//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_FA5836A2CADA11DC8CD47C8555D89593
#define UUID_FA5836A2CADA11DC8CD47C8555D89593

#include <boost/exception/enable_exception_cloning.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/detail/cloning_base.hpp>
#include <exception>

namespace
boost
    {
    class
    unknown_exception:
        public exception,
        public std::exception
        {
        public:

        explicit
        unknown_exception()
            {
            }

        explicit
        unknown_exception( boost::exception const & x ):
            boost::exception(x)
            {
            }
        };

    typedef intrusive_ptr<exception_detail::clone_base const> exception_ptr;

    template <class T>
    exception_ptr
    clone_exception( T const & e )
        {
        if( boost::exception_detail::cloning_base const * cb = dynamic_cast<boost::exception_detail::cloning_base const *>(&e) )
            if( exception_detail::clone_base const * c = cb->clone() )
                return exception_ptr(c);
        if( boost::exception const * be = dynamic_cast<boost::exception const *>(&e) )
            return exception_ptr(exception_detail::make_clone(unknown_exception(*be)));
        else
            return exception_ptr(exception_detail::make_clone(unknown_exception()));
        }

    inline
    void
    rethrow_exception( exception_ptr const & p )
        {
        p->rethrow();
        }
    }

#endif
