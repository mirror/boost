// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/relation.hpp
/// \brief Includes the relation class

#ifndef BOOST_BIMAP_RELATION_RELATION_HPP
#define BOOST_BIMAP_RELATION_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

// Boost.Bimap
#include <boost/bimap/relation/mutant_relation.hpp>
#include <boost/bimap/relation/standard_relation.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>

#include <cstddef>

namespace boost {
namespace bimaps {

/// \brief Defines the relation class
/**

The relation class is an extension of the std framework proposed to relate
two types. In the actual standard std::pair is the way to tie to types
together. This two types are related but in a directed way. The first type
is related to the second one but the inverse relationship does not hold.
This is the reason why the names of the two members: \c first and \c second
is a consistent naming convension. However, there are a lot of cases where
do not exist a prefered type. There is no way to have the two types at
the same level with std::pair. In that cases a relation will fit better.
With a nice left/right naming convention and support to view the relation
as a signature compatible std::pair with first/second, is a very lightweight
class that as an additional feature supports user defined tags to access
the values so the code generated is autodocummented.

\ingroup relation_group

                                                                          **/

namespace relation {

namespace detail {

/// \brief Metafunction to test if the compiler supports the mutant idiom.
/**

See also select_relation, mutant_relation, standard_relation.
                                                                    **/

template< class TA, class TB >
struct is_mutant_idiom_supported_for
{
    #if defined(BOOST_MSVC)

        // In MSVC offset of works even for non-POD types. This allow a
        // strong check of the mutant idiom.

        typedef ::std::size_t offset_type;

        typedef structured_pair<TA,TB,normal_layout> pab;
        typedef structured_pair<TB,TA,mirror_layout> pba;
        typedef mutant_relation<TA,TB,true>          rel;
        typedef mutant_relation<TA,TB,false>         rvw;

        static const offset_type rel_left  = offsetof(rel,left);
        static const offset_type rel_right = offsetof(rel,right);

        static const offset_type rvw_left  = offsetof(rvw,left);
        static const offset_type rvw_right = offsetof(rvw,right);

        static const offset_type pab_left  = offsetof(pab,first);
        static const offset_type pab_right = offsetof(pab,second);

        static const offset_type pba_left  = offsetof(pba,second);
        static const offset_type pba_right = offsetof(pba,first);

        static const bool mutant_is_supported =

            (   rel_left  == rvw_left  &&
                rel_right == rvw_right &&
                rel_left  == pab_left  &&
                rel_right == pab_right &&
                rel_left  == pba_left  &&
                rel_right == pba_right     );

    #else

        // This is the base test, supported in any standard compliant
        // compiler. Other compiler specifics checks can be added above.
        // It is a strong check based in sizeof. It is pesimistic, if it fails,
        // the compiler may support the mutant idiom anyway. For compiler that
        // used struct aligment different from 1 this will probably fail.

        static const int sA = sizeof(
            BOOST_DEDUCED_TYPENAME tags::support::value_type_of<TA>::type );
        static const int sB = sizeof(
            BOOST_DEDUCED_TYPENAME tags::support::value_type_of<TB>::type );

        static const int sAB = sA + sB;

        static const bool mutant_is_supported =

            ( sizeof( structured_pair<TA,TB,normal_layout> ) == sAB ) &&
            ( sizeof( structured_pair<TB,TA,mirror_layout> ) == sAB ) &&
            ( sizeof( mutant_relation<TA,TB,false>         ) == sAB ) &&
            ( sizeof( mutant_relation<TA,TB,true>          ) == sAB ) ;

    #endif

    typedef mpl::bool_< true > type; //mutant_is_supported > type;
    static const bool value = type::value;
};

} // namespace detail

/// \brief Abstraction of a related pair of values, that extends the std::pair class.
/**

A \c select_relation<X,Y>::type has to be viewed in the following way: x is related
with y and y is related with x.

\verbatim
            __________             __________
           |          |           |          |
           |          |           |          |
           |    X     | <-------> |    Y     |
           |          |           |          |
           |__________|           |__________|

              left                  right

\endverbatim

By no means a relation imposes a ordering between the data.
This is the main difference with the concept of a pair in
the std library. If used with tags you can even exchange the
left and right parameter in the template definition and all
the code will continue working.

If not tags are used, the first/second members are replaced
by the more symetric approach: member_at::left and
member_at::right.

\note Even when user tags are specified the
      member_at idiom still works.

With the actual standard, the optimal implementation is not ANSI compliant.
However most compilers support it so this metafunction check if the compiler
will do the right thing with the layout of each class and if the mutant idiom
is supported. If this is the case mutant_relation will be used. If it is not
supported then standard_relation, a suboptimasl approach based in references
will be used. Using this metafunction is compliante with the standard and
optimal for each compiler.

See also mutant_relation, standard_relation, member_at, get(), value_type_of,
pair_by(), pair_type_by.

\ingroup relation_group
                                                           **/

template< class TA, class TB, bool force_mutable = false >
struct select_relation
{
    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::bimaps::relation::detail::is_mutant_idiom_supported_for<TA,TB> ,
        // {
                mutant_relation<TA,TB,force_mutable>,
        // }
        // else
        // {
                standard_relation<TA,TB,force_mutable>
        // }

    >::type type;
};


/// \brief Functions, Metafunctions and Utilies to work with the relation class.
/**

All the entities defined in this namespace use the member_at idiom and user tags
to work with the relation class. It is a good pratice to use this utilities instead
of the direct access to members of the class. For example:

\code

typedef relation<int,std::string> rel;
rel r;
...

// This way of access to the value of a member
int number = get<member_at::left>(r);

// Is prefered over the more direct approach
int number = r.left;

\endcode

There is no runtime penalty in using the get() function and what is more
important have an easier migration path if the user decides to use tags and
want to autodocument the code using them. Remember that this is no necessary
since the member_at idiom is supported even when there are user defined tags
specified. The following is the same example using user tags.

\code

struct id {};
struct name {};

typedef relation< tagged<int,id>, tagged<std::string,name> > rel;
rel r;
...

// This is still valid...
int number = get<member_at::left>(r);

// But now we can use a better way to access the relation information
int worker_id = get<id>(r);

get<name>(r) = "John Smith";

\endcode

\ingroup relation_group

                                                                               **/
namespace support {}

} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_RELATION_HPP

