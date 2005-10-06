///////////////////////////////////////////////////////////////////////////////
// charset_transforms.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_CHARSET_TRANSFORMS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_CHARSET_TRANSFORMS_HPP_EAN_10_04_2005

#include <boost/mpl/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/utility/never_true.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // charset_state
    //
    template<typename CharSetT, typename TraitsT>
    struct charset_state
    {
        typedef TraitsT traits_type;
        typedef typename CharSetT::char_type char_type;
        typedef typename CharSetT::icase_type icase_type;
      
        explicit charset_state(CharSetT &charset, traits_type const &traits)
          : charset_(charset)
          , traits_(traits)
        {
        }

        template<bool NotT>
        void set(literal_matcher<traits_type, icase_type::value, NotT> const &ch) const
        {
            // BUGBUG fixme!
            BOOST_MPL_ASSERT_NOT((mpl::bool_<NotT>));
            set_char(this->charset_.charset_, ch.ch_, this->traits_, icase_type());
        }

        void set(range_matcher<traits_type, icase_type::value> const &rg) const
        {
            // BUGBUG fixme!
            BOOST_ASSERT(!rg.not_);
            set_range(this->charset_.charset_, rg.ch_min_, rg.ch_max_, this->traits_, icase_type());
        }

        template<int SizeT>
        void set(set_matcher<traits_type, SizeT> const &set_) const
        {
            // BUGBUG fixme!
            BOOST_ASSERT(!set_.not_);
            for(int i=0; i<SizeT; ++i)
            {
                set_char(this->charset_.charset_, set_.set_[i], this->traits_, icase_type::value);
            }
        }

        void set(posix_charset_matcher<traits_type, icase_type::value> const &posix) const
        {
            set_class(this->charset_.charset_, posix.mask_, posix.not_, this->traits_, icase_type::value);
        }

        template<typename UnknownT>
        void set(UnknownT const &) const
        {
            // If this assert fires, it means that you have put something in a set[] that doesn't
            // belong there. For instance, set["hello"]. Legal members of sets are characters, 
            // character ranges, list-initialized sets such as (set='a','b','c') and posix-style
            // character sets such as digit and ~alpha.
            BOOST_MPL_ASSERT((never_true<UnknownT>));
        }

    private:
        CharSetT &charset_;
        traits_type const &traits_;
    };

    template<typename CharSetT, typename TraitsT>
    charset_state<CharSetT, TraitsT> make_charset_state(CharSetT &charset, TraitsT const &traits)
    {
        return charset_state<CharSetT, TraitsT>(charset, traits);
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    struct charset_transform
    {
        template<typename, typename, typename VisitorT>
        struct apply
        {
            typedef typename VisitorT::char_type char_type;

            // if sizeof(char_type)==1, merge everything into a basic_chset
            // BUGBUG this is not optimal.
            typedef typename mpl::if_
            <
                mpl::equal_to<mpl::sizeof_<char_type>, mpl::size_t<1> >
              , basic_chset<char_type>
              , compound_charset<typename VisitorT::traits_type>
            >::type charset_type;

            typedef charset_matcher
            <
                typename VisitorT::traits_type
              , VisitorT::icase_type::value
              , charset_type
            > matcher_type;

            typedef proto::unary_op<matcher_type, proto::noop_tag> type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor, bool complement = false)
        {
            typedef typename apply<OpT, StateT, VisitorT>::matcher_type matcher_type;
            matcher_type matcher;
            // Walks the tree and fills in the charset
            proto::compile(proto::right(op), make_charset_state(matcher, visitor.traits()), visitor, set_tag());
            if(complement)
            {
                matcher.charset_.inverse();
            }
            return proto::noop(matcher);
        }
    };

}}}

#endif

