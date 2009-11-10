
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_HELPERS_INPUT_ITERATOR_HEADER)
#define BOOST_UNORDERED_TEST_HELPERS_INPUT_ITERATOR_HEADER

#include <boost/config.hpp>
#include <boost/iterator_adaptors.hpp>

namespace test
{
    template <class Iterator>
    struct proxy
    {
        typedef BOOST_DEDUCED_TYPENAME Iterator::value_type value_type;

        proxy(value_type const& v) : v_(v) {}
        proxy(proxy const& x) : v_(x.v_) {}
        operator value_type const&() const { return v_; }
        
        value_type v_;
    private:
        proxy& operator=(proxy const&);
    };

    template <class Iterator>
    struct input_iterator_adaptor
        : boost::iterator_adaptor<
            input_iterator_adaptor<Iterator>, Iterator,
            boost::use_default, std::input_iterator_tag,
            proxy<Iterator> >
    {
        typedef boost::iterator_adaptor<
            input_iterator_adaptor<Iterator>, Iterator,
            boost::use_default, std::input_iterator_tag,
            proxy<Iterator> > base;

        explicit input_iterator_adaptor(Iterator it = Iterator())
            : base(it) {}
    };

    template <class Iterator>
    input_iterator_adaptor<Iterator> input_iterator(Iterator it)
    {
        return input_iterator_adaptor<Iterator>(it);
    }
}

#endif

