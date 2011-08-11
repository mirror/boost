/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/algorithm/iteration/ext_/for_each_s.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/container/ext_/tree.hpp>

struct print
{
    template <typename T>
    void operator()(T const& v) const
    {
        std::cout << "[ " << v << " ] ";
    }
};

int
main()
{
    using namespace boost::fusion;

    {
        for_each_s(
            make_tree(
                make_vector(double(0),'B')
              , make_tree(
                    make_vector(1,2,long(3))
                  , make_tree(make_vector('a','b','c'))
                  , make_tree(make_vector(short('d'),'e','f'))
                )
              , make_tree(
                    make_vector(4,5,6)
                  , make_tree(make_vector(float(1),'h','i'))
                  , make_tree(make_vector('j','k','l'))
                )
            )
          , print()
        );
    }

    return boost::report_errors();
}

