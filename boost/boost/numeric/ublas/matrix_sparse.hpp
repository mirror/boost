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

#ifndef BOOST_UBLAS_MATRIX_SPARSE_H
#define BOOST_UBLAS_MATRIX_SPARSE_H

#include <boost/numeric/ublas/config.hpp>
#include <boost/numeric/ublas/storage_sparse.hpp>
#include <boost/numeric/ublas/matrix.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    // Array based sparse matrix class
    template<class T, class F, class A>
    class sparse_matrix:
        public matrix_expression<sparse_matrix<T, F, A> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING matrix_expression<sparse_matrix<T, F, A> >::operator ();
#endif
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        // typedef const T &const_reference;
        typedef typename type_traits<T>::const_reference const_reference;
#ifndef BOOST_UBLAS_STRICT_SPARSE_ELEMENT_ASSIGN
        typedef T &reference;
#else
        typedef typename map_traits<A>::reference reference;
#endif
        typedef const T *const_pointer;
        typedef T *pointer;
        typedef F functor_type;
        typedef A array_type;
        typedef const A const_array_type;
        typedef const sparse_matrix<T, F, A> const_self_type;
        typedef sparse_matrix<T, F, A> self_type;
        typedef const matrix_const_reference<const_self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef typename A::const_iterator const_iterator_type;
        typedef typename A::iterator iterator_type;
        typedef sparse_tag storage_category;
        typedef typename F::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        sparse_matrix ():
            size1_ (0), size2_ (0), non_zeros_ (0), data_ () {}
        BOOST_UBLAS_INLINE
        sparse_matrix (size_type size1, size_type size2, size_type non_zeros = 0):
            size1_ (size1), size2_ (size2), non_zeros_ (non_zeros), data_ () {
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            non_zeros_ = std::max (non_zeros_, std::min (size1_, size2_));
            map_traits<array_type>::reserve (data_, non_zeros_);
#endif
        }
        BOOST_UBLAS_INLINE
        sparse_matrix (const sparse_matrix &m):
            size1_ (m.size1_), size2_ (m.size2_), non_zeros_ (m.non_zeros_), data_ (m.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix (const matrix_expression<AE> &ae, size_type non_zeros = 0):
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()), non_zeros_ (non_zeros), data_ () {
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            non_zeros_ = std::max (non_zeros_, std::min (size1_, size2_));
            map_traits<array_type>::reserve (data_, non_zeros_);
#endif
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return size1_;
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return size2_;
        }
        BOOST_UBLAS_INLINE
        size_type non_zeros () const {
            return data_.size ();
        }
        BOOST_UBLAS_INLINE
        const_array_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type &data () {
            return data_;
        }

        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, size_type non_zeros = 0) {
            size1_ = size1;
            size2_ = size2;
            non_zeros_ = non_zeros;
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            non_zeros_ = std::max (non_zeros_, std::min (size1_, size2_));
            map_traits<array_type>::reserve (data (), non_zeros_);
#endif
            data ().clear ();
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            const_iterator_type it (data ().find (functor_type::element (i, size1_, j, size2_)));
            if (it == data ().end () || (*it).first != functor_type::element (i, size1_, j, size2_))
                return zero_;
            return (*it).second;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            return data () [functor_type::element (i, size1_, j, size2_)];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        sparse_matrix &operator = (const sparse_matrix &m) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &m, external_logic ());
            if (this != &m) {
                BOOST_UBLAS_CHECK (size1_ == m.size1_, bad_size ());
                BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                size1_ = m.size1_;
                size2_ = m.size2_;
                non_zeros_ = m.non_zeros_;
                data () = m.data ();
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        sparse_matrix &assign_temporary (sparse_matrix &m) { 
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix &operator = (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (ae, non_zeros_));
#else
            // return assign (self_type (ae, non_zeros_));
            self_type temporary (ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix &reset (const matrix_expression<AE> &ae) {
            self_type temporary (ae, non_zeros_);
            resize (temporary.size1 (), temporary.size2 (), non_zeros_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix &assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix& operator += (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (*this + ae, non_zeros_));
#else
            // return assign (self_type (*this + ae, non_zeros_));
            self_type temporary (*this + ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix& operator -= (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (*this - ae, non_zeros_));
#else
            // return assign (self_type (*this - ae, non_zeros_));
            self_type temporary (*this - ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_matrix &minus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        sparse_matrix& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        sparse_matrix& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (sparse_matrix &m) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &m, external_logic ());
            if (this != &m) {
                // Precondition for container relaxed as requested during review.
                // BOOST_UBLAS_CHECK (size1_ == m.size1_, bad_size ());
                // BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                // BOOST_UBLAS_CHECK (non_zeros_ == m.non_zeros_, bad_size ());
                std::swap (size1_, m.size1_);
                std::swap (size2_, m.size2_);
                std::swap (non_zeros_, m.non_zeros_);
                data ().swap (m.data ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (sparse_matrix &m1, sparse_matrix &m2) {
            m1.swap (m2);
        }
#endif

        // Element insertion and erasure
        BOOST_UBLAS_INLINE
        void insert (size_type i, size_type j, const_reference t) {
#ifdef BOOST_UBLAS_CHECK_FOR_ZERO
            if (t == value_type ())
                return;
#endif
            BOOST_UBLAS_CHECK (data ().find (functor_type::element (i, size1_, j, size2_)) == data ().end (), bad_index ());
            data ().insert (data ().end (), std::pair<size_type, value_type> (functor_type::element (i, size1_, j, size2_), t));
        }
        BOOST_UBLAS_INLINE
        void erase (size_type i, size_type j) {
            // FIXME: shouldn't we use const_iterator_type here?
            iterator_type it = data ().find (functor_type::element (i, size1_, j, size2_));
            if (it == data ().end ())
                return;
            data ().erase (it);
        }
        BOOST_UBLAS_INLINE
        void clear () {
            data ().clear ();
        }

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        typedef matrix_row_iterator<self_type, sparse_bidirectional_iterator_tag> iterator1;
        typedef matrix_column_iterator<self_type, sparse_bidirectional_iterator_tag> iterator2;
        typedef matrix_row_const_iterator<self_type, sparse_bidirectional_iterator_tag> const_iterator1;
        typedef matrix_column_const_iterator<self_type, sparse_bidirectional_iterator_tag> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base1<const_iterator1, value_type, const_reference> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1, value_type, reference> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2, value_type, const_reference> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2, value_type, reference> reverse_iterator2;
#else
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;
#endif

        // Element lookup
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator1 find1 (int rank, size_type i, size_type j) const {
            const_iterator_type it (data ().lower_bound (functor_type::element (i, size1_, j, size2_)));
            const_iterator_type it_end (data ().end ());
            size_type index2 = size_type (-1);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
            size_type index1 = size_type (-1);
#endif
            while (it != it_end) {
                index2 = functor_type::index2 ((*it).first, size1_, size2_);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                index1 = functor_type::index1 ((*it).first, size1_, size2_);
                BOOST_UBLAS_CHECK (index1 >= i || index2 >= j, internal_logic ());
#endif
                if ((rank == 0 && index2 >= j) ||
                    (rank == 1 && index2 == j) ||
                    (i >= size1_))
                    break;
                ++ i;
                it = data ().lower_bound (functor_type::element (i, size1_, j, size2_));
            }
            if (rank == 1 && index2 != j) {
                i = size1_;
                rank = 0;
            }
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, i);
#else
            return const_iterator1 (*this, rank, i, j, it);
#endif
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            iterator_type it (data ().lower_bound (functor_type::element (i, size1_, j, size2_)));
            iterator_type it_end (data ().end ());
            size_type index2 = size_type (-1);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
            size_type index1 = size_type (-1);
#endif
            while (it != it_end) {
                index2 = functor_type::index2 ((*it).first, size1_, size2_);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                index1 = functor_type::index1 ((*it).first, size1_, size2_);
                BOOST_UBLAS_CHECK (index1 >= i || index2 >= j, internal_logic ());
#endif
                if ((rank == 0 && index2 >= j) ||
                    (rank == 1 && index2 == j) ||
                    (i >= size1_))
                    break;
                ++ i;
                it = data ().lower_bound (functor_type::element (i, size1_, j, size2_));
            }
            if (rank == 1 && index2 != j) {
                i = size1_;
                rank = 0;
            }
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, i);
#else
            return iterator1 (*this, rank, i, j, it);
#endif
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            const_iterator_type it (data ().lower_bound (functor_type::element (i, size1_, j, size2_)));
            const_iterator_type it_end (data ().end ());
            size_type index1 = size_type (-1);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
            size_type index2 = size_type (-1);
#endif
            while (it != it_end) {
                index1 = functor_type::index1 ((*it).first, size1_, size2_);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                index2 = functor_type::index2 ((*it).first, size1_, size2_);
                BOOST_UBLAS_CHECK (index1 >= i || index2 >= j, internal_logic ());
#endif
                if ((rank == 0 && index1 >= i) ||
                    (rank == 1 && index1 == i) ||
                    (j >= size2_)) {
                    break;
                }
                ++ j;
                it = data ().lower_bound (functor_type::element (i, size1_, j, size2_));
            }
            if (rank == 1 && index1 != i) {
                j = size2_;
                rank = 0;
            }
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, j);
#else
            return const_iterator2 (*this, rank, i, j, it);
#endif
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            iterator_type it (data ().lower_bound (functor_type::element (i, size1_, j, size2_)));
            iterator_type it_end (data ().end ());
            size_type index1 = size_type (-1);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
            size_type index2 = size_type (-1);
#endif
            while (it != it_end) {
                index1 = functor_type::index1 ((*it).first, size1_, size2_);
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                index2 = functor_type::index2 ((*it).first, size1_, size2_);
                BOOST_UBLAS_CHECK (index1 >= i || index2 >= j, internal_logic ());
#endif
                if ((rank == 0 && index1 >= i) ||
                    (rank == 1 && index1 == i) ||
                    (j >= size2_)) {
                    break;
                }
                ++ j;
                it = data ().lower_bound (functor_type::element (i, size1_, j, size2_));
            }
            if (rank == 1 && index1 != i) {
                j = size2_;
                rank = 0;
            }
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, j);
#else
            return iterator2 (*this, rank, i, j, it);
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_first1 (int rank, size_type i, size_type j) const {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find_first1 (int rank, size_type i, size_type j) {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_last1 (int rank, size_type i, size_type j) const {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find_last1 (int rank, size_type i, size_type j) {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_first2 (int rank, size_type i, size_type j) const {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find_first2 (int rank, size_type i, size_type j) {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_last2 (int rank, size_type i, size_type j) const {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find_last2 (int rank, size_type i, size_type j) {
            return find2 (rank, i, j);
        }

        // Iterators simply are pointers.

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class const_iterator1:
            public container_const_reference<sparse_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag, 
                                               const_iterator1, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename sparse_matrix::difference_type difference_type;
            typedef typename sparse_matrix::value_type value_type;
            typedef typename sparse_matrix::const_reference reference;
            typedef typename sparse_matrix::const_pointer pointer;
#endif
            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<sparse_matrix> (), rank_ (), i_ (), j_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const sparse_matrix &m, int rank, size_type i, size_type j, const const_iterator_type &it):
                container_const_reference<sparse_matrix> (m), rank_ (rank), i_ (i), j_ (j), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<sparse_matrix> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                const sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    ++ it_;
                else
                    *this = m.find1 (rank_, index1 () + 1, j_);
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                const sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    -- it_;
                else
                    *this = m.find1 (rank_, index1 () - 1, j_);
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*it_).second;
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            const_iterator2 begin () const {
                const sparse_matrix &m = (*this) ();
                return m.find_first2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
            const_iterator2 end () const {
                const sparse_matrix &m = (*this) ();
                return m.find_last2 (1, index1 (), m.size2 ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index1 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index2 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return j_;
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<sparse_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find_last1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class iterator1:
            public container_reference<sparse_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename sparse_matrix::difference_type difference_type;
            typedef typename sparse_matrix::value_type value_type;
            typedef typename sparse_matrix::reference reference;
            typedef typename sparse_matrix::pointer pointer;
#endif
            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<sparse_matrix> (), rank_ (), i_ (), j_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (sparse_matrix &m, int rank, size_type i, size_type j, const iterator_type &it):
                container_reference<sparse_matrix> (m), rank_ (rank), i_ (i), j_ (j), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    ++ it_;
                else
                    *this = m.find1 (rank_, index1 () + 1, j_);
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    -- it_;
                else
                    *this = m.find1 (rank_, index1 () - 1, j_);
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
#ifndef BOOST_UBLAS_STRICT_SPARSE_ELEMENT_ASSIGN
                    return (*it_).second;
#else
                    return map_traits<array_type>::make_reference ((*this) ().data (), it_);
#endif
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            iterator2 begin () const {
                sparse_matrix &m = (*this) ();
                return m.find_first2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
            iterator2 end () const {
                sparse_matrix &m = (*this) ();
                return m.find_last2 (1, index1 (), m.size2 ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index1 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index2 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return j_;
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<sparse_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            iterator_type it_;
            
            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find_last1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class const_iterator2:
            public container_const_reference<sparse_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename sparse_matrix::difference_type difference_type;
            typedef typename sparse_matrix::value_type value_type;
            typedef typename sparse_matrix::const_reference reference;
            typedef typename sparse_matrix::const_pointer pointer;
#endif
            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<sparse_matrix> (), rank_ (), i_ (), j_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const sparse_matrix &m, int rank, size_type i, size_type j, const const_iterator_type &it):
                container_const_reference<sparse_matrix> (m), rank_ (rank), i_ (i), j_ (j), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<sparse_matrix> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                const sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    ++ it_;
                else
                    *this = m.find2 (rank_, i_, index2 () + 1);
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                const sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    -- it_;
                else
                    *this = m.find2 (rank_, i_, index2 () - 1);
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*it_).second;
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            const_iterator1 begin () const {
                const sparse_matrix &m = (*this) ();
                return m.find_first1 (1, 0, index2 ()); 
            }
            BOOST_UBLAS_INLINE
            const_iterator1 end () const {
                const sparse_matrix &m = (*this) ();
                return m.find_last1 (1, m.size1 (), index2 ()); 
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index1 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index2 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return j_;
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<sparse_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find_last2 (0, 0, size2_);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class iterator2:
            public container_reference<sparse_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename sparse_matrix::difference_type difference_type;
            typedef typename sparse_matrix::value_type value_type;
            typedef typename sparse_matrix::reference reference;
            typedef typename sparse_matrix::pointer pointer;
#endif
            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<sparse_matrix> (), rank_ (), i_ (), j_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (sparse_matrix &m, int rank, size_type i, size_type j, const iterator_type &it):
                container_reference<sparse_matrix> (m), rank_ (rank), i_ (i), j_ (j), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    ++ it_;
                else
                    *this = m.find2 (rank_, i_, index2 () + 1);
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                sparse_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    -- it_;
                else
                    *this = m.find2 (rank_, i_, index2 () - 1);
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
#ifndef BOOST_UBLAS_STRICT_SPARSE_ELEMENT_ASSIGN
                    return (*it_).second;
#else
                    return map_traits<array_type>::make_reference ((*this) ().data (), it_);
#endif
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            iterator1 begin () const {
                sparse_matrix &m = (*this) ();
                return m.find_first1 (1, 0, index2 ()); 
            }
            BOOST_UBLAS_INLINE
            iterator1 end () const {
                sparse_matrix &m = (*this) ();
                return m.find_last1 (1, m.size1 (), index2 ()); 
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index1 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    const sparse_matrix &m = (*this) ();
                    return functor_type::index2 ((*it_).first, m.size1 (), m.size2 ());
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<sparse_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            iterator_type it_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find_last2 (0, 0, size2_);
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        size_type size1_;
        size_type size2_;
        size_type non_zeros_;
        array_type data_;
        static value_type zero_;
    };

    template<class T, class F, class A>
    typename sparse_matrix<T, F, A>::value_type sparse_matrix<T, F, A>::zero_ = 0;

    // Array based sparse matrix class 
    template<class T, class F, class A>
    class sparse_vector_of_sparse_vector:
        public matrix_expression<sparse_vector_of_sparse_vector<T, F, A> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING matrix_expression<sparse_vector_of_sparse_vector<T, F, A> >::operator ();
#endif
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        // typedef const T &const_reference;
        typedef typename type_traits<T>::const_reference const_reference;
#ifndef BOOST_UBLAS_STRICT_SPARSE_ELEMENT_ASSIGN
        typedef T &reference;
#else
        typedef typename map_traits<typename A::data_value_type>::reference reference;
#endif
        typedef const T *const_pointer;
        typedef T *pointer;
        typedef A array_type;
        typedef const A const_array_type;
        typedef F functor_type;
        typedef const sparse_vector_of_sparse_vector<T, F, A> const_self_type;
        typedef sparse_vector_of_sparse_vector<T, F, A> self_type;
        typedef const matrix_const_reference<const_self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef typename A::value_type::second_type vector_data_value_type;
        typedef typename A::const_iterator vector_const_iterator_type;
        typedef typename A::iterator vector_iterator_type;
        typedef typename A::value_type::second_type::const_iterator const_iterator_type;
        typedef typename A::value_type::second_type::iterator iterator_type;
        typedef sparse_tag storage_category;
        typedef typename F::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector ():
            size1_ (0), size2_ (0), non_zeros_ (0), data_ () {
            data_ [functor_type::size1 (size1_, size2_)] = vector_data_value_type ();
        }
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector (size_type size1, size_type size2, size_type non_zeros = 0):
            size1_ (size1), size2_ (size2), non_zeros_ (non_zeros), data_ () {
            data_ [functor_type::size1 (size1_, size2_)] = vector_data_value_type ();
        }
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector (const sparse_vector_of_sparse_vector &m): 
            size1_ (m.size1_), size2_ (m.size2_), non_zeros_ (m.non_zeros_), data_ (m.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector (const matrix_expression<AE> &ae, size_type non_zeros = 0):
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()), non_zeros_ (non_zeros), data_ () {
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return size1_;
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return size2_;
        }
        BOOST_UBLAS_INLINE
        size_type non_zeros () const {
            size_type non_zeros = 0;
            for (vector_const_iterator_type itv = data_ ().begin (); itv != data_ ().end (); ++ itv)
                non_zeros += (*itv).size ();
            return non_zeros;
        }
        BOOST_UBLAS_INLINE
        const_array_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type &data () {
            return data_;
        }

        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, size_type non_zeros = 0) {
            size1_ = size1;
            size2_ = size2;
            non_zeros_ = non_zeros;
            data ().clear ();
            data () [functor_type::size1 (size1_, size2_)] = vector_data_value_type ();
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            vector_const_iterator_type itv (data ().find (functor_type::element1 (i, size1_, j, size2_)));
            if (itv == data ().end () || (*itv).first != functor_type::element1 (i, size1_, j, size2_))
                return zero_;
            const_iterator_type it ((*itv).second.find (functor_type::element2 (i, size1_, j, size2_)));
            if (it == (*itv).second.end () || (*it).first != functor_type::element2 (i, size1_, j, size2_))
                return zero_;
            return (*it).second;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            return data () [functor_type::element1 (i, size1_, j, size2_)] [functor_type::element2 (i, size1_, j, size2_)];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &operator = (const sparse_vector_of_sparse_vector &m) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &m, external_logic ());
            if (this != &m) {
                BOOST_UBLAS_CHECK (size1_ == m.size1_, bad_size ());
                BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                size1_ = m.size1_;
                size2_ = m.size2_;
                non_zeros_ = m.non_zeros_;
                data () = m.data ();
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &assign_temporary (sparse_vector_of_sparse_vector &m) {
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &operator = (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (ae, non_zeros_));
#else
            // return assign (self_type (ae, non_zeros_));
            self_type temporary (ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &reset (const matrix_expression<AE> &ae) {
            self_type temporary (ae, non_zeros_);
            resize (temporary.size1 (), temporary.size2 (), non_zeros_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector& operator += (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (*this + ae, non_zeros_));
#else
            // return assign (self_type (*this + ae, non_zeros_));
            self_type temporary (*this + ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector& operator -= (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (*this - ae, non_zeros_));
#else
            // return assign (self_type (*this - ae, non_zeros_));
            self_type temporary (*this - ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector &minus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        sparse_vector_of_sparse_vector& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (sparse_vector_of_sparse_vector &m) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &m, external_logic ());
            if (this != &m) {
                // Precondition for container relaxed as requested during review.
                // BOOST_UBLAS_CHECK (size1_ == m.size1_, bad_size ());
                // BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                // BOOST_UBLAS_CHECK (non_zeros_ == m.non_zeros_, bad_size ());
                std::swap (size1_, m.size1_);
                std::swap (size2_, m.size2_);
                std::swap (non_zeros_, m.non_zeros_);
                data ().swap (m.data ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (sparse_vector_of_sparse_vector &m1, sparse_vector_of_sparse_vector &m2) {
            m1.swap (m2);
        }
#endif

        // Element insertion and erasure
        BOOST_UBLAS_INLINE
        void insert (size_type i, size_type j, const_reference t) {
#ifdef BOOST_UBLAS_CHECK_FOR_ZERO
            if (t == value_type ())
                return;
#endif
            vector_iterator_type itv (data ().find (functor_type::element1 (i, size1_, j, size2_)));
            if (itv == data ().end ()) 
                itv = data ().insert (data ().end (), std::pair<size_type, vector_data_value_type> (functor_type::element1 (i, size1_, j, size2_), vector_data_value_type ()));
            BOOST_UBLAS_CHECK ((*itv).second.find (functor_type::element2 (i, size1_, j, size2_)) == (*itv).second.end (), bad_index ());
            (*itv).second.insert ((*itv).second.end (), std::pair<size_type, value_type> (functor_type::element2 (i, size1_, j, size2_), t));
        }
        BOOST_UBLAS_INLINE
        void erase (size_type i, size_type j) {
            vector_iterator_type itv (data ().find (functor_type::element1 (i, size1_, j, size2_)));
            if (itv == data ().end ()) 
                return;
            iterator_type it ((*itv).second.find (functor_type::element2 (i, size1_, j, size2_)));
            if (it == (*itv).second.end ())
                return;
            (*itv).second.erase (it);
        }
        BOOST_UBLAS_INLINE
        void clear () {
            data ().clear ();
        }

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        typedef matrix_row_iterator<self_type, sparse_bidirectional_iterator_tag> iterator1;
        typedef matrix_column_iterator<self_type, sparse_bidirectional_iterator_tag> iterator2;
        typedef matrix_row_const_iterator<self_type, sparse_bidirectional_iterator_tag> const_iterator1;
        typedef matrix_column_const_iterator<self_type, sparse_bidirectional_iterator_tag> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base1<const_iterator1, value_type, const_reference> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1, value_type, reference> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2, value_type, const_reference> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2, value_type, reference> reverse_iterator2;
#else
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;
#endif

        // Element lookup
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator1 find1 (int rank, size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_const_iterator_type itv (data ().lower_bound (functor_type::element1 (i, size1_, j, size2_)));
                vector_const_iterator_type itv_end (data ().end ());
                if (itv == itv_end)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator1 (*this, i);
#else
                    return const_iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());
#endif

                const_iterator_type it ((*itv).second.lower_bound (functor_type::element2 (i, size1_, j, size2_)));
                const_iterator_type it_end ((*itv).second.end ());
                if (it != it_end) {
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index1 (functor_type::index1 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#endif
                    size_type index2 (functor_type::index2 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
                    if ((rank == 0 && index2 >= j) ||
                        (rank == 1 && index2 == j))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return const_iterator1 (*this, i);
#else
                        return const_iterator1 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || i >= size1_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator1 (*this, i);
#else
                    return const_iterator1 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ i;
            }
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_iterator_type itv (data ().lower_bound (functor_type::element1 (i, size1_, j, size2_)));
                vector_iterator_type itv_end (data ().end ());
                if (itv == itv_end)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator1 (*this, i);
#else
                    return iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());
#endif

                iterator_type it ((*itv).second.lower_bound (functor_type::element2 (i, size1_, j, size2_)));
                iterator_type it_end ((*itv).second.end ());
                if (it != it_end) {
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index1 (functor_type::index1 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#endif
                    size_type index2 (functor_type::index2 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
                    if ((rank == 0 && index2 >= j) ||
                        (rank == 1 && index2 == j))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return iterator1 (*this, i);
#else
                        return iterator1 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || i >= size1_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator1 (*this, i);
#else
                    return iterator1 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ i;
            }
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_const_iterator_type itv (data ().lower_bound (functor_type::element1 (i, size1_, j, size2_)));
                vector_const_iterator_type itv_end (data ().end ());
                if (itv == itv_end)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator2 (*this, j);
#else
                    return const_iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());
#endif

                const_iterator_type it ((*itv).second.lower_bound (functor_type::element2 (i, size1_, j, size2_)));
                const_iterator_type it_end ((*itv).second.end ());
                if (it != it_end) {
                    size_type index1 (functor_type::index1 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index2 (functor_type::index2 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
#endif
                    if ((rank == 0 && index1 >= i) ||
                        (rank == 1 && index1 == i))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return const_iterator2 (*this, j);
#else
                        return const_iterator2 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || j >= size2_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator2 (*this, j);
#else
                    return const_iterator2 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ j;
            }
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_iterator_type itv (data ().lower_bound (functor_type::element1 (i, size1_, j, size2_)));
                vector_iterator_type itv_end (data ().end ());
                if (itv == itv_end)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator2 (*this, j);
#else
                    return iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());
#endif

                iterator_type it ((*itv).second.lower_bound (functor_type::element2 (i, size1_, j, size2_)));
                iterator_type it_end ((*itv).second.end ());
                if (it != it_end) {
                    size_type index1 (functor_type::index1 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index2 (functor_type::index2 ((*itv).first, (*it).first));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
#endif
                    if ((rank == 0 && index1 >= i) ||
                        (rank == 1 && index1 == i))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return iterator2 (*this, j);
#else
                        return iterator2 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || j >= size2_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator2 (*this, j);
#else
                    return iterator2 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ j;
            }
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_first1 (int rank, size_type i, size_type j) const {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find_first1 (int rank, size_type i, size_type j) {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_last1 (int rank, size_type i, size_type j) const {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find_last1 (int rank, size_type i, size_type j) {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_first2 (int rank, size_type i, size_type j) const {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find_first2 (int rank, size_type i, size_type j) {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_last2 (int rank, size_type i, size_type j) const {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find_last2 (int rank, size_type i, size_type j) {
            return find2 (rank, i, j);
        }

        // Iterators simply are pointers.

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class const_iterator1:
            public container_const_reference<sparse_vector_of_sparse_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename sparse_vector_of_sparse_vector::difference_type difference_type;
            typedef typename sparse_vector_of_sparse_vector::value_type value_type;
            typedef typename sparse_vector_of_sparse_vector::const_reference reference;
            typedef typename sparse_vector_of_sparse_vector::const_pointer pointer;
#endif
            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<sparse_vector_of_sparse_vector> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const sparse_vector_of_sparse_vector &m, int rank, size_type i, size_type j, const vector_const_iterator_type &itv, const const_iterator_type &it):
                container_const_reference<sparse_vector_of_sparse_vector> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<sparse_vector_of_sparse_vector> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), itv_ (it.itv_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    ++ it_;
                else {
                    i_ = index1 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end1 ().itv_) 
                        *this = m.find1 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index2 () != j_) 
                            *this = m.find1 (rank_, i_, j_);
                    } 
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    -- it_;
                else {
                    i_ = index1 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end1 ().itv_) 
                        *this = m.find1 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index2 () != j_) 
                            *this = m.find1 (rank_, i_, j_);
                    } 
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*it_).second;
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            const_iterator2 begin () const {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_first2 (1, index1 (), 0); 
            }
            BOOST_UBLAS_INLINE
            const_iterator2 end () const {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_last2 (1, index1 (), m.size2 ()); 
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 ((*itv_).first, (*it_).first);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 ((*itv_).first, (*it_).first);
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<sparse_vector_of_sparse_vector>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_const_iterator_type itv_;
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find_last1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class iterator1:
            public container_reference<sparse_vector_of_sparse_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename sparse_vector_of_sparse_vector::difference_type difference_type;
            typedef typename sparse_vector_of_sparse_vector::value_type value_type;
            typedef typename sparse_vector_of_sparse_vector::reference reference;
            typedef typename sparse_vector_of_sparse_vector::pointer pointer;
#endif
            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<sparse_vector_of_sparse_vector> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (sparse_vector_of_sparse_vector &m, int rank, size_type i, size_type j, const vector_iterator_type &itv, const iterator_type &it):
                container_reference<sparse_vector_of_sparse_vector> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    ++ it_;
                else {
                    i_ = index1 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end1 ().itv_) 
                        *this = m.find1 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index2 () != j_) 
                            *this = m.find1 (rank_, i_, j_);
                    } 
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    -- it_;
                else {
                    i_ = index1 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end1 ().itv_) 
                        *this = m.find1 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index2 () != j_) 
                            *this = m.find1 (rank_, i_, j_);
                    } 
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*it_).second;
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            iterator2 begin () const {
                sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_first2 (1, index1 (), 0); 
            }
            BOOST_UBLAS_INLINE
            iterator2 end () const {
                sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_last2 (1, index1 (), m.size2 ()); 
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 ((*itv_).first, (*it_).first);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 ((*itv_).first, (*it_).first);
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<sparse_vector_of_sparse_vector>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_iterator_type itv_;
            iterator_type it_;
            
            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find_last1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class const_iterator2:
            public container_const_reference<sparse_vector_of_sparse_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename sparse_vector_of_sparse_vector::difference_type difference_type;
            typedef typename sparse_vector_of_sparse_vector::value_type value_type;
            typedef typename sparse_vector_of_sparse_vector::const_reference reference;
            typedef typename sparse_vector_of_sparse_vector::const_pointer pointer;
#endif
            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<sparse_vector_of_sparse_vector> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const sparse_vector_of_sparse_vector &m, int rank, size_type i, size_type j, const vector_const_iterator_type &itv, const const_iterator_type &it):
                container_const_reference<sparse_vector_of_sparse_vector> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<sparse_vector_of_sparse_vector> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), itv_ (it.itv_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    ++ it_;
                else {
                    j_ = index2 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end2 ().itv_) 
                        *this = m.find2 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index1 () != i_) 
                            *this = m.find2 (rank_, i_, j_);
                    } 
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    -- it_;
                else {
                    j_ = index2 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end2 ().itv_) 
                        *this = m.find2 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index1 () != i_) 
                            *this = m.find2 (rank_, i_, j_);
                    } 
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*it_).second;
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            const_iterator1 begin () const {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_first1 (1, 0, index2 ()); 
            }
            BOOST_UBLAS_INLINE
            const_iterator1 end () const {
                const sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_last1 (1, m.size1 (), index2 ()); 
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 ((*itv_).first, (*it_).first);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 ((*itv_).first, (*it_).first);
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<sparse_vector_of_sparse_vector>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_const_iterator_type itv_;
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find_last2 (0, 0, size2_);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class iterator2:
            public container_reference<sparse_vector_of_sparse_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename sparse_vector_of_sparse_vector::difference_type difference_type;
            typedef typename sparse_vector_of_sparse_vector::value_type value_type;
            typedef typename sparse_vector_of_sparse_vector::reference reference;
            typedef typename sparse_vector_of_sparse_vector::pointer pointer;
#endif
            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<sparse_vector_of_sparse_vector> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (sparse_vector_of_sparse_vector &m, int rank, size_type i, size_type j, const vector_iterator_type &itv, const iterator_type &it):
                container_reference<sparse_vector_of_sparse_vector> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    ++ it_;
                else {
                    j_ = index2 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end2 ().itv_)
                        *this = m.find2 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index1 () != i_) 
                            *this = m.find2 (rank_, i_, j_);
                    } 
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                sparse_vector_of_sparse_vector &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    -- it_;
                else {
                    j_ = index2 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end2 ().itv_) 
                        *this = m.find2 (rank_, i_, j_);
                    else if (rank_ == 1) {
                        it_ = (*itv_).second.begin ();
                        if (it_ == (*itv_).second.end () || index1 () != i_) 
                            *this = m.find2 (rank_, i_, j_);
                    } 
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*it_).second;
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            iterator1 begin () const {
                sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_first1 (1, 0, index2 ()); 
            }
            BOOST_UBLAS_INLINE
            iterator1 end () const {
                sparse_vector_of_sparse_vector &m = (*this) ();
                return m.find_last1 (1, m.size1 (), index2 ()); 
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 ((*itv_).first, (*it_).first);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 ((*itv_).first, (*it_).first);
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<sparse_vector_of_sparse_vector>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_iterator_type itv_;
            iterator_type it_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find_last2 (0, 0, size2_);
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        size_type size1_;
        size_type size2_;
        size_type non_zeros_;
        array_type data_;
        static value_type zero_;
    };

    template<class T, class F, class A>
    typename sparse_vector_of_sparse_vector<T, F, A>::value_type sparse_vector_of_sparse_vector<T, F, A>::zero_ = 0;

    // Array based sparse matrix class
    template<class T, class F, class IA, class TA>
    class compressed_matrix:
        public matrix_expression<compressed_matrix<T, F, IA, TA> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING matrix_expression<compressed_matrix<T, F, IA, TA> >::operator ();
#endif
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        // typedef const T &const_reference;
        typedef typename type_traits<T>::const_reference const_reference;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef T *pointer;
        typedef IA index_array_type;
        typedef TA value_array_type;
        typedef F functor_type;
        typedef const compressed_matrix<T, F, IA, TA> const_self_type;
        typedef compressed_matrix<T, F, IA, TA> self_type;
        typedef const matrix_const_reference<const_self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef typename IA::const_iterator vector_const_iterator_type;
        typedef typename IA::iterator vector_iterator_type;
        typedef typename IA::const_iterator const_iterator_type;
        typedef typename IA::iterator iterator_type;
        typedef sparse_tag storage_category;
        typedef typename F::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        compressed_matrix (): 
            size1_ (0), size2_ (0), non_zeros_ (0), 
            filled1_ (0), filled2_ (0),
            index1_data_ (), 
            index2_data_ (), value_data_ () {
            index1_data_.clear ();
        }
        BOOST_UBLAS_INLINE
        compressed_matrix (size_type size1, size_type size2, size_type non_zeros = 0): 
            size1_ (size1), size2_ (size2), non_zeros_ (non_zeros),
            filled1_ (0), filled2_ (0),
            index1_data_ (functor_type::size1 (size1_, size2_)),
            index2_data_ (non_zeros), value_data_ (non_zeros) {
            index1_data_.clear ();
        }
        BOOST_UBLAS_INLINE
        compressed_matrix (const compressed_matrix &m):
            size1_ (m.size1_), size2_ (m.size2_), non_zeros_ (m.non_zeros_), 
            filled1_ (m.filled1_), filled2_ (m.filled2_),
            index1_data_ (m.index1_data_), 
            index2_data_ (m.index2_data_), value_data_ (m.value_data_) {
            index1_data_.clear ();
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix (const matrix_expression<AE> &ae, size_type non_zeros = 0): 
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()), non_zeros_ (non_zeros), 
            filled1_ (0), filled2_ (0),
            index1_data_ (functor_type::size1 (ae ().size1 (), ae ().size2 ())),
            index2_data_ (non_zeros), value_data_ (non_zeros) {
            index1_data_.clear ();
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const { 
            return size1_;
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const { 
            return size2_;
        }
        BOOST_UBLAS_INLINE
        size_type non_zeros () const { 
            return non_zeros_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index1_data () const {
            return index1_data_;
        }
        BOOST_UBLAS_INLINE
        index_array_type &index1_data () {
            return index1_data_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index2_data () const {
            return index2_data_;
        }
        BOOST_UBLAS_INLINE
        index_array_type &index2_data () {
            return index2_data_;
        }
        BOOST_UBLAS_INLINE
        const value_array_type &value_data () const {
            return value_data_;
        }
        BOOST_UBLAS_INLINE
        value_array_type &value_data () {
            return value_data_;
        }

        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, size_type non_zeros = 0) {
            size1_ = size1;
            size2_ = size2;
            non_zeros_ = non_zeros;
            filled1_ = 0;
            filled2_ = 0;
            index1_data ().resize (functor_type::size1 (size1, size2));
            index2_data ().resize (non_zeros);
            value_data ().resize (non_zeros);
            index1_data ().clear ();
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            size_type element1 (functor_type::element1 (i, size1_, j, size2_));
            size_type element2 (functor_type::element2 (i, size1_, j, size2_));
            vector_const_iterator_type itv (index1_data ().begin () + element1);
            if (filled1_ <= element1)
                return zero_;
            const_iterator_type it_begin (index2_data ().begin () + *itv - 1);
            const_iterator_type it_end (index2_data ().begin () + filled2_);
            if (filled1_ > element1 + 1)
                it_end = index2_data ().begin () + *(itv + 1) - 1;
            const_iterator_type it (std::lower_bound (it_begin, it_end, element2 + 1, std::less<size_type> ()));
            if (it == it_end || *it != element2 + 1)
                return zero_;
            return value_data () [it - index2_data ().begin ()];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            size_type element1 (functor_type::element1 (i, size1_, j, size2_));
            size_type element2 (functor_type::element2 (i, size1_, j, size2_));
            vector_const_iterator_type itv (index1_data ().begin () + element1);
            if (filled1_ <= element1)
                insert (i, j, value_type ());
            const_iterator_type it_begin (index2_data ().begin () + *itv - 1);
            const_iterator_type it_end (index2_data ().begin () + filled2_);
            if (filled1_ > element1 + 1)
                it_end = index2_data ().begin () + *(itv + 1) - 1;
            const_iterator_type it (std::lower_bound (it_begin, it_end, element2 + 1, std::less<size_type> ()));
            if (it == it_end || *it != element2 + 1)
                insert (i, j, value_type ());
            return value_data () [it - index2_data ().begin ()];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        compressed_matrix &operator = (const compressed_matrix &m) { 
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &m, external_logic ());
            if (this != &m) {
                BOOST_UBLAS_CHECK (size1_ == m.size1_, bad_size ());
                BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                size1_ = m.size1_;
                size2_ = m.size2_;
                non_zeros_ = m.non_zeros_;
                filled1_ = m.filled1_;
                filled2_ = m.filled2_;
                index1_data () = m.index1_data ();
                index2_data () = m.index2_data ();
                value_data () = m.value_data ();
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        compressed_matrix &assign_temporary (compressed_matrix &m) { 
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix &operator = (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (ae, non_zeros_));
#else
            // return assign (self_type (ae, non_zeros_));
            self_type temporary (ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix &reset(const matrix_expression<AE> &ae) {
            self_type temporary (ae, non_zeros_);
            resize (temporary.size1 (), temporary.size2 (), non_zeros_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix& operator += (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (*this + ae, non_zeros_));
#else
            // return assign (self_type (*this + ae, non_zeros_));
            self_type temporary (*this + ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix& operator -= (const matrix_expression<AE> &ae) {
#ifdef BOOST_UBLAS_MUTABLE_TEMPORARY
            return assign_temporary (self_type (*this - ae, non_zeros_));
#else
            // return assign (self_type (*this - ae, non_zeros_));
            self_type temporary (*this - ae, non_zeros_);
            return assign_temporary (temporary);
#endif
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_matrix &minus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_matrix& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_matrix& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (compressed_matrix &m) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &m, external_logic ());
            if (this != &m) {
                // Precondition for container relaxed as requested during review.
                // BOOST_UBLAS_CHECK (size1_ == m.size1_, bad_size ());
                // BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                // BOOST_UBLAS_CHECK (non_zeros_ == m.non_zeros_, bad_size ());
                std::swap (size1_, m.size1_);
                std::swap (size2_, m.size2_);
                std::swap (non_zeros_, m.non_zeros_);
                std::swap (filled1_, m.filled1_);
                std::swap (filled2_, m.filled2_);
                index1_data ().swap (m.index1_data ());
                index2_data ().swap (m.index2_data ());
                value_data ().swap (m.value_data ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (compressed_matrix &m1, compressed_matrix &m2) {
            m1.swap (m2);
        }
#endif

        // Element insertion and erasure
        BOOST_UBLAS_INLINE
        void insert (size_type i, size_type j, const_reference t) {
// FIXME: Doesn't work if the first element is zero.
// #ifdef BOOST_UBLAS_CHECK_FOR_ZERO
//            if (t == value_type ())
//                return;
// #endif
            size_type element1 = functor_type::element1 (i, size1_, j, size2_);
            size_type element2 = functor_type::element2 (i, size1_, j, size2_);
            if (filled1_ < element1 + 1) {
                do {
                    index1_data () [filled1_] = filled2_ + 1;
                } while (++ filled1_ < element1 + 1);
            } else {
                BOOST_UBLAS_CHECK (filled1_ - 1 == element1, external_logic ());
                BOOST_UBLAS_CHECK (index2_data () [filled2_ - 1] < element2 + 1, external_logic ()); 
            }
            index2_data () [filled2_] = element2 + 1;
            value_data () [filled2_] = t;
            ++ filled2_;
        }
        BOOST_UBLAS_INLINE
        void erase (size_type i, size_type j) {
#ifdef BOOST_UBLAS_BOUNDS_CHECK
            size_type element1 = functor_type::element1 (i, size1_, j, size2_);
            BOOST_UBLAS_CHECK (filled1_ == element1 + 1, external_logic ());
            size_type element2 = functor_type::element2 (i, size1_, j, size2_);
            BOOST_UBLAS_CHECK (filled2_ > 0 && index2_data () [filled2_ - 1] == element2 + 1, external_logic ());
#endif
            -- filled2_;
            if (index1_data () [filled1_ - 1] > filled2_ + 1) {
                index1_data () [filled1_ - 1] = 0;
                -- filled1_;
            }
        }
        BOOST_UBLAS_INLINE
        void clear () {
            filled1_ = 0;
            filled2_ = 0;
            index1_data ().clear ();
        }

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        typedef matrix_row_iterator<self_type, sparse_bidirectional_iterator_tag> iterator1;
        typedef matrix_column_iterator<self_type, sparse_bidirectional_iterator_tag> iterator2;
        typedef matrix_row_const_iterator<self_type, sparse_bidirectional_iterator_tag> const_iterator1;
        typedef matrix_column_const_iterator<self_type, sparse_bidirectional_iterator_tag> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base1<const_iterator1, value_type, const_reference> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1, value_type, reference> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2, value_type, const_reference> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2, value_type, reference> reverse_iterator2;
#else
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;
#endif

        // Element lookup
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator1 find1 (int rank, size_type i, size_type j) const {
            for (;;) {
                size_type element1 (functor_type::element1 (i, size1_, j, size2_));
                size_type element2 (functor_type::element2 (i, size1_, j, size2_));
                vector_const_iterator_type itv (index1_data ().begin () + std::min (filled1_, element1));
                if (filled1_ <= element1)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator1 (*this, i);
#else
                    return const_iterator1 (*this, rank, i, j, itv, index2_data ().begin () + filled2_);
#endif

                const_iterator_type it_begin (index2_data ().begin () + *itv - 1);
                const_iterator_type it_end (index2_data ().begin () + filled2_);
                if (filled1_ > element1 + 1)
                    it_end = index2_data ().begin () + *(itv + 1) - 1;

                const_iterator_type it (std::lower_bound (it_begin, it_end, element2 + 1, std::less<size_type> ()));
                if (it != it_end) {
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index1 (functor_type::index1 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#endif
                    size_type index2 (functor_type::index2 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
                    if ((rank == 0 && index2 >= j) ||
                        (rank == 1 && index2 == j))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return const_iterator1 (*this, i);
#else
                        return const_iterator1 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || i >= size1_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator1 (*this, i);
#else
                    return const_iterator1 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ i;
            }
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            for (;;) {
                size_type element1 (functor_type::element1 (i, size1_, j, size2_));
                size_type element2 (functor_type::element2 (i, size1_, j, size2_));
                vector_iterator_type itv (index1_data ().begin () + std::min (filled1_, element1));
                if (filled1_ <= element1)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator1 (*this, i);
#else
                    return iterator1 (*this, rank, i, j, itv, index2_data ().begin () + filled2_);
#endif

                iterator_type it_begin (index2_data ().begin () + *itv - 1);
                iterator_type it_end (index2_data ().begin () + filled2_);
                if (filled1_ > element1 + 1)
                    it_end = index2_data ().begin () + *(itv + 1) - 1;

                iterator_type it (std::lower_bound (it_begin, it_end, element2 + 1, std::less<size_type> ()));
                if (it != it_end) {
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index1 (functor_type::index1 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#endif
                    size_type index2 (functor_type::index2 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
                    if ((rank == 0 && index2 >= j) ||
                        (rank == 1 && index2 == j))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return iterator1 (*this, i);
#else
                        return iterator1 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || i == size1_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator1 (*this, i);
#else
                    return iterator1 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ i;
            }
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            for (;;) {
                size_type element1 (functor_type::element1 (i, size1_, j, size2_));
                size_type element2 (functor_type::element2 (i, size1_, j, size2_));
                vector_const_iterator_type itv (index1_data ().begin () + std::min (filled1_, element1));
                if (filled1_ <= element1)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator2 (*this, j);
#else
                    return const_iterator2 (*this, rank, i, j, itv, index2_data ().begin () + filled2_);
#endif

                const_iterator_type it_begin (index2_data ().begin () + *itv - 1);
                const_iterator_type it_end (index2_data ().begin () + filled2_);
                if (filled1_ > element1 + 1)
                    it_end = index2_data ().begin () + *(itv + 1) - 1;

                const_iterator_type it (std::lower_bound (it_begin, it_end, element2 + 1, std::less<size_type> ()));
                if (it != it_end) {
                    size_type index1 (functor_type::index1 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index2 (functor_type::index2 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
#endif
                    if ((rank == 0 && index1 >= i) ||
                        (rank == 1 && index1 == i))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return const_iterator2 (*this, j);
#else
                        return const_iterator2 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || j == size2_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return const_iterator2 (*this, j);
#else
                    return const_iterator2 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ j;
            }
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            for (;;) {
                size_type element1 (functor_type::element1 (i, size1_, j, size2_));
                size_type element2 (functor_type::element2 (i, size1_, j, size2_));
                vector_iterator_type itv (index1_data ().begin () + std::min (filled1_, element1));
                if (filled1_ <= element1)
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator2 (*this, j);
#else
                    return iterator2 (*this, rank, i, j, itv, index2_data ().begin () + filled2_);
#endif

                iterator_type it_begin (index2_data ().begin () + *itv - 1);
                iterator_type it_end (index2_data ().begin () + filled2_);
                if (filled1_ > element1 + 1)
                    it_end = index2_data ().begin () + *(itv + 1) - 1;

                iterator_type it (std::lower_bound (it_begin, it_end, element2 + 1, std::less<size_type> ()));
                if (it != it_end) {
                    size_type index1 (functor_type::index1 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index1 >= i, internal_logic ());
#ifdef BOOST_UBLAS_BOUNDS_CHECK
                    size_type index2 (functor_type::index2 (itv - index1_data ().begin (), (*it) - 1));
                    BOOST_UBLAS_CHECK (index2 >= j, internal_logic ());
#endif
                    if ((rank == 0 && index1 >= i) ||
                        (rank == 1 && index1 == i))
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                        return iterator2 (*this, j);
#else
                        return iterator2 (*this, rank, i, j, itv, it);
#endif
                }

                if (rank == 0 || j == size2_) {
                    if (rank == 1)
                        rank = 0;
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
                    return iterator2 (*this, j);
#else
                    return iterator2 (*this, rank, i, j, itv, it_end);
#endif
                }
                ++ j;
            }
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_first1 (int rank, size_type i, size_type j) const {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find_first1 (int rank, size_type i, size_type j) {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_last1 (int rank, size_type i, size_type j) const {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find_last1 (int rank, size_type i, size_type j) {
            return find1 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_first2 (int rank, size_type i, size_type j) const {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find_first2 (int rank, size_type i, size_type j) {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_last2 (int rank, size_type i, size_type j) const {
            return find2 (rank, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find_last2 (int rank, size_type i, size_type j) {
            return find2 (rank, i, j);
        }

        // Iterators simply are pointers.

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class const_iterator1:
            public container_const_reference<compressed_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename compressed_matrix::difference_type difference_type;
            typedef typename compressed_matrix::value_type value_type;
            typedef typename compressed_matrix::const_reference reference;
            typedef typename compressed_matrix::const_pointer pointer;
#endif
            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<compressed_matrix> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const compressed_matrix &m, int rank, size_type i, size_type j, const vector_const_iterator_type &itv, const const_iterator_type &it):
                container_const_reference<compressed_matrix> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<compressed_matrix> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), itv_ (it.itv_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                const compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    ++ it_;
                else {
                    i_ = index1 () + 1;
                    if (rank_ == 1)
                        *this = m.find1 (rank_, i_, j_);
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                const compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    -- it_;
                else {
                    i_ = index1 () - 1;
                    if (rank_ == 1)
                        *this = m.find1 (rank_, i_, j_);
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*this) ().value_data () [it_ - (*this) ().index2_data ().begin ()];
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            const_iterator2 begin () const {
                const compressed_matrix &m = (*this) ();
                return m.find_first2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
            const_iterator2 end () const {
                const compressed_matrix &m = (*this) ();
                return m.find_last2 (1, index1 (), m.size2 ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return j_;
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<compressed_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_const_iterator_type itv_;
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find_last1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class iterator1:
            public container_reference<compressed_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename compressed_matrix::difference_type difference_type;
            typedef typename compressed_matrix::value_type value_type;
            typedef typename compressed_matrix::reference reference;
            typedef typename compressed_matrix::pointer pointer;
#endif
            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<compressed_matrix> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (compressed_matrix &m, int rank, size_type i, size_type j, const vector_iterator_type &itv, const iterator_type &it):
                container_reference<compressed_matrix> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    ++ it_;
                else {
                    i_ = index1 () + 1;
                    if (rank_ == 1)
                        *this = m.find1 (rank_, i_, j_);
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast1 ())
                    -- it_;
                else {
                    i_ = index1 () - 1;
                    if (rank_ == 1)
                        *this = m.find1 (rank_, i_, j_);
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*this) ().value_data () [it_ - (*this) ().index2_data ().begin ()];
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            iterator2 begin () const {
                compressed_matrix &m = (*this) ();
                return m.find_first2 (1, index1 (), 0); 
            }
            BOOST_UBLAS_INLINE
            iterator2 end () const {
                compressed_matrix &m = (*this) ();
                return m.find_last2 (1, index1 (), m.size2 ()); 
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<compressed_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_iterator_type itv_;
            iterator_type it_;

            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find_last1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class const_iterator2:
            public container_const_reference<compressed_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename compressed_matrix::difference_type difference_type;
            typedef typename compressed_matrix::value_type value_type;
            typedef typename compressed_matrix::const_reference reference;
            typedef typename compressed_matrix::const_pointer pointer;
#endif
            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<compressed_matrix> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const compressed_matrix &m, int rank, size_type i, size_type j, const vector_const_iterator_type itv, const const_iterator_type &it):
                container_const_reference<compressed_matrix> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<compressed_matrix> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), itv_ (it.itv_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                const compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    ++ it_;
                else {
                    j_ = index2 () + 1;
                    if (rank_ == 1)
                        *this = m.find2 (rank_, i_, j_);
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                const compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    -- it_;
                else {
                    j_ = index2 () - 1;
                    if (rank_ == 1)
                        *this = m.find2 (rank_, i_, j_);
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*this) ().value_data () [it_ - (*this) ().index2_data ().begin ()];
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            const_iterator1 begin () const {
                const compressed_matrix &m = (*this) ();
                return m.find_first1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
            const_iterator1 end () const {
                const compressed_matrix &m = (*this) ();
                return m.find_last1 (1, m.size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<compressed_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_const_iterator_type itv_;
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find_last2 (0, 0, size2_);
        }

#ifndef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        class iterator2:
            public container_reference<compressed_matrix>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename compressed_matrix::difference_type difference_type;
            typedef typename compressed_matrix::value_type value_type;
            typedef typename compressed_matrix::reference reference;
            typedef typename compressed_matrix::pointer pointer;
#endif
            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<compressed_matrix> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (compressed_matrix &m, int rank, size_type i, size_type j, const vector_iterator_type &itv, const iterator_type &it):
                container_reference<compressed_matrix> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    ++ it_;
                else {
                    j_ = index2 () + 1;
                    if (rank_ == 1)
                        *this = m.find2 (rank_, i_, j_);
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                compressed_matrix &m = (*this) ();
                if (rank_ == 1 && functor_type::fast2 ())
                    -- it_;
                else {
                    j_ = index2 ();
                    if (rank_ == 1)
                        *this = m.find2 (rank_, i_, j_);
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                    BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                    return (*this) ().value_data () [it_ - (*this) ().index2_data ().begin ()];
                } else {
                    return (*this) () (i_, j_);
                }
            }

            BOOST_UBLAS_INLINE
            iterator1 begin () const {
                compressed_matrix &m = (*this) ();
                return m.find_first1 (1, 0, index2 ()); 
            }
            BOOST_UBLAS_INLINE
            iterator1 end () const {
                compressed_matrix &m = (*this) ();
                return m.find_last1 (1, m.size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                if (rank_ == 1) {
                    return functor_type::index1 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                if (rank_ == 1) {
                    return functor_type::index2 (itv_ - (*this) ().index1_data ().begin (), (*it_) - 1);
                } else {
                    return j_;
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<compressed_matrix>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vector_iterator_type itv_;
            iterator_type it_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find_last2 (0, 0, size2_);
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        size_type size1_;
        size_type size2_;
        size_type non_zeros_;
        size_type filled1_;
        size_type filled2_;
        index_array_type index1_data_;
        index_array_type index2_data_;
        value_array_type value_data_;
        static value_type zero_;
    };

    template<class T, class F, class IA, class TA>
    typename compressed_matrix<T, F, IA, TA>::value_type compressed_matrix<T, F, IA, TA>::zero_ = 0;

#ifdef BOOST_UBLAS_USE_SPARSE_MATRIX_PROD_SPECIALIZATION

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template<class T1, class A1, class T2, class E2>
    struct matrix_vector_binary1_traits<T1, sparse_matrix<T1, column_major, A1>,
                                        T2, E2> {
        typedef sparse_tag storage_category;
        typedef column_major_tag orientation_category;
        typedef BOOST_UBLAS_TYPENAME promote_traits<T1, T2>::promote_type promote_type;
        typedef sparse_vector<promote_type> result_type;
    };
#endif

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_vector<typename promote_traits<typename E1::value_type,
                                          typename E2::value_type>::promote_type>
#else
    typename matrix_vector_binary1_traits<typename E1::value_type, E1,
                                          typename E2::value_type, E2>::result_type
#endif
    prod (const matrix_expression<E1> &e1,
          const vector_expression<E2> &e2,
          sparse_tag,
          column_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_vector<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type,
                                                                  BOOST_UBLAS_TYPENAME E2::value_type>::promote_type> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_vector_binary1_traits<BOOST_UBLAS_TYPENAME E1::value_type, E1,
                                                                  BOOST_UBLAS_TYPENAME E2::value_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        result_type r (e1 ().size2 ());
        r.clear ();
        typename E1::const_iterator2 it2e1 (e1 ().begin2 ());
        typename E1::const_iterator2 it2e1_end (e1 ().end2 ());
        while (it2e1 != it2e1_end) {
            typename matrix_column<const E1>::const_iterator it1e1 ((*it2e1).begin ());
            typename matrix_column<const E1>::const_iterator it1e1_end ((*it2e1).end ());
            typename E2::const_iterator ite2 (e2 ().begin ());
            typename E2::const_iterator ite2_end (e2 ().end ());
            size_type i = std::min (it1e1.index (), ite2.index ());
            while (it1e1 != it1e1_end && ite2 != ite2_end) {
                value_type t1 = i - it1e1.index () ? value_type () : *it1e1;
                value_type t2 = i - ite2.index () ? value_type () : *ite2;
                r (i) += t1 * t2;
                if (it1e1.index () <= i) 
                    ++ it1e1;
                if (ite2.index () <= i) 
                    ++ ite2;
                i = std::min (it1e1.index (), ite2.index ());
            }
            ++ it2e1;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        result_type r (e1 ().size2 ());
        r.clear ();
        typename E1::const_iterator2 it2e1 (e1 ().begin2 ());
        typename E1::const_iterator2 it2e1_end (e1 ().end2 ());
        while (it2e1 != it2e1_end) {
            typename E1::const_iterator1 it1e1 (it2e1.begin ());
            typename E1::const_iterator1 it1e1_end (it2e1.end ());
            typename E2::const_iterator ite2 (e2 ().begin ());
            typename E2::const_iterator ite2_end (e2 ().end ());
            size_type i = std::min (it1e1.index1 (), ite2.index ());
            while (it1e1 != it1e1_end && ite2 != ite2_end) {
                value_type t1 = i - it1e1.index1 () ? value_type () : *it1e1;
                value_type t2 = i - ite2.index () ? value_type () : *ite2;
                r (i) += t1 * t2;
                if (it1e1.index1 () <= i) 
                    ++ it1e1;
                if (ite2.index () <= i) 
                    ++ ite2;
                i = std::min (it1e1.index1 (), ite2.index ());
            }
            ++ it2e1;
        }
        return r;
#endif
    }

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_vector<typename type_traits<typename promote_traits<typename E1::value_type, 
                                                               typename E2::value_type>::promote_type>::precision_type>
#else
    typename matrix_vector_binary1_traits<typename type_traits<typename E1::value_type>::precision_type, E1, 
                                          typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
#endif
    prec_prod (const matrix_expression<E1> &e1, 
               const vector_expression<E2> &e2,
               sparse_tag,
               column_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_vector<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type, 
                                                                                                   BOOST_UBLAS_TYPENAME E2::value_type>::promote_type>::precision_type> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_vector_binary1_traits<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E1::value_type>::precision_type, E1, 
                                                                  BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E2::value_type>::precision_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        result_type r (e1 ().size2 ());       
        r.clear ();
        typename E1::const_iterator2 it2e1 (e1 ().begin2 ());
        typename E1::const_iterator2 it2e1_end (e1 ().end2 ());
        while (it2e1 != it2e1_end) {
            typename matrix_column<const E1>::const_iterator it1e1 ((*it2e1).begin ());
            typename matrix_column<const E1>::const_iterator it1e1_end ((*it2e1).end ());
            typename E2::const_iterator ite2 (e2 ().begin ());
            typename E2::const_iterator ite2_end (e2 ().end ());
            size_type i = std::min (it1e1.index (), ite2.index ());
            while (it1e1 != it1e1_end && ite2 != ite2_end) {
                value_type t1 = i - it1e1.index () ? value_type () : *it1e1;
                value_type t2 = i - ite2.index () ? value_type () : *ite2;
                r (i) += t1 * t2;
                if (it1e1.index () <= i) 
                    ++ it1e1;
                if (ite2.index () <= i) 
                    ++ ite2;
                i = std::min (it1e1.index (), ite2.index ());
            }
            ++ it2e1;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        result_type r (e1 ().size2 ());       
        r.clear ();
        typename E1::const_iterator2 it2e1 (e1 ().begin2 ());
        typename E1::const_iterator2 it2e1_end (e1 ().end2 ());
        while (it2e1 != it2e1_end) {
            typename E1::const_iterator1 it1e1 (it2e1.begin ());
            typename E1::const_iterator1 it1e1_end (it2e1.end ());
            typename E2::const_iterator ite2 (e2 ().begin ());
            typename E2::const_iterator ite2_end (e2 ().end ());
            size_type i = std::min (it1e1.index1 (), ite2.index ());
            while (it1e1 != it1e1_end && ite2 != ite2_end) {
                value_type t1 = i - it1e1.index1 () ? value_type () : *it1e1;
                value_type t2 = i - ite2.index () ? value_type () : *ite2;
                r (i) += t1 * t2;
                if (it1e1.index1 () <= i) 
                    ++ it1e1;
                if (ite2.index () <= i) 
                    ++ ite2;
                i = std::min (it1e1.index1 (), ite2.index ());
            }
            ++ it2e1;
        }
        return r;
#endif
    }

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template<class T1, class E1, class T2, class A2>
    struct matrix_vector_binary2_traits<T1, E1,
                                        T2, sparse_matrix<T2, column_major, A2> > {
        typedef sparse_tag storage_category;
        typedef row_major_tag orientation_category;
        typedef BOOST_UBLAS_TYPENAME promote_traits<T1, T2>::promote_type promote_type;
        typedef sparse_vector<promote_type> result_type;
    };
#endif

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_vector<typename promote_traits<typename E1::value_type, 
                                          typename E2::value_type>::promote_type>
#else
    typename matrix_vector_binary2_traits<typename E1::value_type, E1, 
                                          typename E2::value_type, E2>::result_type
#endif
    prod (const vector_expression<E1> &e1, 
          const matrix_expression<E2> &e2, 
          sparse_tag,
          row_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_vector<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type, 
                                                                  BOOST_UBLAS_TYPENAME E2::value_type>::promote_type> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_vector_binary2_traits<BOOST_UBLAS_TYPENAME E1::value_type, E1, 
                                                                  BOOST_UBLAS_TYPENAME E2::value_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size () == e2 ().size1 (), bad_size ());
        result_type r (e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator1 it1e2 (e2 ().begin1 ());
        typename E2::const_iterator1 it1e2_end (e2 ().end1 ());
        while (it1e2 != it1e2_end) {
            typename matrix_row<const E2>::const_iterator it2e2 ((*it1e2).begin ());
            typename matrix_row<const E2>::const_iterator it2e2_end ((*it1e2).end ());
            typename E1::const_iterator ite1 (e1 ().begin ());
            typename E1::const_iterator ite1_end (e1 ().end ());
            size_type i = std::min (it2e2.index (), ite1.index ());
            while (it2e2 != it2e2_end && ite1 != ite1_end) {
                value_type t2 = i - it2e2.index () ? value_type () : *it2e2;
                value_type t1 = i - ite1.index () ? value_type () : *ite1;
                r (i) += t2 * t1;
                if (it2e2.index () <= i) 
                    ++ it2e2;
                if (ite1.index () <= i) 
                    ++ ite1;
                i = std::min (it2e2.index (), ite1.index ());
            }
            ++ it1e2;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size () == e2 ().size1 (), bad_size ());
        result_type r (e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator1 it1e2 (e2 ().begin1 ());
        typename E2::const_iterator1 it1e2_end (e2 ().end1 ());
        while (it1e2 != it1e2_end) {
            typename E2::const_iterator2 it2e2 (it1e2.begin ());
            typename E2::const_iterator2 it2e2_end (it1e2.end ());
            typename E1::const_iterator ite1 (e1 ().begin ());
            typename E1::const_iterator ite1_end (e1 ().end ());
            size_type i = std::min (it2e2.index2 (), ite1.index ());
            while (it2e2 != it2e2_end && ite1 != ite1_end) {
                value_type t2 = i - it2e2.index2 () ? value_type () : *it2e2;
                value_type t1 = i - ite1.index () ? value_type () : *ite1;
                r (i) += t2 * t1;
                if (it2e2.index2 () <= i) 
                    ++ it2e2;
                if (ite1.index () <= i) 
                    ++ ite1;
                i = std::min (it2e2.index2 (), ite1.index ());
            }
            ++ it1e2;
        }
        return r;
#endif
    }

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_vector<typename type_traits<typename promote_traits<typename E1::value_type, 
                                                               typename E2::value_type>::promote_type>::precision_type>
#else
    typename matrix_vector_binary2_traits<typename type_traits<typename E1::value_type>::precision_type, E1, 
                                          typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
#endif
    prec_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2, 
               sparse_tag,
               row_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_vector<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type, 
                                                                                             BOOST_UBLAS_TYPENAME E2::value_type>::promote_type>::precision_type> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_vector_binary2_traits<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E1::value_type>::precision_type, E1, 
                                                                  BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E2::value_type>::precision_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size () == e2 ().size1 (), bad_size ());
        result_type r (e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator1 it1e2 (e2 ().begin1 ());
        typename E2::const_iterator1 it1e2_end (e2 ().end1 ());
        while (it1e2 != it1e2_end) {
            typename matrix_row<const E2>::const_iterator it2e2 ((*it1e2).begin ());
            typename matrix_row<const E2>::const_iterator it2e2_end ((*it1e2).end ());
            typename E1::const_iterator ite1 (e1 ().begin ());
            typename E1::const_iterator ite1_end (e1 ().end ());
            size_type i = std::min (it2e2.index (), ite1.index ());
            while (it2e2 != it2e2_end && ite1 != ite1_end) {
                value_type t2 = i - it2e2.index () ? value_type () : *it2e2;
                value_type t1 = i - ite1.index () ? value_type () : *ite1;
                r (i) += t2 * t1;
                if (it2e2.index () <= i) 
                    ++ it2e2;
                if (ite1.index () <= i) 
                    ++ ite1;
                i = std::min (it2e2.index (), ite1.index ());
            }
            ++ it1e2;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size () == e2 ().size1 (), bad_size ());
        result_type r (e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator1 it1e2 (e2 ().begin1 ());
        typename E2::const_iterator1 it1e2_end (e2 ().end1 ());
        while (it1e2 != it1e2_end) {
            typename E2::const_iterator2 it2e2 (it1e2.begin ());
            typename E2::const_iterator2 it2e2_end (it1e2.end ());
            typename E1::const_iterator ite1 (e1 ().begin ());
            typename E1::const_iterator ite1_end (e1 ().end ());
            size_type i = std::min (it2e2.index2 (), ite1.index ());
            while (it2e2 != it2e2_end && ite1 != ite1_end) {
                value_type t2 = i - it2e2.index2 () ? value_type () : *it2e2;
                value_type t1 = i - ite1.index () ? value_type () : *ite1;
                r (i) += t2 * t1;
                if (it2e2.index2 () <= i) 
                    ++ it2e2;
                if (ite1.index () <= i) 
                    ++ ite1;
                i = std::min (it2e2.index2 (), ite1.index ());
            }
            ++ it1e2;
        }
        return r;
#endif
    }

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template<class T1, class A1, class T2, class A2>
    struct matrix_matrix_binary_traits<T1, sparse_matrix<T1, column_major, A1> ,
                                       T2, sparse_matrix<T2, column_major, A2> > {
        typedef sparse_tag storage_category;
        typedef column_major_tag orientation_category;
        typedef BOOST_UBLAS_TYPENAME promote_traits<T1, T2>::promote_type promote_type;
        typedef sparse_matrix<promote_type, row_major> result_type;
    };
#endif

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_matrix<typename promote_traits<typename E1::value_type,
                                          typename E2::value_type>::promote_type, row_major>
#else
    typename matrix_matrix_binary_traits<typename E1::value_type, E1,
                                         typename E2::value_type, E2>::result_type
#endif
    prod (const matrix_expression<E1> &e1,
          const matrix_expression<E2> &e2,
          sparse_tag,
          column_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_matrix<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type,
                                                                  BOOST_UBLAS_TYPENAME E2::value_type>::promote_type, row_major> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_matrix_binary_traits<BOOST_UBLAS_TYPENAME E1::value_type, E1,
                                                                 BOOST_UBLAS_TYPENAME E2::value_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator2 it2e2 (e2 ().begin2 ());
        typename E2::const_iterator2 it2e2_end (e2 ().end2 ());
        while (it2e2 != it2e2_end) {
            typename matrix_column<const E2>::const_iterator it2e1 ((*it2e2).begin ());
            typename matrix_column<const E2>::const_iterator it2e1_end ((*it2e2).end ());
            while (it2e1 != it2e1_end) {
                value_type t2 = *it2e1;
                typename matrix_column<const E1>::const_iterator it1e (column (e1 (), it2e1.index ()).begin ());
                typename matrix_column<const E1>::const_iterator it1e_end (column (e1 (), it2e1.index ()).end ());
                while (it1e != it1e_end) {
                    // FIXME: wrong indices.
                    // r (it1e2.index (), it2e1.index ()) += *it1e2 * t2;
                    r (it1e.index (), it2e2.index ()) += *it1e * t2;
                    ++ it1e;
                }
                ++ it2e1;
            }
            ++ it2e2;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator2 it2e2 (e2 ().begin2 ());
        typename E2::const_iterator2 it2e2_end (e2 ().end2 ());
        while (it2e2 != it2e2_end) {
            typename E2::const_iterator1 it2e1 (it2e2.begin ());
            typename E2::const_iterator1 it2e1_end (it2e2.end ());
            while (it2e1 != it2e1_end) {
                value_type t2 = *it2e1;
                typename E1::const_iterator1 it1e1 (e1 ().find_first1 (1, 0, it2e1.index1 ()));
                typename E1::const_iterator1 it1e1_end (e1 ().find_last1 (1, e1 ().size1 (), it2e1.index1 ()));
                while (it1e1 != it1e1_end) {
                    BOOST_UBLAS_CHECK (it1e1.index2 () == it2e1.index1 (), internal_logic ());
                    // FIXME: wrong indices.
                    // r (it1e2.index2 (), it2e1.index2 ()) += *it1e2 * t2;
                    r (it1e1.index1 (), it2e1.index2 ()) += *it1e1 * t2;
                    ++ it1e1;
                }
                ++ it2e1;
            }
            ++ it2e2;
        }
        return r;
#endif
    }

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_matrix<typename type_traits<typename promote_traits<typename E1::value_type,
                                                               typename E2::value_type>::promote_type>::precision_type, row_major>
#else
    typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
                                         typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
#endif
    prec_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               sparse_tag,
               column_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_matrix<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type,
                                                                                                   BOOST_UBLAS_TYPENAME E2::value_type>::promote_type>::precision_type, row_major> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_matrix_binary_traits<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E1::value_type>::precision_type, E1,
                                                                 BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E2::value_type>::precision_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator2 it2e2 (e2 ().begin2 ());
        typename E2::const_iterator2 it2e2_end (e2 ().end2 ());
        while (it2e2 != it2e2_end) {
            typename matrix_column<const E2>::const_iterator it2e1 ((*it2e2).begin ());
            typename matrix_column<const E2>::const_iterator it2e1_end ((*it2e2).end ());
            while (it2e1 != it2e1_end) {
                value_type t2 = *it2e1;
                typename matrix_column<const E1>::const_iterator it1e (column (e1 (), it2e1.index ()).begin ());
                typename matrix_column<const E1>::const_iterator it1e_end (column (e1 (), it2e1.index ()).end ());
                while (it1e != it1e_end) {
                    // FIXME: wrong indices.
                    // r (it1e2.index (), it2e1.index ()) += *it1e2 * t2;
                    r (it1e.index (), it2e2.index ()) += *it1e * t2;
                    ++ it1e;
                }
                ++ it2e1;
            }
            ++ it2e2;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E2::const_iterator2 it2e2 (e2 ().begin2 ());
        typename E2::const_iterator2 it2e2_end (e2 ().end2 ());
        while (it2e2 != it2e2_end) {
            typename E2::const_iterator1 it2e1 (it2e2.begin ());
            typename E2::const_iterator1 it2e1_end (it2e2.end ());
            while (it2e1 != it2e1_end) {
                value_type t2 = *it2e1;
                typename E1::const_iterator1 it1e1 (e1 ().find_first1 (1, 0, it2e1.index1 ()));
                typename E1::const_iterator1 it1e1_end (e1 ().find_last1 (1, e1 ().size1 (), it2e1.index1 ()));
                while (it1e1 != it1e1_end) {
                    BOOST_UBLAS_CHECK (it1e1.index2 () == it2e1.index1 (), internal_logic ());
                    // FIXME: wrong indices.
                    // r (it1e2.index2 (), it2e1.index2 ()) += *it1e2 * t2;
                    r (it1e1.index1 (), it2e1.index2 ()) += *it1e1 * t2;
                    ++ it1e1;
                }
                ++ it2e1;
            }
            ++ it2e2;
        }
        return r;
#endif
    }

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template<class T1, class A1, class T2, class A2>
    struct matrix_matrix_binary_traits<T1, sparse_matrix<T1, row_major, A1> ,
                                       T2, sparse_matrix<T2, row_major, A2> > {
        typedef sparse_tag storage_category;
        typedef row_major_tag orientation_category;
        typedef BOOST_UBLAS_TYPENAME promote_traits<T1, T2>::promote_type promote_type;
        typedef sparse_matrix<promote_type, column_major> result_type;
    };
#endif

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_matrix<typename promote_traits<typename E1::value_type,
                                          typename E2::value_type>::promote_type, column_major>
#else
    typename matrix_matrix_binary_traits<typename E1::value_type, E1,
                                         typename E2::value_type, E2>::result_type
#endif
    prod (const matrix_expression<E1> &e1,
          const matrix_expression<E2> &e2,
          sparse_tag,
          row_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_matrix<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type,
                                                                  BOOST_UBLAS_TYPENAME E2::value_type>::promote_type, column_major> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_matrix_binary_traits<BOOST_UBLAS_TYPENAME E1::value_type, E1,
                                                                 BOOST_UBLAS_TYPENAME E2::value_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E1::const_iterator1 it1e1 (e1 ().begin1 ());
        typename E1::const_iterator1 it1e1_end (e1 ().end1 ());
        while (it1e1 != it1e1_end) {
            typename matrix_row<const E1>::const_iterator it1e2 ((*it1e1).begin ());
            typename matrix_row<const E1>::const_iterator it1e2_end ((*it1e1).end ());
            while (it1e2 != it1e2_end) {
                value_type t1 = *it1e2;
                typename matrix_row<const E2>::const_iterator it2e (row (e2 (), it1e2.index ()).begin ());
                typename matrix_row<const E2>::const_iterator it2e_end (row (e2 (), it1e2.index ()).end ());
                while (it2e != it2e_end) {
                    // FIXME: wrong indices.
                    // r (it2e1.index (), it1e2.index ()) += t1 * *it2e1;
                    r (it1e1.index (), it2e.index ()) += t1 * *it2e;
                    ++ it2e;
                }
                ++ it1e2;
            }
            ++ it1e1;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E1::const_iterator1 it1e1 (e1 ().begin1 ());
        typename E1::const_iterator1 it1e1_end (e1 ().end1 ());
        while (it1e1 != it1e1_end) {
            typename E1::const_iterator2 it1e2 (it1e1.begin ());
            typename E1::const_iterator2 it1e2_end (it1e1.end ());
            while (it1e2 != it1e2_end) {
                value_type t1 = *it1e2;
                typename E2::const_iterator2 it2e2 (e2 ().find_first2 (1, it1e2.index2 (), 0));
                typename E2::const_iterator2 it2e2_end (e2 ().find_last2 (1, it1e2.index2 (), e2 ().size2 ()));
                while (it2e2 != it2e2_end) {
                    BOOST_UBLAS_CHECK (it1e2.index2 () == it2e2.index1 (), internal_logic ());
                    // FIXME: wrong indices.
                    // r (it2e1.index1 (), it1e2.index1 ()) += t1 * *it2e1;
                    r (it1e2.index1 (), it2e2.index2 ()) += t1 * *it2e2;
                    ++ it2e2;
                }
                ++ it1e2;
            }
            ++ it1e1;
        }
        return r;
#endif
    }

    template<class E1, class E2>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    sparse_matrix<typename type_traits<typename promote_traits<typename E1::value_type,
                                                               typename E2::value_type>::promote_type>::precision_type, column_major>
#else
    typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
                                         typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
#endif
    prec_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               sparse_tag,
               row_major_tag) {
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typedef sparse_matrix<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type,
                                                                                             BOOST_UBLAS_TYPENAME E2::value_type>::promote_type>::precision_type, column_major> result_type;
#else
        typedef BOOST_UBLAS_TYPENAME matrix_matrix_binary_traits<BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E1::value_type>::precision_type, E1,
                                                                 BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME E2::value_type>::precision_type, E2>::result_type result_type;
#endif
        typedef BOOST_UBLAS_TYPENAME result_type::size_type size_type;
        typedef BOOST_UBLAS_TYPENAME result_type::value_type value_type;

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E1::const_iterator1 it1e1 (e1 ().begin1 ());
        typename E1::const_iterator1 it1e1_end (e1 ().end1 ());
        while (it1e1 != it1e1_end) {
            typename matrix_row<const E1>::const_iterator it1e2 ((*it1e1).begin ());
            typename matrix_row<const E1>::const_iterator it1e2_end ((*it1e1).end ());
            while (it1e2 != it1e2_end) {
                value_type t1 = *it1e2;
                typename matrix_row<const E2>::const_iterator it2e (row (e2 (), it1e2.index ()).begin ());
                typename matrix_row<const E2>::const_iterator it2e_end (row (e2 (), it1e2.index ()).end ());
                while (it2e != it2e_end) {
                    // FIXME: wrong indices.
                    // r (it2e1.index (), it1e2.index ()) += t1 * *it2e1;
                    r (it1e1.index (), it2e.index ()) += t1 * *it2e;
                    ++ it2e;
                }
                ++ it1e2;
            }
            ++ it1e1;
        }
        return r;
#else
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        result_type r (e1 ().size1 (), e2 ().size2 ());
        r.clear ();
        typename E1::const_iterator1 it1e1 (e1 ().begin1 ());
        typename E1::const_iterator1 it1e1_end (e1 ().end1 ());
        while (it1e1 != it1e1_end) {
            typename E1::const_iterator2 it1e2 (it1e1.begin ());
            typename E1::const_iterator2 it1e2_end (it1e1.end ());
            while (it1e2 != it1e2_end) {
                value_type t1 = *it1e2;
                typename E2::const_iterator2 it2e2 (e2 ().find_first2 (1, it1e2.index2 (), 0));
                typename E2::const_iterator2 it2e2_end (e2 ().find_last2 (1, it1e2.index2 (), e2 ().size2 ()));
                while (it2e2 != it2e2_end) {
                    BOOST_UBLAS_CHECK (it1e2.index2 () == it2e2.index1 (), internal_logic ());
                    // FIXME: wrong indices.
                    // r (it2e1.index1 (), it1e2.index1 ()) += t1 * *it2e1;
                    r (it1e2.index1 (), it2e2.index2 ()) += t1 * *it2e2;
                    ++ it2e2;
                }
                ++ it1e2;
            }
            ++ it1e1;
        }
        return r;
#endif
    }

#endif

}}}

#endif


