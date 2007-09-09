//  Boost cerrno.hpp header  -------------------------------------------------//

//  Copyright Beman Dawes 2005.
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

#ifndef BOOST_CERRNO_HPP
#define BOOST_CERRNO_HPP

#include <cerrno>

//  supply errno values likely to be missing, particularly on Windows

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT 9901
#endif

#ifndef EADDRINUSE
#define EADDRINUSE 9902
#endif

#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL 9903
#endif

#ifndef EISCONN
#define EISCONN 9904
#endif

#ifndef EBADMSG
#define EBADMSG 9905
#endif

#ifndef ECONNABORTED
#define ECONNABORTED 9906
#endif

#ifndef EALREADY
#define EALREADY 9907
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED 9908
#endif

#ifndef ECONNRESET
#define ECONNRESET 9909
#endif

#ifndef EDESTADDRREQ
#define EDESTADDRREQ 9910
#endif

#ifndef EHOSTUNREACH
#define EHOSTUNREACH 9911
#endif

#ifndef EIDRM
#define EIDRM 9912
#endif

#ifndef EMSGSIZE
#define EMSGSIZE 9913
#endif

#ifndef ENETDOWN
#define ENETDOWN 9914
#endif

#ifndef ENETRESET
#define ENETRESET 9915
#endif

#ifndef ENETUNREACH
#define ENETUNREACH 9916
#endif

#ifndef ENOBUFS
#define ENOBUFS 9917
#endif

#ifndef ENOLINK
#define ENOLINK 9918
#endif

#ifndef ENODATA
#define ENODATA 9919
#endif

#ifndef ENOMSG
#define ENOMSG 9920
#endif

#ifndef ENOPROTOOPT
#define ENOPROTOOPT 9921
#endif

#ifndef ENOSR
#define ENOSR 9922
#endif

#ifndef ENOTSOCK
#define ENOTSOCK 9923
#endif

#ifndef ENOSTR
#define ENOSTR 9924
#endif

#ifndef ENOTCONN
#define ENOTCONN 9925
#endif

#ifndef ENOTSUP
#define ENOTSUP 9926
#endif

#ifndef ECANCELED
#define ECANCELED 9927
#endif

#ifndef EINPROGRESS
#define EINPROGRESS 9928
#endif

#ifndef EOPNOTSUPP
#define EOPNOTSUPP 9929
#endif

#ifndef EWOULDBLOCK
#define EWOULDBLOCK 9930
#endif

#ifndef EOWNERDEAD
#define EOWNERDEAD  9931
#endif

#ifndef EPROTO
#define EPROTO 9932
#endif

#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT 9933
#endif

#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE 9934
#endif

#ifndef ETIME
#define ETIME 9935
#endif

#ifndef ETXTBSY
#define ETXTBSY 9936
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT 9938
#endif

#ifndef ELOOP
#define ELOOP 9939
#endif

#ifndef EOVERFLOW
#define EOVERFLOW 9940
#endif

#ifndef EPROTOTYPE
#define EPROTOTYPE 9941
#endif

#ifndef ENOSYS
#define ENOSYS 9942
#endif

#ifndef EINVAL
#define EINVAL 9943
#endif

#ifndef ERANGE
#define ERANGE 9944
#endif

#ifndef EILSEQ
#define EILSEQ 9945
#endif

#endif // include guard
