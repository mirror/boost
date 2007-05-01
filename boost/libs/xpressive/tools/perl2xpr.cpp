///////////////////////////////////////////////////////////////////////////////
// perl2xpr.cpp
//      A utility for translating a Perl regular expression into an
//      xpressive static regular expression.
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stack>
#include <string>
#include <iostream>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/xpressive/regex_actions.hpp>

using namespace boost::xpressive;

int main(int argc, char *argv[])
{
    int i = 1;
    bool nocase = false;
    char const *dot = " ~_n ";
    char const *bos = " bos ";
    char const *eos = " eos ";

    for(; i < argc && '-' == *argv[i]; ++i)
    {
        switch(argv[i][1])
        {
        case 'i':           // perl /i modifier
            nocase = true;
            break;
        case 's':           // perl /s modifier
            dot = " _ ";
            break;
        case 'm':           // perl /m modifier
            bos = " bol ";
            eos = " eol ";
            break;
        default:
            std::cerr << "Unknown option : " << argv[i] << std::endl;
            return -1;
        }
    }

    if(i == argc)
    {
        std::cerr << "Usage:\n    perl2xpr [-i] [-s] [-m] 're'\n";
        return -1;
    }

    // Local variables used by the semantic actions below
    local<int> mark_nbr;
    local<std::string> tmp;
    local<std::stack<std::string> > strings;

    // The rules in the dynamic regex grammar
    cregex regex, alts, seq, quant, repeat, atom, escape, group, lit, charset, setelem;

    lit     = ~(set='.','^','$','*','+','?','(',')','{','}','[',']','\\','|')
            ;

    escape  = as_xpr("b")   [top(strings) += " _b "]
            | as_xpr("B")   [top(strings) += " ~_b "]
            | as_xpr("d")   [top(strings) += " _d "]
            | as_xpr("D")   [top(strings) += " ~_d "]
            | as_xpr("s")   [top(strings) += " _s "]
            | as_xpr("S")   [top(strings) += " ~_s "]
            | as_xpr("w")   [top(strings) += " _w "]
            | as_xpr("W")   [top(strings) += " ~_w "]
            | _d            [top(strings) += " s" + _ + " "]
            | _             [top(strings) += " as_xpr('" + _ + "') "]
            ;

    group   = as_xpr("?:")  [top(strings) += " ( "]         >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | as_xpr("?i:") [top(strings) += " icase( "]    >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | as_xpr("?>")  [top(strings) += " keep( "]     >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | as_xpr("?=")  [top(strings) += " before( "]   >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | as_xpr("?!")  [top(strings) += " ~before( "]  >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | as_xpr("?<=") [top(strings) += " after( "]    >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | as_xpr("?<!") [top(strings) += " ~after( "]   >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            | nil [top(strings) += " ( s" + as<std::string>(++mark_nbr) + "= "] >> ref(regex) >> as_xpr(')') [top(strings) += " ) "]
            ;

    setelem = as_xpr('\\') >> _ [top(strings) += " as_xpr('" + _ + "') "]
            | "[:" >> !as_xpr('^') [top(strings) += "~"] >> (+_w) [top(strings) += _ ] >> ":]"
            | ((s1=~as_xpr(']')) >> '-' >> (s2=~as_xpr(']'))) [top(strings) += "range('" + s1 + "','" + s2 + "')"]
            ;

    charset = !as_xpr('^') [top(strings) += " ~ "]
            >> nil [top(strings) += " set[ "]
            >> (setelem | (~as_xpr(']')) [top(strings) += " as_xpr('" + _ + "') "])
            >> *( nil [ top(strings) += " | " ] >> (setelem | (~as_xpr(']')) [ top(strings) += "'" + _ + "'" ] ) )
            >> as_xpr(']') [top(strings) += " ] "]
            ;

    atom    = (+(lit >> ~before((set='*','+','?','{'))) | lit) [top(strings) += " as_xpr(\"" + _ + "\") "]
            | as_xpr('.') [top(strings) += dot]
            | as_xpr('^') [top(strings) += bos]
            | as_xpr('$') [top(strings) += eos]
            | '\\' >> escape
            | '(' >> group
            | '[' >> charset
            ;

    repeat  = as_xpr('{') [top(strings) += " repeat<"]
            >> (+_d) [top(strings) += _]
            >> !(
                    as_xpr(',') [top(strings) += ","]
                 >> (
                        (+_d) [top(strings) += _]
                      | nil   [top(strings) += "inf"]
                    )
                )
            >> as_xpr('}') [top(strings) += ">(", tmp += " ) "]
            ;

    quant   = nil [push(strings, "")]
            >> atom [tmp = top(strings), pop(strings)]
            >> !(
                    nil [push(strings, "")]
                 >> (
                        as_xpr("*") [top(strings) += " * "]
                      | as_xpr("+") [top(strings) += " + "]
                      | as_xpr("?") [top(strings) += " ! "]
                      | repeat
                    )
                 >> !( as_xpr('?') [ top(strings) = " - " + top(strings) ] )
                 >> nil [ tmp = top(strings) + tmp, pop(strings) ]
                )
            >> nil [top(strings) += tmp]
            ;

    seq     = quant >> *( nil [top(strings) += " >> "] >> quant )
            ;

    alts    = seq >> *( as_xpr('|') [top(strings) += " | "] >> seq )
            ;

    regex   = alts
            ;

    strings.get().push("");
    if(!regex_match(argv[i], regex))
    {
        std::cerr << "ERROR: unrecognized regular expression" << std::endl;
        return -1;
    }
    else if(nocase)
    {
        std::cout << "icase( " << strings.get().top() << " )" << std::endl;
    }
    else
    {
        std::cout << strings.get().top() << std::endl;
    }

    return 0;
}
