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

#include <boost/format/format_class.hpp>
#include <boost/format/group.hpp>

#include <boost/format/detail/msvc_disambiguater.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace io {
namespace detail {
namespace  { 

    template<class Ch, class Tr> inline
    void clear_buffer(io::basic_outsstream<Ch,Tr> & os) { 
        os.clear_buffer();
    }

    template<class Ch, class Tr>
    void mk_str( std::basic_string<Ch,Tr> & res, 
                 const Ch * beg,
                 std::streamsize size,
                 std::streamsize w, 
                 const Ch c, 
                 std::ios_base::fmtflags f, 
                 int prefix_space, // 0 or 1
                 bool center) 
        // applies centered / left / right  padding  to the string  [beg, beg+size[
        // Effects : the result is placed in res.
    {
        res.resize(0);
        std::streamsize n=w-size - prefix_space;
        std::streamsize n_after = 0, n_before = 0; 

        if(n<=0) { // no need to pad.
            res.reserve(size + prefix_space);
        }
        else { 
            res.reserve(w); // allocate once for the 2 inserts
            if(center) 
                n_after = n/2, n_before = n - n_after; 
            else 
                if(f & std::ios_base::left)
                    n_after = n;
                else
                    n_before = n;
        }
    
        // now make the res string :
        if(n_before) res.append(n_before, c);
        if(prefix_space) 
            res.append(1,' ');
        res.append(beg, size);
        if(n_after) res.append(n_after, c);

    } // -mk_str(..) 


#if BOOST_WORKAROUND( BOOST_MSVC, <= 1300) 
// MSVC needs to be tricked to disambiguate this simple overload..
// the trick is in "boost/format/msvc_disambiguater.hpp"
  
    template< class Ch, class Tr, class T> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const T& x ) {
        disambiguater<Ch, Tr, T>::put_head(os, x, 1L);
    }
    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr>& os, const T& x ) {
        disambiguater<Ch, Tr, T>::put_last(os, x, 1L);
    }

#else  

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

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST 
    template< class Ch, class Tr, class T> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr>& , T& ) {
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr>& os, T& x ) {
        os << x ;
    }
#endif
#endif  // -msvc workaround



  
    template< class Ch, class Tr, class T> 
    void put( T x, 
              const format_item<Ch, Tr>& specs, 
              std::basic_string<Ch, Tr> & res, 
              io::basic_outsstream<Ch, Tr>& oss_ )
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
        // clear_buffer( oss_); // fixme. is it necessary ?

        const std::ios_base::fmtflags fl=oss_.flags();
        const bool internal = (fl & std::ios_base::internal) != 0;
        // internal can be implied by zeropad, or user-set.
        // left, right, and centered alignment overrule internal,
        // but spacepad & internal ??  fixme

        const std::streamsize w = oss_.width();
        const bool two_stepped_padding = internal && (w != 0)  && specs.truncate_ < 0 ;
      

        res.resize(0);
        if(! two_stepped_padding) {
            if(w>0) 
                oss_.width(0); // handle simple padding via mk_str, not natively in stream 
            put_last( oss_, x);
            const Ch * res_beg = oss_.begin();
            std::streamsize res_size = oss_.pcount();
            if (specs.truncate_ >= 0 && specs.truncate_ < res_size )
                res_size =  specs.truncate_;

            // complex pads :
            int prefix_space = 0;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if( res_size == 0 ||   ( res_beg[0] !='+' && res_beg[0] !='-'  ))
                    prefix_space = 1;

            mk_str(res, res_beg, res_size, w, oss_.fill(), fl, 
                   prefix_space, (specs.pad_scheme_ & format_item_t::centered) !=0 );
        } 
        else  { // 2-stepped padding 
            put_last( oss_, x); // oss_.width() may result in padding.
            const Ch * res_beg = oss_.begin();
            std::streamsize res_size = oss_.pcount();

            if (specs.truncate_ >= 0 && specs.truncate_ < res_size )
                res_size =  specs.truncate_;

            if( res_size  == w) { // okay, only one thing was printed and padded, so res is fine.
                res.assign(res_beg, res_size);
            }
            else { //   length w exceeded
                BOOST_ASSERT(res_size > w);
                // either it was multi-output with first output padding up all width..
                // either it was one big arg and we are fine.
                res.assign(res_beg, res_size);
                res_beg=NULL;  // invalidate pointers.
                clear_buffer( oss_);
                oss_.width(0);
                put_last(oss_, x );
                // minimal-length output
                const Ch * tmp_beg = oss_.begin();
                std::streamsize tmp_size = oss_.pcount();
                BOOST_ASSERT( static_cast<size_t>(tmp_size) <= res.size() );
          
                std::streamsize d;
                if( (d=w - tmp_size) <=0 ) { 
                    // minimal length is already >= w, so no padding (cool!)
                    if(static_cast<size_t>(tmp_size)==res.size()) 
                        ; // res==tmp, so res is good.
                    else 
                        res.assign(tmp_beg, tmp_size);
                }
                else { // hum..  we need to pad (it was necessarily multi-output)
                    typedef typename string_t::size_type size_type;
                    std::streamsize i = 0;
                    while( i<tmp_size && tmp_beg[i] == res[i] ) //find where we should pad
                        ++i;
                    res.assign(tmp_beg, i);
                    res.append(static_cast<size_type>( d ), oss_.fill());
                    res.append(tmp_beg+i, tmp_size-i );
                }
            }
        }
        prev_state.apply_on(oss_);
        clear_buffer( oss_);
        oss_.clear();
    } // end- put(..)

}  // local namespace




    template< class Ch, class Tr, class T> 
    void distribute(basic_format<Ch,Tr>& self, T x) 
        // call put(x, ..) on every occurence of the current argument :
    {
        if(self.cur_arg_ >= self.num_args_)
            {
                if( self.exceptions() & too_many_args_bit )
                    boost::throw_exception(too_many_args()); // too many variables supplied
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
