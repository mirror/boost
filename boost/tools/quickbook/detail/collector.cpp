/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "./collector.hpp"
#include <boost/assert.hpp>

namespace quickbook
{
    collector::collector()
        : main(default_)
        , top(default_)
    {
    }

    collector::collector(std::stringstream& out)
        : main(out) 
        , top(out) 
    {
    }
    
    collector::~collector()
    {
        BOOST_ASSERT(streams.empty()); // assert there are no more pushes than pops!!!
    }
    
    std::ostream& 
    collector::get() const
    {
        return top.get();
    }
    
    std::string
    collector::str() const
    {
        return top.get().str();
    }
    
    void 
    collector::str(std::string const& s)
    {
        top.get().str(s);
    }
    
    void 
    collector::push()
    {
        streams.push(new std::stringstream());
        top = boost::ref(*streams.top());
    }
    
    void 
    collector::pop()
    {
        BOOST_ASSERT(!streams.empty());
        delete streams.top();
        streams.pop();

        if (streams.empty())
            top = boost::ref(main);
        else
            top = boost::ref(*streams.top());
    }
}
