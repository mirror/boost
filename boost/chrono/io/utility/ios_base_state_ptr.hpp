//  boost/chrono/utility/ios_base_pword_ptr.hpp  ------------------------------------------------------------//

//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_UTILITY_IOS_BASE_STATE_PTR_HPP
#define BOOST_CHRONO_UTILITY_IOS_BASE_STATE_PTR_HPP

#include <ios>
#include <boost/assert.hpp>


/**
 *


 */
namespace boost
{
  namespace chrono
  {

    template<typename T>
    class ios_base_state_ptr
    {
    public:
      explicit ios_base_state_ptr(std::ios_base& ios) :
        ios_(ios)
      {
      }
      //ios_base_state_ptr(std::ios_base ios, void (*cleanup_function)(T*));
      ~ios_base_state_ptr()
      {
      }

      T const* get() const BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void* &pw = ios_.pword(index());
        if (pw == 0)
        {
          return 0;
        }
        return static_cast<const T*> (pw);
      }
      T * get() BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void* &pw = ios_.pword(index());
        if (pw == 0)
        {
          return 0;
        }
        return static_cast<T*> (pw);
      }
      T * operator->() BOOST_NOEXCEPT
      {
        return get();
      }
      T const * operator->() const BOOST_NOEXCEPT
      {
        return get();
      }

      T & operator*() BOOST_NOEXCEPT
      {
        return *get();
      }
      T const & operator *() const BOOST_NOEXCEPT
      {
        return *get();
      }

      T * release()BOOST_NOEXCEPT
      {
        T const* f = get();
        reset();
        return f;
      }

      void reset(T* new_value=0) BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void*& pw = ios_.pword(index());
        if (pw != 0)
        {
          delete static_cast<T*> (pw);
        }
        pw = new_value;
      }

      //explicit
      operator bool() const BOOST_NOEXCEPT
      {
        return get()!=0;
      }

      std::ios_base& getios() BOOST_NOEXCEPT
      {
        return ios_;
      }
      std::ios_base& getios() const BOOST_NOEXCEPT
      {
        return ios_;
      }
      operator std::ios_base&() BOOST_NOEXCEPT
      {
        return ios_;
      }
      operator std::ios_base&() const BOOST_NOEXCEPT
      {
        return ios_;
      }
    private:
      static inline bool is_registerd(std::ios_base& ios)
      {
        long iw = ios.iword(index());
        return (iw == 1);
      }
      static inline void set_registered(std::ios_base& ios)
      {
        long& iw = ios.iword(index());
        iw = 1;
      }
      static inline void callback(std::ios_base::event evt, std::ios_base& ios, int index)
      {
        switch (evt)
        {
        case std::ios_base::erase_event:
        {
          void*& pw = ios.pword(index);
          if (pw != 0)
          {
            T* ptr = static_cast<T*> (pw);
            delete ptr;
            pw = 0;
          }
          break;
        }
        case std::ios_base::copyfmt_event:
        {
          void*& pw = ios.pword(index);
          if (pw != 0)
          {
            pw = new T(*static_cast<T*> (pw));
          }
          break;
        }
        default:
          break;
        }
      }

      static inline int index()
      {
        static const int v_ = std::ios_base::xalloc();
        return v_;
      }

      static inline void register_once(int indx, std::ios_base& ios)
      {
        // needs a mask registered
        if (!is_registerd(ios))
        {
          set_registered(ios);
          ios.register_callback(callback, indx);
        }
      }


    protected:
      std::ios_base& ios_;
    };

    /**
     *


     */
    template<typename T>
    class ios_base_state : public ios_base_state_ptr<T>
    {
      typedef ios_base_state_ptr<T> base_type;
    public:
      explicit ios_base_state(std::ios_base& ios) :
      ios_base_state_ptr<T>(ios)
      {
        if (this->get()==0)
        {
          this->base_type::reset(new T());
        }
      }
      //ios_base_state(std::ios_base ios, void (*cleanup_function)(T*));
      ~ios_base_state()
      {
      }

      void reset(T* new_value)BOOST_NOEXCEPT
      {
        BOOST_ASSERT(new_value!=0);
        this->base_type::reset(new_value);
      }

    };


/**
 *
 *
 *
 */
    template<typename Base>
    class ios_base_flags
    {
    public:
      explicit ios_base_flags(std::ios_base& ios) :
        ios_(ios)
      {
      }
      //ios_base_state_ptr(std::ios_base ios, void (*cleanup_function)(T*));
      ~ios_base_flags()
      {
      }

      long flags() const BOOST_NOEXCEPT
      {
        return get();
      }
      long flags(long v) BOOST_NOEXCEPT
      {
        long tmp = flags();
        ref() = v;
        return tmp;
      }

      long setf(long v)
      {
          long tmp = get();
          ref() |= v;
          return tmp;
      }

      void unsetf(long mask)
      {
          ref() &= ~mask;
      }

      long setf(long v, long mask)
      {
          long tmp = get();
          unsetf(mask);
          ref() |= v & mask;
          return tmp;
      }

      operator std::ios_base&() BOOST_NOEXCEPT
      {
        return ios_;
      }
      operator std::ios_base const&() const BOOST_NOEXCEPT
      {
        return ios_;
      }
    private:
      long get() const BOOST_NOEXCEPT
      {
        return ios_.iword(index());
      }
      long& ref() BOOST_NOEXCEPT
      {
        return ios_.iword(index());
      }
      static inline int index()
      {
        static const int v_ = std::ios_base::xalloc();
        return v_;
      }

      std::ios_base& ios_;
    };

  } // namespace chrono
} // namespace boost

#endif // header
