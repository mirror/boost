#ifndef TEST3_H
#define TEST3_H

namespace ublas = boost::numeric::ublas;

template<class V>
void initialize_vector (V &v) {
    int size = v.size ();
    for (int i = 0; i < size; i += 2)
        v [i] = i + 1.f;
}

template<class M>
void initialize_matrix (M &m) {
    int size1 = m.size1 ();
    int size2 = m.size2 ();
    for (int i = 0; i < size1; i += 2)
        for (int j = 0; j < size2; j += 2)
            m (i, j) = i * size1 + j + 1.f;
}

void test_vector ();

void test_matrix_vector ();

void test_matrix ();

// #define USE_RANGE
// #define USE_SLICE

#define USE_MAP_ARRAY
// #define USE_STD_MAP

#define USE_SPARSE_VECTOR
// #define USE_COMPRESSED_VECTOR

#define USE_SPARSE_MATRIX
// #define USE_SPARSE_VECTOR_OF_SPARSE_VECTOR
// #define USE_COMPRESSED_MATRIX

#endif




