/*
 *
 * Copyright (c) 2003
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         escape_syntax_type.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression escape synatx type enumerator.
  */

#ifndef BOOST_REGEX_ERROR_TYPE_HPP
#define BOOST_REGEX_ERROR_TYPE_HPP

#ifdef __cplusplus
namespace boost{
#endif

#ifdef __cplusplus
namespace regex_constants{

enum error_type{

   error_ok = 0,         // not used
   error_no_match = 1,   // not used
   error_bad_pattern = 2,
   error_collate = 3,
   error_ctype = 4,
   error_escape = 5,
   error_backref = 6,
   error_brack = 7,
   error_paren = 8,
   error_brace = 9,
   error_badbrace = 10,
   error_range = 11,
   error_space = 12,
   error_badrepeat = 13,
   error_end = 14,    // not used
   error_size = 15,
   error_right_paren = 16,  // not used
   error_empty = 17,
   error_complexity = 18,
   error_stack = 19,
   error_unknown = 20
};

}
}
#endif // __cplusplus

#endif
