//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Permission to use, copy, modify, distribute and sell this software
//  and its documentation for any purpose is hereby granted without fee,
//  provided that the above copyright notice appear in all copies and
//  that both that copyright notice and this permission notice appear
//  in supporting documentation.  The authors make no representations
//  about the suitability of this software for any purpose.
//  It is provided "as is" without express or implied warranty.
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef BOOST_UBLAS_OPERATION_SPARSE_H
#define BOOST_UBLAS_OPERATION_SPARSE_H

// These scaled additions are borrowed from MTL unashamedly.

namespace boost { namespace numeric { namespace ublas {

    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 row_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        ublas::compressed_matrix<value_type, row_major> m (e1 ().size1 (), e2 ().size2 ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), row_major_tag ());
#endif
        ublas::compressed_vector<value_type> temporary (BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ()));
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            temporary.clear ();
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                temporary.plus_assign (*it2 * row (e2 (), it2.index2 ()));
                ++ it2;
            }
            typename compressed_vector<value_type>::const_iterator it (temporary.begin ());
            typename compressed_vector<value_type>::const_iterator it_end (temporary.end ());
            while (it != it_end) {
                m.push_back (it1.index1 (), it.index (), *it);
                ++ it;
            }
            ++ it1;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return matrix_type (m);
    }

    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 column_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        ublas::compressed_matrix<value_type, column_major> m (e1 ().size1 (), e2 ().size2 ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), column_major_tag ());
#endif
        ublas::compressed_vector<value_type> temporary (BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ()));
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            temporary.clear ();
            typename expression1_type::const_iterator1 it1 (it2.begin ());
            typename expression1_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                temporary.plus_assign (*it1 * column (e1 (), it1.index1 ()));
                ++ it1;
            }
            typename compressed_vector<value_type>::const_iterator it (temporary.begin ());
            typename compressed_vector<value_type>::const_iterator it_end (temporary.end ());
            while (it != it_end) {
                m.push_back (it.index (), it2.index2 (), *it);
                ++ it;
            }
            ++ it2;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return matrix_type (m);
    }

}}}

#endif


