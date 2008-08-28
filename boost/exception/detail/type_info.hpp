//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_C3E1741C754311DDB2834CCA55D89593
#define UUID_C3E1741C754311DDB2834CCA55D89593

#include <boost/detail/sp_typeinfo.hpp>
#include <boost/current_function.hpp>

namespace
boost
    {
    template <class ErrorInfoTag>
    inline
    char const *
    error_info_value()
        {
        return BOOST_CURRENT_FUNCTION;
        }

    namespace
    exception_detail
        {
        typedef detail::sp_typeinfo type_info_;

#ifdef BOOST_NO_TYPEID
        typedef type_info_ type_info_wrapper;
#else
        struct
        type_info_wrapper
            {
            type_info_ const * type;

            explicit
            type_info_wrapper( type_info_ const & t ):
                type(&t)
                {
                }

            bool
            operator<( type_info_wrapper const & b ) const
                {
                return 0!=(type->before(*b.type));
                }
            };
#endif

        template <class ErrorInfoTag>
        inline
        char const *
        type_name()
            {
            return error_info_value<ErrorInfoTag>();
            }
        }
    }

#define BOOST_EXCEPTION_STATIC_TYPEID(T) BOOST_SP_TYPEID(T)

#endif
