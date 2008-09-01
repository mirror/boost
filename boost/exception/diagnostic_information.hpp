//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_0552D49838DD11DD90146B8956D89593
#define UUID_0552D49838DD11DD90146B8956D89593

#include <boost/exception/get_error_info.hpp>
#include <exception>
#include <sstream>
#include <string>

namespace
boost
    {
    namespace
    exception_detail
        {
        char const *
        get_diagnostic_information( exception const & x )
            {
            if( error_info_container * c=x.data_.get() )
                try
                    {
                    return c->diagnostic_information();
                    }
                catch(...)
                    {
                    }
            return 0;
            }

        template <class T>
        std::string
        std_exception_diagnostic_information( std::exception const * x, T const & )
            {
            if( char const * s=x->what() )
                if( *s )
                    return std::string("\nstd::exception::what(): ")+s;
            return std::string();
            }

        template <class T>
        std::string
        std_exception_diagnostic_information( void const *, T const & e )
            {
#ifndef BOOST_NO_RTTI
            if( std::exception const * x=dynamic_cast<std::exception const *>(&e) )
                return std_exception_diagnostic_information(x,e);
            else
#endif
                return std::string();
            }
        }

    inline
    std::string
    diagnostic_information( exception const & x )
        {
        std::ostringstream tmp;
        tmp <<
            "boost::exception diagnostic information:"
#if !defined(BOOST_NO_RTTI) && !defined(BOOST_NO_TYPEID)
            "\nDynamic exception type: " << BOOST_EXCEPTION_DYNAMIC_TYPEID(x).name()
#endif
            ;
        if( boost::shared_ptr<char const * const> f=get_error_info<throw_function>(x) )
            tmp << "\nThrow function: " << *f;
        if( boost::shared_ptr<char const * const> f=get_error_info<throw_file>(x) )
            tmp << "\nThrow file name: " << *f;
        if( boost::shared_ptr<int const> l=get_error_info<throw_line>(x) )
            tmp << "\nThrow file line: " << *l;
		if( char const * s=exception_detail::get_diagnostic_information(x) )
            if( *s )
                tmp << "\n" << s;
        return tmp.str();
        }
    }

#endif
