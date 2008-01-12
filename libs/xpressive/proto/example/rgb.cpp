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
#include <boost/xpressive/proto/transform.hpp>
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

typedef terminal<RedTag>::type RedT;
typedef terminal<BlueTag>::type BlueT;
typedef terminal<GreenTag>::type GreenT;

struct Red;
struct Blue;
struct Green;

///////////////////////////////////////////////////////////////////////////////
// A transform that produces new colors according to some arbitrary rules:
// red & green give blue, red & blue give green, blue and green give red.
struct Red
  : or_<
        plus<Green, Blue>
      , plus<Blue, Green>
      , plus<Red, Red>
      , terminal<RedTag>
    >
{};

struct Green
  : or_<
        plus<Red, Blue>
      , plus<Blue, Red>
      , plus<Green, Green>
      , terminal<GreenTag>
    >
{};

struct Blue
  : or_<
        plus<Red, Green>
      , plus<Green, Red>
      , plus<Blue, Blue>
      , terminal<BlueTag>
    >
{};

struct RGB
  : or_<
        when< Red, RedTag() >
      , when< Blue, BlueTag() >
      , when< Green, GreenTag() >
    >
{};

template<typename Expr>
void printColor(Expr const & expr)
{
    int i = 0; // dummy state and visitor parameter, not used
    std::cout << RGB()(expr, i, i) << std::endl;
}

int main()
{
    printColor(RedT() + GreenT());
    printColor(RedT() + GreenT() + BlueT());
    printColor(RedT() + (GreenT() + BlueT()));

    return 0;
}
//]
