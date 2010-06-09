// Copyright 2009 (C) Dean Michael Berris <me@deanberris.com>
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FUNCTION_INPUT_ITERATOR
#define BOOST_FUNCTION_INPUT_ITERATOR

#include <boost/iterator/iterator_facade.hpp>

namespace boost {

    template <class Function, class Input>
        class function_input_iterator
        : public iterator_facade<
            function_input_iterator<Function, Input>,
            typename Function::result_type,
            single_pass_traversal_tag,
            typename Function::result_type const &
            >
    {
        public:
            function_input_iterator() {}
            function_input_iterator(Function * f_, Input state_ = Input()) 
                : f(f_), state(state_), value((*f)()) {}

            void increment() {
                value = (*f)();
                ++state;
            }

            typename Function::result_type const & 
            dereference() const {
                return value;
            }

            bool equal(function_input_iterator const & other) const {
                return f == other.f && state == other.state;
            }

        private:
            Function * f;
            Input state;
            typename Function::result_type value;
    };

    template <class Function, class Input>
    inline function_input_iterator<Function, Input>
    make_function_input_iterator(Function & f, Input state) {
        typedef function_input_iterator<Function, Input> result_t;
        return result_t(&f, state);
    }

    struct infinite {
        infinite & operator++() { return *this; }
        infinite & operator++(int) { return *this; }
        bool operator==(infinite &) const { return false; };
        bool operator==(infinite const &) const { return false; };
    };
}

#endif

