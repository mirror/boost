// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_RANGE_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_RANGE_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC.

#include <algorithm>                             // min.
#include <cassert>
#include <cstddef>                               // ptrdiff_t.
#include <iosfwd>                                // streamsize, streamoff.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

// Used for simulated tag dispatch.
template<typename Traversal> struct range_adapter_impl;

template<typename Mode, typename Iter>
class range_adapter {
public:
    typedef typename iterator_value<Iter>::type      char_type;
    typedef typename iterator_traversal<Iter>::type  traversal;
    struct category : Mode, device_tag { };
    typedef typename
            mpl::if_<
                is_convertible<
                    traversal,
                    random_access_traversal_tag
                >,
                random_access_traversal_tag,
                single_pass_traversal_tag
            >::type                                  tag;
    typedef range_adapter_impl<tag>                  impl;

    range_adapter(Iter first, Iter last);
    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek(std::streamoff off, std::ios::seekdir way);
private:
    Iter first_, cur_, last_;
};

//------------------Implementation of range_adapter---------------------------//

template<typename Mode, typename Iter>
range_adapter<Mode, Iter>::range_adapter(Iter first, Iter last)
    : first_(first), cur_(first), last_(last) { }

template<typename Mode, typename Iter>
std::streamsize range_adapter<Mode, Iter>::read
    (char_type* s, std::streamsize n)
{ return impl::read(cur_, last_, s, n); }

template<typename Mode, typename Iter>
void range_adapter<Mode, Iter>::write
    (const char_type* s, std::streamsize n)
{ impl::write(cur_, last_, s, n); }


template<typename Mode, typename Iter>
std::streamoff range_adapter<Mode, Iter>::seek
    (std::streamoff off, std::ios::seekdir way)
{ 
    impl::seek(first_, cur_, last_, off, way); 
    return static_cast<std::streamoff>(cur_ - first_);
}

//------------------Implementation of range_adapter_impl----------------------//

template<>
struct range_adapter_impl<single_pass_traversal_tag> {
    template<typename Iter>
    static std::streamsize read
        ( Iter& cur, Iter& last, typename iterator_value<Iter>::type* s,
          std::streamsize n )
    {
        std::streamsize rem = n; // No. of chars remaining.
        while (cur != last && rem-- > 0) *s++ = *cur++;
        return n - rem;
    }

    template<typename Iter>
    static void write
        ( Iter& cur, Iter& last,
          const typename iterator_value<Iter>::type* s, std::streamsize n )
    {
        while (cur != last && n-- > 0) *cur++ = *s++;
        if (cur == last && n > 0)
            throw write_area_exhausted();
    }
};

template<>
struct range_adapter_impl<random_access_traversal_tag> {
    template<typename Iter>
    static std::streamsize read
        ( Iter& cur, Iter& last, typename iterator_value<Iter>::type* s,
          std::streamsize n )
    {
        n = std::min(static_cast<std::streamsize>(last - cur), n);
        std::copy(cur, cur + n, s);
        cur += n;
        return n;
    }

    template<typename Iter>
    static void write
        ( Iter& cur, Iter& last,
          const typename iterator_value<Iter>::type* s, std::streamsize n )
    {
        std::streamsize count =
            std::min(static_cast<std::streamsize>(last - cur), n);
        std::copy(s, s + count, cur);
        cur += count;
        if (count < n) throw write_area_exhausted();
    }

    template<typename Iter>
    static void seek
        ( Iter& first, Iter& cur, Iter& last, std::streamoff off,
          std::ios::seekdir way )
    {
        using namespace std;
        switch (way) {
        case ios::beg:
            if (off > last - first || off < 0) bad_seek();
            cur = first + off;
            break;
        case ios::cur:
            {
                std::ptrdiff_t newoff = cur - first + off;
                if (newoff > last - first || newoff < 0) bad_seek();
                cur += off;
                break;
            }
        case ios::end:
            if (last - first + off < 0 || off > 0) bad_seek();
            cur = last + off;
            break;
        default:
            assert(0);
        }
    }
};

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_RANGE_ADAPTER_HPP_INCLUDED //---------------//
