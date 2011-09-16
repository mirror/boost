//  boost/chrono/duration_style.hpp  ------------------------------------------------------------//
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_DURATION_STYLE_HPP
#define BOOST_CHRONO_DURATION_STYLE_HPP

#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/config.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * Scoped enumeration emulation stating whether the duration I/O style is long or short.
     * prefix_text means duration::rep with whatever stream/locale settings are set for it followed by a long name representing the unit
     * symbol means duration::rep with whatever stream/locale settings are set for it followed by a SI unit abbreviation
     */
    struct duration_style
    {
      enum type {
        prefix_text, symbol
      };
    };


    /**
     * duration parameterized manipulator.
     */
    class duration_fmt
    {
      duration_style::type style_;
    public:

      /**
       * explicit manipulator constructor from a @c duration_style
       */
      explicit duration_fmt(duration_style::type style) BOOST_CHRONO_NOEXCEPT
      : style_(style)
      {}

#ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
      /**
       * explicit conversion to the @c duration_style scoped enum.
       */
      explicit
      operator duration_style::type() const BOOST_CHRONO_NOEXCEPT
      { return style_;}
#endif

      /**
       * gets the @c duration_style scoped enum.
       */
      duration_style::type get_duration_style() const BOOST_CHRONO_NOEXCEPT
      { return style_;}
    };

    /**
     * Change the duration_punc facet associated to the output stream depending on the duration_format style parameter.
     */
    template<class charT, class traits>
    std::basic_ostream<charT, traits>&
    operator <<(std::basic_ostream<charT, traits>& os, duration_fmt d)
    {
      if (d.get_duration_style() == duration_style::symbol)
        os << duration_short;
      else if (d.get_duration_style() == duration_style::prefix_text)
        os << duration_long;
      return os;
    }

    /**
     * Change the duration_punc facet associated to the input stream depending on the duration_format style parameter.
     */
    template<class charT, class traits>
    std::basic_istream<charT, traits>&
    operator >>(std::basic_istream<charT, traits>& is, duration_fmt d)
    {
      if (d.get_duration_style() == duration_style::symbol)
        is >> duration_short;
      else if (d.get_duration_style() == duration_style::prefix_text)
        is >> duration_long;
      return is;
    }

    /**
     * duration_style i/o saver.
     *
     * See Boost.IO i/o state savers for a motivating compression.
     */
    template<typename CharT = char, typename Traits = std::char_traits<CharT> >
    struct duration_style_io_saver
    {

      //! the type of the state to restore
      typedef std::basic_ios<CharT, Traits> state_type;
      //! the type of aspect to save
      typedef duration_style::type aspect_type;

      /**
       * Explicit construction from an i/o stream.
       *
       * Store a reference to the i/o stream and the value of the associated @c duration_style.
       */
      explicit duration_style_io_saver(state_type &s) :
        s_save_(s)
      {
        typedef duration_punct<CharT> Facet;
        std::locale loc = s_save_.getloc();
        if (!std::has_facet<Facet>(loc))
          s_save_.imbue(std::locale(loc, new Facet()));

        const Facet& f = std::use_facet<Facet>(loc);
        if (f.is_long_name())
          a_save_ = duration_style::prefix_text;
        else
          a_save_ = duration_style::symbol;
      }

      /**
       * Construction from an i/o stream and a @c duration_style to restore.
       *
       * Stores a reference to the i/o stream and the value @c duration_style to restore given as parameter.
       */
      duration_style_io_saver(state_type &s, aspect_type new_value) :
        s_save_(s), a_save_(new_value)
      {
      }

      /**
       * Destructor.
       *
       * Restores the i/o stream with the duration_style to be restored.
       */
      ~duration_style_io_saver()
      {
        this->restore();
      }

      /**
       * Restores the i/o stream with the duration_style to be restored.
       */
      void restore()
      {
        s_save_ << duration_fmt(a_save_);
      }
    private:
      state_type& s_save_;
      aspect_type a_save_;
    };

  } // namespace chrono
} // namespace boost


#endif
