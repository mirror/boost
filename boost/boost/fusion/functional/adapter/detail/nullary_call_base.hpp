/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_NULLARY_CALL_BASE_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_NULLARY_CALL_BASE_HPP_INCLUDED

#include <boost/blank.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/fusion/sequence/container/vector/vector10.hpp>
#include <boost/fusion/functional/adapter/detail/has_type.hpp>

#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct reserved { };

    template <class Derived, class Function, bool Enable = detail::has_type< 
        typename remove_reference<Function>::type
          ::template result<
        typename remove_const<typename remove_reference<Function>::type>::type(fusion::vector0)> >::value>
    struct nullary_call_base
    {
        template <typename T> inline void operator()(T reserved::*) const { }
    protected:
        typedef boost::blank r0;
    };

    template <class Derived, class Function>
    struct nullary_call_base<Derived,Function,true>
    {
    private:
        typedef typename remove_const<typename remove_reference<Function>::type>::type function;
    protected:
        typedef typename function::template result<function(vector0)> r0;
    public:

        inline typename r0::type
        operator()() const
        {
            fusion::vector0 arg;
            return static_cast<Derived const *>(this)->fnc_transformed(arg);
        }

        inline typename r0::type
        operator()() 
        {
            fusion::vector0 arg;
            return static_cast<Derived *>(this)->fnc_transformed(arg);
        }
    };

}}}

#endif

