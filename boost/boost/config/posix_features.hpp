//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

// All POSIX feature tests go in this file:

#  ifdef BOOST_HAS_UNISTD_H
#     include <unistd.h>

      // XOpen has <nl_types.h>, but is this the correct version check?
#     if defined(_XOPEN_VERSION) && (_XOPEN_VERSION >= 3)
#        define BOOST_HAS_NL_TYPES_H
#     endif

      // POSIX version 6 requires <stdint.h>
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200100)
#        define BOOST_HAS_STDINT_H
#     endif

      // POSIX defines _POSIX_THREADS > 0 for pthread support,
      // however some platforms define _POSIX_THREADS without
      // a value, hence the (_POSIX_THREADS+0 >= 0) check.
      // Strictly speaking this may catch platforms with a
      // non-functioning stub <pthreads.h>, but such occurrences should
      // occur very rarely if at all.
#     if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(BOOST_HAS_WINTHREADS)
#        define BOOST_HAS_PTHREADS
#     endif

#  endif
