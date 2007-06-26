//[ HelloWorld
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/typeof/std/ostream.hpp>
using namespace boost;

proto::terminal< std::ostream & >::type cout_ = { std::cout };

template< typename Expr >
void evaluate( Expr const & expr )
{
    proto::default_context ctx;
    proto::eval(expr, ctx);
}

int main()
{
    evaluate( cout_ << "hello" << ',' << " world" );
    return 0;
}
//]
