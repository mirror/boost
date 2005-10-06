///////////////////////////////////////////////////////////////////////////////
// test4.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./test.hpp"

///////////////////////////////////////////////////////////////////////////////
// get_test_cases
//
template<typename BidiIterT>
boost::iterator_range<test_case<BidiIterT> const *> get_test_cases()
{
    typedef typename boost::iterator_value<BidiIterT>::type char_type;
    typedef test_case<BidiIterT> test_case;
    typedef basic_regex<BidiIterT> regex_type;

    // for testing recursive static regexes
    regex_type parens = L('(') >> *( keep( +~(set=L('('),L(')')) ) | self ) >> L(')');

    //regex_type parens;
    //parens = L('(') >> *( keep( +~(set=L('('),L(')')) ) | by_ref(parens) ) >> L(')');

    static char_type const *nil = 0;
    static test_case const test_cases[] =
    {
        test_case // test61
        (
            L("this is sublist(now(is(the(time),for(all),good(men))to(come)))ok?")
          , L("\\bsublist\\((?>[^()]*)(?>(?:\\((?>[^()]*)(?>(?:\\((?>[^()]*)(?>(?:\\((?>[^()]*)(?>(?:\\((?>[^()]*)\\)[^()]*)*)\\)[^()]*)*)\\)[^()]*)*)\\)[^()]*)*)\\)")
          , regex_type(_b >> L("sublist") >> parens)
          , L("")
          , backrefs(L("sublist(now(is(the(time),for(all),good(men))to(come)))"), nil)
        )
      , test_case // test62
        (
            L("this is sublist(now(is(the(time),for(all),good(men))to(come))ok?")
          , L("\\bsublist\\((?>[^()]*)(?>(?:\\((?>[^()]*)(?>(?:\\((?>[^()]*)(?>(?:\\((?>[^()]*)(?>(?:\\((?>[^()]*)\\)[^()]*)*)\\)[^()]*)*)\\)[^()]*)*)\\)[^()]*)*)\\)")
          , regex_type(_b >> L("sublist") >> parens)
          , L("")
          , no_match
        )
      , test_case // test63
        (
            L("foobar")
          , L("^baz|bar")
          , regex_type(bos >> L("baz") | L("bar"))
          , L("")
          , backrefs(L("bar"), nil)
        )
      , test_case // test69
        (
            L("FooBarfoobar")
          , L(".*foo")
          , regex_type(icase(*_ >> L("foo")))
          , L("i")
          , backrefs(L("FooBarfoo"), nil)
        )
      , test_case // test70
        (
            L("FooBarfoobar")
          , L(".*boo")
          , regex_type(icase(*_ >> L("boo")))
          , L("i")
          , no_match
        )
      , test_case // test71
        (
            L("FooBarfoobar")
          , L(".*boo|bar")
          , regex_type(icase(*_ >> L("boo") | L("bar")))
          , L("i")
          , backrefs(L("Bar"), nil)
        )
      , test_case // test72
        (
            L("FooBarfoobar")
          , L("bar")
          , regex_type(icase(L("bar")))
          , L("i")
          , backrefs(L("Bar"), nil)
        )
      , test_case // test75
        (
            L("fooooo")
          , L("fo{1,}")
          , regex_type(L('f') >> repeat<1,repeat_max>(L('o')))
          , L("")
          , backrefs(L("fooooo"), nil)
        )
      , test_case // test78
        (
            L("This (has) parens")
          , L("This (\\Q(has)\\E) (parens)")
          , regex_type(L("This ") >> (s1= L("(has)")) >> L(' ') >> (s2= L("parens")))
          , L("")
          , backrefs(L("This (has) parens"), L("(has)"), L("parens"), nil)
        )
      , test_case // test79
        (
            L("This (has) parens")
          , L("This \\Q(has) parens\\E")
          , regex_type(as_xpr(L("This (has) parens")))
          , L("")
          , backrefs(L("This (has) parens"), nil)
        )
      , test_case // test80
        (
            L("This (has) parens")
          , L("This \\Q(has) parens")
          , regex_type(as_xpr(L("This (has) parens")))
          , L("")
          , backrefs(L("This (has) parens"), nil)
        )
    };

    return boost::make_iterator_range(test_cases);
}
