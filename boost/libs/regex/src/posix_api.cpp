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
  *   FILE:        posix_api.cpp
  *   VERSION:     3.04
  *   DESCRIPTION: Implements the Posix API wrappers.
  */

#include <cstdio>
#include <boost/regex.hpp>

namespace boost{

namespace{

unsigned int magic_value = 25631;

const char* names[] = {"REG_NOERROR", "REG_NOMATCH", "REG_BADPAT", "REG_ECOLLATE",
                        "REG_ECTYPE", "REG_EESCAPE", "REG_ESUBREG", "REG_EBRACK",
                        "REG_EPAREN", "REG_EBRACE", "REG_BADBR", "REG_ERANGE",
                        "REG_ESPACE", "REG_BADRPT", "REG_EMPTY", "REG_E_UNKNOWN"};
} // namespace

BOOST_RE_IX_DECL int BOOST_RE_CCALL regcompA(regex_tA* expression, const char* ptr, int f)
{
   BOOST_RE_GUARD_STACK
   if(expression->re_magic != magic_value)
   {
      expression->guts = 0;
      try{
      expression->guts = new regex();
      } catch(...)
      {
         return REG_ESPACE;
      }
   }
   // set default flags:
   jm_uintfast32_t flags = (f & REG_EXTENDED) ? regbase::extended : regbase::basic;
   expression->eflags = (f & REG_NEWLINE) ? match_not_dot_newline : 0;
   // and translate those that are actually set:

   if(f & REG_NOCOLLATE)
      flags |= regbase::nocollate;

   if(f & REG_NOSUB)
      expression->eflags |= match_any;

   if(f & REG_NOSPEC)
      flags |= regbase::literal;
   if(f & REG_ICASE)
      flags |= regbase::icase;
   if(f & REG_ESCAPE_IN_LISTS)
      flags |= regbase::escape_in_lists;
   if(f & REG_NEWLINE_ALT)
      flags |= regbase::newline_alt;

   const char* p2;
   if(f & REG_PEND)
      p2 = expression->re_endp;
   else p2 = ptr + std::strlen(ptr);

   int result;

   try{
      expression->re_magic = magic_value;
      ((regex*)(expression->guts))->set_expression(ptr, p2, flags);
      expression->re_nsub = ((regex*)(expression->guts))->mark_count() - 1;
      result = ((regex*)(expression->guts))->error_code();
   } catch(...)
   {
      result = REG_E_UNKNOWN;
   }
   if(result)
      regfreeA(expression);
   return result;

}

BOOST_RE_IX_DECL unsigned int BOOST_RE_CCALL regerrorA(int code, const regex_tA* e, char* buf, unsigned int buf_size)
{
   BOOST_RE_GUARD_STACK
   unsigned int result = 0;
   if(code & REG_ITOA)
   {
      code &= ~REG_ITOA;
      if(code <= REG_E_UNKNOWN)
      {
         result = std::strlen(names[code]) + 1;
         if(buf_size >= result)
            std::strcpy(buf, names[code]);
         return result;
      }
      return result;
   }
   if(code == REG_ATOI)
   {
      char localbuf[5];
      if(e == 0)
         return 0;
      for(int i = 0; i <= REG_E_UNKNOWN; ++i)
      {
         if(std::strcmp(e->re_endp, names[i]) == 0)
         {
            std::sprintf(localbuf, "%d", i);
            if(std::strlen(localbuf) < buf_size)
               std::strcpy(buf, localbuf);
            return std::strlen(localbuf) + 1;
         }
      }
      std::sprintf(localbuf, "%d", 0);
      if(std::strlen(localbuf) < buf_size)
         std::strcpy(buf, localbuf);
      return std::strlen(localbuf) + 1;
   }
   if(code <= REG_E_UNKNOWN)
   {
      std::string p;
      if((e) && (e->re_magic == magic_value))
         p = ((regex*)(e->guts))->get_traits().error_string(code);
      else
      {
         boost::regex_traits<char> t;
         p = t.error_string(code);
      }
      unsigned int len = p.size();
      if(len < buf_size)
      {
         std::strcpy(buf, p.c_str());
      }
      return len + 1;
   }
   if(buf_size)
      *buf = 0;
   return 0;
}

BOOST_RE_IX_DECL int BOOST_RE_CCALL regexecA(const regex_tA* expression, const char* buf, unsigned int n, regmatch_t* array, int eflags)
{
   BOOST_RE_GUARD_STACK
   bool result = false;
   jm_uintfast32_t flags = match_default | expression->eflags;
   const char* end;
   const char* start;
   cmatch m;
   
   if(eflags & REG_NOTBOL)
      flags |= match_not_bol;
   if(eflags & REG_NOTEOL)
      flags |= match_not_eol;
   if(eflags & REG_STARTEND)
   {
      start = buf + array[0].rm_so;
      end = buf + array[0].rm_eo;
   }
   else
   {
      start = buf;
      end = buf + std::strlen(buf);
   }

   try{
   if(expression->re_magic == magic_value)
   {
      result = regex_search(start, end, m, *(regex*)(expression->guts), flags);
   }
   else
      return result;
   } catch(...)
   {
      return REG_E_UNKNOWN;
   }

   if(result)
   {
      // extract what matched:
     unsigned int i;
      for(i = 0; (i < n) && (i < expression->re_nsub + 1); ++i)
      {
         array[i].rm_so = (m[i].matched == false) ? -1 : (m[i].first - buf);
         array[i].rm_eo = (m[i].matched == false) ? -1 : (m[i].second - buf);
      }
      // and set anything else to -1:
      for(i = expression->re_nsub + 1; i < n; ++i)
      {
         array[i].rm_so = -1;
         array[i].rm_eo = -1;
      }
      return 0;
   }
   return REG_NOMATCH;
}

BOOST_RE_IX_DECL void BOOST_RE_CCALL regfreeA(regex_tA* expression)
{
   BOOST_RE_GUARD_STACK
   if(expression->re_magic == magic_value)
   {
      delete (regex*)(expression->guts);
   }
   expression->re_magic = 0;
}

} // namespace boost


