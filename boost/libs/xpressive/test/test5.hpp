///////////////////////////////////////////////////////////////////////////////
// test5.hpp
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

    static char_type const *nilbr = 0;
    static test_case const test_cases[] =
    {
        test_case // test82
        (
            L("abba1234abba")
          , L("\\d+")
          , regex_type(+_d)
          , L("")
          , backrefs(L("1234"), nilbr)
        )
      , test_case // test83
        (
            L("1234abba1234")
          , L("\\D+")
          , regex_type(+~_d)
          , L("")
          , backrefs(L("abba"), nilbr)
        )
      , test_case // test84
        (
            L("abba1234abba")
          , L("[\\d]+")
          , regex_type(+set[_d])
          , L("")
          , backrefs(L("1234"), nilbr)
        )
      , test_case // test85
        (
            L("1234abba1234")
          , L("[\\D]+")
          , regex_type(+set[~_d])
          , L("")
          , backrefs(L("abba"), nilbr)
        )
      , test_case // test86
        (
            L("abba1234abba")
          , L("[^\\D]+")
          , regex_type(+~set[~_d])
          , L("")
          , backrefs(L("1234"), nilbr)
        )
      , test_case // test87
        (
            L("1234abba1234")
          , L("[^\\d]+")
          , regex_type(+~set[_d])
          , L("")
          , backrefs(L("abba"), nilbr)
        )
      , test_case // test88
        (
            L("1234abba1234")
          , L("[\\W\\D]+")
          , regex_type(+set[~_w | ~_d])
          , L("")
          , backrefs(L("abba"), nilbr)
        )
      , test_case // test89
        (
            L("1234(.;)abba")
          , L("[^\\w\\d]+")
          , regex_type(+~set[_w | _d])
          , L("")
          , backrefs(L("(.;)"), nilbr)
        )
      , test_case // test90
        (
            L("(boo[bar]baz)")
          , L("(\\(()|\\[()).*?(\\)\\2|\\]\\3)")
          , regex_type((s1= L('(') >> (s2= nil) | L('[') >> (s3= nil)) >> -*_ >> (s4= L(')') >> s2 | L(']') >> s3))
          , L("")
          , backrefs(L("(boo[bar]baz)"), L("("), L(""), L(""), L(")"), nilbr)
        )
      , test_case // test91
        (
            L("[boo(bar)baz]")
          , L("(\\(()|\\[()).*?(\\)\\2|\\]\\3)")
          , regex_type((s1= L('(') >> (s2= nil) | L('[') >> (s3= nil)) >> -*_ >> (s4= L(')') >> s2 | L(']') >> s3))
          , L("")
          , backrefs(L("[boo(bar)baz]"), L("["), L(""), L(""), L("]"), nilbr)
        )
      , test_case // test91
        (
            L("[boo[bar]baz]")
          , L("(\\(()|\\[()).*?(\\)\\2|\\]\\3)")
          , regex_type((s1= L('(') >> (s2= nil) | L('[') >> (s3= nil)) >> -*_ >> (s4= L(')') >> s2 | L(']') >> s3))
          , L("")
          , backrefs(L("[boo[bar]"), L("["), L(""), L(""), L("]"), nilbr)
        )
      , test_case // test92
        (
            L("foobarfoo")
          , L("(?<=foo)bar")
          , regex_type(after(L("foo")) >> L("bar"))
          , L("")
          , backrefs(L("bar"), nilbr)
        )
      , test_case // test93
        (
            L("foobarfoo")
          , L("(?<=(f.o))bar")
          , regex_type(after(s1= L('f') >> _ >> L('o')) >> L("bar"))
          , L("")
          , backrefs(L("bar"), L("foo"), nilbr)
        )
      , test_case // test94
        (
            L("foOoo")
          , L("(?<=(fo))o")
          , regex_type(icase(after(s1= L("fo")) >> L('o')))
          , L("i")
          , backrefs(L("O"), L("fo"), nilbr)
        )
      , test_case // test95
        (
            L("fOooo")
          , L("(?<!(fo))o")
          , regex_type(icase(~after(s1= L("fo")) >> L('o')))
          , L("i")
          , backrefs(L("O"), L(""), nilbr)
        )
      , test_case // test96
        (
            L("12foo12")
          , L("[[:alpha:]]+")
          , regex_type(+alpha)
          , L("")
          , backrefs(L("foo"), nilbr)
        )
      , test_case // test97
        (
            L(";12foo12;")
          , L("[[:alpha:][:digit:]]+")
          , regex_type(+set[alpha | digit])
          , L("")
          , backrefs(L("12foo12"), nilbr)
        )
      , test_case // test98
        (
            L("aaaa")
          , L("(?<=())a")
          , regex_type(after(s1= nil) >> L('a'))
          , L("")
          , backrefs(L("a"), L(""), nilbr)
        )
      , test_case // test99
        (
            L("ABCabc123foo")
          , L("(?<=(abc\\d{3}))foo")
          , regex_type(after(s1= L("abc") >> repeat<3>(_d)) >> L("foo"))
          , L("")
          , backrefs(L("foo"), L("abc123"), nilbr)
        )
    };

    return boost::make_iterator_range(test_cases);
}
