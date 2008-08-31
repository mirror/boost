//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_274DA366004E11DCB1DDFE2E56D89593
#define UUID_274DA366004E11DCB1DDFE2E56D89593

#include <boost/exception/detail/counted_base.hpp>
#include <boost/exception/detail/refcount_ptr.hpp>

namespace
boost
    {
    class exception;

    template <class>
    class shared_ptr;

    namespace
    exception_detail
        {
        class error_info_base;
        struct type_info_;

        struct
        error_info_container:
            public exception_detail::counted_base
            {
            virtual char const * diagnostic_information() const = 0;
            virtual shared_ptr<error_info_base const> get( type_info_ const & ) const = 0;
            virtual void set( shared_ptr<error_info_base const> const &, type_info_ const & ) = 0;
            };

        template <class ErrorInfo>
        shared_ptr<typename ErrorInfo::value_type const> get_data( exception const & );

        void set_data( exception const *, shared_ptr<exception_detail::error_info_base const> const &, type_info_ const & );
        }

    class
    exception
        {
        public:

        virtual
        char const *
        diagnostic_information() const throw()
            {
            return _diagnostic_information();
            }

        protected:

        exception()
            {
            }

        virtual ~exception() throw()=0;

        char const *
        _diagnostic_information() const throw()
            {
            if( exception_detail::error_info_container * c=data_.get() )
                try
                    {
                    if( char const * w = c->diagnostic_information() )
                        return w;
                    }
                catch(...)
                    {
                    }
            return "";
            }

        private:

        template <class ErrorInfo>
        friend shared_ptr<typename ErrorInfo::value_type const> exception_detail::get_data( exception const & );

        friend void exception_detail::set_data( exception const *, shared_ptr<exception_detail::error_info_base const> const &, exception_detail::type_info_ const & );

        mutable exception_detail::refcount_ptr<exception_detail::error_info_container> data_;
        };

    inline
    exception::
    ~exception() throw()
        {
        }
    }

#endif
