//-----------------------------------------------------------------------------
// boost fsm/base_event.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FSM_BASE_EVENT_INCLUDED
#define BOOST_FSM_BASE_EVENT_INCLUDED

#include <memory>

namespace fsm {
namespace aux {

// represent an abstract base for FSM events

struct base_event
{
 public:
    virtual ~base_event() {};
    
    std::auto_ptr<base_event> clone() const
    {
        return do_clone();
    }
 
 private:
    virtual std::auto_ptr<base_event> do_clone() const = 0;
};

} // namespace aux
} // namespace fsm

#endif // BOOST_FSM_BASE_EVENT_INCLUDED
