// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Implementation of fundamental i/o operations for VC6.

namespace boost { namespace iostreams {

//--------------Fundamental i/o operations------------------------------------//

template<typename T> struct operations;

namespace detail {

struct custom_tag { };

template<typename T>
struct is_custom
    : mpl::not_<
          is_base_and_derived< custom_tag, operations<T> >
      >
    { };

// Implementation templates for simulated tag dispatch.
template<typename T> struct read_impl;
template<typename T> struct write_impl;
template<typename T> struct filter_impl;
template<typename T> struct direct_impl;
template<typename T> struct seek_impl;
template<typename T> struct close_impl;
template<typename T> struct flush_device_impl;
template<typename T> struct flush_filter_impl;
template<typename T> struct imbue_impl;
template<typename T> struct optimal_buffer_size_impl;

template<> struct read_impl<int> { typedef int type; };
template<> struct write_impl<int> { typedef int type; };
template<> struct seek_impl<int> { typedef int type; };
template<> struct filter_impl<int> { typedef int type; };
template<> struct direct_impl<int> { typedef int type; };
template<> struct close_impl<int> { typedef int type; };
template<> struct flush_device_impl<int> { typedef int type; };
template<> struct flush_filter_impl<int> { typedef int type; };
template<> struct imbue_impl<int> { typedef int type; };
template<> struct optimal_buffer_size_impl<int> { typedef int type; };

} // End namespace detail.

template<typename T>
struct operations : detail::custom_tag { };

template<typename T>
typename io_int<T>::type get(T& t)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::read_impl<T>::inner<unwrapped>::get(detail::unwrap(t));
}

template<typename T>
inline std::streamsize
read(T& t, typename io_char<T>::type* s, std::streamsize n)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::read_impl<T>::inner<unwrapped>::read(detail::unwrap(t), s, n);
}

template<typename T, typename Source>
std::streamsize
read(T& t, Source& src, typename io_char<T>::type* s, std::streamsize n)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::filter_impl<T>::inner<unwrapped>::read(detail::unwrap(t), src, s, n);
}

template<typename T>
bool putback(T& t, typename io_char<T>::type c)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::read_impl<T>::inner<unwrapped>::putback(detail::unwrap(t), c);
}

template<typename T>
bool put(T& t, typename io_char<T>::type c)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::write_impl<T>::inner<unwrapped>::put(detail::unwrap(t), c);
}

template<typename T>
inline std::streamsize
write(T& t, const typename io_char<T>::type* s, std::streamsize n)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::write_impl<T>::inner<unwrapped>::write(detail::unwrap(t), s, n);
}

template<typename T, typename Sink>
inline std::streamsize
write(T& t, Sink& snk, const typename io_char<T>::type* s, std::streamsize n)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::filter_impl<T>::inner<unwrapped>::write(detail::unwrap(t), snk, s, n);
}

template<typename T>
inline stream_offset
seek( T& t, stream_offset off, BOOST_IOS::seekdir way, 
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ return detail::seek_impl<T>::seek(detail::unwrap(t), off, way, which); }

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME io_char<T>::type*,
    BOOST_DEDUCED_TYPENAME io_char<T>::type*
>
input_sequence(T& t) { return detail::direct_impl<T>::input_sequence(t); }

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME io_char<T>::type*,
    BOOST_DEDUCED_TYPENAME io_char<T>::type*
>
output_sequence(T& t) { return detail::direct_impl<T>::output_sequence(t); }

template<typename T>
void close(T& t, BOOST_IOS::openmode which)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    detail::close_impl<T>::inner<unwrapped>::close(detail::unwrap(t), which);
}

template<typename T, typename Sink>
void close(T& t, Sink& snk, BOOST_IOS::openmode which)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    detail::close_impl<T>::inner<unwrapped>::close(detail::unwrap(t), snk, which);
}

template<typename T>
bool flush(T& t)
{ return detail::flush_device_impl<T>::flush(detail::unwrap(t)); }

template<typename T, typename Sink>
bool flush(T& t, Sink& snk)
{ return detail::flush_filter_impl<T>::flush(detail::unwrap(t), snk); }

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue_impl<T>::imbue(detail::unwrap(t), loc); }

template<typename T>
std::streamsize optimal_buffer_size(const T& t)
{
    typedef detail::optimal_buffer_size_impl<T> impl;
    return impl::optimal_buffer_size(detail::unwrap(t));
}

//--------------definition of non_blocking_adapter----------------------------//

// This can be be moved to its own header once the fundamental i/o operations
// are split into separate headers.
template<typename Device>
class non_blocking_adapter {
public:
    typedef typename io_char<Device>::type             char_type;
    struct io_category
        : io_mode<Device>::type, device_tag
        { };
    explicit non_blocking_adapter(Device& dev) : device_(dev) { }
    std::streamsize read(char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = iostreams::read(device_, s, n);
            if (amt == -1)
                break;
            result += amt;
        }
        return result != 0 ? result : -1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = 
                iostreams::write(device_, s + result, n - result);
            result += amt;
        }
        return result;    
    }
    stream_offset seek( stream_offset off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which = 
                            BOOST_IOS::in | BOOST_IOS::out )
    { return iostreams::seek(device_, off, way, which); }
public:
    Device& device_;
};

//----------------------------------------------------------------------------//

namespace detail {

//------------------Definition of read_impl-----------------------------------//

// Helper function for adding -1 as EOF indicator.
inline std::streamsize check_eof(std::streamsize n) { return n != 0 ? n : -1; }

// Helper templates for reading from streambufs.
template<bool IsLinked>
struct true_eof_impl;

template<>
struct true_eof_impl<true> {
    template<typename T>
    static bool true_eof(T& t) { return t.true_eof(); }
};

template<>
struct true_eof_impl<false> {
    template<typename T>
    static bool true_eof(T& t) { return true; }
};

template<typename T>
inline bool true_eof(T& t)
{
    const bool linked = is_linked<T>::value;
    return true_eof_impl<linked>::true_eof(t);
}

template<typename T>
struct read_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          read_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, istream_tag, streambuf_tag, input
              >::type
          >
      >::type
    { };

template<>
struct read_impl<istream_tag> {
    template<typename T>
    struct inner {
        static typename io_int<T>::type get(T& t)
        { return t.get(); }

        template<typename T>
        static std::streamsize
        read(T& t, typename T::char_type* s, std::streamsize n)
        { return check_eof(t.rdbuf()->sgetn(s, n)); }

        template<typename T>
        static bool putback(T& t, typename io_char<T>::type c)
        {
            typedef typename io_char<T>::type               char_type;
            typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
            return !traits_type::eq_int_type( t.rdbuf()->putback(c),
                                            traits_type::eof() );
        }
    };
};

template<>
struct read_impl<streambuf_tag> {
    template<typename T>
    struct inner {
        static typename io_int<T>::type
        get(T& t)
        {
            typedef typename io_char<T>::type  char_type;
            typedef char_traits<char_type>     traits_type;
            typename io_int<T>::type c;
            return !traits_type::is_eof(c = t.sbumpc()) ||
                    detail::true_eof(t)
                        ?
                    c : traits_type::would_block();
        }

        static std::streamsize
        read(T& t, typename io_char<T>::type* s, std::streamsize n)
        {
            std::streamsize amt;
            return (amt = t.sgetn(s, n)) != 0 ?
                amt :
                detail::true_eof(t) ?
                    -1 :
                    0;
        }

        static bool putback(T& t, typename io_char<T>::type c)
        {
            typedef typename io_char<T>::type  char_type;
            typedef char_traits<char_type>     traits_type;
            return !traits_type::is_eof(t.sputbackc());
        }
    };
};

template<>
struct read_impl<input> {
    template<typename T>
    struct inner {
        static typename io_int<T>::type get(T& t)
        {
            typedef typename io_char<T>::type  char_type;
            typedef char_traits<char_type>     traits_type;
            char_type c;
            std::streamsize amt;
            return (amt = t.read(&c, 1)) == 1 ?
                traits_type::to_int_type(c) :
                amt == -1 ?
                    traits_type::eof() :
                    traits_type::would_block();
        }

        static std::streamsize
        read(T& t, typename io_char<T>::type* s, std::streamsize n)
        { return t.read(s, n); }

        static bool putback(T& t, typename io_char<T>::type c)
        {
            typedef typename io_category<T>::type category;
            BOOST_STATIC_ASSERT((is_convertible<category, peekable_tag>::value));
            return t.putback(c);
        }
    };
};

//------------------Definition of write_impl----------------------------------//

template<typename T>
struct write_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          write_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, ostream_tag, streambuf_tag, output
              >::type
          >
      >::type
    { };

template<>
struct write_impl<ostream_tag> {
    template<typename T>
    struct inner {
        static bool put(T& t, typename io_char<T>::type c)
        {
            typedef typename io_char<T>::type               char_type;
            typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
            return !traits_type::eq_int_type( t.rdbuf()->s.sputc(),
                                            traits_type::eof() );
        }

        static std::streamsize write
            (T& t, const typename T::char_type* s, std::streamsize n)
        { return t.rdbuf()->sputn(s, n); }
    };
};

template<>
struct write_impl<streambuf_tag> {
    template<typename T>
    struct inner {
        static bool put(T& t, typename io_char<T>::type c)
        {
            typedef typename io_char<T>::type               char_type;
            typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
            return !traits_type::eq_int_type(t.sputc(c), traits_type::eof());
        }

        static std::streamsize write
            (T& t, const typename io_char<T>::type* s, std::streamsize n)
        { return t.sputn(s, n); }
    };
};

template<>
struct write_impl<output> {
    template<typename T>
    struct inner {
        static bool put(T& t, typename io_char<T>::type c)
        { return t.write(&c, 1) == 1; }

        static std::streamsize
        write(T& t, const typename io_char<T>::type* s, std::streamsize n)
        { return t.write(s, n); }
    };
};

//------------------Definition of filter_impl---------------------------------//

template<typename T>
struct filter_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          filter_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, multichar_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct filter_impl<multichar_tag> {
    template<typename T>
    struct inner {
        template<typename Source>
        static std::streamsize read
            (T& t, Source& src, typename io_char<T>::type* s, std::streamsize n)
        { return t.read(src, s, n); }

        template<typename Sink>
        static std::streamsize
        write( T& t, Sink& snk, const typename io_char<T>::type* s,
                           std::streamsize n )
        { return t.write(snk, s, n); }
    };
};

template<>
struct filter_impl<any_tag> {
    template<typename T>
    struct inner {
        template<typename Source>
        static std::streamsize read
            (T& t, Source& src, typename io_char<T>::type* s, std::streamsize n)
        {
            typedef typename io_char<T>::type  char_type;
            typedef char_traits<char_type>     traits_type;
            for (std::streamsize off = 0; off < n; ++off) {
                typename traits_type::int_type c = t.get(src);
                if (traits_type::is_eof(c))
                    return check_eof(off);
                if (traits_type::would_block(c))
                    return off;
                s[off] = traits_type::to_char_type(c);
            }
            return n;
        }
        template<typename Sink>
        static std::streamsize
        write( T& t, Sink& snk, const typename io_char<T>::type* s,
               std::streamsize n )
        {
            for (std::streamsize off = 0; off < n; ++off)
                if (!t.put(snk, s[off]))
                    return off;
            return n;
        }
    };
};

//------------------Definition of direct_impl-------------------------------//

template<typename T>
struct direct_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          direct_impl<direct_tag>
      >::type
    { };

template<>
struct direct_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME io_char<U>::type*,
        BOOST_DEDUCED_TYPENAME io_char<U>::type*
    >
    input_sequence(U& u) { return u.input_sequence(); }

    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME io_char<U>::type*,
        BOOST_DEDUCED_TYPENAME io_char<U>::type*
    >
    output_sequence(U& u) { return u.output_sequence(); }
};

//------------------Definition of seek_impl-----------------------------------//

template<typename T>
struct seek_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          seek_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, iostream_tag, istream_tag, ostream_tag,
                  streambuf_tag, two_head, any_tag
              >::type
          >
      >::type
    { };

template<>
struct seek_impl<any_tag> {
    template<typename T>
    static stream_offset seek( T& t, stream_offset off,
                               BOOST_IOS::seekdir way, BOOST_IOS::openmode )
    { return t.seek(off, way); }
};

template<>
struct seek_impl<two_head> {
    template<typename T>
    static stream_offset seek( T& t, stream_offset off,
                               BOOST_IOS::seekdir way,
                               BOOST_IOS::openmode which )
    { return t.seek(off, way, which); }
};

struct seek_impl_basic_ios {
    template<typename T>
    static stream_offset seek( T& t, stream_offset off,
                               BOOST_IOS::seekdir way,
                               BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.rdbuf()->pubseekpos(offset_to_position(off));
        } else {
            return t.rdbuf()->pubseekoff(off, way, which);
        }
    }
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
    static stream_offset seek( T& t, stream_offset off,
                               BOOST_IOS::seekdir way,
                               BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.pubseekpos(offset_to_position(off));
        } else {
            return t.pubseekoff(off, way, which);
        }
    }
};

//------------------Definition of close_impl----------------------------------//

template<typename T>
struct close_tag {
    typedef typename io_category<T>::type category;
    typedef typename
            mpl::eval_if<
                is_convertible<category, closable_tag>,
                mpl::if_<
                    mpl::or_<
                        is_convertible<category, two_sequence>,
                        is_convertible<category, dual_use>
                    >,
                    two_sequence,
                    closable_tag
                >,
                mpl::identity<any_tag>
            >::type type;
};

template<typename T>
struct close_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          close_impl<BOOST_DEDUCED_TYPENAME close_tag<T>::type>
      >::type
    { };

// VC6 has trouble deducing the first template argument in each of the
// following implementation functions, and yields an ICE when it is explicitly
// specified. As a result, for VC6 we have made this template parameter a
// parameter of an enclosing struct 'inner'; the implementation functions each
// have one fewer template parameters than they do for other compilers.

// A consequence is that with VC6 close() cannot be customized for user-defined
// classes by specializing close_impl in the usual way.

template<>
struct close_impl<any_tag> {
    template<typename T>
    struct inner {
        static void close(T&, BOOST_IOS::openmode) { }
        template<typename Sink>
        static void close(T&, Sink&, BOOST_IOS::openmode) { }
    };
};

template<>
struct close_impl<closable_tag> {
    template<typename T>
    struct inner {
        static void close(T& t, BOOST_IOS::openmode which)
        {
            typedef typename io_category<T>::type category;
            const bool in =  is_convertible<category, input>::value &&
                            !is_convertible<category, output>::value;
            if (in == ((which & BOOST_IOS::in) != 0))
                t.close();
        }
        template<typename Sink>
        static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
        {
            typedef typename io_category<T>::type category;
            const bool in =  is_convertible<category, input>::value &&
                            !is_convertible<category, output>::value;
            if (in == ((which & BOOST_IOS::in) != 0))
                t.close(snk);
        }
    };
};

template<>
struct close_impl<two_sequence> {
    template<typename T>
    struct inner {
        static void close(T& t, BOOST_IOS::openmode which) { t.close(which); }
        template<typename Sink>
        static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
        { t.close(snk, which); }
    };
};

//------------------Definition of flush_device_impl---------------------------//

template<typename T>
struct flush_device_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          flush_device_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, ostream_tag, streambuf_tag, flushable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct flush_device_impl<ostream_tag> {
    template<typename T>
    static bool flush(T& t)
    { return t.rdbuf()->BOOST_IOSTREAMS_PUBSYNC() == 0; }
};

template<>
struct flush_device_impl<streambuf_tag> {
    template<typename T>
    static bool flush(T& t)
    { return t.BOOST_IOSTREAMS_PUBSYNC() == 0; }
};

template<>
struct flush_device_impl<flushable_tag> {
    template<typename T>
    static bool flush(T& t) { return t.flush(); }
};

template<>
struct flush_device_impl<any_tag> {
    template<typename T>
    static bool flush(T& t) { return true; }
};

//------------------Definition of flush_filter_impl---------------------------//

template<typename T>
struct flush_filter_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          flush_filter_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, flushable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct flush_filter_impl<flushable_tag> {
    template<typename T, typename Sink>
    static bool flush(T& t, Sink& snk) { return t.flush(snk); }
};

template<>
struct flush_filter_impl<any_tag> {
    template<typename T, typename Sink>
    static bool flush(T& t, Sink& snk) { return false; }
};

//------------------Definition of imbue_impl----------------------------------//

template<typename T>
struct imbue_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          imbue_impl<
              BOOST_DEDUCED_TYPENAME 
              dispatch<
                  T, streambuf_tag, localizable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct imbue_impl<any_tag> {
    template<typename T, typename Locale>
    static void imbue(T&, const Locale&) { }
};

template<>
struct imbue_impl<streambuf_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.pubimbue(loc); }
};

template<>
struct imbue_impl<localizable_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.imbue(loc); }
};

//------------------Definition of optimal_buffer_size_impl--------------------//

template<typename T>
struct optimal_buffer_size_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          optimal_buffer_size_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, optimally_buffered_tag, device_tag, filter_tag
              >::type
          >
      >::type
    { };

template<>
struct optimal_buffer_size_impl<optimally_buffered_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T& t)
    { return t.optimal_buffer_size(); }
};

template<>
struct optimal_buffer_size_impl<device_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T& t)
    { return default_device_buffer_size; }
};

template<>
struct optimal_buffer_size_impl<filter_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T& t)
    { return default_filter_buffer_size; }
};

} // End namespace detail.

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.
