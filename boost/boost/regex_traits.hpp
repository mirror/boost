/*
 *
 * Copyright (c) 1998-2000
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
  *   FILE         regex.cpp
  *   VERSION      3.04
  *   DESCRIPTION: Declares regular expression traits classes.
  */

#ifndef BOOST_REGEX_TRAITS_HPP
#define BOOST_REGEX_TRAITS_HPP

#include <boost/cregex.hpp>
#include <boost/re_detail/regex_cstring.hpp>

namespace boost{

#ifdef __BORLANDC__
   #if __BORLANDC__ == 0x530
    #pragma option push -a4 -b -Ve
   #elif __BORLANDC__ > 0x530
    #pragma option push -a8 -b -Ve
   #endif
#endif

template <class charT>
class c_regex_traits;

namespace re_detail{

struct mss
{
   unsigned int id;
   const char* what;
};

BOOST_RE_IX_DECL bool BOOST_RE_CALL re_lookup_def_collate_name(std::string& buf, const char* name);
BOOST_RE_IX_DECL unsigned int BOOST_RE_CALL re_get_default_message(char* buf, unsigned int len, unsigned int id);
extern BOOST_RE_IX_DECL const char *re_default_error_messages[];
BOOST_RE_IX_DECL bool BOOST_RE_CALL re_lookup_def_collate_name(std::string& buf, const char* name);
BOOST_RE_IX_DECL bool BOOST_RE_CALL is_combining(wchar_t c);
//extern BOOST_RE_IX_DECL const wchar_t combining_ranges[];

#ifndef BOOST_RE_NO_WCSTRING
extern BOOST_RE_IX_DECL wchar_t wide_lower_case_map[];
extern BOOST_RE_IX_DECL unsigned short wide_unicode_classes[];
#endif


struct BOOST_RE_IX_DECL regex_traits_base
{
   enum char_syntax_type
   {
      syntax_char = 0,
      syntax_open_bracket = 1,                  // (
      syntax_close_bracket = 2,                 // )
      syntax_dollar = 3,                        // $
      syntax_caret = 4,                         // ^
      syntax_dot = 5,                           // .
      syntax_star = 6,                          // *
      syntax_plus = 7,                          // +
      syntax_question = 8,                      // ?
      syntax_open_set = 9,                      // [
      syntax_close_set = 10,                    // ]
      syntax_or = 11,                           // |
      syntax_slash = 12,                        //
      syntax_hash = 13,                         // #
      syntax_dash = 14,                         // -
      syntax_open_brace = 15,                   // {
      syntax_close_brace = 16,                  // }
      syntax_digit = 17,                        // 0-9
      syntax_b = 18,                            // for \b
      syntax_B = 19,                            // for \B
      syntax_left_word = 20,                    // for \<
      syntax_right_word = 21,                   // for \>
      syntax_w = 22,                            // for \w
      syntax_W = 23,                            // for \W
      syntax_start_buffer = 24,                 // for \`
      syntax_end_buffer = 25,                   // for \'
      syntax_newline = 26,                      // for newline alt
      syntax_comma = 27,                        // for {x,y}

      syntax_a = 28,                            // for \a
      syntax_f = 29,                            // for \f
      syntax_n = 30,                            // for \n
      syntax_r = 31,                            // for \r
      syntax_t = 32,                            // for \t
      syntax_v = 33,                            // for \v
      syntax_x = 34,                            // for \xdd
      syntax_c = 35,                            // for \cx
      syntax_colon = 36,                        // for [:...:]
      syntax_equal = 37,                        // for [=...=]
   
      // perl ops:
      syntax_e = 38,                            // for \e
      syntax_l = 39,                            // for \l
      syntax_L = 40,                            // for \L
      syntax_u = 41,                            // for \u
      syntax_U = 42,                            // for \U
      syntax_s = 43,                            // for \s
      syntax_S = 44,                            // for \S
      syntax_d = 45,                            // for \d
      syntax_D = 46,                            // for \D
      syntax_E = 47,                            // for \Q\E
      syntax_Q = 48,                            // for \Q\E
      syntax_X = 49,                            // for \X
      syntax_C = 50,                            // for \C
      syntax_Z = 51,                            // for \Z
      syntax_G = 52,                            // for \G

      syntax_max = 53
   };
};

struct BOOST_RE_IX_DECL c_traits_base : public regex_traits_base
{
public:
   enum{
      char_class_none = 0,
      char_class_alpha = 1,
      char_class_cntrl = char_class_alpha << 1,
      char_class_digit = char_class_cntrl << 1,
      char_class_lower = char_class_digit << 1,
      char_class_punct = char_class_lower << 1,
      char_class_space = char_class_punct << 1,
      char_class_upper = char_class_space << 1,
      char_class_xdigit = char_class_upper << 1,
      char_class_blank = char_class_xdigit << 1,
      char_class_unicode = char_class_blank << 1,
      char_class_underscore = char_class_unicode << 1,

      char_class_alnum = char_class_alpha | char_class_digit,
      char_class_graph = char_class_alpha | char_class_digit | char_class_punct | char_class_underscore,
      char_class_print = char_class_alpha | char_class_digit | char_class_punct | char_class_underscore | char_class_blank,
      char_class_word = char_class_alpha | char_class_digit | char_class_underscore
   };
   static std::string set_message_catalogue(const std::string& s);
protected:
#if defined(__MWERKS__) && __MWERKS__ <= 0x6000
   friend class c_regex_traits<char>;
   friend class c_regex_traits<wchar_t>;
#endif 

   static char regex_message_catalogue[200];
   enum syntax_map_size
   {
      map_size = UCHAR_MAX + 1
   };

   static unsigned char syntax_map[map_size];
   static unsigned short class_map[map_size];
   static char lower_case_map[map_size];

   static jm_uintfast32_t BOOST_RE_CALL do_lookup_class(const char* p);
   static bool BOOST_RE_CALL do_lookup_collate(std::string& buf, const char* p);
   static void BOOST_RE_CALL do_update_ctype();
   static void BOOST_RE_CALL do_update_collate();
public:
   static std::string error_string(unsigned id);
   static char* get_catalogue() { return regex_message_catalogue; }
};

} // namespace re_detail


template<>
class BOOST_RE_IX_DECL c_regex_traits<char> : public re_detail::c_traits_base
{
   typedef re_detail::c_traits_base base_type;
public:
   typedef char char_type;
   typedef unsigned char uchar_type;
   typedef unsigned int size_type;
   typedef std::string string_type;
   typedef int locale_type;

   static size_t BOOST_RE_CALL length(const char_type* p)
   {
      return std::strlen(p);
   }
   static unsigned int BOOST_RE_CALL syntax_type(size_type c)
   {
      return syntax_map[c];
   }
   static char BOOST_RE_CALL translate(char c, bool icase)
   {
      return icase ? lower_case_map[(size_type)(uchar_type)c] : c;
   }
   static void BOOST_RE_CALL transform(std::string& out, const std::string& in);

   static void BOOST_RE_CALL transform_primary(std::string& out, const std::string& in);

   static bool BOOST_RE_CALL is_separator(char c)
   {
      return BOOST_RE_MAKE_BOOL((c == '\n') || (c == '\r'));
   }

   static bool BOOST_RE_CALL is_combining(char)
   {
      return false;
   }
   
   static bool BOOST_RE_CALL is_class(char c, jm_uintfast32_t f)
   {
      return BOOST_RE_MAKE_BOOL(class_map[(size_type)(uchar_type)c] & f);
   }

   static int BOOST_RE_CALL toi(char c);
   static int BOOST_RE_CALL toi(const char*& first, const char* last, int radix);

   static jm_uintfast32_t BOOST_RE_CALL lookup_classname(const char* first, const char* last)
   {
      std::string s(first, last);
      return do_lookup_class(s.c_str());
   }

   static bool BOOST_RE_CALL lookup_collatename(std::string& buf, const char* first, const char* last)
   {
      std::string s(first, last);
      return do_lookup_collate(buf, s.c_str());
   }

   static locale_type imbue(locale_type l){ return l; }
   locale_type BOOST_RE_CALL getloc()const{ return locale_type(); }

   c_regex_traits()
   {
      init();
   }
   ~c_regex_traits()
   {
      free();
   }
   struct sentry
   {
      sentry(const c_regex_traits<char>&)
      { c_regex_traits<char>::update(); }
      operator void*() { return this; }
   };
   static void update();
private:
   static void init();
   static void free();
   static c_regex_traits<char> i;

   static unsigned sort_type;
   static char sort_delim;
};

#ifndef BOOST_RE_NO_WCSTRING
template<>
class BOOST_RE_IX_DECL c_regex_traits<wchar_t> : public re_detail::c_traits_base
{
   typedef re_detail::c_traits_base base_type;
public:
   typedef wchar_t char_type;
   typedef unsigned short uchar_type;
   typedef unsigned int size_type;
   typedef std::basic_string<wchar_t> string_type;
   typedef int locale_type; 
   static size_t BOOST_RE_CALL length(const char_type* p)
   {
      return std::wcslen(p);
   }
   static unsigned int BOOST_RE_CALL syntax_type(size_type c);
   static wchar_t BOOST_RE_CALL translate(wchar_t c, bool icase)
   {
      return icase ? ((c < 256) ? re_detail::wide_lower_case_map[(uchar_type)c] : std::towlower(c)) : c;
   }

   static void BOOST_RE_CALL transform(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in);

   static void BOOST_RE_CALL transform_primary(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in);

   static bool BOOST_RE_CALL is_separator(wchar_t c)
   {
      return BOOST_RE_MAKE_BOOL((c == L'\n') || (c == L'\r') || (c == (wchar_t)0x2028) || (c == (wchar_t)0x2029));
   }

   static bool BOOST_RE_CALL is_combining(wchar_t c)
   { return re_detail::is_combining(c); }
   
   static bool BOOST_RE_CALL is_class(wchar_t c, jm_uintfast32_t f)
   {
      return BOOST_RE_MAKE_BOOL(((uchar_type)c < 256) ? (re_detail::wide_unicode_classes[(size_type)(uchar_type)c] & f) : do_iswclass(c, f));
   }

   static int BOOST_RE_CALL toi(wchar_t c);
   static int BOOST_RE_CALL toi(const wchar_t*& first, const wchar_t* last, int radix);

   static jm_uintfast32_t BOOST_RE_CALL lookup_classname(const wchar_t* first, const wchar_t* last);

   static bool BOOST_RE_CALL lookup_collatename(std::basic_string<wchar_t>& s, const wchar_t* first, const wchar_t* last);

   static locale_type imbue(locale_type l){ return l; }
   locale_type BOOST_RE_CALL getloc()const{ return locale_type(); }
   c_regex_traits<wchar_t>()
   { init(); }
   ~c_regex_traits<wchar_t>()
   { free(); }
   struct sentry
   {
      sentry(const c_regex_traits<wchar_t>&)
      { c_regex_traits<wchar_t>::update(); }
      operator void*() { return this; }
   };
   static void BOOST_RE_CALL update();
   static unsigned int BOOST_RE_CALL strnarrow(char *s1, unsigned int len, const wchar_t *s2);
   static unsigned int BOOST_RE_CALL strwiden(wchar_t *s1, unsigned int len, const char *s2);
private:
   static bool BOOST_RE_CALL do_iswclass(wchar_t c, jm_uintfast32_t f);
   static void BOOST_RE_CALL free();
   static void BOOST_RE_CALL init();
   static bool BOOST_RE_CALL do_lookup_collate(std::basic_string<wchar_t>& out, const wchar_t* first, const wchar_t* last);
   static c_regex_traits<wchar_t> init_;

   static unsigned sort_type;
   static wchar_t sort_delim;
};
#endif

#if defined(_WIN32) && !defined(BOOST_RE_NO_W32)

namespace re_detail{

struct BOOST_RE_IX_DECL w32_traits_base : public regex_traits_base
{
   enum{
   char_class_none = 0,
   char_class_alnum = C1_ALPHA | C1_DIGIT,
   char_class_alpha = C1_ALPHA,
   char_class_cntrl = C1_CNTRL,
   char_class_digit = C1_DIGIT,
   char_class_graph = C1_UPPER | C1_LOWER | C1_DIGIT | C1_PUNCT | C1_ALPHA,
   char_class_lower = C1_LOWER,
   char_class_print = C1_UPPER | C1_LOWER | C1_DIGIT | C1_PUNCT | C1_BLANK | C1_ALPHA,
   char_class_punct = C1_PUNCT,
   char_class_space = C1_SPACE,
   char_class_upper = C1_UPPER,
   char_class_xdigit = C1_XDIGIT,
   char_class_blank = C1_BLANK,
   char_class_underscore = 0x0200,
   char_class_word = C1_ALPHA | C1_DIGIT | char_class_underscore,
   char_class_unicode = 0x0400
   };
public:
   static std::string set_message_catalogue(const std::string& s);
protected:
   static char regex_message_catalogue[200];
   enum syntax_map_size
   {
      map_size = UCHAR_MAX + 1
   };

   static unsigned char syntax_map[map_size];
   static unsigned short class_map[map_size];
   static char lower_case_map[map_size];

   static jm_uintfast32_t BOOST_RE_CALL do_lookup_class(const char* p);
   static bool BOOST_RE_CALL do_lookup_collate(std::string& buf, const char* p);
   static void BOOST_RE_CALL do_free();
   static void BOOST_RE_CALL do_init();
public:
   static std::string error_string(unsigned id);
   static char* get_catalogue() { return regex_message_catalogue; }
};

} // namespace re_detail

template<class charT>
class w32_regex_traits;

template<>
class BOOST_RE_IX_DECL w32_regex_traits<char> : public re_detail::w32_traits_base
{
   typedef re_detail::w32_traits_base base_type;
public:
   typedef char char_type;
   typedef unsigned char uchar_type;
   typedef unsigned int size_type;
   typedef std::string string_type;
   typedef int locale_type;

   static size_t BOOST_RE_CALL length(const char_type* p)
   {
      return std::strlen(p);
   }
   static unsigned int BOOST_RE_CALL syntax_type(size_type c)
   {
      return syntax_map[c];
   }
   static char BOOST_RE_CALL translate(char c, bool icase)
   {
      return icase ? lower_case_map[(size_type)(uchar_type)c] : c;
   }
   static void BOOST_RE_CALL transform(std::string& out, const std::string& in);

   static void BOOST_RE_CALL transform_primary(std::string& out, const std::string& in);

   static bool BOOST_RE_CALL is_separator(char c)
   {
      return BOOST_RE_MAKE_BOOL((c == '\n') || (c == '\r'));
   }

   static bool BOOST_RE_CALL is_combining(char)
   {
      return false;
   }
   
   static bool BOOST_RE_CALL is_class(char c, jm_uintfast32_t f)
   {
      return BOOST_RE_MAKE_BOOL(class_map[(size_type)(uchar_type)c] & f);
   }

   static int BOOST_RE_CALL toi(char c);
   static int BOOST_RE_CALL toi(const char*& first, const char* last, int radix);

   static jm_uintfast32_t BOOST_RE_CALL lookup_classname(const char* first, const char* last)
   {
      std::string s(first, last);
      return do_lookup_class(s.c_str());
   }

   static bool BOOST_RE_CALL lookup_collatename(std::string& buf, const char* first, const char* last)
   {
      std::string s(first, last);
      return do_lookup_collate(buf, s.c_str());
   }

   static locale_type imbue(locale_type l){ return l; }
   locale_type BOOST_RE_CALL getloc()const{ return locale_type(); }

   struct sentry
   {
      sentry(const w32_regex_traits<char>&)
      { w32_regex_traits<char>::update(); }
      ~sentry(){}
      operator void*() { return this; }
   };
   static void update();
   w32_regex_traits();
   ~w32_regex_traits();
private:
   static w32_regex_traits<char> i;
};

#ifndef BOOST_RE_NO_WCSTRING
template<>
class BOOST_RE_IX_DECL w32_regex_traits<wchar_t> : public re_detail::w32_traits_base
{
   typedef re_detail::w32_traits_base base_type;
public:
   typedef wchar_t char_type;
   typedef unsigned short uchar_type;
   typedef unsigned int size_type;
   typedef std::basic_string<wchar_t> string_type;
   typedef int locale_type; 
   static size_t BOOST_RE_CALL length(const char_type* p)
   {
      return std::wcslen(p);
   }
   static unsigned int BOOST_RE_CALL syntax_type(size_type c);
   static wchar_t BOOST_RE_CALL translate(wchar_t c, bool icase)
   {
      return icase ? ((c < 256) ? re_detail::wide_lower_case_map[(uchar_type)c] : wtolower(c)) : c;
   }

   static void BOOST_RE_CALL transform(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in);

   static void BOOST_RE_CALL transform_primary(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in);

   static bool BOOST_RE_CALL is_separator(wchar_t c)
   {
      return BOOST_RE_MAKE_BOOL((c == L'\n') || (c == L'\r') || (c == (wchar_t)0x2028) || (c == (wchar_t)0x2029));
   }

   static bool BOOST_RE_CALL is_combining(wchar_t c)
   { return re_detail::is_combining(c); }
   
   static bool BOOST_RE_CALL is_class(wchar_t c, jm_uintfast32_t f)
   {
      return BOOST_RE_MAKE_BOOL(((uchar_type)c < 256) ? (wide_unicode_classes[(size_type)(uchar_type)c] & f) : do_iswclass(c, f));
   }

   static int BOOST_RE_CALL toi(wchar_t c);
   static int BOOST_RE_CALL toi(const wchar_t*& first, const wchar_t* last, int radix);

   static jm_uintfast32_t BOOST_RE_CALL lookup_classname(const wchar_t* first, const wchar_t* last);

   static bool BOOST_RE_CALL lookup_collatename(std::basic_string<wchar_t>& s, const wchar_t* first, const wchar_t* last);

   static locale_type imbue(locale_type l){ return l; }
   locale_type BOOST_RE_CALL getloc()const{ return locale_type(); }

   struct sentry
   {
      sentry(const w32_regex_traits<wchar_t>&)
      { w32_regex_traits<wchar_t>::update(); }
      ~sentry(){}
      operator void*() { return this; }
   };
   static void BOOST_RE_CALL update();
   w32_regex_traits();
   ~w32_regex_traits();
   static unsigned int BOOST_RE_CALL strnarrow(char *s1, unsigned int len, const wchar_t *s2);
   static unsigned int BOOST_RE_CALL strwiden(wchar_t *s1, unsigned int len, const char *s2);

private:
   static bool BOOST_RE_CALL do_iswclass(wchar_t c, jm_uintfast32_t f);
   static bool BOOST_RE_CALL do_lookup_collate(std::basic_string<wchar_t>& out, const wchar_t* first, const wchar_t* last);
   static w32_regex_traits<wchar_t> init_;
   static wchar_t BOOST_RE_CALL wtolower(wchar_t c);
   static unsigned short wide_unicode_classes[];
};
#endif // Wide strings
#endif // Win32

#ifndef BOOST_RE_NO_LOCALE_H

} // namspace boost

#include <locale>

namespace boost{

namespace re_detail
{

template <class charT>
struct message_data;

template <>
struct message_data<char>;

template <>
struct message_data<wchar_t>;

struct BOOST_RE_IX_DECL cpp_regex_traits_base : public regex_traits_base
{
   enum char_class_type
   {
      char_class_none = 0,
      char_class_alnum = std::ctype_base::alnum,
      char_class_alpha = std::ctype_base::alpha,
      char_class_cntrl = std::ctype_base::cntrl,
      char_class_digit = std::ctype_base::digit,
      char_class_graph = std::ctype_base::graph,
      char_class_lower = std::ctype_base::lower,
      char_class_print = std::ctype_base::print,
      char_class_punct = std::ctype_base::punct,
      char_class_space = std::ctype_base::space,
      char_class_upper = std::ctype_base::upper,
      char_class_xdigit = std::ctype_base::xdigit,
      char_class_blank = 1<<12,
      char_class_underscore = 1<<13,
      char_class_word = std::ctype_base::alnum | char_class_underscore,
      char_class_unicode = 1<<14,
      char_class_all_base = char_class_alnum | char_class_alpha | char_class_cntrl
                         | char_class_digit | char_class_graph | char_class_lower
                         | char_class_print | char_class_punct | char_class_space
                         | char_class_upper | char_class_xdigit
   };

   static std::string set_message_catalogue(const std::string& s);
protected:
   static char regex_message_cat[200];
};

} // namespace re_detail

template <class charT>
class cpp_regex_traits;

template<>
class BOOST_RE_IX_DECL cpp_regex_traits<char> : public re_detail::cpp_regex_traits_base
{
   typedef re_detail::cpp_regex_traits_base base_type;
private:
   re_detail::message_data<char>* pmd;
   const unsigned char* psyntax;
   char* lower_map;
   const std::ctype<char>* pctype;
   const std::collate<char>* pcollate;
   std::locale locale_inst;
   unsigned sort_type;
   char sort_delim;

   cpp_regex_traits(const cpp_regex_traits&);
   cpp_regex_traits& operator=(const cpp_regex_traits&);

public:
   typedef char char_type;
   typedef unsigned char uchar_type;
   typedef unsigned int size_type;
   typedef std::string string_type;
   typedef std::locale locale_type;

   cpp_regex_traits();
   ~cpp_regex_traits();

   static size_t BOOST_RE_CALL length(const char_type* p)
   {
      return std::strlen(p);
   }
   unsigned int BOOST_RE_CALL syntax_type(size_type c)const
   {
      return psyntax[c];
   }
   char BOOST_RE_CALL translate(char c, bool icase)const
   {
      return icase ? lower_map[(size_type)(uchar_type)c] : c;
   }
   void BOOST_RE_CALL transform(std::string& out, const std::string& in)const
   {
      out = pcollate->transform(in.c_str(), in.c_str() + in.size()).c_str();
   }

   void BOOST_RE_CALL transform_primary(std::string& out, const std::string& in)const;

   static bool BOOST_RE_CALL is_separator(char c)
   {
      return BOOST_RE_MAKE_BOOL((c == '\n') || (c == '\r'));
   }

   static bool BOOST_RE_CALL is_combining(char)
   {
      return false;
   }
   
   bool BOOST_RE_CALL is_class(char c, jm_uintfast32_t f)const
   {
      if(pctype->is((std::ctype<char>::mask)(f & char_class_all_base), c))
         return true;
      if((f & char_class_underscore) && (c == '_'))
         return true;
      if((f & char_class_blank) && ((c == ' ') || (c == '\t')))
         return true;
      return false;
   }

   int BOOST_RE_CALL toi(char c)const;
   int BOOST_RE_CALL toi(const char*& first, const char* last, int radix)const;

   jm_uintfast32_t BOOST_RE_CALL lookup_classname(const char* first, const char* last)const;
   bool BOOST_RE_CALL lookup_collatename(std::string& s, const char* first, const char* last)const;

   std::string BOOST_RE_CALL error_string(unsigned id)const;
   locale_type BOOST_RE_CALL imbue(locale_type l);
   locale_type BOOST_RE_CALL BOOST_RE_CALL getloc()const{ return locale_inst; }

   struct sentry
   {
      sentry(const cpp_regex_traits<char>&){}
      operator void*() { return this; }
   };
};

#ifndef BOOST_RE_NO_WCSTRING
template<>
class BOOST_RE_IX_DECL cpp_regex_traits<wchar_t> : public re_detail::cpp_regex_traits_base
{
   typedef re_detail::cpp_regex_traits_base base_type;
public:
   typedef wchar_t char_type;
   typedef unsigned short uchar_type;
   typedef unsigned int size_type;
   typedef std::basic_string<wchar_t> string_type;
   typedef std::locale locale_type;

private:
   re_detail::message_data<wchar_t>* pmd;
   const unsigned char* psyntax;
   wchar_t* lower_map;
   const std::ctype<wchar_t>* pctype;
   const std::collate<wchar_t>* pcollate;
   const std::codecvt<wchar_t, char, std::mbstate_t>* pcdv;
   std::locale locale_inst;
   unsigned int BOOST_RE_CALL do_syntax_type(size_type c)const;
   unsigned sort_type;
   wchar_t sort_delim;

   cpp_regex_traits(const cpp_regex_traits&);
   cpp_regex_traits& operator=(const cpp_regex_traits&);

public:

   static size_t BOOST_RE_CALL length(const char_type* p)
   {
      return std::wcslen(p);
   }
   unsigned int BOOST_RE_CALL syntax_type(size_type c)const
   {
      return (c < UCHAR_MAX) ? psyntax[c] : do_syntax_type(c);
   }
   wchar_t BOOST_RE_CALL translate(wchar_t c, bool icase)const
   {
      return icase ? (((uchar_type)c) <= UCHAR_MAX) ? lower_map[c] : pctype->tolower(c) : c;
   }
   void BOOST_RE_CALL transform(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in)const
   {
      out = pcollate->transform(in.c_str(), in.c_str() + in.size());
   }

   void BOOST_RE_CALL transform_primary(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in)const;

   static bool BOOST_RE_CALL is_separator(wchar_t c)
   {
      return BOOST_RE_MAKE_BOOL((c == L'\n') || (c == L'\r') || (c == (wchar_t)0x2028) || (c == (wchar_t)0x2029));
   }

   static bool BOOST_RE_CALL is_combining(wchar_t c)
   { return re_detail::is_combining(c); }
   
   bool BOOST_RE_CALL is_class(wchar_t c, jm_uintfast32_t f)const
   {
      if(pctype->is((std::ctype<wchar_t>::mask)(f & char_class_all_base), c))
         return true;
      if((f & char_class_underscore) && (c == '_'))
         return true;
      if((f & char_class_blank) && ((c == ' ') || (c == '\t')))
         return true;
      if((f & char_class_unicode) && (c > (size_type)(uchar_type)255))
         return true;
      return false;
   }

   int BOOST_RE_CALL toi(wchar_t c)const;
   int BOOST_RE_CALL toi(const wchar_t*& first, const wchar_t* last, int radix)const;

   jm_uintfast32_t BOOST_RE_CALL lookup_classname(const wchar_t* first, const wchar_t* last)const;
   bool BOOST_RE_CALL lookup_collatename(std::basic_string<wchar_t>& s, const wchar_t* first, const wchar_t* last)const;

   std::string BOOST_RE_CALL error_string(unsigned id)const;
   cpp_regex_traits();
   ~cpp_regex_traits();
   locale_type BOOST_RE_CALL imbue(locale_type l);
   locale_type BOOST_RE_CALL BOOST_RE_CALL getloc()const{ return locale_inst; }
   unsigned int BOOST_RE_CALL strwiden(wchar_t *s1, unsigned int len, const char *s2)const;

   struct sentry
   {
      sentry(const cpp_regex_traits<wchar_t>&){}
      operator void*() { return this; }
   };
};
#endif // BOOST_RE_NO_WCSTRING

#endif // BOOST_RE_NO_LOCALE_H

#ifdef BOOST_RE_LOCALE_W32

template <class charT>
class regex_traits : public w32_regex_traits<charT>
{
};

#elif defined(BOOST_RE_LOCALE_C)

template <class charT>
class regex_traits : public c_regex_traits<charT>
{
};

#elif defined(BOOST_RE_LOCALE_CPP)

template <class charT>
class regex_traits : public cpp_regex_traits<charT>
{
};

#else
#error No default localisation model defined
#endif

#ifdef __BORLANDC__
 #if __BORLANDC__ > 0x520
  #pragma option pop
 #endif
#endif

} // namespace boost

#endif // include

