/*
 * Copyright (c) 2004 Michael Stevens
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Initialise test values in vector/matrix
 */

template<class V>
void initialize_vector (V &v) {
    typename V::size_type size = v.size ();
    for (typename V::size_type i = 0; i < size; ++ i)
        v [i] = i + 1.f;
}

template<class M>
void initialize_matrix (M &m) {
    typename M::size_type size1 = m.size1 ();
    typename M::size_type size2 = m.size2 ();
    for (typename M::size_type i = 0; i < size1; ++ i)
        for (typename M::size_type j = 0; j < size2; ++ j)
            m (i, j) = i * size1 + j + 1.f;
}
