// -*- C++ -*-
//  Boost general library 'format'   ---------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2001
//                  krempp@crans.ens-cachan.fr
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// ideas taken from Rüdiger Loos's format class
// and Karl Nelson's ofstream

// ----------------------------------------------------------------------------
// feed_args.hpp :  functions for processing each argument 
//                      (feed, feed_manip, and distribute)
// ----------------------------------------------------------------------------


#ifndef BOOST_FORMAT_FEED_ARGS_HPP
#define BOOST_FORMAT_FEED_ARGS_HPP

#include "boost/format/format_class.hpp"
#include "boost/format/group.hpp"

#include "boost/format/msvc_disambiguater.hpp"

namespace boost {
namespace io {
namespace detail {
namespace  { 

  template<class Tr, class Ch> inline
  void empty_buf(BOOST_IO_STD basic_ostringstream<Ch,Tr> & os) { 
    static const std::basic_string<Ch, Tr> emptyStr; // avoids 2 cases ( "" and  L"" )
    os.str(emptyStr); 
  }

  template<class Ch, class Tr>
  void do_fill( std::basic_string<Ch,Tr> & s, 
                std::streamsize w, 
                const Ch c, 
                std::ios_base::fmtflags f, 
                bool center) 
  {
    std::streamsize n=w-s.size();
    if(n<=0) {
      return;
    }
    if(center) 
      {
        s.reserve(w); // allocate once for the 2 inserts
        const std::streamsize n1 = n /2, n0 = n - n1; 
        s.insert(s.begin(), n0, c);
        s.append(n1, c);
      } 
    else 
      {
        if(f & std::ios_base::left) {
          s.append(n, c);
        }
        else {
          s.insert(s.begin(), n, c);
        }
      }
  } // -do_fill(..) 


#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
  template< class Ch, class Tr, class T> inline
  void put_head(BOOST_IO_STD basic_ostream<Ch, Tr>& , const T& ) {
  }

  template< class Ch, class Tr, class T> inline
  void put_head( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const group1<T>& x ) {
    os << group_head(x.a1_); // send the first N-1 items, not the last
  }

  template< class Ch, class Tr, class T> inline
  void put_last( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const T& x ) {
    os << x ;
  }

  template< class Ch, class Tr, class T> inline
  void put_last( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const group1<T>& x ) {
    os << group_last(x.a1_); // this selects the last element
  }

#ifdef BOOST_OVERLOAD_FOR_NON_CONST 
  template< class Ch, class Tr, class T> inline
  void put_head( BOOST_IO_STD basic_ostream<Ch, Tr>& , T& ) {
  }

  template< class Ch, class Tr, class T> inline
  void put_last( BOOST_IO_STD basic_ostream<Ch, Tr>& os, T& x ) {
    os << x ;
  }
#endif

#else  // MSVC needs to be tricked to disambiguate this simple overload..
       // the trick is in "boost/format/msvc_disambiguater.hpp"
  
  template< class Ch, class Tr, class T> inline
  void put_head( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const T& x ) {
    disambiguater<Ch, Tr, T>::put_head(os, x, 1L);
  }
  template< class Ch, class Tr, class T> inline
  void put_last( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const T& x ) {
    disambiguater<Ch, Tr, T>::put_last(os, x, 1L);
  }

#endif  // -msvc workaround



  
  template< class Ch, class Tr, class T> 
  void put( T x, 
            const format_item<Ch, Tr>& specs, 
            std::basic_string<Ch, Tr> & res, 
            BOOST_IO_STD basic_ostringstream<Ch, Tr>& oss_ )
  {
    // does the actual conversion of x, with given params, into a string
    // using the *supplied* strinstream. (the stream state is important)

    typedef std::basic_string<Ch, Tr> string_t;
    typedef format_item<Ch, Tr>  format_item_t;

    stream_format_state<Ch, Tr>   prev_state(oss_);
    
    specs.state_.apply_on(oss_);

    // in case x is a group, apply the manip part of it, 
    // in order to find width
    put_head( oss_, x );
    empty_buf( oss_);

    const std::streamsize w=oss_.width();
    const std::ios_base::fmtflags fl=oss_.flags();
    const bool internal = (fl & std::ios_base::internal) != 0;
    const bool two_phased_filling = internal
                                        &&  ! ( specs.pad_scheme_ & format_item_t::spacepad ) 
                                        && specs.truncate_ < 0 ;

    if( w > 0)
      {
        if(two_phased_filling)
          { } // in this case, let the stream do the padding, and later on, we'll do our hack..
        else {
            oss_.width(0);
        }
      }

    put_last( oss_, x);
    res = oss_.str();

    if (specs.truncate_ >= 0)
      res.erase(specs.truncate_);

    // complex fills :

    if(specs.pad_scheme_ & format_item_t::spacepad)
      {
        if( res.size()==0 ||   ( res[0]!='+' && res[0]!='-'  ))
          {
            res.insert(res.begin(), 1, ' '); // insert 1 space at  pos 0
          }
      }

    if(two_phased_filling)
      {
        if( res.size() - w > 0)
          { 
            // either it was one big arg and we have nothing to do about it,
            // either it was multi-output with first output filling up all width..
            empty_buf( oss_);
            oss_.width(0);
            put_last(oss_, x );
            string_t tmp = oss_.str();  // minimal-length output
            std::streamsize d;
            if( (d=w - tmp.size()) >0 ) // hum.. then we need to pad.
              {
                typedef typename string_t::size_type size_type;
                size_type i = 0;
                while( i<tmp.size() && tmp[i] == res[i] ) // find where we should pad.
                  ++i; 
                tmp.insert(i, static_cast<size_type>( d ), oss_.fill());
                std::swap(res, tmp );
              }
            else
              {
                // size is already >= w, so no padding  (cool!)
                std::swap(res, tmp ); 
              }
          }
        else 
          { // okay, only one thing was printed and padded, so res is fine.
          }
      }
    else if(w > 0) // other cases that need do_fill
      {
        do_fill(res,w,oss_.fill(), fl, (specs.pad_scheme_ & format_item_t::centered) !=0 );
      }

    prev_state.apply_on(oss_);
    empty_buf( oss_);
    oss_.clear();
  }

}  // local namespace





template< class Ch, class Tr, class T> 
void distribute(basic_format<Ch,Tr>& self, T x) 
  // call put(x, ..) on every occurence of the current argument :
{
    if(self.cur_arg_ >= self.num_args_)
      {
        if( self.exceptions() & too_many_args_bit )
          throw too_many_args(); // too many variables have been supplied !
        else return;
      }
    for(unsigned long i=0; i < self.items_.size(); ++i)
    {
      if(self.items_[i].argN_ == self.cur_arg_)
      {
          put<Ch, Tr, T> (x, self.items_[i], self.items_[i].res_, self.oss_ );
      }
  }
}


template<class Ch, class Tr, class T> 
basic_format<Ch, Tr>&  feed(basic_format<Ch,Tr>& self, T x) 
{
  if(self.dumped_) self.clear();
  distribute<Ch, Tr, T> (self, x);
  ++self.cur_arg_;
  if(self.bound_.size() != 0)
    {
      while( self.cur_arg_ < self.num_args_ && self.bound_[self.cur_arg_] )
        ++self.cur_arg_;
    }

  // this arg is finished, reset the stream's format state
  self.state0_.apply_on(self.oss_);
  return self;
}
    

} // namespace detail
} // namespace io
} // namespace boost


#endif //  BOOST_FORMAT_FEED_ARGS_HPP
