//-----------------------------------------------------------------------------
// boost fsm/event.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FSM_EVENT_INCLUDED
#define BOOST_FSM_EVENT_INCLUDED

#include "base_event.hpp"

namespace fsm {
namespace aux {

template< typename Derived >
struct event
    : base_event
{
 public:
    typedef base_event base_t;

 private:
    virtual std::auto_ptr<base_event> do_clone() const
    {
        return std::auto_ptr<base_event>(
              new Derived(static_cast<Derived const&>(*this))
            );
    }
};

} // namespace aux
} // namespace fsm

#endif // BOOST_FSM_EVENT_INCLUDED
