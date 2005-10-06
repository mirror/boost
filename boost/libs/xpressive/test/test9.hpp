///////////////////////////////////////////////////////////////////////////////
// test9.hpp
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

    static char_type const *nil = 0;
    static test_case const test_cases[] =
    {
        test_case // test151
        (
            L("bbbc")
          , L("^(b?\?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbbc"), L("b"), nil)
        )
      , test_case // test152
        (
            L("bbbbc")
          , L("^(b?\?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , no_match
        )
      , test_case // test153
        (
            L("bbbbc")
          , L("^(b?\?)*d$")
          , regex_type(bos >> *(s1= -optional(L('b'))) >> L('d') >> eos)
          , L("")
          , no_match
        )
      , test_case // test154
        (
            L("bc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bc"), L(""), nil)
        )
      , test_case // test155
        (
            L("bbc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L("b"), nil)
        )
      , test_case // test156
        (
            L("bbbc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbbc"), L("b"), nil)
        )
      , test_case // test157
        (
            L("bbbbc")
          , L("^(b?\?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , no_match
        )
      , test_case // test158
        (
            L("bbbbc")
          , L("^(b?\?)*?d$")
          , regex_type(bos >> -*(s1= -optional(L('b'))) >> L('d') >> eos)
          , L("")
          , no_match
        )
      , test_case // test159
        (
            L("bbc")
          , L("^(|||b)*bc$")
          , regex_type(bos >> *(s1= epsilon | epsilon | epsilon | L('b')) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L(""), nil)
        )
      , test_case // test160
        (
            L("bbc")
          , L("^(|||b)*?bc$")
          , regex_type(bos >> -*(s1= epsilon | epsilon | epsilon | L('b')) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L("b"), nil)
        )
      , test_case // test164
        (
            L("1yzZ^aAc2")
          , L("[Z-a]+")
          , regex_type(icase(+range(L('Z'),L('a'))))
          , L("i")
          , backrefs(L("zZ^aA"), nil)
        )
      , test_case // test165
        (
            L("1yzZ^aAc2")
          , L("[Z-a]+")
          , regex_type(+range(L('Z'),L('a')))
          , L("")
          , backrefs(L("Z^a"), nil)
        )
      , test_case // test166
        (
            L("G")
          , L("f|(?i)g")
          , regex_type(L('f') | icase(L('g')))
          , L("")
          , backrefs(L("G"), nil)
        )
      , test_case // test167
        (
            L("aBBa")
          , L("[[:lower:]]+")
          , regex_type(icase(+lower))
          , L("i")
          , backrefs(L("aBBa"), nil)
        )
      , test_case // test168
        (
            L("aA")
          , L("\\x61+")
          , regex_type(icase(+as_xpr(L('\x61'))))
          , L("i")
          , backrefs(L("aA"), nil)
        )
      , test_case // test169
        (
            L("aA")
          , L("[\\x61]+")
          , regex_type(icase(+set[L('\x61')]))
          , L("i")
          , backrefs(L("aA"), nil)
        )
      , test_case // test170
        (
            L("aA")
          , L("\\u0061+")
          , regex_type(icase(+as_xpr(L('\x0061'))))
          , L("i")
          , backrefs(L("aA"), nil)
        )
      , test_case // test171
        (
            L("aA")
          , L("[\\u0061]+")
          , regex_type(icase(+set[L('\x0061')]))
          , L("i")
          , backrefs(L("aA"), nil)
        )
    };

    return boost::make_iterator_range(test_cases);
}
