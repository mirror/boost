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

#ifndef BOOST_UBLAS_OPERATION_H
#define BOOST_UBLAS_OPERATION_H

// axpy-based products
// Alexei Novakov had a lot of ideas to improve these. Thanks.

namespace boost { namespace numeric { namespace ublas {

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, row_major_tag) {
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;

        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            size_type index1 (it1.index1 ());
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                v (index1) += *it2 * e2 () (it2.index2 ());
                ++ it2;
            }
            ++ it1;
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, column_major_tag) {
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;

        typename expression1_type::const_iterator2 it2 (e1 ().begin2 ());
        typename expression1_type::const_iterator2 it2_end (e1 ().end2 ());
        while (it2 != it2_end) {
            size_type index2 (it2.index2 ());
            typename expression1_type::const_iterator1 it1 (it2.begin ());
            typename expression1_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                v (it1.index1 ()) += *it1 * e2 () (index2);
                ++ it1;
            }
            ++ it2;
        }
        return v;
    }

    // Dispatcher
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, bool init = true) {
        typedef typename V::value_type value_type;
        typedef typename E1::orientation_category orientation_category;

        if (init)
            v.assign (zero_vector<value_type> (e1 ().size1 ()));
#ifdef BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign (scalar_assign<value_type, value_type> (), cv, prod (e1, e2));
#endif
        axpy_prod (e1, e2, v, orientation_category ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (v, cv), internal_logic ());
#endif
        return v;
    }
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2) {
        typedef V vector_type;

        vector_type v (e1 ().size1 ());
        // FIXME: needed for c_matrix?!
        // return axpy_prod (e1, e2, v, false);
        return axpy_prod (e1, e2, v, true);
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, column_major_tag) {
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;

        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            size_type index2 (it2.index2 ());
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                v (index2) += *it1 * e1 () (it1.index1 ());
                ++ it1;
            }
            ++ it2;
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, row_major_tag) {
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;

        typename expression2_type::const_iterator1 it1 (e2 ().begin1 ());
        typename expression2_type::const_iterator1 it1_end (e2 ().end1 ());
        while (it1 != it1_end) {
            size_type index1 (it1.index1 ());
            typename expression2_type::const_iterator2 it2 (it1.begin ());
            typename expression2_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                v (it2.index2 ()) += *it2 * e1 () (index1);
                ++ it2;
            }
            ++ it1;
        }
        return v;
    }

    // Dispatcher
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, bool init = true) {
        typedef typename V::value_type value_type;
        typedef typename E2::orientation_category orientation_category;

        if (init)
            v.assign (zero_vector<value_type> (e2 ().size2 ()));
#ifdef BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign (scalar_assign<value_type, value_type> (), cv, prod (e1, e2));
#endif
        axpy_prod (e1, e2, v, orientation_category ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (v, cv), internal_logic ());
#endif
        return v;
    }
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2) {
        typedef V vector_type;

        vector_type v (e2 ().size2 ());
        // FIXME: needed for c_matrix?!
        // return axpy_prod (e1, e2, v, false);
        return axpy_prod (e1, e2, v, true);
    }

    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, row_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), row_major_tag ());
#endif
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                // row (m, it1.index1 ()).plus_assign (*it2 * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                while (itr != itr_end) {
                    m (it1.index1 (), itr.index ()) += *it2 * *itr;
                    ++ itr;
                }
                ++ it2;
            }
            ++ it1;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return m;
    }

    template<class M, class F, class E1, class E2>
    BOOST_UBLAS_INLINE
// GCC 2.95 diagnoses ambiguities.
#if !defined (__GNUC__) || !(__GNUC__ <= 2 && __GNUC_MINOR__ <= 95)
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, const F &f, row_major_tag) {
#else
    M &
    axpy_prod_functor (const matrix_expression<E1> &e1,
                       const matrix_expression<E2> &e2,
                       M &m, const F &f, row_major_tag) {
#endif
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), row_major_tag ());
#endif
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                // row (m, it1.index1 ()).plus_assign (*it2 * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                while (itr != itr_end) {
                    if (f.other (it1.index1 (), itr.index ()))
                        m (it1.index1 (), itr.index ()) += *it2 * *itr;
                    ++ itr;
                }
                ++ it2;
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
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, column_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), column_major_tag ());
#endif
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                // column (m, it2.index2 ()).plus_assign (*it1 * column (e1 (), it1.index1 ()));
                matrix_column<expression1_type> mc (e1 (), it1.index1 ());
                typename matrix_column<expression1_type>::const_iterator itc (mc.begin ());
                typename matrix_column<expression1_type>::const_iterator itc_end (mc.end ());
                while (itc != itc_end) {
                    m (itc.index (), it2.index2 ()) += *it1 * *itc;
                    ++ itc;
                }
                ++ it1;
            }
            ++ it2;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (m, cm), internal_logic ());
#endif
        return m;
    }

    template<class M, class F, class E1, class E2>
    BOOST_UBLAS_INLINE
// GCC 2.95 diagnoses ambiguities.
#if !defined (__GNUC__) || !(__GNUC__ <= 2 && __GNUC_MINOR__ <= 95)
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, const F &f, column_major_tag) {
#else
    M &
    axpy_prod_functor (const matrix_expression<E1> &e1,
                       const matrix_expression<E2> &e2,
                       M &m, const F &f, column_major_tag) {
#endif
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign (scalar_assign<value_type, value_type> (), cm, prod (e1, e2), column_major_tag ());
#endif
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                // column (m, it2.index2 ()).plus_assign (*it1 * column (e1 (), it1.index1 ()));
                matrix_column<expression1_type> mc (e1 (), it1.index1 ());
                typename matrix_column<expression1_type>::const_iterator itc (mc.begin ());
                typename matrix_column<expression1_type>::const_iterator itc_end (mc.end ());
                while (itc != itc_end) {
                    if (f.other (itc.index (), it2.index2 ()))
                        m (itc.index (), it2.index2 ()) += *it1 * *itc;
                    ++ itc;
                }
                ++ it1;
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
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return axpy_prod (e1, e2, m, orientation_category ());
    }
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        // FIXME: needed for c_matrix?!
        // return axpy_prod (e1, e2, m, false);
        return axpy_prod (e1, e2, m, true);
    }

    template<class M, class F, class E1, class E2>
    BOOST_UBLAS_INLINE
// GCC 2.95 diagnoses ambiguities.
#if !defined (__GNUC__) || !(__GNUC__ <= 2 && __GNUC_MINOR__ <= 95)
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, const F &f, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return axpy_prod (e1, e2, m, f, orientation_category ());
    }
#else
    M &
    axpy_prod_functor (const matrix_expression<E1> &e1,
                       const matrix_expression<E2> &e2,
                       M &m, const F &f, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return axpy_prod_functor (e1, e2, m, f, orientation_category ());
    }
#endif
    template<class M, class F, class E1, class E2>
    BOOST_UBLAS_INLINE
// GCC 2.95 diagnoses ambiguities.
#if !defined (__GNUC__) || !(__GNUC__ <= 2 && __GNUC_MINOR__ <= 95)
    M
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               const F &f) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        // FIXME: needed for c_matrix?!
        // return axpy_prod (e1, e2, m, f, false);
        return axpy_prod (e1, e2, m, f, true);
    }
#else
    M
    axpy_prod_functor (const matrix_expression<E1> &e1,
                       const matrix_expression<E2> &e2,
                       const F &f) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        // FIXME: needed for c_matrix?!
        // return axpy_prod_functor (e1, e2, m, f, false);
        return axpy_prod_functor (e1, e2, m, f, true);
    }
#endif

    template<class T1, class E1, class E2, class T2, class V>
    BOOST_UBLAS_INLINE
    V &
    axpy_mult_vec (const T1 &t1,
                   const matrix_expression<E1> &e1,
                   const vector_expression<E2> &e2,
                   const T2 &t2,
                   V &v) {
        typedef V vector_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (t2 * v);
        indexing_vector_assign (scalar_plus_assign<value_type, value_type> (), cv, t1 * prod (e1, e2));
#endif
        v *= t2;
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                v (it1.index1 ()) += (t1 * *it2) * e2 () (it2.index2 ());
                ++ it2;
            }
            ++ it1;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (v, cv), internal_logic ());
#endif
        return v;
    }

    template<class T1, class E1, class E2, class T2, class V>
    BOOST_UBLAS_INLINE
    V &
    axpy_mult_vec (const T1 &t1,
                   const vector_expression<E1> &e1,
                   const matrix_expression<E2> &e2,
                   const T2 &t2,
                   V &v) {
        typedef V vector_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (t2 * v);
        indexing_vector_assign (scalar_plus_assign<value_type, value_type> (), cv, t1 * prod (e1, e2));
#endif
        v *= t2;
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                v (it2.index2 ()) += (t1 * *it1) * e1 () (it1.index1 ());
                ++ it1;
            }
            ++ it2;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (v, cv), internal_logic ());
#endif
        return v;
    }

    template<class T1, class E1, class E2, class T2, class M>
    BOOST_UBLAS_INLINE
    M &
    axpy_mult_mat (const T1 &t1,
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
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            // matrix_row<matrix_type> mr (m, it1.index1 ());
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
            while (it2 != it2_end) {
                // mr.plus_assign ((t1 * *it2) * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                value_type t (t1 * *it2);
                while (itr != itr_end) {
                    m (it1.index1 (), itr.index ()) += t * *itr;
                    ++ itr;
                }
                ++ it2;
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
    axpy_mult_mat (const T1 &t1,
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
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            // matrix_column<matrix_type> mc (m, it2.index2 ());
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
            while (it1 != it1_end) {
                // mc.plus_assign ((t1 * *it1) * column (e1 (), it1.index1 ()));
                matrix_column<expression1_type> mc (e1 (), it1.index1 ());
                typename matrix_column<expression1_type>::const_iterator itc (mc.begin ());
                typename matrix_column<expression1_type>::const_iterator itc_end (mc.end ());
                value_type t (t1 * *it1);
                while (itc != itc_end) {
                    m (itc.index (), it2.index2 ()) += t * *itc;
                    ++ itc;
                }
                ++ it1;
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
    axpy_mult_mat (const T1 &t1,
                   const matrix_expression<E1> &e1,
                   const matrix_expression<E2> &e2,
                   const T2 &t2,
                   M &m) {
        typedef typename M::orientation_category orientation_category;
        return axpy_mult_mat (t1, e1, e2, t2, m, orientation_category ());
    }

}}}

#endif


