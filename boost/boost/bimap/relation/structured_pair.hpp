// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/structured_pair.hpp
/// \brief Defines the structured_pair class.

#ifndef BOOST_BIMAP_RELATION_STRUCTURED_PAIR_HPP
#define BOOST_BIMAP_RELATION_STRUCTURED_PAIR_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/type_traits/remove_const.hpp>

#include <boost/call_traits.hpp>
#include <boost/operators.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/bimap/relation/pair_layout.hpp>
#include <boost/bimap/relation/symmetrical_base.hpp>
#include <boost/bimap/relation/support/get.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>


namespace boost {
namespace bimaps {
namespace relation {

/// \brief Storage definition of the left view of a mutant relation.
/**

See also storage_finder, mirror_storage.
                                                                            **/

template< class FirstType, class SecondType >
class normal_storage :
    public symmetrical_base<FirstType,SecondType>
{
    typedef symmetrical_base<FirstType,SecondType> base_;

    public:

    typedef normal_storage storage_;

    typedef BOOST_DEDUCED_TYPENAME base_::left_value_type  first_type;
    typedef BOOST_DEDUCED_TYPENAME base_::right_value_type second_type;

    first_type   first;
    second_type  second;

    normal_storage() {}

    normal_storage(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        first_type >::param_type f,
                   BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        second_type>::param_type s)

        : first(f), second(s) {}

          BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()      { return first;  }
    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return first;  }
          BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()      { return second; }
    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return second; }
};

/// \brief Storage definition of the right view of a mutant relation.
/**

See also storage_finder, normal_storage.
                                                                            **/

template< class FirstType, class SecondType >
class mirror_storage :
    public symmetrical_base<SecondType,FirstType>
{
    typedef symmetrical_base<SecondType,FirstType> base_;

    public:

    typedef mirror_storage storage_;

    typedef BOOST_DEDUCED_TYPENAME base_::left_value_type   second_type;
    typedef BOOST_DEDUCED_TYPENAME base_::right_value_type  first_type;

    second_type  second;
    first_type   first;

    mirror_storage() {}

    mirror_storage(BOOST_DEDUCED_TYPENAME ::boost::call_traits<first_type  >::param_type f,
                   BOOST_DEDUCED_TYPENAME ::boost::call_traits<second_type >::param_type s)

        : second(s), first(f)  {}

          BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()      { return second; }
    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return second; }
          BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()      { return first;  }
    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return first;  }
};

/** \struct boost::bimaps::relation::storage_finder
\brief Obtain the a storage with the correct layout.

\code
template< class FirstType, class SecondType, class Layout >
struct storage_finder
{
    typedef {normal/mirror}_storage<FirstType,SecondType> type;
};
\endcode

See also normal_storage, mirror_storage.
                                                                        **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class FirstType,
    class SecondType,
    class Layout
>
struct storage_finder
{
    typedef normal_storage<FirstType,SecondType> type;
};

template
<
    class FirstType,
    class SecondType
>
struct storage_finder<FirstType,SecondType,mirror_layout>
{
    typedef mirror_storage<FirstType,SecondType> type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class TA, class TB, bool FM >
class mutant_relation;

/// \brief A std::pair signature compatible class that allows you to control
///        the internal structure of the data.
/**
This class allows you to specify the order in wich the two data types will be
in the layout of the class.
                                                                               **/

template< class FirstType, class SecondType, class Layout = normal_layout >
class structured_pair :

    public storage_finder
    <
        FirstType, SecondType,

        Layout

    >::type

{
    typedef typename storage_finder<
        FirstType, SecondType, Layout >::type base_;

    public:

    typedef ::boost::mpl::vector3<
        structured_pair< FirstType, SecondType, normal_layout >,
        structured_pair< FirstType, SecondType, mirror_layout >,
        BOOST_DEDUCED_TYPENAME ::boost::mpl::if_<
            BOOST_DEDUCED_TYPENAME ::boost::is_same<Layout, normal_layout>::type,
            mutant_relation< FirstType, SecondType, true >,
            mutant_relation< SecondType, FirstType, true >
        >::type

    > mutant_views;

    structured_pair() {}

    structured_pair(BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type  >::param_type x,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type >::param_type y)

        : base_(x,y) {}

    template< class OtherLayout >
    structured_pair(
        const structured_pair<FirstType,SecondType,OtherLayout> & p)

        : base_(p.first,p.second) {}

    template< class OtherLayout >
    structured_pair& operator=(
        const structured_pair<FirstType,SecondType,OtherLayout> & p)
    {
        base_::first = p.first;
        base_::second = p.second;
        return *this;
    }

    template< class First, class Second >
    structured_pair(const std::pair<First,Second> & p) :
        base_(p.first,p.second)
    {}

    template< class First, class Second >
    structured_pair& operator=(const std::pair<First,Second> & p)
    {
        base_::first  = p.first;
        base_::second = p.second;
        return *this;
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,structured_pair>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,structured_pair>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }
};

// structured_pair - structured_pair

template< class FirstType, class SecondType, class Layout1, class Layout2 >
bool operator==(const structured_pair<FirstType,SecondType,Layout1> & a,
                const structured_pair<FirstType,SecondType,Layout2> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class FirstType, class SecondType, class Layout1, class Layout2 >
bool operator!=(const structured_pair<FirstType,SecondType,Layout1> & a,
                const structured_pair<FirstType,SecondType,Layout2> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, class Layout1, class Layout2 >
bool operator<(const structured_pair<FirstType,SecondType,Layout1> & a,
               const structured_pair<FirstType,SecondType,Layout2> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class FirstType, class SecondType, class Layout1, class Layout2 >
bool operator<=(const structured_pair<FirstType,SecondType,Layout1> & a,
                const structured_pair<FirstType,SecondType,Layout2> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class FirstType, class SecondType, class Layout1, class Layout2 >
bool operator>(const structured_pair<FirstType,SecondType,Layout1> & a,
               const structured_pair<FirstType,SecondType,Layout2> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class FirstType, class SecondType, class Layout1, class Layout2 >
bool operator>=(const structured_pair<FirstType,SecondType,Layout1> & a,
                const structured_pair<FirstType,SecondType,Layout2> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}

// structured_pair - std::pair

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator==(const structured_pair<FirstType,SecondType,Layout> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator!=(const structured_pair<FirstType,SecondType,Layout> & a,
                const std::pair<F,S> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator<(const structured_pair<FirstType,SecondType,Layout> & a,
               const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator<=(const structured_pair<FirstType,SecondType,Layout> & a,
                const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator>(const structured_pair<FirstType,SecondType,Layout> & a,
               const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator>=(const structured_pair<FirstType,SecondType,Layout> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}

// std::pair - sturctured_pair

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator==(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Layout> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator!=(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Layout> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator<(const std::pair<F,S> & a,
               const structured_pair<FirstType,SecondType,Layout> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator<=(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Layout> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator>(const std::pair<F,S> & a,
               const structured_pair<FirstType,SecondType,Layout> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class FirstType, class SecondType, class Layout, class F, class S >
bool operator>=(const std::pair<F,S> & a,
                const structured_pair<FirstType,SecondType,Layout> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}



} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_STRUCTURED_PAIR_HPP

