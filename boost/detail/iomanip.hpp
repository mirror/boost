/*==============================================================================
    Copyright (c) 2010-2011 Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_DETAIL_IOMANIP_HPP
#define BOOST_DETAIL_IOMANIP_HPP

#include <boost/config.hpp>

#if (defined(BOOST_CLANG) || defined(BOOST_INTEL_LINUX)) && \
    defined(BOOST_GNU_STDLIB) 
  #include <ios>
  #include <istream>
  #include <ostream>
  
  namespace boost {
  namespace detail {
  
  //[resetiosflags
  class resetiosflags_manip {
   private:
    std::ios_base::fmtflags mask;
  
   public:
    explicit resetiosflags_manip (std::ios_base::fmtflags m):
      mask(m) { }
  
    template<class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>&
    operator>> (std::basic_istream<CharT, Traits>& is,
                resetiosflags_manip const& x)
    {
      is.unsetf(x.mask);
      return is;
    }
  
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits>& os,
                resetiosflags_manip const& x)
    {
      os.unsetf(x.mask);
      return os;
    }
  };
  
  inline resetiosflags_manip resetiosflags (std::ios_base::fmtflags mask) {
    return resetiosflags_manip(mask);
  }
  //]
  
  //[setiosflags
  class setiosflags_manip {
   private:
    std::ios_base::fmtflags mask;
  
   public:
    explicit setiosflags_manip (std::ios_base::fmtflags m):
      mask(m) { }
  
    template<class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>&
    operator>> (std::basic_istream<CharT, Traits>& is,
                setiosflags_manip const& x) {
      is.setf(x.mask);
      return is;
    }
  
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits>& os,
                setiosflags_manip const& x) {
      os.setf(x.mask);
      return os;
    }
  };
  
  inline setiosflags_manip setiosflags (std::ios_base::fmtflags mask) {
    return setiosflags_manip(mask);
  }
  //]
  
  //[setbase
  class setbase_manip {
   private:
    int base;
  
   public:
    explicit setbase_manip (int b):
      base(b) { }
  
    template<class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>&
    operator>> (std::basic_istream<CharT, Traits>& is, setbase_manip const& x) {
      using namespace std;
      switch (x.base) {
        case 8:
          is << std::oct; 
          return is;
        case 10:
          is << std::dec;
          return is;
        case 16:
          is << std::hex; 
          return is;
        default:
          is.setf(ios_base::fmtflags(0), ios_base::basefield);
          return is;
      }
    }
  
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits>& os, setbase_manip const& x) {
      using namespace std;
      switch (x.base) {
        case 8:
          os << std::oct; 
          return os;
        case 10:
          os << std::dec;
          return os;
        case 16:
          os << std::hex; 
          return os;
        default:
          os.setf(ios_base::fmtflags(0), ios_base::basefield);
          return os;
      }
    }
  };
  
  inline setbase_manip setbase (int base) {
    return setbase_manip(base);
  }
  //]
  
  //[setfill
  template<class CharT>
  class setfill_manip {
   private:
    CharT fill;
  
   public:
    explicit setfill_manip (CharT c):
      fill(c) { }
  
    template<class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits>& os, setfill_manip const& x) {
      os.fill(x.fill);
      return os;
    }
  };
  
  template<class CharT>
  inline setfill_manip<CharT> setfill (CharT c) {
    return setfill_manip<CharT>(c);
  }
  //]
  
  //[setprecision
  class setprecision_manip {
   private:
    int n;
  
   public:
    explicit setprecision_manip (int n_):
      n(n_) { }
  
    template<class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>&
    operator>> (std::basic_istream<CharT, Traits>& is,
                setprecision_manip const& x) {
      is.precision(x.n);
      return is;
    }
  
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits>& os,
                setprecision_manip const& x) {
      os.precision(x.n);
      return os;
    }
  };
  
  inline setprecision_manip setprecision (int n_) {
    return setprecision_manip(n_);
  }
  //]
  
  //[setw
  class setw_manip {
   private: 
    int n;
  
   public:
    explicit setw_manip (int n_):
      n(n_) { }
  
    template<class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>&
    operator>> (std::basic_istream<CharT, Traits>& is, setw_manip const& x) {
      is.width(x.n);
      return is;
    }
  
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits>& os, setw_manip const& x) {
      os.width(x.n);
      return os;
    }
  };
  
  inline setw_manip setw (int n_) {
    return setw_manip(n_);
  }
  //]

  } // detail
  } // boost

#else
  #include <iomanip>

  namespace boost {
  namespace detail {

  using ::std::resetiosflags;
  using ::std::setiosflags;
  using ::std::setbase;
  using ::std::setfill;
  using ::std::setprecision;
  using ::std::setw;

  } // detail
  } // boost

#endif

#endif // BOOST_DETAIL_IOMANIP_HPP
