// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/standard_pair_view.hpp
/// \brief Defines the standard_pair_view class.

#ifndef BOOST_BIMAP_RELATION_STANDARD_PAIR_VIEW_HPP
#define BOOST_BIMAP_RELATION_STANDARD_PAIR_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/standard_relation_fwd.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

#include <utility>

#include <boost/call_traits.hpp>
#include <boost/operators.hpp>
#include <boost/bimap/relation/pair_layout.hpp>
#include <boost/bimap/relation/symmetrical_base.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>
#include <boost/bimap/relation/structured_pair.hpp>
#include <boost/bimap/relation/support/get.hpp>

namespace boost {
namespace bimaps {
namespace relation {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< bool constant, class Type >
struct add_const_if_c : ::boost::mpl::if_c< constant, BOOST_DEDUCED_TYPENAME ::boost::add_const< Type >::type , Type > {};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief The left side view of a standard relation
/**
See also reference_binder_finder, normal_reference_binder.
                                                                        **/

template< class FirstType, class SecondType, bool constant = false >
struct normal_reference_binder :

    public symmetrical_base<FirstType,SecondType>
{
    typedef symmetrical_base<FirstType,SecondType> base_;

    public:

    typedef normal_reference_binder reference_binder_;

    typedef BOOST_DEDUCED_TYPENAME add_const_if_c<
        constant,
        BOOST_DEDUCED_TYPENAME base_:: left_value_type 

    >::type  first_type;

    typedef BOOST_DEDUCED_TYPENAME add_const_if_c< 
        constant,
        BOOST_DEDUCED_TYPENAME base_::right_value_type 

    >::type second_type;

     first_type & first;
    second_type & second;

    template< class Relation >
    normal_reference_binder(Relation & r) :
        first(r.left), second(r.right) {}

    normal_reference_binder(first_type & f, second_type & s) :
        first(f), second(s) {}

           first_type & get_left ()       { return first;  }
    const  first_type & get_left () const { return first;  }
          second_type & get_right()       { return second; }
    const second_type & get_right() const { return second; }
};

/// \brief The right side view of a standard relation
/**
See also reference_binder_finder, mirror_reference_binder.
                                                                        **/
template< class FirstType, class SecondType, bool constant = false >
struct mirror_reference_binder :

    public symmetrical_base<SecondType,FirstType>
{

    typedef symmetrical_base<SecondType,FirstType> base_;

    public:

    typedef mirror_reference_binder reference_binder_;

    typedef BOOST_DEDUCED_TYPENAME add_const_if_c<
        constant,
        BOOST_DEDUCED_TYPENAME base_::right_value_type 

    >::type  first_type;

    typedef BOOST_DEDUCED_TYPENAME add_const_if_c<
        constant,
        BOOST_DEDUCED_TYPENAME base_:: left_value_type 

    >::type second_type;

    second_type & second;
     first_type & first;

    template< class Relation >
    mirror_reference_binder(Relation & r) :
        second(r.left), first(r.right) {}

    mirror_reference_binder(first_type & f, second_type & s) :
        second(s), first(f) {}

          second_type & get_left ()       { return second; }
    const second_type & get_left () const { return second; }
           first_type & get_right()       { return first;  }
    const  first_type & get_right() const { return first;  }
};


/** \struct boost::bimaps::relation::reference_binder_finder
\brief Obtain the a pair reference binder with the correct layout.

\code
template< class FirstType, class SecondType, class Layout >
struct reference_binder_finder
{
    typedef {normal/mirror}_reference_binder<FirstType,SecondType> type;
};
\endcode

See also normal_reference_binder, mirror_reference_binder.
                                                                        **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class FirstType, class SecondType, bool constant, class Layout >
struct reference_binder_finder
{
    typedef normal_reference_binder<FirstType,SecondType,constant> type;
};

template< class FirstType, class SecondType, bool constant >
struct reference_binder_finder<FirstType,SecondType,constant,mirror_layout>
{
    typedef mirror_reference_binder<FirstType,SecondType,constant> type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief A side view of a relation that is full compliant with the standard.
/**

See also standard_relation, const_standard_pair_view.
                                                                                **/

template< class FirstType, class SecondType, class Layout >
class standard_pair_view :

    public reference_binder_finder<FirstType,SecondType,false,Layout>::type,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,normal_layout>,
        standard_pair_view<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,normal_layout>,
        structured_pair<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,normal_layout>,
        structured_pair<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,mirror_layout>,
        structured_pair<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        standard_pair_view<FirstType,SecondType,mirror_layout>,
        structured_pair<FirstType,SecondType,mirror_layout>

    > > > > > > >

{
    typedef BOOST_DEDUCED_TYPENAME
        reference_binder_finder<FirstType,SecondType,false,Layout>::type base_;

    public:

    template< class Relation >
    explicit standard_pair_view(Relation & r) :
        base_(r) {}

    // Interaction with structured pair

    private:

    typedef structured_pair<FirstType,SecondType,Layout> structured_pair_type;

    public:

    operator const structured_pair_type () const
    {
        return structured_pair_type(
            base_::first, base_::second
        );
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,standard_pair_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,standard_pair_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    // totally_ordered - standard_pair_view

    template< class OtherLayout >
    bool operator==(const standard_pair_view<FirstType,SecondType,OtherLayout> & p) const
    {
        return ( ( base_::first  == p.first  ) &&
                 ( base_::second == p.second ) );
    }

    template< class OtherLayout >
    bool operator<(const standard_pair_view<FirstType,SecondType,OtherLayout> & p) const
    {
        return (  ( base_::first  <  p.first  ) ||
                 (( base_::first == p.first ) && ( base_::second < p.second )));
    }

    // totally_ordered - structured_pair

    template< class OtherLayout >
    bool operator==(const structured_pair<FirstType,SecondType,OtherLayout> & p) const
    {
        return ( ( base_::first  == p.first  ) &&
                 ( base_::second == p.second ) );
    }

    template< class OtherLayout >
    bool operator<(const structured_pair<FirstType,SecondType,OtherLayout> & p) const
    {
        return (  ( base_::first  <  p.first  ) ||
                 (( base_::first == p.first ) && ( base_::second < p.second )));
    }

};



/// \brief A side view of a relation that is full compliant with the standard.
/**

See also standard_relation, const_standard_pair_view.
                                                                                **/

template< class FirstType, class SecondType, class Layout >
class const_standard_pair_view :

    public reference_binder_finder<FirstType,SecondType,true,Layout>::type,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,normal_layout>,
        const_standard_pair_view<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,normal_layout>,
        standard_pair_view<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,normal_layout>,
        standard_pair_view<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,mirror_layout>,
        standard_pair_view<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,mirror_layout>,
        standard_pair_view<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,normal_layout>,
        structured_pair<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,normal_layout>,
        structured_pair<FirstType,SecondType,mirror_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,mirror_layout>,
        structured_pair<FirstType,SecondType,normal_layout>,

    ::boost::totally_ordered<
        const_standard_pair_view<FirstType,SecondType,mirror_layout>,
        structured_pair<FirstType,SecondType,mirror_layout>

    > > > > > > > > > > >

{
    typedef BOOST_DEDUCED_TYPENAME
        reference_binder_finder<FirstType,SecondType,true,Layout>::type base_;

    public:

    template< class OtherLayout >
    const_standard_pair_view(const standard_pair_view<FirstType,SecondType,OtherLayout> & p) :
        base_(p.first,p.second) {}

    template< class Relation >
    explicit const_standard_pair_view(Relation & r) :
        base_(r) {}

    // Interaction with structured pair

    private:

    typedef structured_pair<FirstType,SecondType,Layout> structured_pair_type;

    public:

    operator const structured_pair_type () const
    {
        return structured_pair_type(
            base_::first, base_::second
        );
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const_standard_pair_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    // totally_ordered - const_standard_pair_view

    template< class OtherLayout >
    bool operator==(const const_standard_pair_view<FirstType,SecondType,OtherLayout> & p) const
    {
        return ( ( base_::first  == p.first  ) &&
                 ( base_::second == p.second ) );
    }

    template< class OtherLayout >
    bool operator<(const const_standard_pair_view<FirstType,SecondType,OtherLayout> & p) const
    {
        return (  ( base_::first  <  p.first  ) ||
                 (( base_::first == p.first ) && ( base_::second < p.second )));
    }

    // totally_ordered - standard_pair_view

    template< class OtherLayout >
    bool operator==(const standard_pair_view<FirstType,SecondType,OtherLayout> & p) const
    {
        return ( ( base_::first  == p.first  ) &&
                 ( base_::second == p.second ) );
    }

    template< class OtherLayout >
    bool operator<(const standard_pair_view<FirstType,SecondType,OtherLayout> & p) const
    {
        return (  ( base_::first  <  p.first  ) ||
                 (( base_::first == p.first ) && ( base_::second < p.second )));
    }

    // totally_ordered - structured_pair

    template< class OtherLayout >
    bool operator==(const structured_pair<FirstType,SecondType,OtherLayout> & p) const
    {
        return ( ( base_::first  == p.first  ) &&
                 ( base_::second == p.second ) );
    }

    template< class OtherLayout >
    bool operator<(const structured_pair<FirstType,SecondType,OtherLayout> & p) const
    {
        return (  ( base_::first  <  p.first  ) ||
                 (( base_::first == p.first ) && ( base_::second < p.second )));
    }
};



// standard_pair_view - std::pair

template< class First, class Second, class L, class F, class S >
bool operator==(const standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class First, class Second, class L, class F, class S >
bool operator!=(const standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return ! ( a == b );
}

template< class First, class Second, class L, class F, class S >
bool operator<(const standard_pair_view<First,Second,L> & a,
               const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator<=(const standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>(const standard_pair_view<First,Second,L> & a,
               const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>=(const standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}


// std::pair - standard_pair_view

template< class First, class Second, class L, class F, class S >
bool operator==(const std::pair<F,S> & a,
                const standard_pair_view<First,Second,L> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class First, class Second, class L, class F, class S >
bool operator!=(const std::pair<F,S> & a,
                const standard_pair_view<First,Second,L> & b)
{
    return ! ( a == b );
}

template< class First, class Second, class L, class F, class S >
bool operator<(const std::pair<F,S> & a,
               const standard_pair_view<First,Second,L> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator<=(const std::pair<F,S> & a,
                const standard_pair_view<First,Second,L> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>(const std::pair<F,S> & a,
               const standard_pair_view<First,Second,L> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>=(const std::pair<F,S> & a,
                const standard_pair_view<First,Second,L> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}


// const_standard_pair_view - std::pair

template< class First, class Second, class L, class F, class S >
bool operator==(const const_standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class First, class Second, class L, class F, class S >
bool operator!=(const const_standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return ! ( a == b );
}

template< class First, class Second, class L, class F, class S >
bool operator<(const const_standard_pair_view<First,Second,L> & a,
               const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator<=(const const_standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>(const const_standard_pair_view<First,Second,L> & a,
               const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>=(const const_standard_pair_view<First,Second,L> & a,
                const std::pair<F,S> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}


// std::pair - const_standard_pair_view

template< class First, class Second, class L, class F, class S >
bool operator==(const std::pair<F,S> & a,
                const const_standard_pair_view<First,Second,L> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}

template< class First, class Second, class L, class F, class S >
bool operator!=(const std::pair<F,S> & a,
                const const_standard_pair_view<First,Second,L> & b)
{
    return ! ( a == b );
}

template< class First, class Second, class L, class F, class S >
bool operator<(const std::pair<F,S> & a,
               const const_standard_pair_view<First,Second,L> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator<=(const std::pair<F,S> & a,
                const const_standard_pair_view<First,Second,L> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>(const std::pair<F,S> & a,
               const const_standard_pair_view<First,Second,L> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}

template< class First, class Second, class L, class F, class S >
bool operator>=(const std::pair<F,S> & a,
                const const_standard_pair_view<First,Second,L> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}


} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_STANDARD_PAIR_VIEW_HPP

