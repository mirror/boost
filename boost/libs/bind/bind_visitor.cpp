#if defined(_MSC_VER) && !defined(__ICL)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  bind_visitor.cpp - tests bind.hpp with a visitor
//
//  Version 1.00.0003 (2001-10-18)
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <iostream>
#include <typeinfo>

int hash = 0;

struct ref_visitor
{
    template<class R, class F, class L> void operator()(boost::_bi::bind_t<R, F, L> const & b) const
    {
        b.accept(*this);
    }

    template<class T> void operator()(boost::reference_wrapper<T> const & r) const
    {
        std::cout << "Reference to " << typeid(T).name() << " @ " << &r.get() << " (with value " << r.get() << ")\n";
        hash += r.get();
    }

#ifndef BOOST_MSVC

    template<class T> void operator()(T const &) const
    {
        std::cout << "Catch-all: " << typeid(T).name() << '\n';
    }

#else

    void operator()(...) const
    {
    }

#endif

};

int f(int & i, int & j)
{
    ++i;
    --j;
    return i + j;
}

int x = 2;
int y = 7;

int detect_errors(bool x)
{
    if(x)
    {
        std::cerr << "no errors detected.\n";
        return 0;
    }
    else
    {
        std::cerr << "test failed.\n";
        return 1;
    }
}

int main()
{
    using namespace boost;

    ref_visitor()(bind<int>(bind(f, ref(x), _1), ref(y)));

    return detect_errors(hash == 9);
}
