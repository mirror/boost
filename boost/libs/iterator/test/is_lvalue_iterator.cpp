// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <deque>
#include <iterator>
#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/broken_compiler_spec.hpp>
#include <boost/iterator/is_lvalue_iterator.hpp>
#include <boost/iterator.hpp>

// Last, for BOOST_NO_LVALUE_RETURN_DETECTION
#include <boost/iterator/detail/config_def.hpp>

struct v
{
    v();
    ~v();
};

BOOST_TT_BROKEN_COMPILER_SPEC(v)

struct value_iterator : boost::iterator<std::input_iterator_tag,v>
{
    v operator*() const;
};

struct noncopyable_iterator : boost::iterator<std::forward_iterator_tag,boost::noncopyable>
{
    boost::noncopyable const& operator*() const;
};

struct proxy_iterator : boost::iterator<std::output_iterator_tag,v>
{
#if BOOST_WORKAROUND(__GNUC__, == 2)
    typedef boost::iterator<std::input_iterator_tag,v> base;
    typedef base::iterator_category iterator_category;
    typedef base::value_type value_type;
    typedef base::difference_type difference_type;
    typedef base::pointer pointer;
    typedef base::reference reference;
#endif 
    
    struct proxy
    {
        operator v&() const;
        proxy& operator=(v) const;
    };
        
    proxy operator*() const;
};

BOOST_TT_BROKEN_COMPILER_SPEC(proxy_iterator::proxy)

int main()
{
    BOOST_STATIC_ASSERT(boost::is_readable_lvalue_iterator<v*>::value);
    BOOST_STATIC_ASSERT(boost::is_readable_lvalue_iterator<v const*>::value);
    BOOST_STATIC_ASSERT(boost::is_readable_lvalue_iterator<std::deque<v>::iterator>::value);
    BOOST_STATIC_ASSERT(boost::is_readable_lvalue_iterator<std::deque<v>::const_iterator>::value);
    BOOST_STATIC_ASSERT(!boost::is_readable_lvalue_iterator<std::back_insert_iterator<std::deque<v> > >::value);
    BOOST_STATIC_ASSERT(!boost::is_readable_lvalue_iterator<std::ostream_iterator<v> >::value);
    BOOST_STATIC_ASSERT(!boost::is_readable_lvalue_iterator<proxy_iterator>::value);
#ifndef BOOST_NO_LVALUE_RETURN_DETECTION
    BOOST_STATIC_ASSERT(!boost::is_readable_lvalue_iterator<value_iterator>::value);
#endif
    // Make sure inaccessible copy constructor doesn't prevent
    // reference binding
    BOOST_STATIC_ASSERT(boost::is_readable_lvalue_iterator<noncopyable_iterator>::value);

    
    BOOST_STATIC_ASSERT(boost::is_writable_lvalue_iterator<v*>::value);
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<v const*>::value);
    BOOST_STATIC_ASSERT(boost::is_writable_lvalue_iterator<std::deque<v>::iterator>::value);
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<std::deque<v>::const_iterator>::value);
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<std::back_insert_iterator<std::deque<v> > >::value);
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<std::ostream_iterator<v> >::value);
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<proxy_iterator>::value);
#ifndef BOOST_NO_LVALUE_RETURN_DETECTION
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<value_iterator>::value);
#endif
    BOOST_STATIC_ASSERT(!boost::is_writable_lvalue_iterator<noncopyable_iterator>::value);
    
    return 0;
}
