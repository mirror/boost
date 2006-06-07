/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_COLLECTOR_HPP)
#define BOOST_SPIRIT_QUICKBOOK_COLLECTOR_HPP

#include <string>
#include <stack>
#include <sstream>
#include <boost/ref.hpp>
#include <boost/noncopyable.hpp>

namespace quickbook
{
    struct collector : boost::noncopyable
    {
        collector();
        collector(std::stringstream& out);
        ~collector();
        
        std::ostream& get() const;
        std::string str() const;
        void str(std::string const& s);
        void push();
        void pop();

    private:

        std::stack<std::stringstream*> streams;
        boost::reference_wrapper<std::stringstream> main;
        boost::reference_wrapper<std::stringstream> top;
        std::stringstream default_;
    };
    
    template <typename T>
    inline collector& 
    operator<<(collector& out, T const& val)
    {
        out.get() << val;
        return out;
    }
}

#endif // BOOST_SPIRIT_QUICKBOOK_COLLECTOR_HPP

