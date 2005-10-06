///////////////////////////////////////////////////////////////////////////////
// test6.hpp
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
        test_case // test103
        (
            L("a\nxb\n")
          , L("(?!^)x")
          , regex_type(~before(bol) >> L('x'))
          , L("m")
          , no_match
        )
      , test_case // test104
        (
            L("a\nxb\n")
          , L("(?!^)x")
          , regex_type(~before(bos) >> L('x'))
          , L("")
          , backrefs(L("x"), nil)
        )
      , test_case // test105
        (
            L("a\nxb\n")
          , L("(?!\\A)x")
          , regex_type(~before(bos) >> L('x'))
          , L("m")
          , backrefs(L("x"), nil)
        )
      , test_case // test106
        (
            L("(this)")
          , L("^(?:\\(()|())\\w+(?:\\)\\1|\\2)$")
          , regex_type(bos >> (L('(') >> (s1= epsilon) | (s2= epsilon)) >> +_w >> (L(')') >> s1 | s2) >> eos)
         
          , L("")
          , backrefs(L("(this)"), L(""), L(""), nil)
        )
      , test_case // test107
        (
            L("this")
          , L("^(?:\\(()|())\\w+(?:\\)\\1|\\2)$")
          , regex_type(bos >> (L('(') >> (s1= epsilon) | (s2= epsilon)) >> +_w >> (L(')') >> s1 | s2) >> eos)
          , L("")
          , backrefs(L("this"), L(""), L(""), nil)
        )
      , test_case // test108
        (
            L("this)")
          , L("^(?:\\(()|())\\w+(?:\\)\\1|\\2)$")
          , regex_type(bos >> (L('(') >> (s1= epsilon) | (s2= epsilon)) >> +_w >> (L(')') >> s1 | s2) >> eos)
          , L("")
          , no_match
        )
      , test_case // test109
        (
            L("(this")
          , L("^(?:\\(()|())\\w+(?:\\)\\1|\\2)$")
          , regex_type(bos >> (L('(') >> (s1= epsilon) | (s2= epsilon)) >> +_w >> (L(')') >> s1 | s2) >> eos)
          , L("")
          , no_match
        )
      , test_case // test110
        (
            L("abba123abba")
          , L("[[:^alpha:]]+")
          , regex_type(+~alpha)
          , L("")
          , backrefs(L("123"), nil)
        )
      , test_case // test111
        (
            L("abba123abba")
          , L("[[:^alpha:][:alpha:]]+")
          , regex_type(+set[alpha | ~alpha])
          , L("")
          , backrefs(L("abba123abba"), nil)
        )
      , test_case // test112
        (
            L("123abba123")
          , L("[^[:^alpha:]]+")
          , regex_type(+~set[~alpha])
          , L("")
          , backrefs(L("abba"), nil)
        )
      //, test_case // test113
      //  (
      //      L("123abba123")
      //    , L("[[:alpha:]\\y]+")
      //    , as_xpr(L("[[:alpha:]\\y]+"))
      //    , L("")
      //    , backrefs(L("123abba123"), nil)
      //  )
      , test_case // test114
        (
            L("abba123abba")
          , L("[^[:^alnum:][:^digit:]]+")
          , regex_type(+~set[~alnum | ~digit])
          , L("")
          , backrefs(L("123"), nil)
        )
      , test_case // test115
        (
            L("aaaaA")
          , L("^(a\\1?){4}$")
          , regex_type(icase(bos >> repeat<4>(s1= L('a') >> !s1) >> eos))
          , L("i")
          , backrefs(L("aaaaA"), L("A"), nil)
        )
      , test_case // test116
        (
            L("aaaaAa")
          , L("^(a\\1?){4}$")
          , regex_type(icase(bos >> repeat<4>(s1= L('a') >> !s1) >> eos))
          , L("i")
          , backrefs(L("aaaaAa"), L("Aa"), nil)
        )
    };

    return boost::make_iterator_range(test_cases);
}
