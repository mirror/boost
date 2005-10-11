///////////////////////////////////////////////////////////////////////////////
// visitor.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_VISITOR_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_VISITOR_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/regex_impl.hpp>
#include <boost/xpressive/detail/static/productions/transmogrify.hpp>
#include <boost/xpressive/detail/core/matcher/mark_begin_matcher.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename BidiIterT>
    struct xpression_visitor_base
    {
        explicit xpression_visitor_base(shared_ptr<regex_impl<BidiIterT> > const &self)
          : impl_()
          , self_(self)
        {
        }

        void swap(xpression_visitor_base &that)
        {
            this->impl_.swap(that.impl_);
            this->self_.swap(that.self_);
        }

        int get_hidden_mark()
        {
            return -(int)(++this->impl_.hidden_mark_count_);
        }

        void mark_number(int mark_number)
        {
            if(0 < mark_number)
            {
                this->impl_.mark_count_ =
                    (std::max)(this->impl_.mark_count_, (std::size_t)mark_number);
            }
        }

        shared_ptr<regex_impl<BidiIterT> > &self()
        {
            return this->self_;
        }

        regex_impl<BidiIterT> &impl()
        {
            return this->impl_;
        }

    protected:

        template<typename MatcherT>
        void visit_(MatcherT const &)
        {
            // no-op
        }

        template<bool ByRefT>
        void visit_(regex_placeholder<BidiIterT, ByRefT> const &rex)
        {
            // when visiting a regex embedded by reference, track the references
            this->impl_.track_reference(rex.impl_);
        }

        void visit_(mark_placeholder const &backref)
        {
            // keep track of the largest mark number found
            this->mark_number(backref.mark_number_);
        }

        void visit_(mark_begin_matcher const &mark_begin)
        {
            // keep track of the largest mark number found
            this->mark_number(mark_begin.mark_number_);
        }

    private:

        regex_impl<BidiIterT> impl_;
        shared_ptr<regex_impl<BidiIterT> > self_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct xpression_visitor
      : xpression_visitor_base<BidiIterT>
    {
        typedef BidiIterT iterator_type;
        typedef ICaseT icase_type;
        typedef TraitsT traits_type;
        typedef typename boost::iterator_value<BidiIterT>::type char_type;

        explicit xpression_visitor(TraitsT const &tr, shared_ptr<regex_impl<BidiIterT> > const &self)
          : xpression_visitor_base<BidiIterT>(self)
          , traits_(tr)
        {
        }

        template<typename MatcherT>
        struct apply
        {
            typedef typename transmogrify<BidiIterT, ICaseT, TraitsT, MatcherT>::type type;
        };

        template<typename MatcherT>
        typename apply<MatcherT>::type
        call(MatcherT const &matcher)
        {
            this->visit_(matcher);
            return transmogrify<BidiIterT, ICaseT, TraitsT, MatcherT>::call(matcher, *this);
        }

        TraitsT const &traits() const
        {
            return this->traits_;
        }

    private:

        TraitsT traits_;
    };

}}}

#endif
