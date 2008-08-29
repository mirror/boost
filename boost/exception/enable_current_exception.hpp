//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_78CC85B2914F11DC8F47B48E55D89593
#define UUID_78CC85B2914F11DC8F47B48E55D89593

#include <boost/exception/exception.hpp>

namespace
boost
    {
    namespace
    exception_detail
        {
        class
        clone_base
            {
            public:

            virtual clone_base const * clone() const = 0;
            virtual void rethrow() const = 0;
            virtual ~clone_base() throw() = 0;
            };

        inline
        clone_base::
        ~clone_base() throw()
            {
            }

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
        class
        clone_impl:
            public T,
            public clone_base
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

            clone_base const *
            clone() const
                {
                return new clone_impl(*this);
                }

            void
            rethrow() const
                {
                throw *this;
                }
            };
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
