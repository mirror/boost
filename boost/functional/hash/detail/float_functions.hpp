
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_FUNCTIONAL_HASH_DETAIL_FLOAT_FUNCTIONS_HPP)
#define BOOST_FUNCTIONAL_HASH_DETAIL_FLOAT_FUNCTIONS_HPP

#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/type_traits/ice.hpp>
#include <boost/detail/select_type.hpp>
//#include <boost/assert.hpp>

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// The C++ standard requires that the C float functions are overloarded
// for float, double and long double in the std namespace, but some of the older
// library implementations don't support this. On some that don't, the C99
// float functions (frexpf, frexpl, etc.) are available.
//
// The following tries to automatically detect which are available.

namespace BOOST_HASH_DETECT_FLOAT_FUNCTIONS {
    // Dummy functions to detect when the actual function we want isn't
    // available.
    //
    // AFAICT these have to be outside of the boost namespace, as if they're in
    // the boost namespace they'll always be preferable to any other function
    // (since the arguments are built in types, ADL can't be used).

    struct none {};

    none ldexpf(int, int);
    none ldexpl(int, int);
    none frexpf(int, int*);
    none frexpl(int, int*);

    template <class Float> none ldexp(Float, int);
    template <class Float> none frexp(Float, int*);    
}

namespace boost {
    namespace hash_detail {
        namespace detect {
            using namespace std;
            using namespace BOOST_HASH_DETECT_FLOAT_FUNCTIONS;            
          
            // A type for detecting return type of functions.
            template <typename T> struct is;
            template <> struct is<float> { char x[10]; };
            template <> struct is<double> { char x[20]; };
            template <> struct is<long double> { char x[30]; };
            template <> struct is<none> { char x[40]; };

            // Convert the return type of a function to a type we can use.
            template <typename T> is<T> float_type(T);

#define BOOST_HASH_CALL_FLOAT_FUNC(func, type2)                             \
            struct func##_access {                                          \
                template <typename Float>                                   \
                struct check                                                \
                {                                                           \
                    static Float x;                                         \
                    static type2 y;                                         \
                    BOOST_STATIC_CONSTANT(bool, value =                     \
                        sizeof(float_type(func(x,y)))                       \
                            == sizeof(is<Float>));                          \
                };                                                          \
                                                                            \
                template <typename Float>                                   \
                struct call                                                 \
                {                                                           \
                    Float operator()(Float a, type2 b) const                \
                    {                                                       \
                        return func(a, b);                                  \
                    }                                                       \
                };                                                          \
            }

            BOOST_HASH_CALL_FLOAT_FUNC(ldexpf, int);
            BOOST_HASH_CALL_FLOAT_FUNC(ldexpl, int);
            BOOST_HASH_CALL_FLOAT_FUNC(ldexp, int);
            BOOST_HASH_CALL_FLOAT_FUNC(frexpf, int*);
            BOOST_HASH_CALL_FLOAT_FUNC(frexpl, int*);
            BOOST_HASH_CALL_FLOAT_FUNC(frexp, int*);
            
#undef BOOST_CALL_HAS_FLOAT_FUNC
        }
        
        // check
        //
        // Use in select_impl to help old compilers with a value template.
        
        template <typename Float, typename Access>
        struct check : Access::BOOST_NESTED_TEMPLATE check<Float> {};

        // found_impl
        //
        // Used in select_impl when an appropriate function has
        // been found.

        template <typename Float, typename Access>
        struct found_impl
        {
            // Ignore further types

            template <typename Float2, typename Access2>
            struct x {
                typedef found_impl type;
            };
            
            // Use Access for result

            struct type : Access::BOOST_NESTED_TEMPLATE call<Float>
            {
                BOOST_STATIC_CONSTANT(bool, value = true);
            };
        };
        
        // select_impl
        //
        // Used to choose which floating point function to use for a particular
        // floating point type.

        struct select_impl
        {
            // Check if Access is appropriate for Float

            template <typename Float, typename Access>
            struct x :
                boost::detail::if_true <
                    ::boost::hash_detail::check<Float, Access>::value
                >
                ::BOOST_NESTED_TEMPLATE then<
                    found_impl<Float, Access>, select_impl
                > {};

            // Result for nothing found.

            struct type
            {
                BOOST_STATIC_CONSTANT(bool, value = false);
            };
        };

        // call_ldexp
        //
        // call_ldexp::value = Is there an appropriate version of call_ldexp
        //                     for this type?
        // Is there is, this is a function object that will call that overload

        template <typename Float>
        struct call_ldexp : select_impl
                :: BOOST_NESTED_TEMPLATE x<Float, detect::ldexp_access>::type
                :: BOOST_NESTED_TEMPLATE x<Float, detect::ldexpf_access>::type
                :: BOOST_NESTED_TEMPLATE x<Float, detect::ldexpl_access>::type
                :: type {};

        // call_frexp
        //
        // call_frexp::value = Is there an appropriate version of call_frexp
        //                     for this type?
        // Is there is, this is a function object that will call that overload

        template <typename Float>
        struct call_frexp : select_impl
                :: BOOST_NESTED_TEMPLATE x<Float, detect::frexp_access>::type
                :: BOOST_NESTED_TEMPLATE x<Float, detect::frexpf_access>::type
                :: BOOST_NESTED_TEMPLATE x<Float, detect::frexpl_access>::type
                :: type {};

        // has_float_functions
        //
        // Is there an overload of frexp and ldexp for the given float type.

        template<typename Float>
        struct has_float_functions
        {
            BOOST_STATIC_CONSTANT(bool, value = (
                ::boost::type_traits::ice_and<
                    ::boost::hash_detail::call_ldexp<Float>::value,
                    ::boost::hash_detail::call_frexp<Float>::value
                >::value
            ));
        };


        // select_hash_type
        //
        // If there is support for a particular floating point type, use that
        // otherwise use double (there's always support for double).
             
        template <typename Float>
        struct select_hash_type :
            boost::detail::if_true <
                ::boost::hash_detail::has_float_functions<Float>::value
            > ::BOOST_NESTED_TEMPLATE then <
                Float, double
            > {};
    }
}

#endif
