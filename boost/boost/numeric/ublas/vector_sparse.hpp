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

#ifndef BOOST_UBLAS_VECTOR_SPARSE_H
#define BOOST_UBLAS_VECTOR_SPARSE_H

#include <boost/numeric/ublas/config.hpp>
#include <boost/numeric/ublas/storage_sparse.hpp>
#include <boost/numeric/ublas/vector.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    // Array based sparse vector class
    template<class T, class A>
    class sparse_vector:
        public vector_expression<sparse_vector<T, A> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<sparse_vector<T, A> >::operator ();
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
        typedef A array_type;
        typedef const A const_array_type;
        typedef const sparse_vector<T, A> const_self_type;
        typedef sparse_vector<T, A> self_type;
        typedef const vector_const_reference<const_self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef typename A::const_iterator const_iterator_type;
        typedef typename A::iterator iterator_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        sparse_vector ():
            size_ (0), non_zeros_ (0), data_ () {}
        BOOST_UBLAS_INLINE
        sparse_vector (size_type size, size_type non_zeros = 0):
            size_ (size), non_zeros_ (non_zeros), data_ () {
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            non_zeros_ = std::max (non_zeros_, size_type (1));
            map_traits<array_type>::reserve (data_, non_zeros_);
#endif
        }
        BOOST_UBLAS_INLINE
        sparse_vector (const sparse_vector &v):
            size_ (v.size_), non_zeros_ (v.non_zeros_), data_ (v.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            size_ (ae ().size ()), non_zeros_ (non_zeros), data_ () {
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            non_zeros_ = std::max (non_zeros_, size_type (1));
            map_traits<array_type>::reserve (data_, non_zeros_);
#endif
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
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
        void resize (size_type size, size_type non_zeros = 0) {
            size_ = size;
            non_zeros_ = non_zeros;
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            non_zeros_ = std::max (non_zeros_, size_type (1));
            map_traits<array_type>::reserve (data (), non_zeros_);
#endif
            data ().clear ();
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            const_iterator_type it (data ().find (i));
            if (it == data ().end () || (*it).first != i)
                return zero_;
            return (*it).second;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () [i];
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        sparse_vector &operator = (const sparse_vector &v) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &v, external_logic ());
            if (this != &v) {
                BOOST_UBLAS_CHECK (size_ == v.size_, bad_size ());
                size_ = v.size_;
                non_zeros_ = v.non_zeros_;
                data () = v.data ();
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        sparse_vector &assign_temporary (sparse_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector &operator = (const vector_expression<AE> &ae) {
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
        sparse_vector &reset (const vector_expression<AE> &ae) {
            self_type temporary (ae, non_zeros_);
            resize (temporary.size (), non_zeros_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector &operator += (const vector_expression<AE> &ae) {
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
        sparse_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        sparse_vector &operator -= (const vector_expression<AE> &ae) {
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
        sparse_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        sparse_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        sparse_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (sparse_vector &v) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &v, external_logic ());
            if (this != &v) {
                // Precondition for container relaxed as requested during review.
                // BOOST_UBLAS_CHECK (size_ == v.size_, bad_size ());
                // BOOST_UBLAS_CHECK (non_zeros_ == v.non_zeros_, bad_size ());
                std::swap (size_, v.size_);
                std::swap (non_zeros_, v.non_zeros_);
                data ().swap (v.data ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (sparse_vector &v1, sparse_vector &v2) {
            v1.swap (v2);
        }
#endif

        // Element insertion and erasure
        BOOST_UBLAS_INLINE
        void insert (size_type i, const_reference t) {
#ifdef BOOST_UBLAS_CHECK_FOR_ZERO
            if (t == value_type ())
                return;
#endif
            BOOST_UBLAS_CHECK (data ().find (i) == data ().end (), bad_index ());
            data ().insert (data ().end (), std::pair<size_type, value_type> (i, t));
        }
        BOOST_UBLAS_INLINE
        void erase (size_type i) {
            // FIXME: shouldn't we use const_iterator_type here?
            iterator_type it = data ().find (i);
            if (it == data ().end ())
                return;
            data ().erase (it);
        }
        BOOST_UBLAS_INLINE
        void clear () {
            data ().clear ();
        }

        class const_iterator;
        class iterator;

        // Element lookup
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
            return const_iterator (*this, data ().lower_bound (i));
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator find (size_type i) {
            return iterator (*this, data ().lower_bound (i));
        }
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            return find (i);
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            return find (i);
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            return find (i);
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            return find (i);
        }

        // Iterators simply are pointers.

        class const_iterator:
            public container_const_reference<sparse_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename sparse_vector::difference_type difference_type;
            typedef typename sparse_vector::value_type value_type;
            typedef typename sparse_vector::const_reference reference;
            typedef typename sparse_vector::const_pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<sparse_vector> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const sparse_vector &v, const const_iterator_type &it):
                container_const_reference<sparse_vector> (v), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<sparse_vector> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename sparse_vector::iterator &it):
                container_const_reference<sparse_vector> (it ()), it_ (it.it_) {}
#endif
            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*it_).second;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return (*it_).first;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<sparse_vector>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_iterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size_);
        }

        class iterator:
            public container_reference<sparse_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename sparse_vector::difference_type difference_type;
            typedef typename sparse_vector::value_type value_type;
            typedef typename sparse_vector::reference reference;
            typedef typename sparse_vector::pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<sparse_vector> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (sparse_vector &v, const iterator_type &it):
                container_reference<sparse_vector> (v), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
#ifndef BOOST_UBLAS_STRICT_SPARSE_ELEMENT_ASSIGN
                return (*it_).second;
#else
                return map_traits<array_type>::make_reference ((*this) ().data (), it_);
#endif
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return (*it_).first;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<sparse_vector>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size_);
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        size_type size_;
        size_type non_zeros_;
        array_type data_;
        static value_type zero_;
    };

    template<class T, class A>
    typename sparse_vector<T, A>::value_type sparse_vector<T, A>::zero_ = 0;

    // Array based sparse vector class
    template<class T, class IA, class TA>
    class compressed_vector:
        public vector_expression<compressed_vector<T, IA, TA> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<compressed_vector<T, IA, TA> >::operator ();
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
        typedef const compressed_vector<T, IA, TA> const_self_type;
        typedef compressed_vector<T, IA, TA> self_type;
        typedef const vector_const_reference<const_self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef typename IA::const_iterator const_iterator_type;
        typedef typename IA::iterator iterator_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        compressed_vector (): 
            size_ (0), non_zeros_ (0), filled_ (0),
            index_data_ (), value_data_ () {}
        BOOST_UBLAS_INLINE
        compressed_vector (size_type size, size_type non_zeros = 0):
            size_ (size), non_zeros_ (non_zeros), filled_ (0),
            index_data_ (non_zeros), value_data_ (non_zeros) {}
        BOOST_UBLAS_INLINE
        compressed_vector (const compressed_vector &v): 
            size_ (v.size_), non_zeros_ (v.non_zeros_), filled_ (v.filled_),
            index_data_ (v.index_data_), value_data_ (v.value_data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            size_ (ae ().size ()), non_zeros_ (non_zeros), filled_ (0),
            index_data_ (non_zeros), value_data_ (non_zeros) { 
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const { 
            return size_; 
        }
        BOOST_UBLAS_INLINE
        size_type non_zeros () const {
            return non_zeros_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index_data () const {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        index_array_type &index_data () {
            return index_data_;
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
        void resize (size_type size, size_type non_zeros = 0) {
            size_ = size;
            non_zeros_ = non_zeros;
            filled_ = 0;
            index_data ().resize (non_zeros);
            value_data ().resize (non_zeros);
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            const_iterator_type it (std::lower_bound (index_data ().begin (), index_data ().begin () + filled_, i + 1, std::less<size_type> ()));
            if (it == index_data ().begin () + filled_ || *it != i + 1)
                return zero_;
            return value_data () [it - index_data ().begin ()];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            iterator_type it (std::lower_bound (index_data ().begin (), index_data ().begin () + filled_, i + 1, std::less<size_type> ()));
            if (it == index_data ().begin () + filled_ || *it != i + 1) 
                insert (i, value_type ());
            return value_data () [it - index_data ().begin ()];
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const { 
            return (*this) (i); 
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) { 
            return (*this) (i); 
        }

        // Assignment
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const compressed_vector &v) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &v, external_logic ());
            if (this != &v) {
                BOOST_UBLAS_CHECK (size_ == v.size_, bad_size ());
                size_ = v.size_;
                non_zeros_ = v.non_zeros_;
                filled_ = v.filled_;
                index_data () = v.index_data ();
                value_data () = v.value_data ();
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        compressed_vector &assign_temporary (compressed_vector &v) { 
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const vector_expression<AE> &ae) {
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
        compressed_vector &reset (const vector_expression<AE> &ae) {
            self_type temporary (ae, non_zeros_);
            resize (temporary.size (), non_zeros_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator += (const vector_expression<AE> &ae) {
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
        compressed_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator -= (const vector_expression<AE> &ae) {
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
        compressed_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (compressed_vector &v) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &v, external_logic ());
            if (this != &v) {
                // Precondition for container relaxed as requested during review.
                // BOOST_UBLAS_CHECK (size_ == v.size_, bad_size ());
                // BOOST_UBLAS_CHECK (non_zeros_ == v.non_zeros_, bad_size ());
                std::swap (size_, v.size_);
                std::swap (non_zeros_, v.non_zeros_);
                std::swap (filled_, v.filled_);
                index_data ().swap (v.index_data ());
                value_data ().swap (v.value_data ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (compressed_vector &v1, compressed_vector &v2) {
            v1.swap (v2);
        }
#endif

        // Element insertion and erasure
        BOOST_UBLAS_INLINE
        void insert (size_type i, const_reference t) {
// FIXME: Doesn't work if the first element is zero.
// #ifdef BOOST_UBLAS_CHECK_FOR_ZERO
//             if (t == value_type ())
//                 return;
// #endif
            BOOST_UBLAS_CHECK (filled_ == 0 || index_data () [filled_ - 1] < i + 1, external_logic ()); 
            index_data () [filled_] = i + 1;
            value_data () [filled_] = t;
            ++ filled_;
        }
        BOOST_UBLAS_INLINE
        void erase (size_type i) {
            BOOST_UBLAS_CHECK (filled_ > 0 && index_data () [filled_ - 1] == i + 1, external_logic ());
            -- filled_;
        }
        BOOST_UBLAS_INLINE
        void clear () {
            filled_ = 0;
        }

        class const_iterator;
        class iterator;

        // Element lookup
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {            
            return const_iterator (*this, std::lower_bound (index_data ().begin (), index_data ().begin () + filled_, i + 1, std::less<size_type> ()));
        }
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        iterator find (size_type i) {
            return iterator (*this, std::lower_bound (index_data ().begin (), index_data ().begin () + filled_, i + 1, std::less<size_type> ()));
        }
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            return find (i);
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            return find (i);
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            return find (i);
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            return find (i);
        }

        // Iterators simply are pointers.

        class const_iterator:
            public container_const_reference<compressed_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename compressed_vector::difference_type difference_type;
            typedef typename compressed_vector::value_type value_type;
            typedef typename compressed_vector::const_reference reference;
            typedef typename compressed_vector::const_pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<compressed_vector> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const compressed_vector &v, const const_iterator_type &it):
                container_const_reference<compressed_vector> (v), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<compressed_vector> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename compressed_vector::iterator &it):
                container_const_reference<compressed_vector> (it ()), it_ (it.it_) {}
#endif
            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data () [it_ - (*this) ().index_data ().begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return (*it_) - 1;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<compressed_vector>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_iterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size_);
        }

        class iterator:
            public container_reference<compressed_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef sparse_bidirectional_iterator_tag iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename compressed_vector::difference_type difference_type;
            typedef typename compressed_vector::value_type value_type;
            typedef typename compressed_vector::reference reference;
            typedef typename compressed_vector::pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<compressed_vector> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (compressed_vector &v, const iterator_type &it):
                container_reference<compressed_vector> (v), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data () [it_ - (*this) ().index_data ().begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return (*it_) - 1;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<compressed_vector>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size_);
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        size_type size_;
        size_type non_zeros_;
        size_type filled_;
        index_array_type index_data_;
        value_array_type value_data_;
        static value_type zero_;
    };

    template<class T, class IA, class TA>
    typename compressed_vector<T, IA, TA>::value_type compressed_vector<T, IA, TA>::zero_ = 0;

}}}

#endif


