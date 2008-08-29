//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_78CC85B2914F11DC8F47B48E55D89593
#define UUID_78CC85B2914F11DC8F47B48E55D89593

#include <boost/exception/exception.hpp>
#include <boost/exception/detail/cloning_base.hpp>
#include <boost/assert.hpp>
#include <new>

namespace
boost
    {
    namespace
    exception_detail
        {
        inline
        void
        copy_boost_exception( exception * a, exception const * b )
            {
            *a = *b;
            }

        inline
        void
        copy_boost_exception( void *, void const * )
            {
            }

        template <class T>
        new_clone make_clone( T const & );

        template <class T>
        class
        clone_impl:
            public T,
            public cloning_base
            {
            public:

            explicit
            clone_impl( T const & x ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            ~clone_impl() throw()
                {
                }

            private:

            new_clone
            clone() const
                {
                return make_clone<T>(*this);
                }
            };

        class
        clone_base
            {
            public:

            virtual void rethrow() const=0;
            virtual ~clone_base() throw()=0;
            };

        inline
        clone_base::
        ~clone_base() throw()
            {
            }

        struct
        bad_alloc_impl:
            public clone_base,
            public std::bad_alloc
            {
            void
            rethrow() const
                {
                throw *this;
                }
            };

        template <class T>
        class
        exception_clone:
            public T,
            public clone_base
            {
            public:

            explicit
            exception_clone( T const & x ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            private:

            ~exception_clone() throw()
                {
                }

            void
            rethrow() const
                {
                throw clone_impl<T>(*this);
                }
            };

        inline
        void
        delete_clone( clone_base const * c )
            {
            BOOST_ASSERT(c!=0);
            delete c;
            }

        inline
        void
        delete_clone_noop( clone_base const * )
            {
            }

        template <class T>
        inline
        new_clone
        make_clone( T const & x )
            {
            new_clone tmp = {0,0};
            try
                {
                tmp.c_=new exception_clone<T>(x);
                tmp.d_=&delete_clone;
                }
            catch(
            std::bad_alloc & )
                {
                static bad_alloc_impl bad_alloc;
                tmp.c_=&bad_alloc;
                tmp.d_=&delete_clone_noop;
                }
            catch(
            ... )
                {
                BOOST_ASSERT(0);
                }
            return tmp;
            }
        }

    template <class T>
    inline
    exception_detail::clone_impl<T>
    enable_current_exception( T const & x )
        {
        return exception_detail::clone_impl<T>(x);
        }
    }

#endif
