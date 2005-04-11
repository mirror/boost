// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp> // BOOST_MSVC, SFINAE.
#include <boost/detail/workaround.hpp>           
#include <boost/iostreams/detail/template_params.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
# include <boost/type_traits/is_base_and_derived.hpp>
#endif

#define BOOST_IOSTREAMS_FORWARD_PIPABLE(filter, arity) \
    template< BOOST_PP_ENUM_PARAMS(arity, typename T) \
              BOOST_PP_COMMA_IF(arity) typename Component> \
    ::boost::iostreams::pipeline< \
        ::boost::iostreams::detail::pipeline_segment< \
            filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity) \
        >, \
        Component \
    > operator|( const filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity)& f, \
                 const Component& c ) \
    { \
        typedef ::boost::iostreams::detail::pipeline_segment< \
                    filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity) \
                > segment; \
        return ::boost::iostreams::pipeline<segment, Component> \
                   (segment(f), c); \
    } \
    /**/

#ifndef BOOST_NO_SFINAE
# define BOOST_IOSTREAMS_BACKWARD_PIPABLE(filter, arity) \
    template< typename Source BOOST_PP_COMMA_IF(arity) \
              BOOST_PP_ENUM_PARAMS(arity, typename T) > \
    typename \
    ::boost::enable_if< \
        ::boost::iostreams::is_device<Source>, \
        ::boost::iostreams::pipeline< \
            ::boost::iostreams::detail::pipeline_segment<Source>, \
            filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity) \
        > \
    >::type \
    operator|( const Source& src, \
               const filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity)& f ) \
    { \
        typedef ::boost::iostreams::detail::pipeline_segment<Source> segment; \
        return ::boost::iostreams::pipeline< \
                   segment, filter BOOST_IOSTREAMS_TEMPLATE_ARGS(arity) \
               >(segment(src), f); \
    } \
    /**/
#else
# define BOOST_IOSTREAMS_BACKWARD_PIPABLE(filter, arity)
#endif

#define BOOST_IOSTREAMS_PIPABLE(filter, arity) \
    BOOST_IOSTREAMS_FORWARD_PIPABLE(filter, arity) \
    /**/

namespace boost { namespace iostreams { 
    
namespace detail {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || \
    BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
    /**/
struct pipeline_base { };

template<typename T>
struct is_pipeline 
    : is_base_and_derived<pipeline_base, T>
    { };
#endif

template<typename Component>
class pipeline_segment 
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || \
    BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
    /**/
    : pipeline_base 
#endif 
{
public:
    pipeline_segment(const Component& component) 
        : component_(component) 
        { }
    template<typename Fn>
    void for_each(Fn fn) const { fn(component_); }
private:
    const Component& component_;
};

} // End namespace detail.
                    
//------------------Definition of Pipeline------------------------------------//

template<typename Pipeline, typename Component>
struct pipeline : Pipeline {
    typedef Pipeline   piper_type;
    typedef Component  component_type;
    pipeline(const Pipeline& p, const Component& component)
        : Pipeline(p), component_(component)
        { }
    template<typename Fn>
    void for_each(Fn fn) const
    {
        Pipeline::for_each(fn);
        fn(component_);
    }
    const Pipeline& tail() const { return *this; }
    const Component& head() const { return component_; }
private:
    const Component& component_;
};

template<typename Piper, typename Filter, typename Component>
pipeline<pipeline<Piper, Filter>, Component>
operator|(const pipeline<Piper, Filter>& p, const Component& cmp)
{
    BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    return pipeline<pipeline<Piper, Filter>, Component>(p, cmp);
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
