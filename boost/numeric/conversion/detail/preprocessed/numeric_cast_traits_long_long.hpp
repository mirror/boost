//
//! Copyright (c) 2011-2012
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
namespace boost { namespace numeric {
    
    
    template <>
    struct numeric_cast_traits
        <
            char
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long long
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long long
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long long
          , long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<long long> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long long
          , unsigned long long
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<unsigned long long> rounding_policy;
    }; 
}}
