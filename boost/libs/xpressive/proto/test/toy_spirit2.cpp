///////////////////////////////////////////////////////////////////////////////
// toy_spirit2.cpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cctype>
#include <string>
#include <iomanip>
#include <iostream>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/construct.hpp>
#include <boost/xpressive/proto/transform/fold_to_list.hpp>
#if BOOST_VERSION < 103500
# include <boost/spirit/fusion/algorithm/for_each.hpp>
# include <boost/spirit/fusion/algorithm/fold.hpp>
# include <boost/spirit/fusion/algorithm/any.hpp>
#else
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/algorithm/query/any.hpp>
#endif
#include <boost/test/unit_test.hpp>

namespace boost
{
    // global tags
    struct char_tag {};
    struct space_tag {};

    // global primitives
    proto::terminal<char_tag>::type const char_ = {{}};
    proto::terminal<space_tag>::type const space = {{}};

    using proto::lit;
    using proto::literal;
}

namespace boost { namespace spirit2
{
    namespace utility
    {
        inline bool char_icmp(char ch, char lo, char hi)
        {
            return ch == lo || ch == hi;
        }

        template<typename FwdIter>
        inline bool string_cmp(char const *sz, FwdIter &begin, FwdIter end)
        {
            FwdIter tmp = begin;
            for(; *sz; ++tmp, ++sz)
                if(tmp == end || *tmp != *sz)
                    return false;
            begin = tmp;
            return true;
        }

        template<typename FwdIter>
        inline bool string_icmp(std::string const &str, FwdIter &begin, FwdIter end)
        {
            BOOST_ASSERT(0 == str.size() % 2);
            FwdIter tmp = begin;
            std::string::const_iterator istr = str.begin(), estr = str.end();
            for(; istr != estr; ++tmp, istr += 2)
                if(tmp == end || *tmp != *istr && *tmp != *(istr+1))
                    return false;
            begin = tmp;
            return true;
        }

        inline bool in_range(char ch, char lo, char hi)
        {
            return ch >= lo && ch <= hi;
        }

        inline bool in_irange(char ch, char lo, char hi)
        {
            return in_range(ch, lo, hi)
                || in_range(std::tolower(ch), lo, hi)
                || in_range(std::toupper(ch), lo, hi);
        }

        inline std::string to_istr(char const *sz)
        {
            std::string res;
            res.reserve(std::strlen(sz) * 2);
            for(; *sz; ++sz)
            {
                res.push_back(std::tolower(*sz));
                res.push_back(std::toupper(*sz));
            }
            return res;
        }
    } // namespace utility

    // Composite parser that contains a Fusion cons-list of other parsers
    // OR
    // A compiler that compiles an expression and wraps the result in 
    // a composite<> wrapper
    template<typename Tag, typename List>
    struct composite
    {
        composite(List const &list)
          : elems(list)
        {}

        List elems;
    };

    template<typename Tag, typename Grammar>
    struct as_composite
      : Grammar
    {
        as_composite();

        // The apply<> struct and the call() member are to satisfy the
        // proto compiler/transform protocol
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef composite<
                Tag
              , typename Grammar::template apply<Expr, State, Visitor>::type
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return typename apply<Expr, State, Visitor>::type
                (Grammar::call(expr, state, visitor));
        }
    };

    struct char_range
      : std::pair<char, char>
    {
        char_range(char from, char to)
          : std::pair<char, char>(from, to)
        {}
    };

    struct ichar
    {
        ichar(char ch)
          : lo_(std::tolower(ch))
          , hi_(std::toupper(ch))
        {}

        char lo_, hi_;
    };

    struct istr
    {
        istr(char const *sz)
          : str_(utility::to_istr(sz))
        {}

        std::string str_;
    };

    struct ichar_range
      : std::pair<char, char>
    {
        ichar_range(char_range const &rng)
          : std::pair<char, char>(rng)
        {}
    };

    // The no-case directive
    struct no_case_tag {};

    // The no-case transform, applies the tree-transform with
    // mpl::true_ as the visitor.
    template<typename Grammar>
    struct no_case_transform
      : Grammar
    {
        no_case_transform();

        template<typename Expr, typename State, typename>
        struct apply
          : Grammar::template apply<Expr, State, mpl::true_>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &)
        {
            mpl::true_ case_sensitive;
            return Grammar::call(expr, state, case_sensitive);
        }
    };

    // remove_case specializations for stripping case-sensitivity from parsers
    template<typename T, bool CaseSensitive>
    struct remove_case
    {
        typedef T type;
        template<typename U> static U const &call(U const &t)
        {
            return t;
        }
    };

    template<>
    struct remove_case<char, true>
    {
        typedef ichar type;
        static ichar call(char ch)
        {
            return ichar(ch);
        }
    };

    template<>
    struct remove_case<char const *, true>
    {
        typedef istr type;
        static istr call(char const *sz)
        {
            return istr(sz);
        }
    };

    template<typename T, std::size_t N>
    struct remove_case<T(&)[N], true>
      : remove_case<char const *, true>
    {};

    template<>
    struct remove_case<char_range, true>
    {
        typedef ichar_range type;
        static ichar_range call(char_range const &rng)
        {
            return ichar_range(rng);
        }
    };

    // A case-sensitive transform that removes case conditionally, depending on
    // a compile-time flag carried by the visitor.
    template<typename Grammar>
    struct case_sensitive
      : Grammar
    {
        case_sensitive();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : remove_case<
                typename Grammar::template apply<Expr, State, Visitor>::type
              , Visitor::value
            >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)       
        {
            return apply<Expr, State, Visitor>::call(Grammar::call(expr, state, visitor));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// Begin ToySpiritGrammar here
    ///////////////////////////////////////////////////////////////////////////////

    struct ToySpiritGrammar;

    struct AnyChar
      : proto::terminal<char_tag>
    {};

    struct CharLiteral
      : proto::terminal<char>
    {};

    struct NTBSLiteral
      : proto::terminal<char const *>
    {};

    struct CharParser
      : proto::function<AnyChar, CharLiteral>
    {};

    struct CharRangeParser
      : proto::function<AnyChar, CharLiteral, CharLiteral>
    {};

    struct NoCase
      : proto::terminal<no_case_tag>
    {};

    // Extract the arg from terminals
    struct ToySpiritTerminal
      : proto::or_<
            proto::trans::arg< AnyChar >
          , case_sensitive< proto::trans::arg< CharLiteral > >
          , case_sensitive< proto::trans::arg< NTBSLiteral > >
          , case_sensitive< 
                proto::trans::arg< proto::trans::arg_c< CharParser, 1 > >   // char_('a')
            >
          , case_sensitive<
                proto::trans::construct<                                    // char_('a','z')
                    char_range
                  , proto::trans::arg< proto::trans::arg_c< CharRangeParser, 1 > >
                  , proto::trans::arg< proto::trans::arg_c< CharRangeParser, 2 > >
                >
            >
        >
    {};

    // sequence rule folds all >>'s together into a list
    // and wraps the result in a composite<> wrapper
    struct ToySpiritSequence
      : as_composite<
            proto::tag::right_shift
          , proto::trans::reverse_fold_to_list<
                proto::right_shift<ToySpiritGrammar, ToySpiritGrammar>
            >
        >
    {};

    // alternate rule folds all |'s together into a list
    // and wraps the result in a composite<> wrapper
    struct ToySpiritAlternate
      : as_composite<
            proto::tag::bitwise_or
          , proto::trans::reverse_fold_to_list<
                proto::bitwise_or<ToySpiritGrammar, ToySpiritGrammar>
            >
        >
    {};

    // Directives such as no_case are handled here
    struct ToySpiritDirective
      : no_case_transform<
            proto::trans::arg_c<
                proto::subscript< NoCase, ToySpiritGrammar >
              , 1
            >
        >
    {};

    // A ToySpiritGrammar is an alternate, a sequence, a directive or a terminal
    struct ToySpiritGrammar
      : proto::or_<
            ToySpiritSequence
          , ToySpiritAlternate
          , ToySpiritDirective
          , ToySpiritTerminal
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    /// End ToySpiritGrammar
    ///////////////////////////////////////////////////////////////////////////////

    // Globals
    NoCase::type const no_case = {{}};

    // Parser
    template<typename Iterator, typename Derived>
    struct with_reset
    {
        with_reset(Iterator begin, Iterator end)
          : first(begin), second(end)
        {}

        template<typename T>
        bool operator()(T const &t) const
        {
            Iterator tmp = this->first;
            if((*static_cast<Derived const *>(this))(t))
                return true;
            this->first = tmp;
            return false;
        }

        bool done() const
        {
            return this->first == this->second;
        }

        mutable Iterator first;
        Iterator second;
    };

    template<typename Iterator>
    struct parser
      : with_reset<Iterator, parser<Iterator> >
    {
        typedef with_reset<Iterator, parser<Iterator> > with_reset;

        parser(Iterator begin, Iterator end)
          : with_reset(begin, end)
        {}

#if BOOST_VERSION < 103500
        template<typename, typename> // used by fusion::fold
        struct apply
        {
            typedef bool type;
        };
#else
        template<typename, typename> // used by fusion::fold
        struct result
        {
            typedef bool type;
        };
#endif

        template<typename T>
        bool operator()(T const &t, bool success) const // used by fusion::fold
        {
            return success && (*this)(t);
        }

        template<typename List>
        bool operator()(composite<proto::tag::bitwise_or, List> const &alternates) const
        {
            return fusion::any(alternates.elems, *static_cast<with_reset const *>(this));
        }

        template<typename List>
        bool operator()(composite<proto::tag::right_shift, List> const &sequence) const
        {
            return fusion::fold(sequence.elems, true, *this);
        }

        bool operator()(char_tag ch) const
        {
            if(this->done())
                return false;
            ++this->first;
            return true;
        }

        bool operator()(char ch) const
        {
            if(this->done() || ch != *this->first)
                return false;
            ++this->first;
            return true;
        }

        bool operator()(ichar ich) const
        {
            if(this->done() || !utility::char_icmp(*this->first, ich.lo_, ich.hi_))
                return false;
            ++this->first;
            return true;
        }

        bool operator()(char const *sz) const
        {
            return utility::string_cmp(sz, this->first, this->second);
        }

        bool operator()(istr const &s) const
        {
            return utility::string_icmp(s.str_, this->first, this->second);
        }

        bool operator()(char_range rng) const
        {
            if(this->done() || !utility::in_range(*this->first, rng.first, rng.second))
                return false;
            ++this->first;
            return true;
        }

        bool operator()(ichar_range rng) const
        {
            if(this->done() || !utility::in_irange(*this->first, rng.first, rng.second))
                return false;
            ++this->first;
            return true;
        }
    };

    template<typename Rule, typename Iterator>
    typename proto::if_matches< Rule, ToySpiritGrammar, bool >::type
    parse_impl(Rule const &rule, Iterator begin, Iterator end)
    {
        mpl::false_ is_case_sensitive;
        parser<Iterator> parse_fun(begin, end);
        return parse_fun(ToySpiritGrammar::call(rule, 0, is_case_sensitive));
    }

    // 2nd overload provides a short error message for invalid rules
    template<typename Rule, typename Iterator>
    typename proto::if_not_matches< Rule, ToySpiritGrammar, bool >::type
    parse_impl(Rule const &rule, Iterator begin, Iterator end)
    {
        BOOST_MPL_ASSERT((proto::matches<Rule, ToySpiritGrammar>));
        return false;
    }

    // parse() converts rule literals to proto expressions if necessary
    // and dispatches to parse_impl
    template<typename Rule, typename Iterator>
    bool parse(Rule const &rule, Iterator begin, Iterator end)
    {
        return parse_impl(proto::as_expr(rule), begin, end);
    }

}}

using namespace boost;

void test_toy_spirit2()
{
    using spirit2::no_case;
    std::string hello("abcd");

    BOOST_CHECK(
        spirit2::parse(
            "abcd"
          , hello.begin()
          , hello.end()
        )
    );

    BOOST_CHECK(
        spirit2::parse(
            char_ >> char_('b') >> 'c' >> char_
          , hello.begin()
          , hello.end()
        )
    );

    BOOST_CHECK(
       !spirit2::parse(
            char_ >> char_('b') >> 'c' >> 'D'
          , hello.begin()
          , hello.end()
        )
    );

    BOOST_CHECK(
        spirit2::parse(
            char_ >> char_('b') >> 'c' >> 'e'
          | char_ >> no_case[char_('B') >> "C" >> char_('D','Z')]
          , hello.begin()
          , hello.end()
        )
    );
}

using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test proto, grammars and tree transforms");

    test->add(BOOST_TEST_CASE(&test_toy_spirit2));

    return test;
}
