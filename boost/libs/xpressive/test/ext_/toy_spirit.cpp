///////////////////////////////////////////////////////////////////////////////
// toy_spirit.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cctype>
#include <string>
#include <iostream>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/pass_through.hpp>
#include <boost/xpressive/proto/compiler/conditional.hpp>
#include <boost/test/unit_test.hpp>

//void remove_string(std::string &str, char const *find)
//{
//    std::size_t pos = 0, len = std::strlen(find);
//    while(std::string::npos != (pos = str.find(find, pos)))
//    {
//        str.erase(pos, len);
//    }
//}
//
//template<typename T> void display_type(T const &)
//{
//    std::string str = typeid(T).name();
//    remove_string(str, "struct ");
//    remove_string(str, "boost::");
//    remove_string(str, "proto::");
//    remove_string(str, "spirit2::");
//    remove_string(str, "fusion::");
//    remove_string(str, ",void_t");
//
//    std::cout << str << std::endl;
//}

namespace boost
{
    // global tags
    struct char_tag {};
    struct ichar_tag {};
    struct istring_tag {};
    struct ichar_range_tag {};
    struct never_tag {};
    struct always_tag {};
    struct space_tag {};

    // global primitives
    proto::meta::terminal<char_tag>::type const char_ = {{}};
    proto::meta::terminal<space_tag>::type const space = {{}};

    template<typename T>
    struct literal
    {
        typedef typename proto::meta::terminal<T>::type type;
    };

    template<typename T>
    typename literal<T>::type lit(T const &t)
    {
        typename literal<T>::type that = {t};
        return that;
    }
}

namespace boost { namespace spirit2
{

    // Spirit2-specific tags ...
    struct parser_tag {};
    struct no_case_tag {};
    struct skipper_tag {};

    // handy typedefs
    typedef proto::meta::terminal<char_tag>::type anychar_p;
    typedef proto::meta::terminal<ichar_tag>::type ianychar_p;
    typedef proto::meta::terminal<char>::type chlit_p;
    typedef proto::meta::terminal<std::string>::type str_p;
    typedef proto::meta::terminal<char const *>::type szlit_p;
    typedef proto::meta::terminal<istring_tag>::type ianystr_p;
    typedef proto::meta::terminal<ichar_range_tag>::type ianychar_range_p;
    typedef proto::meta::terminal<never_tag>::type never_p;
    typedef proto::meta::terminal<space_tag>::type space_p;

    typedef result_of<anychar_p(char)>::type char_p;
    typedef result_of<ianychar_p(char, char)>::type ichar_p;
    typedef result_of<anychar_p(char, char)>::type char_range_p;
    typedef result_of<ianystr_p(std::string)>::type istr_p;
    typedef result_of<ianychar_range_p(char, char)>::type ichar_range_p;

    ianychar_p const ichar_ = {{}};
    ianystr_p const istr_ = {{}};
    ianychar_range_p const ichar_range_ = {{}};

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

        struct any_convertible
        {
            template<typename T>
            any_convertible(T const &);
        };

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

    namespace parser
    {
        template<typename Node, typename Context>
        bool parse(Node const &node, Context &ctx);

        // context
        template<typename FwdIter, typename Skipper = never_p>
        struct context
          : context<FwdIter>
        {
            context(FwdIter first, FwdIter second, Skipper const &skip)
              : context<FwdIter>(first, second)
              , skipper_(skip)
            {}

            void skip()
            {
                while(parser::parse(this->skipper_, static_cast<context<FwdIter> &>(*this)))
                    ;
            }
        private:
            context &operator =(context const &);
            Skipper skipper_;
        };

        template<typename FwdIter>
        struct context<FwdIter, never_p>
          : std::pair<FwdIter, FwdIter>
        {
            typedef FwdIter iterator;

            context(FwdIter first, FwdIter second, never_p = never_p())
              : std::pair<FwdIter, FwdIter>(first, second)
            {}

            void skip() {}
        };

        template<typename FwdIter, typename Skipper>
        context<FwdIter, Skipper> &reset(context<FwdIter, Skipper> &ctx, FwdIter first)
        {
            ctx.first = first;
            return ctx;
        }

        namespace primitives
        {
            // parse function for anychar_p
            template<typename Context>
            bool parse(anychar_p const &, Context &ctx)
            {
                if(ctx.first == ctx.second)
                    return false;
                ++ctx.first;
                return true;
            }

            // parse function for char_p
            template<typename Context>
            bool parse(char_p const &p, Context &ctx)
            {
                if(ctx.first == ctx.second || *ctx.first != proto::arg(p.arg1))
                    return false;
                ++ctx.first;
                return true;
            }

            // parse function for space_p
            template<typename Context>
            bool parse(space_p const &p, Context &ctx)
            {
                if(ctx.first == ctx.second || !std::isspace(*ctx.first))
                    return false;
                ++ctx.first;
                return true;
            }

            // parse function for bare character literals
            template<typename Context>
            bool parse(chlit_p const &p, Context &ctx)
            {
                return primitives::parse(char_(p.arg0), ctx);
            }

            // case-insensitive character parser
            template<typename Context>
            bool parse(ichar_p const &p, Context &ctx)
            {
                if(ctx.first == ctx.second
                  || !utility::char_icmp(*ctx.first, proto::arg(p.arg1), proto::arg(p.arg2)))
                    return false;
                ++ctx.first;
                return true;
            }

            template<typename Context>
            bool parse(szlit_p const &p, Context &ctx)
            {
                return utility::string_cmp(proto::arg(p), ctx.first, ctx.second);
            }

            template<typename Context>
            bool parse(istr_p const &p, Context &ctx)
            {
                return utility::string_icmp(proto::arg(p.arg1), ctx.first, ctx.second);
            }

            // parse function for char_range_p
            template<typename Context>
            bool parse(char_range_p const &p, Context &ctx)
            {
                BOOST_ASSERT(proto::arg(p.arg1) <= proto::arg(p.arg2));
                if(ctx.first == ctx.second
                  || !utility::in_range(*ctx.first, proto::arg(p.arg1), proto::arg(p.arg2)))
                    return false;
                ++ctx.first;
                return true;
            }

            // parse function for ichar_range_p
            template<typename Context>
            bool parse(ichar_range_p const &p, Context &ctx)
            {
                BOOST_ASSERT(proto::arg(p.arg1) <= proto::arg(p.arg2));
                if(ctx.first == ctx.second
                  || !utility::in_irange(*ctx.first, proto::arg(p.arg1), proto::arg(p.arg2)))
                    return false;
                ++ctx.first;
                return true;
            }

            // parse function for complemented thingies (where thingies are assumed 
            // to be 1 character wide).
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::complement_tag, Args, 1> const &p, Context &ctx)
            {
                typename Context::iterator tmp = ctx.first;
                if(primitives::parse(proto::arg(p), ctx))
                    return ctx.first = tmp, false;
                ctx.first = ++tmp;
                return true;
            }

            // never_p parse function always returns false.
            template<typename Context>
            bool parse(never_p const &, Context &)
            {
                return false;
            }

            struct no_type { bool b[2]; };
            no_type parse(utility::any_convertible, utility::any_convertible);

        } // namespace primitives

        namespace composites
        {
            // for A >> B, succeeds if A and B matches.
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::right_shift_tag, Args, 2> const &node, Context &ctx)
            {
                return parser::parse(proto::left(node), ctx)
                    && parser::parse(proto::right(node), ctx);
            }

            // for A | B, succeeds if either A or B matches at this point.
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::bitor_tag, Args, 2> const &node, Context &ctx)
            {
                typename Context::iterator tmp = ctx.first;
                return parser::parse(proto::left(node), ctx)
                    || parser::parse(proto::right(node), reset(ctx, tmp));
            }

            // for *A, greedily match A as many times as possible.
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::unary_star_tag, Args, 1> const &node, Context &ctx)
            {
                typename Context::iterator tmp = ctx.first;
                while(parser::parse(proto::arg(node), ctx))
                    tmp = ctx.first;
                // make sure that when we return true, the iterator is at the correct position!
                ctx.first = tmp;
                return true;
            }

            // for +A, greedily match A one or more times.
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::unary_plus_tag, Args, 1> const &node, Context &ctx)
            {
                return parser::parse(proto::arg(node), ctx)
                    && parser::parse(*proto::arg(node), ctx);
            }

            // for !A, optionally match A.
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::logical_not_tag, Args, 1> const &node, Context &ctx)
            {
                typename Context::iterator tmp = ctx.first;
                if(!parser::parse(proto::arg(node), ctx))
                    ctx.first = tmp;
                return true;
            }

            // for (A - B), matches when A but not B matches.
            template<typename Args, typename Context>
            bool parse(proto::basic_expr<proto::subtract_tag, Args, 2> const &node, Context &ctx)
            {
                typename Context::iterator tmp = ctx.first;
                return !parser::parse(proto::right(node), ctx)
                    && parser::parse(proto::left(node), reset(ctx, tmp));
            }
        }

        // is_primitive, true if T is a Spirit primitive parser
        template<typename T>
        struct is_primitive
        {
            static T &t;
            BOOST_STATIC_CONSTANT(bool, value = sizeof(bool) == sizeof(primitives::parse(t, t)));
            typedef mpl::bool_<value> type;
        };

        // A proto lambda
        struct is_primitive_predicate
        {
            template<typename Node, typename State, typename Context>
            struct apply
              : is_primitive<Node>
            {};
        };

        // parser for primitives, calls skip parser first
        template<typename Node, typename Context>
        bool parse(Node const &node, Context &ctx)
        {
            if(is_primitive<Node>::value)
                ctx.skip();
            using primitives::parse;
            using composites::parse;
            return (parse)(node, ctx);
        }

    } // namespace parser

    namespace no_case_
    {
        template<typename Arg>
        struct remove_case
        {
            typedef Arg type;

            static Arg const &call(Arg const &arg)
            {
                return arg;
            }
        };

        template<>
        struct remove_case<char_p>
        {
            typedef ichar_p type;

            static type call(char_p const &p)
            {
                char lo = std::tolower(proto::arg(p.arg1));
                char hi = std::toupper(proto::arg(p.arg1));
                return ichar_(lo, hi);
            }
        };

        template<>
        struct remove_case<chlit_p>
        {
            typedef ichar_p type;

            static type call(chlit_p const &p)
            {
                char lo = std::tolower(p.arg0);
                char hi = std::toupper(p.arg0);
                return ichar_(lo, hi);
            }
        };

        template<>
        struct remove_case<char_range_p>
        {
            typedef ichar_range_p type;

            static type call(char_range_p const &p)
            {
                char lo = proto::arg(p.arg1);
                char hi = proto::arg(p.arg2);
                return ichar_range_(lo, hi);
            }
        };

        struct remove_case_ntbs
        {
            typedef istr_p type;

            template<typename Node>
            static type call(Node const &p)
            {
                return istr_(utility::to_istr(proto::arg(p)));
            }
        };

        template<>
        struct remove_case<szlit_p> // char const *
          : remove_case_ntbs
        {};

        struct no_case_compiler
        {
            template<typename Node, typename State, typename Context>
            struct apply
              : remove_case<Node>
            {};

            template<typename Node, typename State, typename Context>
            static typename apply<Node, State, Context>::type
            call(Node const &node, State const &, Context &)
            {
                return apply<Node, State, Context>::call(node);
            }
        };

        struct no_case_directive
        {
            template<typename Node>
            typename proto::meta::compile<Node, mpl::void_, mpl::void_, no_case_tag>::type
            operator [](Node const &node) const
            {
                mpl::void_ null;
                return proto::compile(node, null, null, no_case_tag());
            }
        };
    }

    namespace skipper
    {
        struct skipper_compiler
        {
            template<typename Node, typename State, typename Context>
            struct apply
            {
                typedef typename proto::meta::binary_expr<
                    proto::right_shift_tag
                  , typename proto::meta::unary_expr<proto::unary_star_tag, State>::type
                  , Node
                >::type type;
            };

            template<typename Node, typename State, typename Context>
            static typename apply<Node, State, Context>::type
            call(Node const &node, State const &state, Context &)
            {
                typename apply<Node, State, Context>::type that = {{state}, node};
                return that;
            }
        };

        template<typename Skipper>
        struct skip_directive
        {
            skip_directive(Skipper const &skip)
              : skip_(skip)
            {}

            template<typename Node>
            typename proto::meta::compile<Node, Skipper, mpl::void_, skipper_tag>::type
            operator [](Node const &node) const
            {
                mpl::void_ null;
                return proto::compile(node, this->skip_, null, skipper_tag());
            }
        private:
            Skipper skip_;
        };
    }

    /////////////
    // Directives
    /////////////

    // no_case
    no_case_::no_case_directive const no_case = {};

    // skip
    template<typename Skipper>
    skipper::skip_directive<Skipper> skip(Skipper const &skip)
    {
        return skipper::skip_directive<Skipper>(skip);
    }

    /////////////
    // parse
    /////////////

    template<typename FwdIter, typename Rule>
    bool parse(FwdIter begin, FwdIter end, Rule const &rule)
    {
        parser::context<FwdIter> ctx(begin, end);
        return parser::parse(rule, ctx);
    }

    // parse with a skip parser can be implemented in one of two ways:
    // Method 1)
    //      The skip parser is passed to all the parsers which invoke it
    //      before they invoke themselves. This is how Spirit-1 does it,
    //      and it is the cause of the Scanner Business. However, it has
    //      the advantage of not needing a parser transformation phase.
    // Method 2)
    //      Transform the expression template to insert the skip parser
    //      in between all sequenced parsers. That is, transform (A >> B)
    //      to (*skip >> A >> *skip >> B). This has the advantage of making
    //      it unnecessary to pass the scanner to all the parsers, which 
    //      means its type doesn't show up in function signatures, avoiding
    //      the Scanner Business.
    // Recommendation:
    //      Both methods should be supported. Method 1 should be preferred
    //      when calling parse with parsers defined inline. Method 2 should
    //      be preferred when a parser expression is assigned to a rule<>,
    //      thereby making the type of the rule<> independent of the skip
    //      parser used. I imagine a syntax like:
    //          rule<> r = skip(space)[A >> B >> C]
    template<typename FwdIter, typename Rule, typename Skipper>
    bool parse(FwdIter begin, FwdIter end, Rule const &rule, Skipper const &skipper)
    {
        //// Method 1: pass skip parser in the context structure.
        //parser::context<FwdIter, Skipper> ctx(begin, end, skipper);
        //return parser::parse(rule, ctx);

        // Method 2: Embed skip parser via tree transformation.
        parser::context<FwdIter> ctx(begin, end);
        return parser::parse(spirit2::skip(skipper)[rule], ctx);
    }

}}

namespace boost { namespace proto
{
    // no_case_ transformation rules
    template<typename OpTag>
    struct compiler<OpTag, spirit2::no_case_tag>
      : pass_through_compiler<spirit2::no_case_tag>
    {};

    template<>
    struct compiler<terminal_tag, spirit2::no_case_tag>
      : spirit2::no_case_::no_case_compiler
    {};

    template<>
    struct compiler<function_tag, spirit2::no_case_tag>
      : spirit2::no_case_::no_case_compiler
    {};

    // skipper transformation rules
    // transforms (A >> B) to (*skip >> A >> *skip >> B)
    template<typename OpTag>
    struct compiler<OpTag, spirit2::skipper_tag>
      : proto::conditional_compiler<
            spirit2::parser::is_primitive_predicate
          , spirit2::skipper::skipper_compiler
          , pass_through_compiler<spirit2::skipper_tag>
        >
    {};

}}

using namespace boost;
using namespace spirit2;

void test_toy_spirit()
{
    std::string str("abcd");

    // This will fail:
    BOOST_CHECK(!spirit2::parse(str.begin(), str.end()
                   , char_ >> char_('a')));

    // This will succeed:
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , char_ >> char_('b') >> char_ >> 'd'));

    // This will succeed:
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , 'a' >> ('c' >> char_ | 'b' >> char_('d') | 'b' >> char_('c')) >> 'd'));

    // This will succeed:
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , *(char_ - 'd')));

    // This will succeed:
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , no_case[char_('A') >> 'B' >> "CD"]));

    // This will succeed:
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , no_case[*char_('A','Z')]));

    literal<char>::type a = lit('a');
    literal<char const *>::type bcd = lit("bcd");

    // This will succeed:
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , +~~a >> no_case[bcd]));

    // Scanner Business: R.I.P. :-)
    str = "a  b    cd";
    BOOST_CHECK(spirit2::parse(str.begin(), str.end()
                   , char_('a') >> 'b' >> 'c' >> 'd', space >> space));
}

using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test proto and and toy spirit-2");

    test->add(BOOST_TEST_CASE(&test_toy_spirit));

    return test;
}
