// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/manage_additional_parameters.hpp
/// \brief Utility class to extract the additional parameters from the template parameters.

#ifndef BOOST_BIMAP_DETAIL_MANAGE_ADDITIONAL_PARAMETERS_HPP
#define BOOST_BIMAP_DETAIL_MANAGE_ADDITIONAL_PARAMETERS_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <memory>

// Boost.MPL
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/bimap/detail/is_set_type_of.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/// \brief Metafunction to check if a given type is a data_hook specification.

template< class Type >
struct is_data_hook : ::boost::mpl::false_ {};

/** \struct boost::bimaps::detail::manage_additional_parameters
\brief Utility class to extract the additional parameters from the template parameters.

\code
template< class AP1, class AP2, class AP3 >
struct manage_additional_parameters
{
    struct parameters
    {
        typedef -unspecified- set_type_of_relation;
        typedef -unspecified- data_hook;
        typedef -unspecified- allocator;
    };

    typedef parameters type;
};
\endcode

See also bimap, bimap_core.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class AP1, class AP2, class AP3 >
struct manage_additional_parameters
{
    // (1) manage_additional_parameters<
    //         not_specified,not_specified,not_specified>
    //
    //     set_type_of_relation: based on the left key type
    //     hook_data:            no additional data
    //     allocator:            default allocator

    struct case_NNN
    {
        typedef left_based set_type_of_relation;
        typedef std::allocator<void> allocator;
    };

    // (2) manage_additional_parameters<Allocator,not_specified,not_specified>
    //
    //     set_type_of_relation: based on the left key type
    //     hook_data:            no additional data
    //     allocator:            Allocator

    struct case_ANN
    {
        typedef left_based set_type_of_relation;
        typedef AP1 allocator;
    };

    // (3) manage_additional_parameters<
    //         SetOfRelationType,not_specified,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     hook_data:            no additional data
    //     allocator:            default allocator

    struct case_SNN
    {
        typedef AP1 set_type_of_relation;
        typedef std::allocator<void> allocator;
    };

    // (4) manage_additional_parameters<
    //          SetTypeOfRelation,Allocator,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     hook_data:            no additional data
    //     allocator:            Allocator

    struct case_SAN
    {
        typedef AP1 set_type_of_relation;
        typedef AP2 allocator;
    };

    // (5) manage_additional_parameters<DataToHook,not_specified,not_specified>
    //
    //     set_type_of_relation: based on the left key type
    //     hook_data:            DataToHook
    //     allocator:            default allocator

    struct case_HNN
    {
        typedef left_based set_type_of_relation;
        typedef std::allocator<void> allocator;
    };

    // (6) manage_additional_parameters<
    //         SetTypeOfRelation,DataToHook,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     hook_data:            DataToHook
    //     allocator:            default allocator

    struct case_SHN
    {
        typedef AP1 set_type_of_relation;
        typedef std::allocator<void> allocator;
    };

    // (7) manage_additional_parameters<
    //         DataToHook,Allocator,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     hook_data:            DataToHook
    //     allocator:            default allocator

    struct case_HAN
    {
        typedef left_based set_type_of_relation;
        typedef AP2 allocator;
    };

    // (8) manage_additional_parameters<
    //         SetTypeOfRelation,DataToHook,Allocator>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     hook_data:            DataToHook
    //     allocator:            Allocator

    struct case_SHA
    {
        typedef AP1 set_type_of_relation;
        typedef AP2 allocator;
    };

    // Some annidated mpl::if_ and we are done!

    typedef BOOST_DEDUCED_TYPENAME mpl::if_
    <
        ::boost::mpl::is_na<AP1>,
        case_NNN, // (1)
        BOOST_DEDUCED_TYPENAME mpl::if_
        <
            ::boost::mpl::is_na<AP2>,
            BOOST_DEDUCED_TYPENAME mpl::if_
            <
                is_set_type_of_relation<AP1>,
                case_SNN, // (3)
                BOOST_DEDUCED_TYPENAME mpl::if_
                <
                    is_data_hook<AP1>,
                    case_HNN, // (5)
                    case_ANN  // (2)

                >::type

            >::type,
            BOOST_DEDUCED_TYPENAME mpl::if_
            <
                ::boost::mpl::is_na<AP3>,
                BOOST_DEDUCED_TYPENAME mpl::if_
                <
                    is_data_hook<AP1>,
                    case_HAN, // (7)
                    BOOST_DEDUCED_TYPENAME mpl::if_
                    <
                        is_data_hook<AP2>,
                        case_SHN, // (6)
                        case_SAN  // (4)

                    >::type

                >::type,

                case_SHA // (8)

            >::type

        >::type

    >::type type;

};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MANAGE_ADDITIONAL_PARAMETERS_HPP

