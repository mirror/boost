//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_274DA366004E11DCB1DDFE2E56D89593
#define UUID_274DA366004E11DCB1DDFE2E56D89593

#include <boost/exception/detail/type_info.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/exception/detail/counted_base.hpp>
#include <boost/intrusive_ptr.hpp>
#include <typeinfo>

namespace
boost
    {
    class exception;

    template <class T>
    class shared_ptr;

    namespace
    exception_detail
        {
        class error_info_base;

        struct
        error_info_container:
            public exception_detail::counted_base
            {
            virtual char const * diagnostic_information( char const *, char const * ) const = 0;
            virtual shared_ptr<error_info_base const> get( type_info_ const & ) const = 0;
            virtual void set( shared_ptr<error_info_base const> const &, type_info_ const & ) = 0;
            };

        template <class ErrorInfo>
        shared_ptr<typename ErrorInfo::value_type const> get_data( exception const & );

        void set_data( exception const *, shared_ptr<exception_detail::error_info_base const> const &, exception_detail::type_info_ const & );
        }

    class
    exception
        {
        public:

        virtual
        char const *
        diagnostic_information() const throw()
            {
            return _diagnostic_information(0);
            }

        protected:

        exception()
            {
            }

        exception( exception const & e ):
            data_(e.data_)
            {
            }

        char const *
        _diagnostic_information( char const * std_what ) const throw()
            {
            if( data_ )
                try
                    {
                    char const * w = data_->diagnostic_information(std_what,dynamic_type_name());
                    BOOST_ASSERT(w!=0);
                    return w;
                    }
                catch(...)
                    {
                    }
            return std_what ? std_what : dynamic_type_name();
            }

#if BOOST_WORKAROUND( BOOST_MSVC, BOOST_TESTED_AT(1500) )
        //Force class exception to be abstract.
        //Otherwise, MSVC bug allows throw exception(), even though the copy constructor is protected.
        virtual ~exception() throw()=0;
#else
#if BOOST_WORKAROUND( __GNUC__, BOOST_TESTED_AT(4) )
        virtual //Disable bogus GCC warning.
#endif
        ~exception() throw()
            {
            }
#endif

        private:

        friend void exception_detail::set_data( exception const *, shared_ptr<exception_detail::error_info_base const> const &, exception_detail::type_info_ const & );

        template <class ErrorInfo>
        friend shared_ptr<typename ErrorInfo::value_type const> exception_detail::get_data( exception const & );

        char const *
        dynamic_type_name() const
            {
            return
#if defined(BOOST_NO_RTTI) || defined(BOOST_NO_TYPEID)
                "Unknown type deriving from boost::exception"
#else
                typeid(*this).name()
#endif
                ;
            }

        mutable intrusive_ptr<exception_detail::error_info_container> data_;
        };

#if BOOST_WORKAROUND( BOOST_MSVC, BOOST_TESTED_AT(1500) ) //See above.
    inline
    exception::
    ~exception() throw()
        {
        }
#endif
    }

#endif
