//  Boost string_algo library find_iterator.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_ITERATOR_DETAIL_HPP
#define BOOST_STRING_FIND_ITERATOR_DETAIL_HPP


#include <boost/algorithm/string/config.hpp>
#include <boost/algorithm/string/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace boost {
    namespace algorithm { 
        namespace detail {

//  finder virtualizer -----------------------------------------------//

            template<typename IteratorT>
            struct virtual_finder
            {
                // typedefs
                typedef IteratorT input_iterator_type;
                typedef iterator_range<IteratorT> match_type;

                // virtual destructor
                virtual ~virtual_finder() {}

                // clone
                virtual virtual_finder* clone() const=0;

                // operation
                virtual match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const=0;
            };

            template<typename IteratorT, typename FinderT>
            struct virtual_finder_typed : public virtual_finder<IteratorT>
            {
                // typedefs
                typedef virtual_finder<IteratorT> base_type;
                typedef BOOST_STRING_TYPENAME 
                    base_type::input_iterator_type input_iterator_type;
                typedef BOOST_STRING_TYPENAME 
                    base_type::match_type match_type;

                // constuction
                virtual_finder_typed( FinderT Finder ) : m_Finder(Finder) {}

                // clone
                virtual_finder_typed* clone() const
                {
                    return new virtual_finder_typed(m_Finder);
                }

                // operation
                virtual match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    return m_Finder(Begin,End);
                }

            private:
                // Finder
                FinderT m_Finder;
            };


//  find_iterator base -----------------------------------------------//

            // Find iterator base
            template<typename IteratorT>
            class find_iterator_base
            {
            protected:
                // typedefs
                typedef IteratorT input_iterator_type;
                typedef iterator_range<IteratorT> match_type;

            protected:
            // Protected construction/destruction

                // Default constructor
                find_iterator_base() : m_pFinder(0) {};
                // Copy construction
                find_iterator_base( const find_iterator_base& Other ) :
                    m_pFinder(0)
                {
                    if ( Other.m_pFinder )
                    {
                        m_pFinder=Other.m_pFinder->clone();
                    }
                }
                // Constructor
                template<typename FinderT>
                find_iterator_base( FinderT Finder, int ) :
                    m_pFinder( new virtual_finder_typed<IteratorT,FinderT>(Finder) ) {}

                // Destructor
                ~find_iterator_base()
                {
                    if (m_pFinder) delete m_pFinder;
                }

                // Find operation
                match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    if (m_pFinder)
                    {
                        return m_pFinder->do_find(Begin,End);
                    }
                    else
                    {
                        return match_type(End,End);
                    }
                }

                // Check
                bool is_null() const
                {
                    return !m_pFinder;
                }

            private:
                // Finder
                virtual_finder<IteratorT>* m_pFinder;
            };

       } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_FIND_ITERATOR_DETAIL_HPP
