// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/standard_relation.hpp
/// \brief Includes the relation class

#ifndef BOOST_BIMAP_RELATION_STANDARD_RELATION_VIEW_HPP
#define BOOST_BIMAP_RELATION_STANDARD_RELATION_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/standard_relation_fwd.hpp>

#include <boost/mpl/bool.hpp>
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
#include <boost/bimap/relation/structured_pair.hpp>


namespace boost {
namespace bimaps {
namespace relation {

template< class TA, class TB >
class const_standard_relation_view;

/** \brief Standard relation above view.

See also standard_relation.
                                                           **/

template< class TA, class TB >
class standard_relation_view  :

    public symmetrical_base<TA,TB>
{

    typedef symmetrical_base<TA,TB> base_;

    public:

    //@{
        /// A signature compatible std::pair that is a view of the relation.

        typedef structured_pair<TA,TB,normal_layout> left_pair ;
        typedef structured_pair<TB,TA,mirror_layout> right_pair;

        typedef standard_pair_view<TA,TB,false,normal_layout>
            left_pair_reference;

        typedef standard_pair_view<TB,TA,false,mirror_layout>
            right_pair_reference;

        typedef const standard_pair_view<TA,TB,true,normal_layout>
            const_left_pair_reference;

        typedef const standard_pair_view<TB,TA,true,mirror_layout>
            const_right_pair_reference;

    //@}

    //@{

        /// data, exposed for easy manipulation
        BOOST_DEDUCED_TYPENAME base_:: left_value_type &  left;
        BOOST_DEDUCED_TYPENAME base_::right_value_type & right;

    //@}

    private:

    typedef standard_relation<TA,TB,true > relation_force_mutable;
    typedef standard_relation<TA,TB,false> relation_not_force_mutable;

    public:

    explicit standard_relation_view(relation_force_mutable & rel) :

        left (rel.left),
        right(rel.right)
    {}

    // The following functions are redundant if you only consider this class.
    // They are included to make easier the construction of the get and the
    // pair_by metafunction. Remember that not all compiler supports the mutant
    // idiom.

    BOOST_DEDUCED_TYPENAME base_::left_value_type & get_left()
    {
        return left;
    }

    const BOOST_DEDUCED_TYPENAME base_::left_value_type & get_left() const
    {
        return left;
    }

    BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()
    {
        return right;
    }

    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right() const
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

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,standard_relation_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,standard_relation_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }
};

/** \brief Const Standard relation above view.

See also standard_relation_view, standard_relation.
                                                           **/

template< class TA, class TB >
class const_standard_relation_view  :

    public symmetrical_base<TA,TB>
{

    typedef symmetrical_base<TA,TB> base_;

    public:

    //@{
        /// A signature compatible std::pair that is a view of the relation.

        typedef structured_pair<TA,TB,normal_layout> left_pair ;
        typedef structured_pair<TB,TA,mirror_layout> right_pair;

        typedef standard_pair_view<TA,TB,false,normal_layout>
            left_pair_reference;

        typedef standard_pair_view<TB,TA,false,mirror_layout>
            right_pair_reference;

        typedef standard_pair_view<TA,TB,true,normal_layout>
            const_left_pair_reference;

        typedef standard_pair_view<TB,TA,true,mirror_layout>
            const_right_pair_reference;

    //@}

    //@{

        /// data, exposed for easy manipulation
        const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  left;
        const BOOST_DEDUCED_TYPENAME base_::right_value_type & right;

    //@}

    private:

    typedef standard_relation<TA,TB,true > relation_force_mutable;
    typedef standard_relation<TA,TB,false> relation_not_force_mutable;
    typedef standard_relation_view<TA,TB> relation_view;

    public:

    explicit const_standard_relation_view(const relation_force_mutable & rel) :

        left (rel.left),
        right(rel.right)
    {}

    // The following functions are redundant if you only consider this class.
    // They are included to make easier the construction of the get and the
    // pair_by metafunction. Remember that not all compiler supports the mutant
    // idiom.

    const BOOST_DEDUCED_TYPENAME base_::left_value_type & get_left() const
    {
        return left;
    }

    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right() const
    {
        return right;
    }

    const_left_pair_reference get_left_pair() const
    {
        return const_left_pair_reference(*this);
    }

    const_right_pair_reference get_right_pair() const
    {
        return const_right_pair_reference(*this);
    }

    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const_standard_relation_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }

    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const_standard_relation_view>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }
};

// standard_relation_view - standard_relation_view

template< class FirstType, class SecondType >
bool operator==(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType >
bool operator!=(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType >
bool operator<(const standard_relation_view<FirstType,SecondType> & a,
               const standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType >
bool operator<=(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType >
bool operator>(const standard_relation_view<FirstType,SecondType> & a,
               const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType >
bool operator>=(const standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// const_standard_relation_view - const_standard_relation_view

template< class FirstType, class SecondType >
bool operator==(const const_standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType >
bool operator!=(const const_standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType >
bool operator<(const const_standard_relation_view<FirstType,SecondType> & a,
               const const_standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType >
bool operator<=(const const_standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType >
bool operator>(const const_standard_relation_view<FirstType,SecondType> & a,
               const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType >
bool operator>=(const const_standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// standard_relation_view - const_standard_relation_view

template< class FirstType, class SecondType >
bool operator==(const standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType >
bool operator!=(const standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType >
bool operator<(const standard_relation_view<FirstType,SecondType> & a,
               const const_standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType >
bool operator<=(const standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType >
bool operator>(const standard_relation_view<FirstType,SecondType> & a,
               const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType >
bool operator>=(const standard_relation_view<FirstType,SecondType> & a,
                const const_standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}

// const_standard_relation_view - standard_relation_view

template< class FirstType, class SecondType >
bool operator==(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}

template< class FirstType, class SecondType >
bool operator!=(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ! ( a == b );
}

template< class FirstType, class SecondType >
bool operator<(const const_standard_relation_view<FirstType,SecondType> & a,
               const standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}

template< class FirstType, class SecondType >
bool operator<=(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}

template< class FirstType, class SecondType >
bool operator>(const const_standard_relation_view<FirstType,SecondType> & a,
               const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}

template< class FirstType, class SecondType >
bool operator>=(const const_standard_relation_view<FirstType,SecondType> & a,
                const standard_relation_view<FirstType,SecondType> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}


} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_STANDARD_RELATION_VIEW_HPP


