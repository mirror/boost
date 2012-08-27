/**
 *  \file util.hpp
 *
 *  \brief Utility macros/functions for testing and debugging purpose.
 *
 *  Copyright (c) 2009-2012, Marco Guazzone
 *
 *  Distributed under the Boost Software License, Version 1.0. (See
 *  accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */

#ifndef BOOST_NUMERIC_UBLAS_TEST_UTILS_HPP
#define BOOST_NUMERIC_UBLAS_TEST_UTILS_HPP


#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>


namespace boost { namespace numeric { namespace ublas { namespace test { namespace detail { namespace /*<unnamed>*/ {

template <typename T1, typename T2, typename T3>
inline
bool close_to(T1 x, T2 y, T3 tol)
{
    if (::std::isnan(x) || ::std::isnan(y))
    {
        // According to IEEE, NaN are different event by itself
        return false;
    }
    return ::std::abs(x-y) <= (::std::max(::std::abs(x), ::std::abs(y))*tol);
}

}}}}}} // Namespace boost::numeric::ublas::test::detail::<unnamed>


/// Expand its argument.
#define BOOST_UBLAS_TEST_EXPAND_(x) x


/// Transform its argument into a string.
#define BOOST_UBLAS_TEST_STRINGIFY_(x) #x


/// Concatenate its two \e string arguments.
#define BOOST_UBLAS_TEST_JOIN_(x,y) x ## y


/// Output the message \a x if in debug-mode; otherwise output nothing.
#ifndef NDEBUG
# 	define BOOST_UBLAS_DEBUG_TRACE(x) ::std::cerr << "[Debug>> " << BOOST_UBLAS_TEST_EXPAND_(x) << ::std::endl
#else
# 	define BOOST_UBLAS_DEBUG_TRACE(x) /**/
#endif // NDEBUG


/// Define the name of the entire test suite.
#define DCS_TEST_SUITE(m) ::std::cerr << "--- Test Suite: " << m << " ---" << ::std::endl;


/// Define the beginning of a test suite.
#define BOOST_UBLAS_TEST_BEGIN() 	/* [BOOST_UBLAS_TEST_BEGIN] */ \
									{ \
										/* Begin of Test Suite */ \
										unsigned int test_fails__(0) \
									/* [/BOOST_UBLAS_TEST_BEGIN] */


/// Define a test case \a x inside the current test suite.
#define BOOST_UBLAS_TEST_DEF(x) void BOOST_UBLAS_TEST_EXPAND_(x)(unsigned int& test_fails__)


/// Call the test case \a x.
#define BOOST_UBLAS_TEST_DO(x) 	/* [BOOST_UBLAS_TEST_DO] */ \
								try \
								{ \
									BOOST_UBLAS_TEST_EXPAND_(x)(test_fails__); \
								} \
								catch (::std::exception& e) \
								{ \
									++test_fails__; \
									BOOST_UBLAS_TEST_ERROR( e.what() ); \
								} \
								catch (...) \
								{ \
									++test_fails__; \
								} \
								/* [/BOOST_UBLAS_TEST_DO] */


/// Define the end of a test suite.
#define BOOST_UBLAS_TEST_END() 	/* [BOOST_UBLAS_TEST_END] */ \
								if (test_fails__ > 0) \
								{ \
									::std::cerr << "Number of failed tests: " << test_fails__ << ::std::endl; \
								} \
								else \
								{ \
									::std::cerr << "No failed test" << ::std::endl; \
								} \
								} /* End of test suite */ \
								/* [/BOOST_UBLAS_TEST_END] */


/// Check the truth of assertion \a x.
#define BOOST_UBLAS_TEST_CHECK(x)	/* [BOOST_UBLAS_TEST_CHECK] */ \
									if (!(x)) \
									{ \
										BOOST_UBLAS_TEST_ERROR( "Failed assertion: " << BOOST_UBLAS_TEST_STRINGIFY_(x) ); \
										++test_fails__; \
									} \
									/* [/BOOST_UBLAS_TEST_CHECK] */


/// Check for the equality of \a x against \a y.
#define BOOST_UBLAS_TEST_CHECK_EQ(x,y)	/* [BOOST_UBLAS_TEST_CHECK_EQUAL] */ \
										if (!(BOOST_UBLAS_TEST_PARAM_EXPAND_(x) == BOOST_UBLAS_TEST_PARAM_EXPAND_(y))) \
										{ \
											BOOST_UBLAS_TEST_ERROR( "Failed assertion: (" << BOOST_UBLAS_TEST_STRINGIFY_(x) << " == " << BOOST_UBLAS_TEST_STRINGIFY_(y) << ")" ); \
											++test_fails__; \
										} \
										/* [/BOOST_UBLAS_TEST_CHECK_EQUAL] */


/// Alias for macro \c BOOST_UBLAS_TEST_CHECK_EQ (for backward compatibility).
#define BOOST_UBLAS_TEST_CHECK_EQUAL(x,y) BOOST_UBLAS_TEST_CHECK_EQ(x,y)


/// Check that \a x and \a y are close with respect to a given precision.
#define BOOST_UBLAS_TEST_CHECK_CLOSE(x,y,e)	/* [BOOST_UBLAS_TEST_CHECK_PRECISION] */ \
											if (!::boost::numeric::ublas::test::detail::close_to(BOOST_UBLAS_TEST_EXPAND_(x), BOOST_UBLAS_TEST_EXPAND_(y), BOOST_UBLAS_TEST_EXPAND_(e))) \
											{ \
												BOOST_UBLAS_TEST_ERROR( "Failed assertion: abs(" << BOOST_UBLAS_TEST_STRINGIFY_(x) << "-" << BOOST_UBLAS_TEST_STRINGIFY_(y) << ") <= " << BOOST_UBLAS_TEST_STRINGIFY_(e) << " [with " << BOOST_UBLAS_TEST_STRINGIFY_(x) << " == " << BOOST_UBLAS_TEST_EXPAND_(x) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(y) << " == " << BOOST_UBLAS_TEST_EXPAND_(y) << " and " << BOOST_UBLAS_TEST_STRINGIFY_(e) << " == " << BOOST_UBLAS_TEST_EXPAND_(e) << "]" ); \
												++test_fails__; \
											} \
											/* [/BOOST_UBLAS_TEST_CHECK_PRECISION] */


/// Alias for macro \c BOOST_UBLAS_TEST_CHECK_CLOSE (for backward compatibility),
#define BOOST_UBLAS_TEST_CHECK_PRECISION(x,y,e) BOOST_UBLAS_TEST_CHECK_CLOSE(x,y,e)


/// Check that \a x is close to \a y with respect to a given relative precision.
#define BOOST_UBLAS_TEST_CHECK_REL_PRECISION(x,y,e)	/* [BOOST_UBLAS_TEST_CHECK_REL_PRECISION] */ \
													if (!::boost::numeric::ublas::test::detail::close_to(BOOST_UBLAS_TEST_EXPAND_(x)/BOOST_UBLAS_TEST_EXPAND_(y), 1.0, BOOST_UBLAS_TEST_EXPAND_(e))) \
													{ \
														BOOST_UBLAS_TEST_ERROR( "Failed assertion: abs((" << BOOST_UBLAS_TEST_STRINGIFY_(x) << "-" << BOOST_UBLAS_TEST_STRINGIFY_(y) << ")/" << BOOST_UBLAS_TEST_STRINGIFY_(y) << ") <= " << BOOST_UBLAS_TEST_STRINGIFY_(e)  << " [with " << BOOST_UBLAS_TEST_STRINGIFY_(x) << " == " << BOOST_UBLAS_TEST_EXPAND_(x) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(y) << " == " << BOOST_UBLAS_TEST_EXPAND_(y) << " and " << BOOST_UBLAS_TEST_STRINGIFY_(e) << " == " << BOOST_UBLAS_TEST_EXPAND_(e) << "]" ); \
														++test_fails__; \
													} \
													/* [/BOOST_UBLAS_TEST_CHECK_REL_PRECISION] */


/// Check that elements of \a x and \a y are equal.
#define BOOST_UBLAS_TEST_CHECK_VECTOR_EQ(x,y,n)	/* [BOOST_UBLAS_TEST_CHECK_VECTOR_EQ] */ \
												if (BOOST_UBLAS_TEST_EXPAND_(n) > 0) \
												{ \
													unsigned long n__ = BOOST_UBLAS_TEST_EXPAND_(n); \
													for (unsigned long i__ = n__; i__ > 0; --i__) \
													{ \
														if (!(BOOST_UBLAS_TEST_EXPAND_(x)[n__-i__]==BOOST_UBLAS_TEST_EXPAND_(y)[n__-i__])) \
														{ \
															BOOST_UBLAS_TEST_ERROR( "Failed assertion: (" << BOOST_UBLAS_TEST_STRINGIFY_(x[i__]) << "==" << BOOST_UBLAS_TEST_STRINGIFY_(y[i__]) << ")" << " [with " << BOOST_UBLAS_TEST_STRINGIFY_(x[i__]) << " == " << BOOST_UBLAS_TEST_EXPAND_(x)[n__-i__] << ", " << BOOST_UBLAS_TEST_STRINGIFY_(y[i__]) << " == " << BOOST_UBLAS_TEST_EXPAND_(y)[n__-i__] << ", " << BOOST_UBLAS_TEST_STRINGIFY_(i__) << " == " << i__ << " and " << BOOST_UBLAS_TEST_STRINGIFY_(n) << " == " << n__ << "]" ); \
															++test_fails__; \
														} \
													} \
												} \
												/* [/BOOST_UBLAS_TEST_CHECK_VECTOR_EQ] */


/// Check that elements of \a x and \a y are close with respect to a given precision.
#define BOOST_UBLAS_TEST_CHECK_VECTOR_CLOSE(x,y,n,e)	/* [BOOST_UBLAS_TEST_CHECK_VECTOR_CLOSE] */ \
														if (BOOST_UBLAS_TEST_EXPAND_(n) > 0) \
														{ \
															unsigned long n__ = BOOST_UBLAS_TEST_EXPAND_(n); \
															for (unsigned long i__ = n__; i__ > 0; --i__) \
															{ \
																if (!::boost::numeric::ublas::test::detail::close_to(BOOST_UBLAS_TEST_EXPAND_(x)[n__-i__], BOOST_UBLAS_TEST_EXPAND_(y)[n__-i__], BOOST_UBLAS_TEST_EXPAND_(e))) \
																{ \
																	BOOST_UBLAS_TEST_ERROR( "Failed assertion: abs((" << BOOST_UBLAS_TEST_STRINGIFY_(x[i__]) << "-" << BOOST_UBLAS_TEST_STRINGIFY_(y[i__]) << ") <= " << BOOST_UBLAS_TEST_STRINGIFY_(e)  << " [with " << BOOST_UBLAS_TEST_STRINGIFY_(x[i__]) << " == " << BOOST_UBLAS_TEST_EXPAND_(x)[n__-i__] << ", " << BOOST_UBLAS_TEST_STRINGIFY_(y[i__]) << " == " << BOOST_UBLAS_TEST_EXPAND_(y)[n__-i__] << ", " << BOOST_UBLAS_TEST_STRINGIFY_(i__) << " == " << i__ << " and " << BOOST_UBLAS_TEST_STRINGIFY_(n) << " == " << n__ << "]" ); \
																	++test_fails__; \
																} \
															} \
														} \
														/* [/BOOST_UBLAS_TEST_CHECK_VECTOR_CLOSE] */


/// Check that elements of matrices \a x and \a y are equal.
#define BOOST_UBLAS_TEST_CHECK_MATRIX_EQ(x,y,nr,nc)	/* [BOOST_UBLAS_TEST_CHECK_MATRIX_EQ] */ \
													for (unsigned long i__ = 0; i__ < BOOST_UBLAS_TEST_EXPAND_(nr); ++i__) \
													{ \
														for (unsigned long j__ = 0; j__ < BOOST_UBLAS_TEST_EXPAND_(nc); ++j__) \
														{ \
															if (!(BOOST_UBLAS_TEST_EXPAND_(x)(i__,j__)==BOOST_UBLAS_TEST_EXPAND_(y)(i__,j__))) \
															{ \
																BOOST_UBLAS_TEST_ERROR( "Failed assertion: (" << BOOST_UBLAS_TEST_STRINGIFY_(x(i__,j__)) << " == " << BOOST_UBLAS_TEST_STRINGIFY_(y(i__,j__)) << ") [with " << BOOST_UBLAS_TEST_STRINGIFY_(x(i__,j__)) << " == " << BOOST_UBLAS_TEST_EXPAND_(x)(i__,j__) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(y(i__,j__)) << " == " << BOOST_UBLAS_TEST_EXPAND_(y)(i__,j__) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(i__) << " == " << i__ << ", " << BOOST_UBLAS_TEST_STRINGIFY_(j__) << " == " << BOOST_UBLAS_TEST_EXPAND_(j__) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(nr) << " == " << BOOST_UBLAS_TEST_EXPAND_(nr) << " and " << BOOST_UBLAS_TEST_STRINGIFY_(nc) << " == " << BOOST_UBLAS_TEST_EXPAND_(nc) << "]" ); \
															} \
														} \
													} \
													/* [/BOOST_UBLAS_TEST_CHECK_MATRIX_EQ] */


/// Check that elements of matrices \a x and \a y are close with respect to a given precision.
#define BOOST_UBLAS_TEST_CHECK_MATRIX_CLOSE(x,y,nr,nc,e)	/* [BOOST_UBLAS_TEST_CHECK_MATRIX_CLOSE] */ \
															for (unsigned long i__ = 0; i__ < BOOST_UBLAS_TEST_EXPAND_(nr); ++i__) \
															{ \
																for (unsigned long j__ = 0; j__ < BOOST_UBLAS_TEST_EXPAND_(nc); ++j__) \
																{ \
																	if (!::boost::numeric::ublas::test::detail::close_to(BOOST_UBLAS_TEST_EXPAND_(x)(i__,j__), BOOST_UBLAS_TEST_EXPAND_(y)(i__,j__), BOOST_UBLAS_TEST_EXPAND_(e))) \
																	{ \
																		BOOST_UBLAS_TEST_ERROR( "Failed assertion: abs((" << BOOST_UBLAS_TEST_STRINGIFY_(x(i__,j__)) << "-" << BOOST_UBLAS_TEST_STRINGIFY_(y(i__,j__)) << ") <= " << BOOST_UBLAS_TEST_STRINGIFY_(e)  << " [with " << BOOST_UBLAS_TEST_STRINGIFY_(x(i__,j__)) << " == " << BOOST_UBLAS_TEST_EXPAND_(x)(i__,j__) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(y(i__,j__)) << " == " << BOOST_UBLAS_TEST_EXPAND_(y)(i__,j__) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(i__) << " == " << i__ << ", " << BOOST_UBLAS_TEST_STRINGIFY_(j__) << " == " << BOOST_UBLAS_TEST_EXPAND_(j__) << ", " << BOOST_UBLAS_TEST_STRINGIFY_(nr) << " == " << BOOST_UBLAS_TEST_EXPAND_(nr) << " and " << BOOST_UBLAS_TEST_STRINGIFY_(nc) << " == " << BOOST_UBLAS_TEST_EXPAND_(nc) << "]" ); \
																	} \
																} \
															} \
															/* [/BOOST_UBLAS_TEST_CHECK_MATRIX_CLOSE] */


///< Output the error message \a x.
#define BOOST_UBLAS_TEST_ERROR(x) ::std::cerr << "[Error (" << __FILE__ << ":" << __func__ << ":" << __LINE__ << ")>> " << BOOST_UBLAS_TEST_EXPAND_(x) << ::std::endl

#endif // BOOST_NUMERIC_UBLAS_TEST_UTILS_HPP
