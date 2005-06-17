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

#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/io.hpp>
#include "../bench1/bench13.cpp"


#ifdef USE_FLOAT
template struct bench_3<boost::numeric::interval<float>, 3>;
template struct bench_3<boost::numeric::interval<float>, 10>;
template struct bench_3<boost::numeric::interval<float>, 30>;
template struct bench_3<boost::numeric::interval<float>, 100>;
#endif

#ifdef USE_DOUBLE
template struct bench_3<boost::numeric::interval<double>, 3>;
template struct bench_3<boost::numeric::interval<double>, 10>;
template struct bench_3<boost::numeric::interval<double>, 30>;
template struct bench_3<boost::numeric::interval<double>, 100>;
#endif

#ifdef USE_BOOST_COMPLEX
#ifdef USE_FLOAT
template struct bench_3<boost::complex<boost::numeric::interval<float> >, 3>;
template struct bench_3<boost::complex<boost::numeric::interval<float> >, 10>;
template struct bench_3<boost::complex<boost::numeric::interval<float> >, 30>;
template struct bench_3<boost::complex<boost::numeric::interval<float> >, 100>;
#endif

#ifdef USE_DOUBLE
template struct bench_3<boost::complex<boost::numeric::interval<double> >, 3>;
template struct bench_3<boost::complex<boost::numeric::interval<double> >, 10>;
template struct bench_3<boost::complex<boost::numeric::interval<double> >, 30>;
template struct bench_3<boost::complex<boost::numeric::interval<double> >, 100>;
#endif
#endif
