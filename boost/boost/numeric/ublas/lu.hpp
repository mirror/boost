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

#ifndef BOOST_UBLAS_LU_H
#define BOOST_UBLAS_LU_H

namespace boost { namespace numeric { namespace ublas {

    template<class T, class A = unbounded_array<T> >
    class permutation_matrix:
        public vector<T, A> {
    public:
        typedef vector<T, A> vector_type;
        typedef typename vector_type::size_type size_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        permutation_matrix (size_type size):
            vector<T, A> (size) {
            for (size_type i = 0; i < size; ++ i)
                (*this) (i) = i;
        }
        BOOST_UBLAS_INLINE
        ~permutation_matrix () {}

        // Assignment
        BOOST_UBLAS_INLINE
        permutation_matrix &operator = (const permutation_matrix &m) {
            vector_type::operator = (m);
            return *this;
        }
    };

    template<class PM, class MV>
    BOOST_UBLAS_INLINE
    void swap_rows (const PM &pm, MV &mv, vector_tag) {
        typedef typename PM::size_type size_type;
        typedef typename MV::value_type value_type;

        size_type size = pm.size ();
        for (size_type i = 0; i < size; ++ i) {
            if (i != pm (i))
                std::swap (mv (i), mv (pm (i)));
        }
    }
    template<class PM, class MV>
    BOOST_UBLAS_INLINE
    void swap_rows (const PM &pm, MV &mv, matrix_tag) {
        typedef typename PM::size_type size_type;
        typedef typename MV::value_type value_type;

        size_type size = pm.size ();
        for (size_type i = 0; i < size; ++ i) {
            if (i != pm (i))
                row (mv, i).swap (row (mv, pm (i)));
        }
    }
    // Dispatcher
    template<class PM, class MV>
    BOOST_UBLAS_INLINE
    void swap_rows (const PM &pm, MV &mv) {
        swap_rows (pm, mv, BOOST_UBLAS_TYPENAME MV::type_category ());
    }

    template<class M, class PM>
    typename M::size_type lu_factorize (M &m, PM &pm) {
        typedef M matrix_type;
        typedef BOOST_UBLAS_TYPENAME M::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME M::value_type value_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix_type cm (m);
#endif
        int singular = 0;
        size_type size1 = m.size1 ();
        size_type size2 = m.size2 ();
        size_type size = std::min (size1, size2);
        for (size_type i = 0; i < size; ++ i) {
            matrix_column<M> mci (column (m, i));
            matrix_row<M> mri (row (m, i));
            size_type i_norm_inf = i + index_norm_inf (project (mci, range (i, size1)));
            BOOST_UBLAS_CHECK (i_norm_inf < size1, external_logic ());
            if (m (i_norm_inf, i) != value_type ()) {
                if (i_norm_inf != i) {
                    pm (i) = i_norm_inf;
                    row (m, i_norm_inf).swap (mri);
                } else {
                    BOOST_UBLAS_CHECK (pm (i) == i_norm_inf, external_logic ());
                }
                project (mci, range (i + 1, size1)) *= value_type (1) / m (i, i);
            } else if (singular == 0) {
                singular = i + 1;
            }
            project (m, range (i + 1, size1), range (i + 1, size2)).minus_assign (
                outer_prod (project (mci, range (i + 1, size1)),
                            project (mri, range (i + 1, size2))));
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        swap_rows (pm, cm);
        BOOST_UBLAS_CHECK (singular != 0 ||
                           equals (prod (triangular_adaptor<matrix_type, unit_lower> (m),
                                         triangular_adaptor<matrix_type, upper> (m)), cm), internal_logic ());
#endif
        return singular;
    }

    template<class M, class PM>
    typename M::size_type axpy_lu_factorize (M &m, PM &pm) {
        typedef M matrix_type;
        typedef BOOST_UBLAS_TYPENAME M::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME M::value_type value_type;
        typedef vector<value_type> vector_type;

#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix_type cm (m);
#endif
        int singular = 0;
        size_type size1 = m.size1 ();
        size_type size2 = m.size2 ();
        size_type size = std::min (size1, size2);
#ifndef BOOST_UBLAS_LU_WITH_INPLACE_SOLVE
        matrix_type mr (m);
        mr.assign (zero_matrix<value_type> (size1, size2));
        vector_type v (size1);
        for (size_type i = 0; i < size; ++ i) {
            matrix_range<matrix_type> lrr (project (mr, range (0, i), range (0, i)));
            vector_range<matrix_column<matrix_type> > urr (project (column (mr, i), range (0, i)));
            urr.assign (solve (lrr, project (column (m, i), range (0, i)), unit_lower_tag ()));
            project (v, range (i, size1)).assign (
                project (column (m, i), range (i, size1)) -
                axpy_prod<vector_type> (project (mr, range (i, size1), range (0, i)), urr));
            size_type i_norm_inf = i + index_norm_inf (project (v, range (i, size1)));
            BOOST_UBLAS_CHECK (i_norm_inf < size1, external_logic ());
            if (v (i_norm_inf) != value_type ()) {
                if (i_norm_inf != i) {
                    pm (i) = i_norm_inf;
                    std::swap (v (i_norm_inf), v (i));
                    project (row (m, i_norm_inf), range (i + 1, size2)).swap (project (row (m, i), range (i + 1, size2)));
                } else {
                    BOOST_UBLAS_CHECK (pm (i) == i_norm_inf, external_logic ());
                }
                project (column (mr, i), range (i + 1, size1)).assign (
                    project (v, range (i + 1, size1)) / v (i));
                if (i_norm_inf != i) {
                    project (row (mr, i_norm_inf), range (0, i)).swap (project (row (mr, i), range (0, i)));
                }
            } else if (singular == 0) {
                singular = i + 1;
            }
            mr (i, i) = v (i);
        }
        m.assign (mr);
#else
        matrix_type lr (m);
        matrix_type ur (m);
        lr.assign (identity_matrix<value_type> (size1, size2));
        ur.assign (zero_matrix<value_type> (size1, size2));
        vector_type v (size1);
        for (size_type i = 0; i < size; ++ i) {
            matrix_range<matrix_type> lrr (project (lr, range (0, i), range (0, i)));
            vector_range<matrix_column<matrix_type> > urr (project (column (ur, i), range (0, i)));
            urr.assign (project (column (m, i), range (0, i)));
            inplace_solve (lrr, urr, unit_lower_tag ());
            project (v, range (i, size1)).assign (
                project (column (m, i), range (i, size1)) -
                axpy_prod<vector_type> (project (lr, range (i, size1), range (0, i)), urr));
            size_type i_norm_inf = i + index_norm_inf (project (v, range (i, size1)));
            BOOST_UBLAS_CHECK (i_norm_inf < size1, external_logic ());
            if (v (i_norm_inf) != value_type ()) {
                if (i_norm_inf != i) {
                    pm (i) = i_norm_inf;
                    std::swap (v (i_norm_inf), v (i));
                    project (row (m, i_norm_inf), range (i + 1, size2)).swap (project (row (m, i), range (i + 1, size2)));
                } else {
                    BOOST_UBLAS_CHECK (pm (i) == i_norm_inf, external_logic ());
                }
                project (column (lr, i), range (i + 1, size1)).assign (
                    project (v, range (i + 1, size1)) / v (i));
                if (i_norm_inf != i) {
                    project (row (lr, i_norm_inf), range (0, i)).swap (project (row (lr, i), range (0, i)));
                }
            } else if (singular == 0) {
                singular = i + 1;
            }
            ur (i, i) = v (i);
        }
        m.assign (triangular_adaptor<matrix_type, strict_lower> (lr) +
                  triangular_adaptor<matrix_type, upper> (ur));
#endif
#ifdef BOOST_UBLAS_TYPE_CHECK
        swap_rows (pm, cm);
        BOOST_UBLAS_CHECK (singular != 0 ||
                           equals (prod (triangular_adaptor<matrix_type, unit_lower> (m),
                                         triangular_adaptor<matrix_type, upper> (m)), cm), internal_logic ());
#endif
        return singular;
    }

    template<class M, class PMT, class PMA, class MV>
    void lu_substitute (const M &m, const permutation_matrix<PMT, PMA> &pm, MV &mv) {
        typedef const M const_matrix_type;
        typedef typename boost::mpl::if_c<boost::is_same<typename MV::type_category, vector_tag>::value,
                                          vector<typename MV::value_type>,
                                          matrix<typename MV::value_type> >::type matrix_vector_type;

        swap_rows (pm, mv);
#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix_vector_type cmv1 (mv);
#endif
        inplace_solve (m, mv, unit_lower_tag ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (prod (triangular_adaptor<const_matrix_type, unit_lower> (m), mv), cmv1), internal_logic ());
        matrix_vector_type cmv2 (mv);
#endif
        inplace_solve (m, mv, upper_tag ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (prod (triangular_adaptor<const_matrix_type, upper> (m), mv), cmv2), internal_logic ());
#endif
    }
    template<class MV, class M, class PMT, class PMA>
    void lu_substitute (MV &mv, const M &m, const permutation_matrix<PMT, PMA> &pm) {
        typedef const M const_matrix_type;
        typedef typename boost::mpl::if_c<boost::is_same<typename MV::type_category, vector_tag>::value,
                                          vector<typename MV::value_type>,
                                          matrix<typename MV::value_type> >::type matrix_vector_type;

        swap_rows (pm, mv);
#ifdef BOOST_UBLAS_TYPE_CHECK
        matrix_vector_type cmv1 (mv);
#endif
        inplace_solve (mv, m, upper_tag ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (prod (mv, triangular_adaptor<const_matrix_type, upper> (m)), cmv1), internal_logic ());
        matrix_vector_type cmv2 (mv);
#endif
        inplace_solve (mv, m, unit_lower_tag ());
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (prod (mv, triangular_adaptor<const_matrix_type, unit_lower> (m)), cmv2), internal_logic ());
#endif
    }

}}}

#endif


