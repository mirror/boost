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

    /**
     * @c ios_base_state_ptr is a smart pointer to a ios_base specific state.
     */
    template<typename T>
    class ios_base_state_ptr
    {
    public:
      /**
       * The pointee type
       */
      typedef T element_type;
      /**
       * Explicit constructor.
       * @param ios the ios
       * @Effects Constructs a @c ios_base_state_ptr by storing the associated @c ios.
       */
      explicit ios_base_state_ptr(std::ios_base& ios) :
        ios_(ios)
      {
      }
      ~ios_base_state_ptr()
      {
      }

      /**
       * @Effects Allocates the index if not already done
       * Registers the callback responsible of maintaining the state pointer coherency, if not already done.
       * Retrieves the associated ios pointer
       * @return the retrieved pointer.
       */
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
      /**
       * @Effects as if @c return get();
       * @return the retrieved pointer.
       */
      T * operator->() BOOST_NOEXCEPT
      {
        return get();
      }
      T const * operator->() const BOOST_NOEXCEPT
      {
        return get();
      }

      /**
       * @Effects as if @c return *get();
       * @return a reference to the retrieved state.
       * @Remark The behavior is undefined if @c get()==0.
       */
      T & operator*() BOOST_NOEXCEPT
      {
        return *get();
      }
      T const & operator *() const BOOST_NOEXCEPT
      {
        return *get();
      }

      /**
       * @Effects reset the current pointer after storing in a temporary variable the pointer to the current state.
       * @return the stored state pointer.
       */
      T * release()BOOST_NOEXCEPT
      {
        T const* f = get();
        reset();
        return f;
      }

      /**
       *
       * @param new_ptr the new pointer.
       * @Effects deletes the current state and replace it with the new one.
       */
      void reset(T* new_ptr=0) BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void*& pw = ios_.pword(index());
        delete static_cast<T*> (pw);
        pw = new_ptr;
      }

      //explicit
      /**
       * Explicit conversion to bool.
       */
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
     * @c ios_base_state is a non null variant of @c ios_base_state_ptr.
     * @tparm T
     * @Requires Must be DefaultConstructible and HeapAllocatable
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
        return value();
      }
      long flags(long v) BOOST_NOEXCEPT
      {
        long tmp = flags();
        ref() = v;
        return tmp;
      }

      long setf(long v)
      {
          long tmp = value();
          ref() |= v;
          return tmp;
      }

      void unsetf(long mask)
      {
          ref() &= ~mask;
      }

      long setf(long v, long mask)
      {
          long tmp = value();
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
      long value() const BOOST_NOEXCEPT
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
