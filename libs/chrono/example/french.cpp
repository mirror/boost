//  french.cpp  ----------------------------------------------------------//

//  Copyright 2010 Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

// Adapted to Boost from the original Hawards's code


#include <boost/chrono/config.hpp>

#if ! defined BOOST_CHRONO_USES_DURATION_PUT
#undef BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
#undef BOOST_CHRONO_IO_USE_XALLOC
#endif

#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <iostream>
#include <locale>

#if defined BOOST_CHRONO_USES_DURATION_PUT
#include <boost/chrono/io/duration_units.hpp>

    using namespace boost;
    using namespace boost::chrono;

    template <typename CharT=char, class OutputIterator = std::ostreambuf_iterator<CharT> >
    class duration_units_fr: public duration_units_default<CharT, OutputIterator>
    {
    public:
      typedef CharT char_type;
      typedef OutputIterator iter_type;

      explicit duration_units_fr(size_t refs = 0) :
        duration_units_default<CharT, OutputIterator>(refs)
      {
      }
    protected:

      std::size_t do_get_plural_form(int_least64_t value) const
      {
        return (value == -1 || value == 0 || value == 1) ? 0 : 1;
      }

      std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<1> , std::size_t pf) const
      {
        static const CharT t[] =
        { 's' };
        static const std::basic_string<CharT> symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 'e' };
        static const std::basic_string<CharT> singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 'e', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }

      std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<60> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'm', 'i', 'n' };
        static const std::basic_string<CharT> symbol(t, t + sizeof (t) / sizeof (t[0]));

        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const std::basic_string<CharT> singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }

      std::basic_string<CharT> do_get_plural_form(duration_style_type style, ratio<3600> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'h' };
        static const std::basic_string<CharT> symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 'h', 'e', 'u', 'r', 'e' };
        static const std::basic_string<CharT> singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'h', 'e', 'u', 'r', 'e', 's' };
        static const std::basic_string<CharT> plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }
    };
#endif

int main()
{
    using std::cout;
    using std::locale;
    using namespace boost;
    using namespace boost::chrono;

#if defined BOOST_CHRONO_USES_DURATION_PUT
    cout.imbue(locale(locale(), new duration_units_fr<>()));
#else

    cout.imbue(locale(locale(), new duration_punct<char>
        (
            duration_style::prefix,
            "secondes", "minutes", "heures",
            "s", "m", "h"
        )));
#endif
    hours h(5);
    minutes m(45);
    seconds s(15);
    milliseconds ms(763);
    cout << h << ", " << m << ", " << s << " et " << ms << '\n';
    cout << hours(0) << ", " << minutes(0) << ", " << s << " et " << ms << '\n';
    return 0;
}
