///////////////////////////////////////////////////////////////////////////////
// as_set.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_SET_HPP_EAN_04_05_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_SET_HPP_EAN_04_05_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/sizeof.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>

namespace boost { namespace xpressive { namespace detail
{

    template<typename Grammar>
    struct increment
      : Grammar
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
          : mpl::next<typename Grammar::template apply<Expr, State, Visitor>::type>
        {};
    };

    struct SetSize
      : proto::or_<
            increment<proto::trans::left<proto::comma<SetSize, proto::terminal<char> > > >
          , proto::trans::always<proto::assign<set_initializer_type, proto::terminal<char> >, mpl::int_<1> >
        >
    {};

    template<typename Char>
    struct SetFillContext
      : proto::callable_context<SetFillContext<Char> >
    {
        explicit SetFillContext(Char *buf)
          : buffer(buf)
          , index(0)
        {}

        typedef xpressive::detail::set_initializer result_type;

        template<typename Tag, typename Left, typename Right>
        result_type operator()(Tag, Left const &left, Right const &ch)
        {
            this->buffer[this->index++] = proto::arg(ch);
            return proto::eval(left, *this);
        }

        Char *buffer;
        int index;
    };

    template<typename Grammar>
    struct as_list_set
      : Grammar
    {
        as_list_set();

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef set_matcher<
                typename Visitor::traits_type
              , SetSize::apply<Expr, State, Visitor>::type::value
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typename apply<Expr, State, Visitor>::type set(visitor.traits());
            SetFillContext<typename Visitor::char_type> ctx(set.set_);
            proto::eval(expr, ctx);
            int const size = SetSize::apply<Expr, State, Visitor>::type::value;
            for(int i = 0; i < size; ++i)
            {
                set.set_[i] = visitor.traits().translate(set.set_[i]);
            }
            return set;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // charset_context
    //
    template<typename Grammar, typename CharSet, typename Visitor>
    struct charset_context
    {
        template<typename Expr, typename Tag>
        struct eval_
        {
            typedef void result_type;
            void operator()(Expr const &expr, charset_context const &ctx) const
            {
                ctx.set(Grammar::call(expr, end_xpression(), ctx.visitor_));
            }
        };

        template<typename Expr>
        struct eval_<Expr, proto::tag::bitwise_or>
        {
            typedef void result_type;
            void operator()(Expr const &expr, charset_context const &ctx) const
            {
                proto::eval(proto::left(expr), ctx);
                proto::eval(proto::right(expr), ctx);
            }
        };

        // Gah, this is to work around a MSVC bug.
        template<typename Expr>
        struct eval
          : eval_<Expr, typename Expr::tag_type>
        {};

        typedef typename Visitor::traits_type traits_type;
        typedef typename CharSet::char_type char_type;
        typedef typename CharSet::icase_type icase_type;

        explicit charset_context(CharSet &charset, Visitor &visitor)
          : charset_(charset)
          , visitor_(visitor)
        {}

        template<bool Not>
        void set(literal_matcher<traits_type, icase_type::value, Not> const &ch) const
        {
            // BUGBUG fixme!
            BOOST_MPL_ASSERT_NOT((mpl::bool_<Not>));
            set_char(this->charset_.charset_, ch.ch_, this->visitor_.traits(), icase_type());
        }

        void set(range_matcher<traits_type, icase_type::value> const &rg) const
        {
            // BUGBUG fixme!
            BOOST_ASSERT(!rg.not_);
            set_range(this->charset_.charset_, rg.ch_min_, rg.ch_max_, this->visitor_.traits(), icase_type());
        }

        template<int Size>
        void set(set_matcher<traits_type, Size> const &set_) const
        {
            // BUGBUG fixme!
            BOOST_ASSERT(!set_.not_);
            for(int i=0; i<Size; ++i)
            {
                set_char(this->charset_.charset_, set_.set_[i], this->visitor_.traits(), icase_type::value);
            }
        }

        void set(posix_charset_matcher<traits_type> const &posix) const
        {
            set_class(this->charset_.charset_, posix.mask_, posix.not_, this->visitor_.traits());
        }

        CharSet &charset_;
        Visitor &visitor_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Grammar>
    struct as_set
      : Grammar
    {
        as_set();

        template<typename, typename, typename Visitor>
        struct apply
        {
            typedef typename Visitor::char_type char_type;

            // if sizeof(char_type)==1, merge everything into a basic_chset
            // BUGBUG this is not optimal.
            typedef typename mpl::if_<
                mpl::equal_to<mpl::sizeof_<char_type>, mpl::size_t<1> >
              , basic_chset<char_type>
              , compound_charset<typename Visitor::traits_type>
            >::type charset_type;

            typedef charset_matcher<
                typename Visitor::traits_type
              , Visitor::icase_type::value
              , charset_type
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef typename apply<Expr, State, Visitor>::type set_type;
            set_type matcher;
            charset_context<Grammar, set_type, Visitor> ctx(matcher, visitor);
            // Walks the tree and fills in the charset
            proto::eval(expr, ctx);
            return matcher;
        }
    };

    template<typename Grammar>
    struct inverse
      : Grammar
    {
        inverse();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : Grammar::template apply<Expr, State, Visitor>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typename apply<Expr, State, Visitor>::type set =
                Grammar::call(expr, state, visitor);
            set.inverse();
            return set;
        }
    };

}}}

#endif
