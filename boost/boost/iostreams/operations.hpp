// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <utility>                              // pair.
#include <boost/config.hpp>                     // BOOST_NO_STD_LOCALE.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/iterator_traits.hpp>
#include <boost/iostreams/detail/ios_traits.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

//--------------Fundamental i/o operations------------------------------------//

template<typename T>
BOOST_IOSTREAMS_INT_TYPE(T) get(T&);

template<typename T>
std::streamsize read(T&, BOOST_IOSTREAMS_CHAR_TYPE(T)*, std::streamsize);

template<typename T>
void putback(T&, BOOST_IOSTREAMS_CHAR_TYPE(T));

template<typename T>
void put(T&, BOOST_IOSTREAMS_CHAR_TYPE(T));

template<typename T>
void write(T&, const BOOST_IOSTREAMS_CHAR_TYPE(T)*, std::streamsize);

template<typename T>
std::streamoff
seek( T&, std::streamoff, std::ios::seekdir,
      std::ios::openmode mode =
          std::ios::in | std::ios::out );

template<typename T, typename Source>
std::streamsize
read(T&, Source&, BOOST_IOSTREAMS_CHAR_TYPE(T)*, std::streamsize);

template<typename T, typename Sink>
void write(T&, Sink&, const BOOST_IOSTREAMS_CHAR_TYPE(T)*, std::streamsize);

template<typename T>
void close(T&, std::ios::openmode);

template<typename T, typename Sink>
void close(T&, Sink&, std::ios::openmode which);

// Avoid including <locale>.
template<typename T, typename Locale>
void imbue(T&, const Locale& loc);

template<typename T>
std::pair<BOOST_IOSTREAMS_CHAR_TYPE(T)*, BOOST_IOSTREAMS_CHAR_TYPE(T)*> 
input_sequence(T&);

template<typename T>
std::pair<BOOST_IOSTREAMS_CHAR_TYPE(T)*, BOOST_IOSTREAMS_CHAR_TYPE(T)*> 
output_sequence(T&);

//--------------Implementation of read, write, get and put--------------------//

namespace detail {

// Implementation templates for simulated tag dispatch.
template<typename Category> struct read_impl;
template<typename Category> struct write_impl;
template<typename Category> struct seek_impl;
template<typename Category> struct close_impl;
template<typename Category> struct read_filter_impl;
template<typename Category> struct write_filter_impl;
template<typename Category> struct close_filter_impl;

template<>
struct read_impl<input> {
    template<typename T>
    static BOOST_IOSTREAMS_INT_TYPE(T) get(T& t)
    {
        typedef std::char_traits<BOOST_IOSTREAMS_CHAR_TYPE(T)> traits_type;
        BOOST_IOSTREAMS_CHAR_TYPE(T) c;
        return t.read(&c, 1) == 1 ?
            traits_type::to_int_type(c) :
            traits_type::eof();
    }

    template<typename T>
    static std::streamsize
    read(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
    { return t.read(s, n); }

    // Suggeted by Peter Dimov. See
    // http://lists.boost.org/MailArchives/boost/msg06980.php.
    template<typename T> struct always_false : mpl::false_ { };

    template<typename T>
    static void putback(T&, BOOST_IOSTREAMS_CHAR_TYPE(T))
    { BOOST_STATIC_ASSERT(always_false<T>::value); }
};

template<>
struct read_impl<peekable_tag> : read_impl<input> {
    template<typename T>
    static void putback(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c) { t.putback(c); }
};

template<>
struct read_impl<istream_tag> {
    template<typename T>
    static BOOST_IOSTREAMS_INT_TYPE(T) get(T& t)
    { return t.get(); }

    template<typename T>
    static std::streamsize
    read(T& t, typename T::char_type* s, std::streamsize n)
    { t.read(s, n); return t.gcount(); }

    template<typename T>
    static void putback(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
    { t.putback(c); }
};

template<>
struct read_impl<streambuf_tag> {
    template<typename T>
    static BOOST_IOSTREAMS_INT_TYPE(T) get(T& t)
    { return t.sbumpc(); }

    template<typename T>
    static std::streamsize
    read(T& t, typename T::char_type* s, std::streamsize n)
    { return t.sgetn(s, n); }

    template<typename T>
    static void putback(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
    { t.sputbackc(c); }
};

template<>
struct write_impl<output> {
    template<typename T>
    static void put(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
    { t.write(&c, 1); }

    template<typename T>
    static void
    write(T& t, const BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
    { t.write(s, n); }
};

template<>
struct write_impl<ostream_tag> {
    template<typename T>
    static void put(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
    { t.put(c); }

    template<typename T>
    static void write(T& t, const typename T::char_type* s, std::streamsize n)
    { t.write(s, n); }
};

template<>
struct write_impl<streambuf_tag> {
    template<typename T>
    static void put(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
    { t.sputc(c); }

    template<typename T>
    static void write(T& t, const typename T::char_type* s, std::streamsize n)
    { t.sputn(s, n); }
};

template<>
struct write_impl<insert_iterator_tag> {
    template<typename T>
    static void put(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
    { *t++ = c; }

    template<typename T>
    static void write( T& t, const typename iter_val<T>::type* s,
                       std::streamsize n )
    { while (n--) *t++ = *s++; }
};

template<>
struct seek_impl<any_tag> {
    template<typename T>
    static std::streamoff seek( T& t, std::streamoff off, std::ios::seekdir way,
                                std::ios::openmode )
    { return t.seek(off, way); }
};

template<>
struct seek_impl<two_head> {
    template<typename T>
    static std::streamoff seek( T& t, std::streamoff off, std::ios::seekdir way,
                                std::ios::openmode which )
    { return t.seek(off, way, which); }
};

struct seek_impl_basic_ios {
    template<typename T>
    static std::streamoff seek( T& t, std::streamoff off, std::ios::seekdir way,
                                std::ios::openmode which )
    { return t.rdbuf()->pubseekoff(off, way, which); }
};

template<>
struct seek_impl<istream_tag> : seek_impl_basic_ios { };

template<>
struct seek_impl<ostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_impl<iostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_impl<streambuf_tag> {
    template<typename T>
    static std::streamoff seek( T& t, std::streamoff off, std::ios::seekdir way,
                                std::ios::openmode which )
    { return t.pubseekoff(off, way, which); }
};

template<>
struct close_impl<any_tag> {
    template<typename T>
    static void close(T&, std::ios::openmode) { }
};

template<>
struct close_impl<closable_tag> {
    template<typename T>
    static void close(T& t, std::ios::openmode which)
    {
        typedef BOOST_IOSTREAMS_CATEGORY(T) category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == ((which & std::ios::in) != 0))
            t.close();
    }
};

template<>
struct close_impl<two_sequence> {
    template<typename T>
    static void close(T& t, std::ios::openmode which) { t.close(which); }
};

template<>
struct read_filter_impl<any_tag> {
    template<typename T, typename Source>
    static std::streamsize read
        (T& t, Source& src, BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
    {
        typedef BOOST_IOSTREAMS_CHAR_TYPE(T)        char_type;
        typedef std::char_traits<char_type>  traits_type;
        std::streamsize result;
        for (result = 0; result < n; ++result) {
            BOOST_IOSTREAMS_INT_TYPE(T) c = t.get(src);
            if (traits_type::eq_int_type(c, traits_type::eof()))
                break;
            s[result] = traits_type::to_int_type(c);
        }
        return result;
    }
};

template<>
struct read_filter_impl<multichar_tag> {
    template<typename T, typename Source>
    static std::streamsize read
        (T& t, Source& src, BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
    { return t.read(src, s, n); }
};

template<>
struct write_filter_impl<any_tag> {
    template<typename T, typename Sink>
    static void write( T& t, Sink& snk, const BOOST_IOSTREAMS_CHAR_TYPE(T)* s,
                       std::streamsize n )
    { for (std::streamsize off = 0; off < n; ++off) t.put(snk, s[off]); }
};

template<>
struct write_filter_impl<multichar_tag> {
    template<typename T, typename Sink>
    static void write( T& t, Sink& snk, const BOOST_IOSTREAMS_CHAR_TYPE(T)* s,
                       std::streamsize n )
    { t.write(snk, s, n); }
};

} // End namespace detail.

template<typename T>
BOOST_IOSTREAMS_INT_TYPE(T) get(T& t)
{
    typedef typename detail::dispatch<
                T, istream_tag, streambuf_tag, input
            >::type tag;
    return detail::read_impl<tag>::get(detail::unwrap(t));
}

template<typename T>
inline std::streamsize
read(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
{
    typedef typename detail::dispatch<
                T, istream_tag, streambuf_tag, input
            >::type tag;
    return detail::read_impl<tag>::read(detail::unwrap(t), s, n);
}

template<typename T>
void putback(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
{
    typedef typename detail::dispatch<
                T, istream_tag, streambuf_tag, peekable_tag, input
            >::type tag;
    return detail::read_impl<tag>::putback(detail::unwrap(t), c);
}

template<typename T>
void put(T& t, BOOST_IOSTREAMS_CHAR_TYPE(T) c)
{
    typedef typename detail::dispatch<
                T, ostream_tag, streambuf_tag, insert_iterator_tag, output
            >::type tag;
    detail::write_impl<tag>::put(detail::unwrap(t), c);
}

template<typename T>
inline void
write(T& t, const BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
{
    typedef typename detail::dispatch<
                T, ostream_tag, streambuf_tag, insert_iterator_tag, output
            >::type tag;
    detail::write_impl<tag>::write(detail::unwrap(t), s, n);
}

template<typename T>
inline std::streamoff
seek( T& t, std::streamoff off, std::ios::seekdir way,
      std::ios::openmode which )
{
    typedef typename detail::dispatch<
                T, iostream_tag, istream_tag, ostream_tag,
                streambuf_tag, detail::two_head, any_tag
            >::type tag;
    return detail::seek_impl<tag>::seek(detail::unwrap(t), off, way, which);
}

template<typename T>
void close(T& t, std::ios::openmode which)
{
    typedef BOOST_IOSTREAMS_CATEGORY(T) category;
    typedef typename
            mpl::eval_if<
                is_convertible<category, closable_tag>,
                mpl::if_<
                    is_convertible<category, detail::two_sequence>,
                    detail::two_sequence,
                    closable_tag
                >,
                mpl::identity<any_tag>
            >::type tag;
    return detail::close_impl<tag>::close(detail::unwrap(t), which);
}

template<typename T, typename Source>
std::streamsize
read(T& t, Source& src, BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
{
    typedef typename detail::dispatch<
                T, multichar_tag, any_tag
            >::type tag;
    return detail::read_filter_impl<tag>::read(detail::unwrap(t), src, s, n);
}

template<typename T, typename Sink>
void write(T& t, Sink& snk, const BOOST_IOSTREAMS_CHAR_TYPE(T)* s, std::streamsize n)
{
    typedef typename detail::dispatch<
                T, multichar_tag, any_tag
            >::type tag;
    detail::write_filter_impl<tag>::write(detail::unwrap(t), snk, s, n);
}

//--------------Implementation of close---------------------------------------//

namespace detail {

        // Implemention of close for filter types.

#include <boost/iostreams/detail/disable_warnings.hpp> // Borland.
template<typename T, typename Sink>
void close_filter( T& t, Sink& snk, std::ios::openmode which,
                   closable_tag, any_tag )
{
    typedef BOOST_IOSTREAMS_CATEGORY(T) category;
    const bool in =  is_convertible<category, input>::value &&
                    !is_convertible<category, output>::value;
    if (in == ((which & std::ios::in) != 0))
        t.close(snk);
}
#include <boost/iostreams/detail/enable_warnings.hpp>

template<typename T, typename Sink>
void close_filter( T& t, Sink& snk, std::ios::openmode which,
                   closable_tag, dual_use )
{ t.close(snk, which); }

template<typename T, typename Sink>
void close_filter( T& t, Sink& snk, std::ios::openmode which,
                   closable_tag, two_sequence )
{ t.close(snk, which); }

template<typename T, typename Sink>
void close_filter( T&, Sink&, std::ios::openmode, any_tag )
{ }

template<typename T, typename Sink>
void close_filter( T& t, Sink& snk, std::ios::openmode which,
                   closable_tag )
{
#if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    typedef io_category<T>::type category;
    close_filter(t, snk, which, closable_tag(), category());
#else
    close_filter(t, snk, which, closable_tag(), get_category(t));
#endif
}

template<typename T, typename Locale>
void imbue(T&, const Locale&, any_tag) { }

// Covers streams as well as localizable filters and devices.
template<typename T, typename Locale>
void imbue(T& t, const Locale& loc, localizable_tag) { t.imbue(loc); }

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc, streambuf_tag) { t.pubimbue(loc); }

} // End namespace detail.

template<typename T, typename Sink>
void close(T& t, Sink& snk, std::ios::openmode which)
{ detail::close_filter(detail::unwrap(t), snk, which, get_category(t)); }

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue(detail::unwrap(t), loc, get_category(t)); }

//--------------Implementation of input_sequence and output_sequence----------//

template<typename T>
inline std::pair<BOOST_IOSTREAMS_CHAR_TYPE(T)*, BOOST_IOSTREAMS_CHAR_TYPE(T)*> 
input_sequence(T& t) { return t.input_sequence(); }

template<typename T>
inline std::pair<BOOST_IOSTREAMS_CHAR_TYPE(T)*, BOOST_IOSTREAMS_CHAR_TYPE(T)*> 
output_sequence(T& t) { return t.output_sequence(); }

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED //-------------------------//
