/**
 * Pointer Container Library
 * (C) Thorsten Ottosen 2003-2005
 * 
 * Permission to copy, use, modify,
 * sell and distribute this software is granted provided this
 * copyright notice appears in all copies. This software is provided
 * "as is" without express or implied warranty, and with no claim as
 * to its suitability for any purpose.
 *
 * See http://www.boost.org/libs/ptr_container for documentation.
 *
 */

#ifndef BOOST_PTR_CONTAINER_EXCEPTION_HPP
#define BOOST_PTR_CONTAINER_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <exception>

namespace boost
{
    class bad_ptr_container_operation : public std::exception
    {
        const char* what_;
    public:
        bad_ptr_container_operation( const char* what ) : what_( what )
        { }
        
        virtual const char* what() const throw()
        {
            return what_;
        }
    };


    
    class bad_index : public bad_ptr_container_operation
    {
    public:
        bad_index( const char* what ) : bad_ptr_container_operation( what )
        { }
    };



    class bad_pointer : public bad_ptr_container_operation
    {
    public:
        bad_pointer() : bad_ptr_container_operation( "Null pointer not allowed in a pointer container!" )
        { }
        
        bad_pointer( const char* text ) : bad_ptr_container_operation( text )
        { }
    };
}

#endif
