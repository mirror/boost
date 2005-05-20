// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEE_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>  // BOOST_DEDUCE_TYPENAME.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/basic_adapter.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

//
// Template name: tee_filter.
// Template paramters:
//      Device - A blocking Sink.
//
template<typename Device>
class tee_filter : public detail::basic_adapter<Device> {
public:
    typedef typename detail::param_type<Device>::type  param_type;
    typedef typename char_type_of<Device>::type        char_type;
    struct category
        : multichar_output_filter_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };

    BOOST_STATIC_ASSERT((
        is_convertible< // Using io_mode causes failures on VC6-7.0.
            BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, output
        >::value
    ));

    explicit tee_filter(param_type dev) 
        : detail::basic_adapter<Device>(dev) 
        { }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::write(snk, s, n);
        iostreams::write(this->component(), s, result);
        return result;
    }

    template<typename Next>
    void close( Next&,
                BOOST_IOS::openmode which =
                    BOOST_IOS::in | BOOST_IOS::out )
    { iostreams::close(this->component(), which); }

    template<typename Sink>
    bool flush(Sink& snk)
    {
        bool r1 = iostreams::flush(snk);
        bool r2 = iostreams::flush(this->component());
        return r1 && r2;
    }
};
BOOST_IOSTREAMS_PIPABLE(tee_filter, 1)

template<typename Device>
tee_filter<Device> tee(const Device& dev) 
{ return tee_filter<Device>(dev); }

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEE_HPP_INCLUDED
