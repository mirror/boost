#ifndef BOOST_SCOPED_ARRAY_HPP_INCLUDED
#define BOOST_SCOPED_ARRAY_HPP_INCLUDED

//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.

#include <boost/assert.hpp>
#include <boost/config.hpp>   // in case ptrdiff_t not in std
#include <cstddef>            // for std::ptrdiff_t

namespace boost
{

//  scoped_array extends scoped_ptr to arrays. Deletion of the array pointed to
//  is guaranteed, either on destruction of the scoped_array or via an explicit
//  reset(). Use shared_array or std::vector if your needs are more complex.

template<typename T> class scoped_array // noncopyable
{
private:

    T* ptr;

    scoped_array(scoped_array const &);
    scoped_array & operator=(scoped_array const &);

public:

    typedef T element_type;

    explicit scoped_array( T* p = 0 ): ptr(p)  // never throws
    {
    }

    ~scoped_array()
    {
        typedef char type_must_be_complete[sizeof(T)];
        delete [] ptr;
    }

    void reset( T* p = 0 )
    {
        typedef char type_must_be_complete[sizeof(T)];

        if ( ptr != p )
        {
            delete [] ptr;
            ptr = p;
        }
    }

    T& operator[](std::ptrdiff_t i) const  // never throws
    {
        BOOST_ASSERT(ptr != 0);
        BOOST_ASSERT(i >= 0);
        return ptr[i];
    }

    T* get() const  // never throws
    {
        return ptr;
    }

    void swap(scoped_array & rhs)
    {
        T * tmp = rhs.ptr;
        rhs.ptr = ptr;
        ptr = tmp;
    }

};

template<class T> inline void swap(scoped_array<T> & a, scoped_array<T> & b)
{
    a.swap(b);
}

} // namespace boost

#endif  // #ifndef BOOST_SCOPED_ARRAY_HPP_INCLUDED
