//
//  shared_ptr_alloc_test.cpp - use to evaluate the impact of count allocations
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/shared_ptr.hpp>
#include <boost/config.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <memory>

int const n = 1024 * 1024;

template<class T> void test(T * = 0)
{
    std::vector< boost::shared_ptr<T> > v;

    std::clock_t t = std::clock();

    for(int i = 0; i < n; ++i)
    {
        boost::shared_ptr<T> pi(new T(i));
        v.push_back(pi);
    }

    t = std::clock() - t;

    std::cout << static_cast<double>(t) / CLOCKS_PER_SEC << '\n';
}

class X
{
public:

    explicit X(int n): n_(n)
    {
    }

    void * operator new(std::size_t)
    {
        return std::allocator<X>().allocate(1, static_cast<X*>(0));
    }

    void operator delete(void * p)
    {
        std::allocator<X>().deallocate(static_cast<X*>(p), 1);
    }

private:

    X(X const &);
    X & operator=(X const &);

    int n_;
};

int main()
{
    std::cout << BOOST_COMPILER "\n";
    std::cout << BOOST_PLATFORM "\n";
    std::cout << BOOST_STDLIB "\n";

#if defined(BOOST_HAS_THREADS)
    std::cout << "BOOST_HAS_THREADS: (defined)\n";
#else
    std::cout << "BOOST_HAS_THREADS: (not defined)\n";
#endif

#if defined(BOOST_SP_USE_STD_ALLOCATOR)
    std::cout << "BOOST_SP_USE_STD_ALLOCATOR: (defined)\n";
#else
    std::cout << "BOOST_SP_USE_STD_ALLOCATOR: (not defined)\n";
#endif

    std::cout << n << " shared_ptr<int> allocations + deallocations:\n";

    test<int>();
    test<int>();
    test<int>();

    std::cout << n << " shared_ptr<X> allocations + deallocations:\n";

    test<X>();
    test<X>();
    test<X>();
}
