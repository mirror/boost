
#ifndef BOOST_RE_OPT_H
#define BOOST_RE_OPT_H

/* #define BOOST_RE_AUTO_CONFIGURE */
#ifdef BOOST_RE_AUTO_CONFIGURE

/* Compiler options: */

/* BOOST_NO_STDC_NAMESPACE         C library not in namespace std */
/* #define BOOST_NO_STDC_NAMESPACE */

/* BOOST_RE_PLATFORM_W32           Platform is MS Win32 */
/* #define BOOST_RE_PLATFORM_W32 */

/* BOOST_RE_NO_W32               Disable Win32 support even when present */
/* #define BOOST_RE_NO_W32 */

/* BOOST_RE_NO_BOOL                If bool is not a distict type. */
/* #define BOOST_RE_NO_BOOL */

/* BOOST_RE_NO_WCHAR_H             If there is no <wchar.h> */
/* #define BOOST_RE_NO_WCHAR_H */

/* BOOST_RE_NO_WCTYPE_H            If there is no <wctype.h> */
/* #define BOOST_RE_NO_WCTYPE_H */

/* BOOST_RE_NO_WCSTRING            If there are no wcslen and wcsncmp functions available. */
/* #define BOOST_RE_NO_WCSTRING */

/* BOOST_RE_NO_SWPRINTF            If there is no swprintf available. */
/* #define BOOST_RE_NO_SWPRINTF */

/* BOOST_RE_NO_WSPRINTF            If there is no wsprintf available. */
/* #define BOOST_RE_NO_WSPRINTF */

/* BOOST_NO_MEMBER_TEMPLATES    If member function templates or nested template classes are not allowed. */
/* #define BOOST_NO_MEMBER_TEMPLATES */

/* BOOST_RE_NO_TEMPLATE_RETURNS    If template functions based on return type are not supported. */
/* #define BOOST_RE_NO_TEMPLATE_RETURNS */

/* BOOST_RE_NO_PARTIAL_FUNC_SPEC   If partial template function specialisation is not supported */
/* #define BOOST_RE_NO_PARTIAL_FUNC_SPEC */

/* BOOST_RE_NO_CAT                 Define if the compiler does not support POSIX style
                             message categories (catopen catgets catclose). */
/* #define BOOST_RE_NO_CAT */

/* BOOST_RE_THREADS                Define if the compiler supports multiple threads in
                             the current translation mode. */
/* #define BOOST_RE_THREADS */

/* BOOST_RE_NO_TEMPLATE_MERGE      If template in separate translation units don't merge at link time */
/* #define BOOST_RE_NO_TEMPLATE_MERGE */

/* BOOST_RE_NO_TEMPLATE_MERGE_A    If template merging from library archives is not supported */
/* #define BOOST_RE_NO_TEMPLATE_MERGE_A */

/* BOOST_RE_NO_TEMPLATE_SWITCH_MERGE If merging of templates containing switch statements is not supported */
/* #define BOOST_RE_NO_TEMPLATE_SWITCH_MERGE */

/* BOOST_RE_CALL                   Optionally define a calling convention for C++ functions */
/* #define BOOST_RE_CALL */

/* BOOST_RE_CCALL                  Optionally define a calling convention for C functions */
/* #define BOOST_RE_CCALL */

/* BOOST_RE_SIZEOF_SHORT           sizeof(short) */
/* #define BOOST_RE_SIZEOF_SHORT */

/* BOOST_RE_SIZEOF_INT             sizeof(int) */
/* #define BOOST_RE_SIZEOF_INT */

/* BOOST_RE_SIZEOF_LONG            sizeof(long) */
/* #define BOOST_RE_SIZEOF_LONG */

/* BOOST_RE_SIZEOF_WCHAR_T         sizeof(wchar_t) */
/* #define BOOST_RE_SIZEOF_WCHAR_T */


/* STL options: */

/* BOOST_RE_NO_ITERATOR_H          Define if you do not have a version of <iterator>. */
/* #define BOOST_RE_NO_ITERATOR_H */

/* BOOST_NO_STD_ALLOCATOR    Define if <memory> does not fully comply with the
                             latest standard, and is not auto-recognised,
                             that means nested template classes
                             which hardly any compilers support at present. */
/* #define BOOST_NO_STD_ALLOCATOR */

/* BOOST_RE_NO_LOCALE_H            Define if there is no verion of the standard
                             <locale> header available. */
/* #define BOOST_RE_NO_LOCALE_H */

/* BOOST_RE_NO_STL                 Disables the use of any supporting STL code. */
/* #define BOOST_RE_NO_STL */

/* BOOST_RE_NO_NOT_EQUAL           Disables the generation of operator!= if this
                             clashes with the STL version. */

/* BOOST_RE_NO_STRING_DEF_ARGS     Define if std::basic_string<charT> not allowed - in
                             other words if the template is missing its required
                      default arguments. */
/* #define BOOST_RE_NO_STRING_DEF_ARGS */

/* BOOST_RE_USE_ALGO               If <algo.h> not <algorithm> is present */
/* #define BOOST_RE_USE_ALGO */

/* BOOST_RE_OLD_IOSTREAM           If the new iostreamm classes are not available */
/* #define BOOST_RE_OLD_IOSTREAM */

/* BOOST_NO_STD_DISTANCE             If std::distance is not present or non-standard */
/* #define BOOST_NO_STD_DISTANCE */

/* BOOST_RE_NO_OI_ASSIGN           If output iterators ostream_iterator<>, back_insert_iterator<> and 
                             front_insert_iterator<> do not have assignment operators */
/* #define BOOST_RE_NO_OI_ASSIGN */


#include <stdexcept>

#ifndef BOOST_RE_NO_ITERATOR_H
#include <iterator>
#ifdef BOOST_RE_USE_ALGO
#include <algo.h>
#else
#include <algorithm>
#endif
#endif

#endif // BOOST_RE_AUTO_CONFIGURE


#endif /* BOOST_RE_OPT_H */











