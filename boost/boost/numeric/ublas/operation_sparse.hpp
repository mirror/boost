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

// These scaled additions were borrowed from MTL unashamedly.
// But Alexei Novakov had a lot of ideas to improve these. Thanks.

namespace boost { namespace numeric { namespace ublas {

    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, bool init,
                 row_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        vector<value_type> temporary (e2 ().size2 ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), row_major_tag ());
#endif
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            size_type jb (temporary.size ());
            size_type je (0);
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                // temporary.plus_assign (*it2 * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                while (itr != itr_end) {
                    size_type j (itr.index ());
                    temporary (j) += *it2 * *itr;
                    jb = std::min (jb, j);
                    je = std::max (je, j);
                    ++ itr;
                }
                ++ it2;
            }
            for (size_type j = jb; j < je + 1; ++ j) {
                if (temporary (j) != value_type ()) {
                    // FIXME: we'll need to extend the container interface!
                    // m.push_back (it1.index1 (), j, temporary (j));
                    // FIXME: What to do with adaptors?
                    // m.insert (it1.index1 (), j, temporary (j));
                    m (it1.index1 (), j) = temporary (j);
                    temporary (j) = value_type ();
                }
            }
            ++ it1;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return m;
    }

    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, bool init,
                 column_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        vector<value_type> temporary (e1 ().size1 ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), column_major_tag ());
#endif
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            size_type ib (temporary.size ());
            size_type ie (0);
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                // column (m, it2.index2 ()).plus_assign (*it1 * column (e1 (), it1.index1 ()));
                matrix_column<expression1_type> mc (e1 (), it1.index1 ());
                typename matrix_column<expression1_type>::const_iterator itc (mc.begin ());
                typename matrix_column<expression1_type>::const_iterator itc_end (mc.end ());
                while (itc != itc_end) {
                    size_type i (itc.index ());
                    temporary (i) += *it1 * *itc;
                    ib = std::min (ib, i);
                    ie = std::max (ie, i);
                    ++ itc;
                }
                ++ it1;
            }
            for (size_type i = ib; i < ie + 1; ++ i) {
                if (temporary (i) != value_type ()) {
                    // FIXME: we'll need to extend the container interface!
                    // m.push_back (i, it2.index2 (), temporary (i));
                    // FIXME: What to do with adaptors?
                    // m.insert (i, it2.index2 (), temporary (i));
                    m (i, it2.index2 ()) = temporary (i);
                    temporary (i) = value_type ();
                }
            }
            ++ it2;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return m;
    }

    // Dispatcher
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, bool init = true) {
        typedef typename M::orientation_category orientation_category;
        return sparse_prod (e1, e2, m, init, orientation_category ());
    }
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        return sparse_prod (e1, e2, m, false);
    }

    template<class T1, class E1, class E2, class T2, class M>
    BOOST_UBLAS_INLINE
    M &
    sparse_mult_mat (const T1 &t1,
                     const matrix_expression<E1> &e1,
                     const matrix_expression<E2> &e2,
                     const T2 &t2,
                     M &m,
                     row_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (t2 * m);
        indexing_matrix_assign (scalar_plus_assign<value_type, value_type> (), cm, t1 * prod (e1, e2), row_major_tag ());
#endif
        m *= t2;
        vector<value_type> temporary (e2 ().size2 ());
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            size_type jb (temporary.size ());
            size_type je (0);
            // temporary.assign (column (m, it1.index1 ()));
            matrix_row<matrix_type> mr (m, it1.index1 ());
            typename matrix_row<matrix_type>::const_iterator itr (mr.begin ());
            typename matrix_row<matrix_type>::const_iterator itr_end (mr.end ());
            while (itr != itr_end) {
                size_type j (itr.index ());
                temporary (j) = *itr;
                jb = std::min (jb, j);
                je = std::max (je, j);
                ++ itr;
            }
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                // temporary.plus_assign ((t1 * *it2) * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                value_type t (t1 * *it2);
                while (itr != itr_end) {
                    size_type j (itr.index ());
                    temporary (j) += t * *itr;
                    jb = std::min (jb, j);
                    je = std::max (je, j);
                    ++ itr;
                }
                ++ it2;
            }
            if (jb <= je) {
                typename vector<value_type>::iterator it (temporary.begin () + jb);
                typename vector<value_type>::iterator it_end (temporary.begin () + je + 1);
                while (it != it_end) {
                    if (*it != value_type ()) {
                        m (it1.index1 (), it.index ()) = *it;
                        *it = value_type ();
                    }
                    ++ it;
                }
            }
            ++ it1;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return m;
    }

    template<class T1, class E1, class E2, class T2, class M>
    BOOST_UBLAS_INLINE
    M &
    sparse_mult_mat (const T1 &t1,
                     const matrix_expression<E1> &e1,
                     const matrix_expression<E2> &e2,
                     const T2 &t2,
                     M &m,
                     column_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (t2 * m);
        indexing_matrix_assign (scalar_plus_assign<value_type, value_type> (), cm, t1 * prod (e1, e2), column_major_tag ());
#endif
        m *= t2;
        vector<value_type> temporary (e1 ().size1 ());
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            size_type ib (temporary.size ());
            size_type ie (0);
            // temporary.assign (column (m, it2.index2 ()));
            matrix_column<matrix_type> mc (m, it2.index2 ());
            typename matrix_column<matrix_type>::const_iterator itc (mc.begin ());
            typename matrix_column<matrix_type>::const_iterator itc_end (mc.end ());
            while (itc != itc_end) {
                size_type i (itc.index ());
                temporary (i) = *itc;
                ib = std::min (ib, i);
                ie = std::max (ie, i);
                ++ itc;
            }
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                // temporary.plus_assign ((t1 * *it1) * column (e1 (), it1.index1 ()));
                matrix_column<expression1_type> mc (e1 (), it1.index1 ());
                typename matrix_column<expression1_type>::const_iterator itc (mc.begin ());
                typename matrix_column<expression1_type>::const_iterator itc_end (mc.end ());
                value_type t (t1 * *it1);
                while (itc != itc_end) {
                    size_type i (itc.index ());
                    temporary (i) += t * *itc;
                    ib = std::min (ib, i);
                    ie = std::max (ie, i);
                    ++ itc;
                }
                ++ it1;
            }
            if (ib <= ie) {
                for (size_type i = ib; i < ie + 1; ++ i) {
                    if (temporary (i) != value_type ()) {
                        m (i, it2.index2 ()) = temporary (i);
                        temporary (i) = value_type ();
                    }
                }
            }
            ++ it2;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return m;
    }

    // Dispatcher
    template<class T1, class E1, class E2, class T2, class M>
    BOOST_UBLAS_INLINE
    M &
    sparse_mult_mat (const T1 &t1,
                     const matrix_expression<E1> &e1,
                     const matrix_expression<E2> &e2,
                     const T2 &t2,
                     M &m) {
        typedef typename M::orientation_category orientation_category;
        return sparse_mult_mat (t1, e1, e2, t2, m, orientation_category ());
    }

}}}

#endif


