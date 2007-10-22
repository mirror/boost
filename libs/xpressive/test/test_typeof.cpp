///////////////////////////////////////////////////////////////////////////////
// test_typeof.cpp
//
//  Copyright 2007 David Jenkins. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <map>
#include <boost/version.hpp>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <boost/xpressive/xpressive_typeof.hpp>
#include <boost/typeof/std/stack.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/map.hpp>

// DJ: I couldn't find these registrations anywhere else, so I put them here
// They are necessary for this program to compile
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::mpl::int_, (int))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::reference_wrapper, (typename))

namespace xp = boost::xpressive;

int main() 
{
    using namespace boost::xpressive;
    // regexes from test_actions.cpp
    std::string result;
    BOOST_PROTO_AUTO(dummy1, (+_w)[ xp::ref(result) += _ ] >> *(' ' >> (+_w)[ xp::ref(result) += ',' + _ ]));
    BOOST_PROTO_AUTO(dummy2, (+_w)[ xp::ref(result) += _ ] >> *(' ' >> (+_w)[ xp::ref(result) += ',' + _ ]) >> repeat<4>(_));
    std::list<int> result2;
    BOOST_PROTO_AUTO(dummy3, (+_d)[ xp::ref(result2)->*push_back( as<int>(_) ) ] 
        >> *(' ' >> (+_d)[ xp::ref(result2)->*push_back( as<int>(_) ) ]));
    std::map<std::string, int> result3;
    BOOST_PROTO_AUTO(dummy4, ( (s1= +_w) >> "=>" >> (s2= +_d) )[ xp::ref(result3)[s1] = as<int>(s2) ]);
    placeholder< std::map<std::string, int> > const _map = {{}};
    BOOST_PROTO_AUTO(dummy5,( (s1= +_w) >> "=>" >> (s2= +_d) )[ _map[s1] = as<int>(s2) ]);

    local<int> left, right;
    std::stack<int> stack_;
    reference<std::stack<int> > stack(stack_);
    cregex expression2;
    BOOST_PROTO_AUTO(group, '(' >> by_ref(expression2) >> ')');
    BOOST_PROTO_AUTO(factor, (+_d)[ push(stack, as<int>(_)) ] | group);
    //BOOST_PROTO_AUTO(term, factor >> *(
    //                            ('*' >> factor)
    //                                [ right = top(stack)
    //                                , pop(stack)
    //                                , left = top(stack)
    //                                , pop(stack)
    //                                , push(stack, left * right)
    //                                ]
    //                          | ('/' >> factor)
    //                                [ right = top(stack)
    //                                , pop(stack)
    //                                , left = top(stack)
    //                                , pop(stack)
    //                                , push(stack, left / right)
    //                                ]
    //                         ));
    //BOOST_PROTO_AUTO(expression, term >> *(
    //                            ('+' >> term)
    //                                [ right = top(stack)
    //                                , pop(stack)
    //                                , left = top(stack)
    //                                , pop(stack)
    //                                , push(stack, left + right)
    //                                ]
    //                          | ('-' >> term)
    //                                [ right = top(stack)
    //                                , pop(stack)
    //                                , left = top(stack)
    //                                , pop(stack)
    //                                , push(stack, left - right)
    //                                ]
    //                         ));

    // regexes from test_symbols.cpp
    std::string result10;
    std::map<std::string,std::string> map10;
    BOOST_PROTO_AUTO(dummy10, (a1=map10)[ xp::ref(result10) = a1 ] >> *(' ' >> (a1=map10)[ xp::ref(result10) += ',' + a1 ]));
    BOOST_PROTO_AUTO(dummy11, (a1=map10)[ xp::ref(result10) = a1 ] 
		>> *((a1=map10)[ xp::ref(result10) += ',', xp::ref(result10) += a1 ]));

    return 0;
}
