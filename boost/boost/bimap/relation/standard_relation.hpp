// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/standard_relation.hpp
/// \brief Includes the relation class

#ifndef BOOST_BIMAP_RELATION_STANDARD_RELATION_HPP
#define BOOST_BIMAP_RELATION_STANDARD_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/standard_relation_fwd.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/serialization/nvp.hpp>

// Boost.Bimap
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>
#include <boost/bimap/tags/support/tag_of.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/relation/symmetrical_base.hpp>
#include <boost/bimap/relation/standard_pair_view.hpp>
#include <boost/bimap/relation/standard_relation_view.hpp>
#include <boost/bimap/relation/structured_pair.hpp>
#include <boost/bimap/relation/support/get.hpp>

#include <boost/functional/hash/hash.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief Abstraction of a related pair of values, that extends the std::pair class.
/**

This is a standard compliant suboptimal relation class.

See also standard_relation, mutant_relation.
\ingroup relation_group
                                                                           **/

template< class TA, class TB, bool force_mutable >
class standard_relation
{
    public:

    typedef BOOST_DEDUCED_TYPENAME tags::support::default_tagged
    <
        TA,
        member_at::left

    >::type tagged_left_type;

    typedef BOOST_DEDUCED_TYPENAME tags::support::default_tagged
    <
        TB,
        member_at::right

    >::type tagged_right_type;

    public:

    typedef       standard_relation<TA,TB>            above_view;
    typedef const standard_relation<TA,TB>      const_above_view;

    typedef             standard_relation_view<TA,TB>       above_view_reference;
    typedef const const_standard_relation_view<TA,TB> const_above_view_reference;

    //@{

        /// The type stored in the relation

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_c< force_mutable,

            BOOST_DEDUCED_TYPENAME ::boost::remove_const<
                BOOST_DEDUCED_TYPENAME tagged_left_type::value_type >::type,
            BOOST_DEDUCED_TYPENAME tagged_left_type::value_type

        >::type left_value_type;

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_c< force_mutable,

            BOOST_DEDUCED_TYPENAME ::boost::remove_const<
                BOOST_DEDUCED_TYPENAME tagged_right_type::value_type >::type,
            BOOST_DEDUCED_TYPENAME tagged_right_type::value_type

        >::type right_value_type;

    //@}

    //@{

        /// The tag of the member. By default it is \c member_at::{side}
        typedef BOOST_DEDUCED_TYPENAME  tagged_left_type::tag  left_tag;
        typedef BOOST_DEDUCED_TYPENAME tagged_right_type::tag right_tag;

    //@}

    public:

    //@{
        /// A signature compatible std::pair that is a view of the relation.

        typedef structured_pair<TA,TB,normal_layout> left_pair ;
        typedef structured_pair<TB,TA,mirror_layout> right_pair;

        typedef standard_pair_view<TA,TB,normal_layout>
            left_pair_reference ;

        typedef standard_pair_view<TB,TA,mirror_layout>
            right_pair_reference;

        typedef const const_standard_pair_view<TA,TB,normal_layout>
            const_left_pair_reference ;

        typedef const const_standard_pair_view<TB,TA,mirror_layout>
            const_right_pair_reference;

    //@}


    //@{

        /// data, exposed for easy manipulation
         left_value_type  left;
        right_value_type right;

    //@}

    private:

    typedef standard_relation<TA,TB,true > relation_force_mutable;
    typedef standard_relation<TA,TB,false> relation_not_force_mutable;

    public:

    standard_relation() {}

    standard_relation(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                           left_value_type>::param_type l,
                      BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                          right_value_type>::param_type r) :
        left (l),
        right(r)
    {}

    standard_relation(const relation_force_mutable & rel) :

        left (rel.left),
        right(rel.right)
    {}

    standard_relation(const relation_not_force_mutable & rel) :

        left (rel.left),
        right(rel.right)
    {}

    standard_relation(const standard_relation_view<TA,TB> & rel) :

        left (rel.left),
        right(rel.right)
    {}

    standard_relation(const const_standard_relation_view<TA,TB> & rel) :

        left (rel.left),
        right(rel.right)
    {}

    // Allow to create relations from views

    explicit standard_relation(const left_pair & lp) :

        left ( lp.first  ),
        right( lp.second )
    {}

    explicit standard_relation(const right_pair & rp) :

        left ( rp.second ),
        right( rp.first  )
    {}

    // Operators

    template< bool FM >
    standard_relation& operator=(const standard_relation<TA,TB,FM> & rel)
    {
        left  = rel.left ;
        right = rel.right;
        return *this;
    }

    // The following functions are redundant if you only consider this class.
    // They are included to make easier the construction of the get and the
    // pair_by metafunction. Remember that not all compiler supports the mutant
    // idiom.

    left_value_type & get_left()
    {
        return left;
    }

    const left_value_type & get_left() const
    {
        return left;
    }

    right_value_type & get_right()
    {
        return right;
    }

    const right_value_type & get_right() const
    {
        return right;
    }

    left_pair_reference get_left_pair()
    {
        return left_pair_reference(*this);
    }
    const_left_pair_reference get_left_pair() const
    {
        return const_left_pair_reference(*this);
    }

    right_pair_reference get_right_pair()
    {
        return right_pair_reference(*this);
    }

    const_right_pair_reference get_right_pair() const
    {
        return const_right_pair_reference(*this);
    }

    above_view_reference get_view()
    {
        return above_view_reference(*this);
    }

    const_above_view_reference get_view() const
    {
        return const_above_view_reference(*this);
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,standard_relation>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,standard_relation>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    #ifndef BOOST_BIMAP_DISABLE_SERIALIZATION

    // Serialization support

    private:

    friend class ::boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(left );
        ar & BOOST_SERIALIZATION_NVP(right);
    }

    #endif // BOOST_BIMAP_DISABLE_SERIALIZATION
};

// hash value

template< class First, class Second, bool FM >
std::size_t hash_value(const standard_relation<First,Second,FM> & p)
{
    std::size_t seed = 0;
    ::boost::hash_combine(seed, p.left );
    ::boost::hash_combine(seed, p.right);

    return seed;
}

// standard_relation - standard_relation

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator==(const standard_relation<FirstType,SecondType,FM1> & a,
                const standard_relation<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator!=(const standard_relation<FirstType,SecondType,FM1> & a,
                const standard_relation<FirstType,SecondType,FM2> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<(const standard_relation<FirstType,SecondType,FM1> & a,
               const standard_relation<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<=(const standard_relation<FirstType,SecondType,FM1> & a,
                const standard_relation<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>(const standard_relation<FirstType,SecondType,FM1> & a,
               const standard_relation<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>=(const standard_relation<FirstType,SecondType,FM1> & a,
                const standard_relation<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// standard_relation - standard_relation_view

template< class FirstType, class SecondType, bool FM >
bool operator==(const standard_relation<FirstType,SecondType,FM> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM >
bool operator!=(const standard_relation<FirstType,SecondType,FM> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM >
bool operator<(const standard_relation<FirstType,SecondType,FM> & a,
               const standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator<=(const standard_relation<FirstType,SecondType,FM> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>(const standard_relation<FirstType,SecondType,FM> & a,
               const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>=(const standard_relation<FirstType,SecondType,FM> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// standard_relation_view - standard_relation

template< class FirstType, class SecondType, bool FM >
bool operator==(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM >
bool operator!=(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM >
bool operator<(const standard_relation_view<FirstType,SecondType> & a,
               const standard_relation<FirstType,SecondType,FM> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator<=(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>(const standard_relation_view<FirstType,SecondType> & a,
               const standard_relation<FirstType,SecondType,FM> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>=(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// standard_relation - const_standard_relation

template< class FirstType, class SecondType, bool FM >
bool operator==(const standard_relation<FirstType,SecondType,FM> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM >
bool operator!=(const standard_relation<FirstType,SecondType,FM> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM >
bool operator<(const standard_relation<FirstType,SecondType,FM> & a,
               const const_standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator<=(const standard_relation<FirstType,SecondType,FM> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>(const standard_relation<FirstType,SecondType,FM> & a,
               const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>=(const standard_relation<FirstType,SecondType,FM> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// const_standard_relation - standard_relation

template< class FirstType, class SecondType, bool FM >
bool operator==(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM >
bool operator!=(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM >
bool operator<(const const_standard_relation_view<FirstType,SecondType> & a,
               const standard_relation<FirstType,SecondType,FM> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator<=(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>(const const_standard_relation_view<FirstType,SecondType> & a,
               const standard_relation<FirstType,SecondType,FM> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM >
bool operator>=(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation<FirstType,SecondType,FM> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}


} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_STANDARD_RELATION_HPP


