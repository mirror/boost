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

    template<typename Function>
    struct get_result_spec
    {
    private:
        typedef typename boost::remove_const<
            typename boost::remove_reference<Function>::type>::type function;

        typedef fusion::vector0 arg;
    public:
        typedef typename function::template result<function(arg)> call_0_result;
        typedef typename function::template result<function const (arg)> 
            call_const_0_result;
    };

    template <class Derived, class Function, 
        bool EnableConst = detail::has_type< 
            typename get_result_spec<Function>::call_const_0_result>::value,
        bool Enable = detail::has_type<
            typename get_result_spec<Function>::call_0_result>::value>
    struct nullary_call_base
    {
    protected:
        typedef typename get_result_spec<Function>::call_const_0_result
            call_const_0_result_class;

        typedef typename get_result_spec<Function>::call_0_result
            call_0_result_class;
    public:
        typedef typename call_const_0_result_class::type
            call_const_0_result;

        inline call_const_0_result operator()() const
        {
            fusion::vector0 arg;
            return static_cast<Derived const *>(this)->fnc_transformed(arg);
        }

        typedef typename get_result_spec<Function>::call_0_result::type 
            call_0_result;

        inline call_0_result operator()() 
        {
            fusion::vector0 arg;
            return static_cast<Derived *>(this)->fnc_transformed(arg);
        }
    };

    template <class Derived, class Function> 
    struct nullary_call_base<Derived, Function, true, false>
    {
    protected:
        typedef typename get_result_spec<Function>::call_const_0_result
            call_const_0_result_class;

        typedef typename boost::blank call_0_result_class;
    public:
        typedef typename call_const_0_result_class::type
            call_const_0_result, call_0_result;

        inline call_const_0_result operator()() const
        {
            fusion::vector0 arg;
            return static_cast<Derived const *>(this)->fnc_transformed(arg);
        }
    };

    template <class Derived, class Function> 
    struct nullary_call_base<Derived, Function, false, true>
    {
    protected:
        typedef typename boost::blank call_const_0_result_class;

        typedef typename get_result_spec<Function>::call_0_result
            call_0_result_class;
    public:
        typedef void call_const_0_result;
        typedef typename call_0_result_class::type call_0_result;

        inline call_const_0_result operator()()
        {
            fusion::vector0 arg;
            return static_cast<Derived *>(this)->fnc_transformed(arg);
        }
    };

    template <class Derived, class Function> 
    struct nullary_call_base<Derived, Function, false, false>
    {
    protected:
        typedef boost::blank call_0_result_class;
        typedef boost::blank call_const_0_result_class;
    public:
        typedef void call_0_result;
        typedef void call_const_0_result;

        template <typename T> inline void operator()(T reserved::*) const { }
    };

}}}

#endif

