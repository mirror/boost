//[ RGB
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This is a simple example of doing arbitrary type manipulations with proto
// transforms. It takes some expression involving primiary colors and combines
// the colors according to arbitrary rules. It is a port of the RGB example
// from PETE (http://www.codesourcery.com/pooma/download.html).

#include <iostream>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/apply.hpp>
#include <boost/xpressive/proto/transform/compose.hpp>
using namespace boost::proto;

struct RedTag
{
    friend std::ostream &operator <<(std::ostream &sout, RedTag)
    {
        return sout << "This expression is red.";
    }
};

struct BlueTag
{
    friend std::ostream &operator <<(std::ostream &sout, BlueTag)
    {
        return sout << "This expression is blue.";
    }
};

struct GreenTag
{
    friend std::ostream &operator <<(std::ostream &sout, GreenTag)
    {
        return sout << "This expression is green.";
    }
};

typedef terminal<RedTag>::type Red;
typedef terminal<BlueTag>::type Blue;
typedef terminal<GreenTag>::type Green;

///////////////////////////////////////////////////////////////////////////////
// A transform that produces new colors according to some arbitrary rules:
// red & green give blue, red & blue give green, blue and green give red.
struct RGB
  : or_<
        // leave terminals as they are
        terminal<_>
      , transform::compose<
            // Match binary nodes, convert left and right to terminals
            plus<RGB, RGB>
            // Forward resulting binary expression to the following transform
          , or_<
                // Green + Blue -> Red
                transform::always<plus<Green, Blue>, Red>
              , transform::always<plus<Blue, Green>, Red>
                // Red + Green -> Blue
              , transform::always<plus<Red, Green>, Blue>
              , transform::always<plus<Green, Red>, Blue>
                // Red + Blue -> Green
              , transform::always<plus<Red, Blue>, Green>
              , transform::always<plus<Blue, Red>, Green>
                // else (both same color), select the left operand
              , transform::left<_>
            >
        >
    >
{};

template<typename Expr>
void printColor(Expr const & expr)
{
    int i = 0; // dummy state and visitor parameter, not used
    std::cout << arg(RGB::call(expr, i, i)) << std::endl;
}

int main()
{
    printColor(Red() + Green());
    printColor(Red() + Green() + Blue());
    printColor(Red() + (Green() + Blue()));

    return 0;
}
//]
