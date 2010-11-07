/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TEST_VALUE_MAKER_HPP_JOFA_080916
#define BOOST_ICL_TEST_VALUE_MAKER_HPP_JOFA_080916

#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/interval_bounds.hpp>

namespace boost{ namespace icl
{

/*FYI completion like that:
std::string make(int n)
{
    std::string value = identity_element<std::string>::value();
    int abs_n = n<0 ? -n : n;
    for(int i=1; i<abs_n; i++)
        value += i%2==1 ? "hello " : "world ";
}
*/

struct mono
{
    mono(){};
    mono& operator ++ (){ return *this; }
    mono& operator -- (){ return *this; }
    mono& operator += (const mono&){ return *this; }
};

bool operator == (const mono&, const mono&){ return true; }
bool operator < (const mono&, const mono&){ return false; }

template<class CharType, class CharTraits>
std::basic_ostream<CharType, CharTraits>&
operator << (std::basic_ostream<CharType, CharTraits>& stream, const mono& object)
{
    return stream << "*";
}



template <class BicrementableT>
BicrementableT make(int n)
{
    BicrementableT value = identity_element<BicrementableT>::value();
    if(n>=0)
        for(int i=0; i<n; i++)
            ++value;
    else
        for(int i=0; i>n; i--)
            --value;

    return value;
}


template <class Type>
struct test_value;

template<>
struct test_value<std::string>
{
    static std::string make(int n)
    {
        std::string value = identity_element<std::string>::value();
        int abs_n = n<0 ? -n : n;
        for(int i=1; i<abs_n; i++)
            value += (i%2==1 ? "hello " : "world ");
        
        return value;
    }
};

template <class Type>
struct test_value
{ 
    static Type make(int n)
    {
        Type value = identity_element<Type>::value();
        if(n>=0)
            for(int i=0; i<n; i++)
                ++value;
        else
            for(int i=0; i>n; i--)
                --value;

        return value;
    }
};


template <class ItvMapT>
struct map_val
{
    typedef typename ItvMapT::domain_type       domain_type;
    typedef typename ItvMapT::codomain_type     codomain_type;
    typedef typename ItvMapT::interval_type     interval_type;
    typedef typename ItvMapT::value_type        value_type;
    typedef typename ItvMapT::segment_type      segment_type;
    typedef typename ItvMapT::domain_mapping_type domain_mapping_type;
    typedef std::pair<domain_type, codomain_type> std_pair_type; 

    static interval_type interval_(int lower, int upper, int bounds = 2)
    {
        return interval_type(test_value<domain_type>::make(lower), 
                             test_value<domain_type>::make(upper), interval_bounds(bounds));
    }

    static segment_type val_pair(int lower, int upper, int val, int bounds = 2)
    {
        return segment_type( interval_(lower, upper, static_cast<bound_type>(bounds)), 
                             test_value<codomain_type>::make(val) );
    }

    static domain_mapping_type map_pair(int key, int val)
    {
        return domain_mapping_type(test_value<  domain_type>::make(key), 
                                   test_value<codomain_type>::make(val));
    }

    static std_pair_type std_pair(int key, int val)
    {
        return std_pair_type(test_value<  domain_type>::make(key), 
                             test_value<codomain_type>::make(val));
    }
};


// Very short value denotation for intervals
// Assumption typename T and IntervalT exists in scope
//I_I : [a,b]
#define I_I(low,up) icl::interval<T>::closed    (make<T>(low), make<T>(up))
//I_D : [a,b)
#define I_D(low,up) icl::interval<T>::right_open(make<T>(low), make<T>(up))
//C_I : (a,b]
#define C_I(low,up) icl::interval<T>::left_open (make<T>(low), make<T>(up))
//C_D : (a,b)
#define C_D(low,up) icl::interval<T>::open      (make<T>(low), make<T>(up))

#define MK_I(ItvT,low,up) ItvT(make<T>(low), make<T>(up))

#define MK_v(key)  make<T>(key)
#define MK_u(key)  make<U>(key)

// Very short value denotation for interval value pairs
// Assumption typename IntervalMapT existes in scope
#define IIv(low,up,val) map_val<IntervalMapT>::val_pair(low,up,val, interval_bounds::_closed)
#define IDv(low,up,val) map_val<IntervalMapT>::val_pair(low,up,val, interval_bounds::_right_open)
#define CIv(low,up,val) map_val<IntervalMapT>::val_pair(low,up,val, interval_bounds::_left_open)
#define CDv(low,up,val) map_val<IntervalMapT>::val_pair(low,up,val, interval_bounds::_open)
#define K_v(key,val)    map_val<IntervalMapT>::map_pair(key,val)
#define sK_v(key,val)   map_val<IntervalMapT>::std_pair(key,val)


}} // namespace boost icl

#endif 

