// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CONTAINER_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONTAINER_HPP_INCLUDED

#include <boost/iostreams/detail/adapters/forward_container_adapter.hpp>
#include <boost/iostreams/detail/adapters/random_access_container_adapter.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> 
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Container, typename Mode>
struct container_device_traits {
    typedef typename Container::iterator                           iterator;
    typedef typename iterator_traversal<iterator>::type            trav;
    typedef typename 
            mpl::if_<
                is_convertible<trav, random_access_traversal_tag>,
                random_access_container_adapter<Container, Mode>,
                forward_container_adapter<Container, Mode>
            >::type                                                type;
    BOOST_STATIC_ASSERT((
        is_convertible<trav, forward_traversal_tag>::value
    ));
};

} // End namespace detail.

template<typename Container, typename Mode>
class container_device 
    : public detail::container_device_traits<Container, Mode>::type
{
private:
    typedef detail::container_device_traits<Container, Mode>  my_traits;
    typedef typename my_traits::type                          base_type;
public:    
    typedef Container                                         container_type;
    typedef typename Container::value_type                    char_type;
    struct category 
        : device_tag,
          Mode
        { };
    container_device() { }
        : base_type(new Container, true) 
        { }
    container_device(const Container& cnt) 
        : base_type(new Container(cnt), true) 
        { }
    container_device(const reference_wrapper<Container>& ref) 
        : base_type(ref.get_pointer(), false) 
        { }
    // Inherits read, write, seek and container.
};

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONTAINER_HPP_INCLUDED
