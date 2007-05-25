// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/mutant_relation.hpp
/// \brief Defines the mutant_relation class

#ifndef BOOST_BIMAP_RELATION_MUTANT_RELATION_HPP
#define BOOST_BIMAP_RELATION_MUTANT_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/operators.hpp>
#include <boost/call_traits.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/functional/hash/hash.hpp>

// Boost.Bimap
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>
#include <boost/bimap/tags/support/tag_of.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/relation/detail/mutant.hpp>
#include <boost/bimap/relation/structured_pair.hpp>
#include <boost/bimap/relation/support/get.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief Abstraction of a related pair of values, that extends the std::pair class.
/**
The mutant_relation is a mutant class. A mutant class can mutate
with zero overhead in other classes that are called views.
Each view has to be StorageCompatible with the base class
of the mutant. Note that all the views have the following
storage structure:

\verbatim
                        __________
                       |          |
                       |    TA    |
                       |__________|
                       |          |
                       |    TB    |
                       |__________|

\endverbatim

See also select_relation, standard_relation.
\ingroup relation_group
                                                           **/

template< class TA, class TB, bool force_mutable = false >
class mutant_relation
{
    public:

    typedef       mutant_relation<TA,TB>         above_view;
    typedef const mutant_relation<TA,TB>   const_above_view;

    typedef       mutant_relation<TA,TB> &       above_view_reference;
    typedef const mutant_relation<TA,TB> & const_above_view_reference;

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

    typedef ::boost::mpl::vector4
    <
        structured_pair< TA, TB, normal_layout >,
        structured_pair< TB, TA, mirror_layout >,
        mutant_relation< TA, TB, true >,
        above_view

    > mutant_views;

    //@{
        /// A signature compatible std::pair that is a view of the relation.

        typedef structured_pair< TA, TB, normal_layout > left_pair ;
        typedef structured_pair< TB, TA, mirror_layout > right_pair;

        typedef left_pair  & left_pair_reference ;
        typedef right_pair & right_pair_reference;

        typedef const left_pair  & const_left_pair_reference ;
        typedef const right_pair & const_right_pair_reference;
    //@}

    //@{

        /// data, exposed for easy manipulation
        left_value_type  left;
        right_value_type right;

    //@}

    mutant_relation() {}

    mutant_relation(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        left_value_type >::param_type l,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        right_value_type>::param_type r) :
        left (l),
        right(r)
    {}

    mutant_relation(const mutant_relation<TA,TB,false> & rel) :

        left (rel.left),
        right(rel.right)
    {}

    mutant_relation(const mutant_relation<TA,TB,true> & rel) :

        left (rel.left),
        right(rel.right)
    {}

    // Operators

    template< bool FM >
    mutant_relation& operator=(const mutant_relation<TA,TB,FM> & rel)
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
        return ::boost::bimaps::relation::detail::mutate<left_pair>(*this);
    }

    const_left_pair_reference get_left_pair() const
    {
        return ::boost::bimaps::relation::detail::mutate<left_pair>(*this);
    }

    right_pair_reference get_right_pair()
    {
        return ::boost::bimaps::relation::detail::mutate<right_pair>(*this);
    }

    const_right_pair_reference get_right_pair() const
    {
        return ::boost::bimaps::relation::detail::mutate<right_pair>(*this);
    }

    above_view_reference get_view()
    {
        return ::boost::bimaps::relation::detail::mutate<above_view>(*this);
    }

    const_above_view_reference get_view() const
    {
        return ::boost::bimaps::relation::detail::mutate<above_view>(*this);
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,mutant_relation>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,mutant_relation>::type
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

template< class FirstType, class SecondType, bool FM >
std::size_t hash_value(const mutant_relation<FirstType,SecondType,FM> & p)
{
    std::size_t seed = 0;
    ::boost::hash_combine(seed, p.left );
    ::boost::hash_combine(seed, p.right);

    return seed;
}

// mutant_relation - mutant_relation

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator==(const mutant_relation<FirstType,SecondType,FM1> & a,
                const mutant_relation<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator!=(const mutant_relation<FirstType,SecondType,FM1> & a,
                const mutant_relation<FirstType,SecondType,FM2> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<(const mutant_relation<FirstType,SecondType,FM1> & a,
               const mutant_relation<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<=(const mutant_relation<FirstType,SecondType,FM1> & a,
                const mutant_relation<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>(const mutant_relation<FirstType,SecondType,FM1> & a,
               const mutant_relation<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>=(const mutant_relation<FirstType,SecondType,FM1> & a,
                const mutant_relation<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_MUTANT_RELATION_HPP



