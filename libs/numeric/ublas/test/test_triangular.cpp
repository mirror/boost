#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>


#include <sys/times.h>
#include <sys/time.h>
#include <sys/stat.h>


namespace ublas  = boost::numeric::ublas;

template<class mat, class vec>
double diff(const mat& A, const vec& x, const vec& b) {
  vec temp(prod(A, x) - b);
  double result = 0;
  for (typename vec::size_type i=0; i<temp.size(); ++i) {
    result += temp(i)*temp(i);
  }
  return sqrt(result);
}

template<class mat, class vec>
double diff(const vec& x, const mat& A, const vec& b) {
  return diff(trans(A), x, b);
}

namespace ublas  = boost::numeric::ublas;


int main() {
  const int n=10000;
#if 1
  ublas::compressed_matrix<double, ublas::row_major>     mat_row_upp(n, n);
  ublas::compressed_matrix<double, ublas::column_major>  mat_col_upp(n, n);
  ublas::compressed_matrix<double, ublas::row_major>     mat_row_low(n, n);
  ublas::compressed_matrix<double, ublas::column_major>  mat_col_low(n, n);
#else
  ublas::matrix<double, ublas::row_major>     mat_row_upp(n, n, 0);
  ublas::matrix<double, ublas::column_major>  mat_col_upp(n, n, 0);
  ublas::matrix<double, ublas::row_major>     mat_row_low(n, n, 0);
  ublas::matrix<double, ublas::column_major>  mat_col_low(n, n, 0);
#endif
  ublas::vector<double>  b(n, 1);

  std::cerr << "Constructing..." << std::endl;
  for (int i=0; i<n; ++i) {
    b(i) = rand() % 10;
    double main = -10 + rand() % 20 ;
    if (main == 0) main+=1;
    double side = -10 + rand() % 20 ;
    if (i-1>=0) {
      mat_row_low(i, i-1) = side;
    }
    mat_row_low(i, i) = main;

    mat_col_low(i, i) = main;
    if (i+1<n) {
      mat_col_low(i+1, i) = side;
    }

    mat_row_upp(i, i) = main;
    if (i+1<n) {
      mat_row_upp(i, i+1) = side;
    }

    if (i-1>=0) {
      mat_col_upp(i-1, i) = side;
    }
    mat_col_upp(i, i) = main;
  }

  std::cerr << "Starting..." << std::endl;
  {
    clock_t start = clock();
    ublas::vector<double>  x(b);
    ublas::inplace_solve(mat_col_low,  x, ublas::lower_tag());
    std::cerr << "Col_low x: " << clock()-start << std::endl;
    std::cerr << "delta: " << diff(mat_col_low, x, b) << "\n";
  }
  {
    clock_t start = clock();
    ublas::vector<double>  x(b);
    ublas::inplace_solve(mat_row_low, x, ublas::lower_tag());
    std::cerr << "Row_low x: " << clock()-start << std::endl;
    std::cerr << "delta: " << diff(mat_row_low, x, b) << "\n";
  }

  {
    clock_t start = clock();
    ublas::vector<double>  x(b);
    ublas::inplace_solve(mat_col_upp,  x, ublas::upper_tag());
    std::cerr << "col_upp x: " << clock()-start << std::endl;
    std::cerr << "delta: " << diff(mat_col_upp, x, b) << "\n";
  }
  {
    clock_t start = clock();
    ublas::vector<double>  x(b);
    ublas::inplace_solve(mat_row_upp, x, ublas::upper_tag());
    std::cerr << "row_upp x: " << clock()-start << std::endl;
    std::cerr << "delta: " << diff(mat_row_upp, x, b) << "\n";
  }

//   {
//     clock_t start = clock();
//     ublas::vector<double>  x(b);
//     ublas::inplace_solve(x, mat_col_low, ublas::lower_tag());
//     std::cerr << "x col_low: " << clock()-start << std::endl;
//     std::cerr << "delta: " << diff(x, mat_col_low, b) << "\n";
//   }
  {
    clock_t start = clock();
    ublas::vector<double>  x(b);
    ublas::inplace_solve(x, mat_row_low, ublas::lower_tag());
    std::cerr << "x row_low: " << clock()-start << std::endl;
    std::cerr << "delta: " << diff(x, mat_row_low, b) << "\n";
  }

//   {
//     clock_t start = clock();
//     ublas::vector<double>  x(b);
//     ublas::inplace_solve(x, mat_col_upp, ublas::upper_tag());
//     std::cerr << "x col_upp: " << clock()-start << std::endl;
//     std::cerr << "delta: " << diff(x, mat_col_upp, b) << "\n";
//   }
  {
    clock_t start = clock();
    ublas::vector<double>  x(b);
    ublas::inplace_solve(x, mat_row_upp, ublas::upper_tag());
    std::cerr << "x row_upp: " << clock()-start << std::endl;
    std::cerr << "delta: " << diff(x, mat_row_upp, b) << "\n";
  }


}
