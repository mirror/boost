#ifndef TEST1_H
#define TEST1_H

namespace ublas = boost::numeric::ublas;

template<class V>
void initialize_vector (V &v) {
    int size = v.size ();
    for (int i = 0; i < size; ++ i)
        v [i] = i + 1.f;
}

template<class M>
void initialize_matrix (M &m) {
    int size1 = m.size1 ();
    int size2 = m.size2 ();
    for (int i = 0; i < size1; ++ i)
        for (int j = 0; j < size2; ++ j)
            m (i, j) = i * size1 + j + 1.f;
}

void test_vector ();

void test_matrix_vector ();

void test_matrix ();

// #define USE_RANGE
// #define USE_SLICE

// #define USE_BOUNDED_ARRAY
#define USE_UNBOUNDED_ARRAY
// #define USE_STD_VECTOR

#define USE_MATRIX
// #define USE_VECTOR_OF_VECTOR

#endif 


