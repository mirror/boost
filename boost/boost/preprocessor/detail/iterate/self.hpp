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
# line BOOST_PP_DETAIL_LINE(indirect inclusion of BOOST_PP_INDIRECT_SELF)
#
# if !defined(BOOST_PP_INDIRECT_SELF)
#   error BOOST_PP:  no file to indirect file to include defined
# else
#   include BOOST_PP_INDIRECT_SELF
#   undef BOOST_PP_INDIRECT_SELF
# endif
