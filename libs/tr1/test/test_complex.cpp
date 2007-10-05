//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef TEST_STD_HEADERS
#include <complex>
#else
#include <boost/tr1/complex.hpp>
#endif

#include "verify_return.hpp"

int main()
{
   verify_return_type(std::arg(0), double(0));
   verify_return_type(std::arg(0.0), double(0));
   verify_return_type(std::arg(0.0L), (long double)(0));
   verify_return_type(std::arg(0.0F), float(0));
   verify_return_type(std::norm(0), double(0));
   verify_return_type(std::norm(0.0), double(0));
   verify_return_type(std::norm(0.0L), (long double)(0));
   verify_return_type(std::norm(0.0F), float(0));
   verify_return_type(std::conj(0), std::complex<double>(0));
   verify_return_type(std::conj(0.0), std::complex<double>(0));
   verify_return_type(std::conj(0.0L), std::complex<long double>(0));
   verify_return_type(std::conj(0.0F), std::complex<float>(0));
   verify_return_type(std::imag(0), double(0));
   verify_return_type(std::imag(0.0), double(0));
   verify_return_type(std::imag(0.0L), (long double)(0));
   verify_return_type(std::imag(0.0F), float(0));
   verify_return_type(std::real(0), double(0));
   verify_return_type(std::real(0.0), double(0));
   verify_return_type(std::real(0.0L), (long double)(0));
   verify_return_type(std::real(0.0F), float(0));
   verify_return_type(std::polar(0), std::complex<double>(0));
   verify_return_type(std::polar(0.0), std::complex<double>(0));
   verify_return_type(std::polar(0.0L), std::complex<long double>(0));
   verify_return_type(std::polar(0.0F), std::complex<float>(0));
   verify_return_type(std::polar(0, 0L), std::complex<double>(0));
   verify_return_type(std::polar(0.0, 0.0L), std::complex<long double>(0));
   verify_return_type(std::polar(0.0L, 0.0F), std::complex<long double>(0));
   verify_return_type(std::polar(0.0F, 0), std::complex<double>(0));

   std::complex<float> f;
   std::complex<double> d;
   std::complex<long double> l;
   float sf;
   double sd;
   long double sl;

   verify_return_type(std::pow(f, f), f);
   verify_return_type(std::pow(f, d), d);
   verify_return_type(std::pow(d, f), d);
   verify_return_type(std::pow(f, l), l);
   verify_return_type(std::pow(l, f), l);
   verify_return_type(std::pow(d, l), l);
   verify_return_type(std::pow(l, d), l);

   verify_return_type(std::pow(f, sf), f);
   verify_return_type(std::pow(f, sd), d);
   verify_return_type(std::pow(d, sf), d);
   verify_return_type(std::pow(f, sl), l);
   verify_return_type(std::pow(l, sf), l);
   verify_return_type(std::pow(d, sl), l);
   verify_return_type(std::pow(l, sd), l);
   verify_return_type(std::pow(f, 0), f);
   verify_return_type(std::pow(d, 0), d);
   verify_return_type(std::pow(l, 0), l);
   verify_return_type(std::pow(f, 0L), d);
   verify_return_type(std::pow(d, 0L), d);
   verify_return_type(std::pow(l, 0L), l);

   verify_return_type(std::pow(sf, f), f);
   verify_return_type(std::pow(sf, d), d);
   verify_return_type(std::pow(sd, f), d);
   verify_return_type(std::pow(sf, l), l);
   verify_return_type(std::pow(sl, f), l);
   verify_return_type(std::pow(sd, l), l);
   verify_return_type(std::pow(sl, d), l);
   verify_return_type(std::pow(2, f), d);
   verify_return_type(std::pow(2, d), d);
   verify_return_type(std::pow(2, l), l);
   verify_return_type(std::pow(2L, f), d);
   verify_return_type(std::pow(2L, d), d);
   verify_return_type(std::pow(2L, l), l);

   verify_return_type(std::tr1::acos(f), f);
   verify_return_type(std::tr1::acos(d), d);
   verify_return_type(std::tr1::acos(l), l);
   verify_return_type(std::tr1::asin(f), f);
   verify_return_type(std::tr1::asin(d), d);
   verify_return_type(std::tr1::asin(l), l);
   verify_return_type(std::tr1::atan(f), f);
   verify_return_type(std::tr1::atan(d), d);
   verify_return_type(std::tr1::atan(l), l);
   verify_return_type(std::tr1::asinh(f), f);
   verify_return_type(std::tr1::asinh(d), d);
   verify_return_type(std::tr1::asinh(l), l);
   verify_return_type(std::tr1::acosh(f), f);
   verify_return_type(std::tr1::acosh(d), d);
   verify_return_type(std::tr1::acosh(l), l);
   verify_return_type(std::tr1::atanh(f), f);
   verify_return_type(std::tr1::atanh(d), d);
   verify_return_type(std::tr1::atanh(l), l);
   verify_return_type(std::tr1::fabs(f), sf);
   verify_return_type(std::tr1::fabs(d), sd);
   verify_return_type(std::tr1::fabs(l), sl);
   return 0;
}

