# ifndef BOOST_PREPROCESSOR_ITERATE_HPP
# define BOOST_PREPROCESSOR_ITERATE_HPP
#
# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.  Permission to copy, use,        *
#  *     modify, sell, and distribute this software is granted provided       *
#  *     this copyright notice appears in all copies.  This software is       *
#  *     provided "as is" without express or implied warranty, and with       *
#  *     no claim at to its suitability for any purpose.                      *
#  *                                                                          *
#  ************************************************************************** */
#
# include <boost/preprocessor/detail/cat.hpp>
# include <boost/preprocessor/dec.hpp>
# include <boost/preprocessor/inc.hpp>
# include <boost/preprocessor/stringize.hpp>
#
# include <boost/preprocessor/tuple/elem.hpp>
#
# define BOOST_PP_ITERATION_DEPTH_LIMIT 5
# define BOOST_PP_ITERATION_LIMIT 256
#
# define BOOST_PP_ITERATION_DEPTH() 0
#
# define BOOST_PP_ITERATION() BOOST_PP_DETAIL_CAT2(BOOST_PP_ITERATION_, BOOST_PP_ITERATION_DEPTH())
#
# define BOOST_PP_ITERATION_START() BOOST_PP_DETAIL_CAT2(BOOST_PP_ITERATION_START_, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_ITERATION_FINISH() BOOST_PP_DETAIL_CAT2(BOOST_PP_ITERATION_FINISH_, BOOST_PP_ITERATION_DEPTH())
#
# define BOOST_PP_FRAME_ITERATION(i) BOOST_PP_DETAIL_CAT2(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_)
#
# define BOOST_PP_FRAME_START(i) BOOST_PP_DETAIL_CAT2(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_START_)
# define BOOST_PP_FRAME_FINISH(i) BOOST_PP_DETAIL_CAT2(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FINISH_)
#
# define BOOST_PP_RELATIVE_0(m) BOOST_PP_DETAIL_CAT2(m, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_RELATIVE_1(m) BOOST_PP_DETAIL_CAT2(m, BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))
# define BOOST_PP_RELATIVE_2(m) BOOST_PP_DETAIL_CAT2(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))
# define BOOST_PP_RELATIVE_3(m) BOOST_PP_DETAIL_CAT2(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))))
# define BOOST_PP_RELATIVE_4(m) BOOST_PP_DETAIL_CAT2(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))))
#
# define BOOST_PP_SET_ITERATION_START() BOOST_PP_DETAIL_CAT4(<boost/preprocessor/detail/iterate/lower, BOOST_PP_INC(BOOST_PP_ITERATION_DEPTH()), ., hpp>)
# define BOOST_PP_SET_ITERATION_FINISH() BOOST_PP_DETAIL_CAT4(<boost/preprocessor/detail/iterate/upper, BOOST_PP_INC(BOOST_PP_ITERATION_DEPTH()), ., hpp>)
#
# define BOOST_PP_LINE(line, file) line BOOST_PP_STRINGIZE(BOOST_PP_DETAIL_CAT2(file, BOOST_PP_DETAIL_CAT2(BOOST_PP_LINE_, BOOST_PP_ITERATION_DEPTH())()))
#
# define BOOST_PP_LINE_0() (!BOOST_PP_ERROR_NO_ACTIVE_ITERATION)
# define BOOST_PP_LINE_1() BOOST_PP_DETAIL_CAT3([, BOOST_PP_ITERATION(), ])
# define BOOST_PP_LINE_2() BOOST_PP_DETAIL_CAT2(BOOST_PP_DETAIL_CAT3([, BOOST_PP_FRAME_ITERATION(1), ]), BOOST_PP_LINE_1())
# define BOOST_PP_LINE_3() BOOST_PP_DETAIL_CAT2(BOOST_PP_DETAIL_CAT3([, BOOST_PP_FRAME_ITERATION(2), ]), BOOST_PP_LINE_2())
# define BOOST_PP_LINE_4() BOOST_PP_DETAIL_CAT2(BOOST_PP_DETAIL_CAT3([, BOOST_PP_FRAME_ITERATION(3), ]), BOOST_PP_LINE_3())
# define BOOST_PP_LINE_5() BOOST_PP_DETAIL_CAT2(BOOST_PP_DETAIL_CAT3([, BOOST_PP_FRAME_ITERATION(4), ]), BOOST_PP_LINE_4())
#
# define BOOST_PP_ITERATE() BOOST_PP_DETAIL_CAT4(<boost/preprocessor/detail/iterate/exp, BOOST_PP_INC(BOOST_PP_ITERATION_DEPTH()), ., hpp>)
#
# define BOOST_PP_LOCAL_ITERATE() <boost/preprocessor/detail/iterate/local_iterate.hpp>
#
# define BOOST_PP_INCLUDE_SELF() <boost/preprocessor/detail/iterate/self.hpp>
#
# endif
