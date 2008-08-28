//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_1A590226753311DD9E4CCF6156D89593
#define UUID_1A590226753311DD9E4CCF6156D89593

#include <boost/shared_ptr.hpp>
#include <boost/exception/detail/get_boost_exception.hpp>
#include <boost/exception/detail/error_info_base.hpp>

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class ErrorInfo>
        inline
        shared_ptr<typename ErrorInfo::value_type const>
        get_data( exception const & x )
            {
            if( x.data_ )
                if( shared_ptr<exception_detail::error_info_base const> eib = x.data_->get(BOOST_EXCEPTION_STATIC_TYPEID(ErrorInfo)) )
                    {
#ifndef BOOST_NO_RTTI
                    BOOST_ASSERT( 0!=dynamic_cast<ErrorInfo const *>(eib.get()) );
#endif
                    ErrorInfo const * w = static_cast<ErrorInfo const *>(eib.get());
                    return shared_ptr<typename ErrorInfo::value_type const>(eib,&w->value());
                    }
            return shared_ptr<typename ErrorInfo::value_type const>();
            }
        }

    template <class ErrorInfo,class E>
    inline
    shared_ptr<typename ErrorInfo::value_type const>
    get_error_info( E const & some_exception )
        {
        if( exception const * x = exception_detail::get_boost_exception(&some_exception) )
            return exception_detail::get_data<ErrorInfo>(*x);
        else
            return shared_ptr<typename ErrorInfo::value_type const>();
        }
    }

#endif
