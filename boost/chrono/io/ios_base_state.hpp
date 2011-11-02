//  boost/chrono/io/ios_base_state.hpp
//
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_IOS_BASE_STATE_HPP
#define BOOST_CHRONO_IO_IOS_BASE_STATE_HPP

#include <boost/chrono/config.hpp>
#include <locale>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/timezone.hpp>

namespace boost
{
  namespace chrono
  {
    namespace detail
    {

      enum chrono_fmt_masks
      {
        duration_style_mask = 1 << 0, timezone_mask = 1 << 1, registerd_callback_mask = 1 << 2
      };
      inline int chrono_io_masks_index()
      {
        static const int v_ = std::ios_base::xalloc();
        return v_;
      }
      inline bool is_registerd(std::ios_base & ios)
      {
        long iw = ios.iword(chrono_io_masks_index());
        return (iw & registerd_callback_mask);
      }
      inline void set_registered(std::ios_base& ios)
      {
        long& iw = ios.iword(chrono_io_masks_index());
        iw |= registerd_callback_mask;
      }
    }// detail

    inline duration_style::type get_duration_style(std::ios_base & ios)
    {
      long iw = ios.iword(detail::chrono_io_masks_index());
      return (iw & detail::duration_style_mask) ? duration_style::symbol : duration_style::prefix;
    }
    inline void set_duration_style(std::ios_base& ios, duration_style::type style)
    {
      long& iw = ios.iword(detail::chrono_io_masks_index());
      iw &= ~detail::duration_style_mask;
      iw |= (style ? detail::duration_style_mask : 0);
    }

    inline timezone_type get_timezone(std::ios_base & ios)
    {
      long iw = ios.iword(detail::chrono_io_masks_index());
      return (iw & detail::timezone_mask) ? timezone::local : timezone::utc;
    }
    inline void set_timezone(std::ios_base& ios, timezone_type style)
    {
      long& iw = ios.iword(detail::chrono_io_masks_index());
      iw &= ~detail::timezone_mask;
      iw |= (style ? detail::timezone_mask : 0);
    }

    namespace detail
    {

      template<typename CharT>
      class ios_base_data
      {
      public:

        ios_base_data() :
          time_fmt_(""),
          duration_fmt_("")
        {
        }

        static inline ios_base_data<CharT>& instance(std::ios_base & ios)
        {
          register_once(index(), ios);
          void* &pw = ios.pword(index());
          if (pw == 0)
          {
            pw = new ios_base_data<CharT>();
          }
          return *static_cast<ios_base_data<CharT>*> (pw);
        }

        inline std::basic_string<CharT> get_time_fmt()
        {
          return time_fmt_;
        }
        inline void set_time_fmt(std::basic_string<CharT> fmt)
        {
          time_fmt_=fmt;
        }
        inline std::basic_string<CharT> get_duration_fmt()
        {
          return duration_fmt_;
        }
        inline void set_duration_fmt(std::basic_string<CharT> fmt)
        {
          duration_fmt_=fmt;
        }
      private:
        static inline void callback(std::ios_base::event evt, std::ios_base& ios, int index)
        {
          switch (evt)
          {
          case std::ios_base::erase_event:
          {
            void*& pw = ios.pword(index);
            if (pw != 0)
            {
              ios_base_data* tmi = static_cast<ios_base_data<CharT>*> (pw);
              delete tmi;
              pw = 0;
            }
            break;
          }
          case std::ios_base::copyfmt_event:
          {
            void*& pw = ios.pword(index);
            if (pw != 0)
            {
              pw = new ios_base_data(*static_cast<ios_base_data<CharT>*> (pw));
            }
            break;
          }
          default:
            break;
          }
        }

        static inline void register_once(int index, std::ios_base& ios)
        {
          if (!detail::is_registerd(ios))
          {
            detail::set_registered(ios);
            ios.register_callback(callback, index);
          }
        }

        static inline int index()
        {
          static const int v_ = std::ios_base::xalloc();
          return v_;
        }

        std::basic_string<CharT> time_fmt_;
        std::basic_string<CharT> duration_fmt_;

      };

    } // detail

    template<typename CharT>
    static inline std::basic_string<CharT> get_time_fmt(std::ios_base & ios)
    {
      return detail::ios_base_data<CharT>::instance(ios).get_time_fmt();
    }
    template<typename CharT>
    static inline void set_time_fmt(std::ios_base& ios, std::basic_string<
        CharT> fmt)
    {

      detail::ios_base_data<CharT>::instance(ios).set_time_fmt(fmt);

    }
  } // chrono
} // boost

#endif  // header
