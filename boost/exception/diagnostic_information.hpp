//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_0552D49838DD11DD90146B8956D89593
#define UUID_0552D49838DD11DD90146B8956D89593

#include <boost/exception/exception.hpp>
#include <boost/exception/detail/type_info.hpp>
#include <exception>
#include <string>

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        std::string
        std_exception_diagnostic_information( std::exception const * x, T const & )
            {
            if( char const * s=x->what() )
                if( *s )
                    return std::string("std::exception::what(): ")+s;
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

        template <class T>
        std::string
        boost_exception_diagnostic_information( boost::exception const * x, T const & )
            {
            if( char const * s=x->diagnostic_information() )
                if( *s )
                    return std::string("boost::exception::diagnostic_information():\n")+s;
            return std::string();
            }

        template <class T>
        std::string
        boost_exception_diagnostic_information( void const *, T const & e )
            {
#ifndef BOOST_NO_RTTI
            if( exception const * x=dynamic_cast<exception const *>(&e) )
                return boost_exception_diagnostic_information(x,e);
            else
#endif
                return std::string();
            }
        }

    template <class T>
    inline
    std::string
    diagnostic_information( T const & x )
        {
        std::string di=
#if defined(BOOST_NO_RTTI) || defined(BOOST_NO_TYPEID)
            std::string("Static exception type: ")+BOOST_EXCEPTION_STATIC_TYPEID(T)
#else
            std::string("Dynamic exception type: ")+BOOST_EXCEPTION_DYNAMIC_TYPEID(x)
#endif
            .name();
        std::string di1=exception_detail::std_exception_diagnostic_information(&x,x);
        if( !di1.empty() )
            {
            di+='\n';
            di+=di1;
            }
        std::string di2=exception_detail::boost_exception_diagnostic_information(&x,x);
        if( !di2.empty() )
            {
            di+='\n';
            di+=di2;
            }
        return di;
        }
    }

#endif
