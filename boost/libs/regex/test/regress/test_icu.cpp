/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         test_icu.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Test code for Unicode regexes with ICU support.
  */

//
// We can only build this if we have ICU support:
//
#include <boost/regex/config.hpp>
#if defined(BOOST_HAS_ICU) && !defined(BOOST_NO_STD_WSTRING)

#include <boost/regex/icu.hpp>
#include "test.hpp"

//
// compare two match_results struct's for equality,
// converting the iterator as needed:
//
template <class MR1, class MR2>
void compare_result(const MR1& w1, const MR2& w2, boost::mpl::int_<2> const*)
{
   typedef boost::u16_to_u32_iterator<typename MR2::value_type::const_iterator> iterator_type;
   typedef typename MR1::size_type size_type;
   if(w1.size() != w2.size())
   {
      BOOST_REGEX_TEST_ERROR("Size mismatch in match_results class", UChar32);
   }
   for(int i = 0; i < (int)w1.size(); ++i)
   {
      if(w1[i].matched)
      {
         if(w2[i].matched == 0)
         {
            BOOST_REGEX_TEST_ERROR("Matched mismatch in match_results class", UChar32);
         }
         if((w1.position(i) != boost::re_detail::distance(iterator_type(w2.prefix().first), iterator_type(w2[i].first))) || (w1.length(i) != boost::re_detail::distance(iterator_type(w2[i].first), iterator_type(w2[i].second))))
         {
            BOOST_REGEX_TEST_ERROR("Iterator mismatch in match_results class", UChar32);
         }
      }
      else if(w2[i].matched)
      {
         BOOST_REGEX_TEST_ERROR("Matched mismatch in match_results class", UChar32);
      }
   }
}
template <class MR1, class MR2>
void compare_result(const MR1& w1, const MR2& w2, boost::mpl::int_<1> const*)
{
   typedef boost::u8_to_u32_iterator<typename MR2::value_type::const_iterator> iterator_type;
   typedef typename MR1::size_type size_type;
   if(w1.size() != w2.size())
   {
      BOOST_REGEX_TEST_ERROR("Size mismatch in match_results class", UChar32);
   }
   for(int i = 0; i < (int)w1.size(); ++i)
   {
      if(w1[i].matched)
      {
         if(w2[i].matched == 0)
         {
            BOOST_REGEX_TEST_ERROR("Matched mismatch in match_results class", UChar32);
         }
         if((w1.position(i) != boost::re_detail::distance(iterator_type(w2.prefix().first), iterator_type(w2[i].first))) || (w1.length(i) != boost::re_detail::distance(iterator_type(w2[i].first), iterator_type(w2[i].second))))
         {
            BOOST_REGEX_TEST_ERROR("Iterator mismatch in match_results class", UChar32);
         }
      }
      else if(w2[i].matched)
      {
         BOOST_REGEX_TEST_ERROR("Matched mismatch in match_results class", UChar32);
      }
   }
}

void test_icu_grep(const boost::u32regex& r, const std::vector< ::UChar32>& search_text)
{
   typedef std::vector< ::UChar32>::const_iterator const_iterator;
   typedef boost::u32regex_iterator<const_iterator> test_iterator;
   boost::regex_constants::match_flag_type opts = test_info<wchar_t>::match_options();
   const int* answer_table = test_info<wchar_t>::answer_table();
   test_iterator start(search_text.begin(), search_text.end(), r, opts), end;
   test_iterator copy(start);
   const_iterator last_end = search_text.begin();
   while(start != end)
   {
      if(start != copy)
      {
         BOOST_REGEX_TEST_ERROR("Failed iterator != comparison.", wchar_t);
      }
      if(!(start == copy))
      {
         BOOST_REGEX_TEST_ERROR("Failed iterator == comparison.", wchar_t);
      }
      test_result(*start, search_text.begin(), answer_table);
      // test $` and $' :
      if(start->prefix().first != last_end)
      {
         BOOST_REGEX_TEST_ERROR("Incorrect position for start of $`", wchar_t);
      }
      if(start->prefix().second != (*start)[0].first)
      {
         BOOST_REGEX_TEST_ERROR("Incorrect position for end of $`", wchar_t);
      }
      if(start->prefix().matched != (start->prefix().first != start->prefix().second))
      {
         BOOST_REGEX_TEST_ERROR("Incorrect position for matched member of $`", wchar_t);
      }
      if(start->suffix().first != (*start)[0].second)
      {
         BOOST_REGEX_TEST_ERROR("Incorrect position for start of $'", wchar_t);
      }
      if(start->suffix().second != search_text.end())
      {
         BOOST_REGEX_TEST_ERROR("Incorrect position for end of $'", wchar_t);
      }
      if(start->suffix().matched != (start->suffix().first != start->suffix().second))
      {
         BOOST_REGEX_TEST_ERROR("Incorrect position for matched member of $'", wchar_t);
      }
      last_end = (*start)[0].second;
      ++start;
      ++copy;
      // move on the answer table to next set of answers;
      if(*answer_table != -2)
         while(*answer_table++ != -2){}
   }
   if(answer_table[0] >= 0)
   {
      // we should have had a match but didn't:
      BOOST_REGEX_TEST_ERROR("Expected match was not found.", wchar_t);
   }
}

void test_icu(const wchar_t&, const test_regex_search_tag& )
{
   boost::u32regex r;
   if(*test_locale::c_str())
   {
      ::Locale l(test_locale::c_str());
      if(l.isBogus())
         return;
      r.imbue(l);
   }

   std::vector< ::UChar32> expression;
   expression.assign(test_info<wchar_t>::expression().begin(), test_info<wchar_t>::expression().end());
   boost::regex_constants::syntax_option_type syntax_options = test_info<UChar32>::syntax_options();
   try{
      r.assign(expression.begin(), expression.end(), syntax_options);
      if(r.status())
      {
         BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done, error code = " << r.status(), UChar32);
      }
      std::vector< ::UChar32> search_text;
      search_text.assign(test_info<wchar_t>::search_text().begin(), test_info<wchar_t>::search_text().end());
      boost::regex_constants::match_flag_type opts = test_info<wchar_t>::match_options();
      const int* answer_table = test_info<wchar_t>::answer_table();
      boost::match_results<std::vector< ::UChar32>::const_iterator> what;
      if(boost::u32regex_search(
         const_cast<std::vector< ::UChar32>const&>(search_text).begin(),
         const_cast<std::vector< ::UChar32>const&>(search_text).end(),
         what,
         r,
         opts))
      {
         test_result(what, const_cast<std::vector< ::UChar32>const&>(search_text).begin(), answer_table);
      }
      else if(answer_table[0] >= 0)
      {
         // we should have had a match but didn't:
         BOOST_REGEX_TEST_ERROR("Expected match was not found.", UChar32);
      }

      if(0 == *test_locale::c_str())
      {
         //
         // Now try UTF-16 construction:
         //
         typedef boost::u32_to_u16_iterator<std::vector<UChar32>::const_iterator> u16_conv;
         std::vector<UChar> expression16, text16;
         boost::match_results<std::vector<UChar>::const_iterator> what16;
         boost::match_results<const UChar*> what16c;
         expression16.assign(u16_conv(expression.begin()), u16_conv(expression.end()));
         text16.assign(u16_conv(search_text.begin()), u16_conv(search_text.end()));
         r = boost::make_u32regex(expression16.begin(), expression16.end(), syntax_options);
         if(boost::u32regex_search(const_cast<const std::vector<UChar>&>(text16).begin(), const_cast<const std::vector<UChar>&>(text16).end(), what16, r, opts))
         {
            compare_result(what, what16, static_cast<boost::mpl::int_<2> const*>(0));
         }
         else if(answer_table[0] >= 0)
         {
            // we should have had a match but didn't:
            BOOST_REGEX_TEST_ERROR("Expected match was not found.", UChar32);
         }
         if(std::find(expression16.begin(), expression16.end(), 0) == expression16.end())
         {
            expression16.push_back(0);
            r = boost::make_u32regex(&*expression16.begin(), syntax_options);
            if(std::find(text16.begin(), text16.end(), 0) == text16.end())
            {
               text16.push_back(0);
               if(boost::u32regex_search((const UChar*)&*text16.begin(), what16c, r, opts))
               {
                  compare_result(what, what16c, static_cast<boost::mpl::int_<2> const*>(0));
               }
               else if(answer_table[0] >= 0)
               {
                  // we should have had a match but didn't:
                  BOOST_REGEX_TEST_ERROR("Expected match was not found.", UChar32);
               }
            }
         }
         //
         // Now try UTF-8 construction:
         //
         typedef boost::u32_to_u8_iterator<std::vector<UChar32>::const_iterator, unsigned char> u8_conv;
         std::vector<unsigned char> expression8, text8;
         boost::match_results<std::vector<unsigned char>::const_iterator> what8;
         boost::match_results<const unsigned char*> what8c;
         expression8.assign(u8_conv(expression.begin()), u8_conv(expression.end()));
         text8.assign(u8_conv(search_text.begin()), u8_conv(search_text.end()));
         r = boost::make_u32regex(expression8.begin(), expression8.end(), syntax_options);
         if(boost::u32regex_search(const_cast<const std::vector<unsigned char>&>(text8).begin(), const_cast<const std::vector<unsigned char>&>(text8).end(), what8, r, opts))
         {
            compare_result(what, what8, static_cast<boost::mpl::int_<1> const*>(0));
         }
         else if(answer_table[0] >= 0)
         {
            // we should have had a match but didn't:
            BOOST_REGEX_TEST_ERROR("Expected match was not found.", UChar32);
         }
         if(std::find(expression8.begin(), expression8.end(), 0) == expression8.end())
         {
            expression8.push_back(0);
            r = boost::make_u32regex(&*expression8.begin(), syntax_options);
            if(std::find(text8.begin(), text8.end(), 0) == text8.end())
            {
               text8.push_back(0);
               if(boost::u32regex_search((const unsigned char*)&*text8.begin(), what8c, r, opts))
               {
                  compare_result(what, what8c, static_cast<boost::mpl::int_<1> const*>(0));
               }
               else if(answer_table[0] >= 0)
               {
                  // we should have had a match but didn't:
                  BOOST_REGEX_TEST_ERROR("Expected match was not found.", UChar32);
               }
            }
         }
      }
      //
      // finally try a grep:
      //
      test_icu_grep(r, search_text);
   }
   catch(const boost::bad_expression& e)
   {
      BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done: " << e.what(), UChar32);
   }
   catch(const std::runtime_error& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::runtime_error: " << r.what(), UChar32);
   }
   catch(const std::exception& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::exception: " << r.what(), UChar32);
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected exception of unknown type", UChar32);
   }
}

void test_icu(const wchar_t&, const test_invalid_regex_tag&)
{
   typedef boost::u16_to_u32_iterator<std::wstring::const_iterator, ::UChar32> conv_iterator;
   std::vector< ::UChar32> expression;
   expression.assign(test_info<wchar_t>::expression().begin(), test_info<wchar_t>::expression().end());
   boost::regex_constants::syntax_option_type syntax_options = test_info<wchar_t>::syntax_options();
   boost::u32regex r;
   if(*test_locale::c_str())
   {
      ::Locale l(test_locale::c_str());
      if(l.isBogus())
         return;
      r.imbue(l);
   }
   //
   // try it with exceptions disabled first:
   //
   try
   {
      if(0 == r.assign(expression.begin(), expression.end(), syntax_options | boost::regex_constants::no_except).status())
      {
         BOOST_REGEX_TEST_ERROR("Expression compiled when it should not have done so.", wchar_t);
      }
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Unexpected exception thrown.", wchar_t);
   }
   //
   // now try again with exceptions:
   //
   bool have_catch = false;
   try{
      r.assign(expression.begin(), expression.end(), syntax_options);
#ifdef BOOST_NO_EXCEPTIONS
      if(r.status())
         have_catch = true;
#endif
   }
   catch(const boost::bad_expression&)
   {
      have_catch = true;
   }
   catch(const std::runtime_error& r)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but a std::runtime_error instead: " << r.what(), wchar_t);
   }
   catch(const std::exception& r)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but a std::exception instead: " << r.what(), wchar_t);
   }
   catch(...)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but got an exception of unknown type instead", wchar_t);
   }
   if(!have_catch)
   {
      // oops expected exception was not thrown:
      BOOST_REGEX_TEST_ERROR("Expected an exception, but didn't find one.", wchar_t);
   }

   if(0 == *test_locale::c_str())
   {
      //
      // Now try UTF-16 construction:
      //
      typedef boost::u32_to_u16_iterator<std::vector<UChar32>::const_iterator> u16_conv;
      std::vector<UChar> expression16;
      expression16.assign(u16_conv(expression.begin()), u16_conv(expression.end()));
      if(0 == boost::make_u32regex(expression16.begin(), expression16.end(), syntax_options | boost::regex_constants::no_except).status())
      {
         BOOST_REGEX_TEST_ERROR("Expression compiled when it should not have done so.", wchar_t);
      }
      if(std::find(expression16.begin(), expression16.end(), 0) == expression16.end())
      {
         expression16.push_back(0);
         if(0 == boost::make_u32regex(&*expression16.begin(), syntax_options | boost::regex_constants::no_except).status())
         {
            BOOST_REGEX_TEST_ERROR("Expression compiled when it should not have done so.", wchar_t);
         }
      }
      //
      // Now try UTF-8 construction:
      //
      typedef boost::u32_to_u8_iterator<std::vector<UChar32>::const_iterator> u8_conv;
      std::vector<unsigned char> expression8;
      expression8.assign(u8_conv(expression.begin()), u8_conv(expression.end()));
      if(0 == boost::make_u32regex(expression8.begin(), expression8.end(), syntax_options | boost::regex_constants::no_except).status())
      {
         BOOST_REGEX_TEST_ERROR("Expression compiled when it should not have done so.", wchar_t);
      }
      if(std::find(expression8.begin(), expression8.end(), 0) == expression8.end())
      {
         expression8.push_back(0);
         if(0 == boost::make_u32regex(&*expression8.begin(), syntax_options | boost::regex_constants::no_except).status())
         {
            BOOST_REGEX_TEST_ERROR("Expression compiled when it should not have done so.", wchar_t);
         }
      }
   }
}

void test_icu(const wchar_t&, const test_regex_replace_tag&)
{
   std::vector< ::UChar32> expression;
   expression.assign(test_info<wchar_t>::expression().begin(), test_info<wchar_t>::expression().end());
   boost::regex_constants::syntax_option_type syntax_options = test_info<UChar32>::syntax_options();
   boost::u32regex r;
   try{
      r.assign(expression.begin(), expression.end(), syntax_options);
      if(r.status())
      {
         BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done, error code = " << r.status(), UChar32);
      }
      typedef std::vector<UChar32> string_type;
      string_type search_text;
      search_text.assign(test_info<UChar32>::search_text().begin(), test_info<UChar32>::search_text().end());
      boost::regex_constants::match_flag_type opts = test_info<UChar32>::match_options();
      string_type format_string;
      format_string.assign(test_info<UChar32>::format_string().begin(), test_info<UChar32>::format_string().end());
      format_string.push_back(0);
      string_type result_string;
      result_string.assign(test_info<UChar32>::result_string().begin(), test_info<UChar32>::result_string().end());
      string_type result;

      boost::u32regex_replace(std::back_inserter(result), search_text.begin(), search_text.end(), r, &*format_string.begin(), opts);
      if(result != result_string)
      {
         BOOST_REGEX_TEST_ERROR("regex_replace generated an incorrect string result", UChar32);
      }
      //
      // Mixed mode character encoding:
      //
      if(0 == *test_locale::c_str())
      {
         //
         // Now try UTF-16 construction:
         //
         typedef boost::u32_to_u16_iterator<std::vector<UChar32>::const_iterator> u16_conv;
         std::vector<UChar> expression16, text16, format16, result16, found16;
         expression16.assign(u16_conv(expression.begin()), u16_conv(expression.end()));
         text16.assign(u16_conv(search_text.begin()), u16_conv(search_text.end()));
         format16.assign(u16_conv(format_string.begin()), u16_conv(format_string.end()));
         result16.assign(u16_conv(result_string.begin()), u16_conv(result_string.end()));
         r = boost::make_u32regex(expression16.begin(), expression16.end(), syntax_options);
         boost::u32regex_replace(std::back_inserter(found16), text16.begin(), text16.end(), r, &*format16.begin(), opts);
         if(result16 != found16)
         {
            BOOST_REGEX_TEST_ERROR("u32regex_replace with UTF-16 string returned incorrect result", UChar32);
         }
         //
         // Now with UnicodeString:
         //
         UnicodeString expression16u, text16u, format16u, result16u, found16u;
         expression16u.setTo(&*expression16.begin(), expression16.size());
         text16u.setTo(&*text16.begin(), text16.size());
         format16u.setTo(&*format16.begin(), format16.size()-1);
         result16u.setTo(&*result16.begin(), result16.size());
         r = boost::make_u32regex(expression16.begin(), expression16.end(), syntax_options);
         found16u = boost::u32regex_replace(text16u, r, format16u, opts);
         if(result16u != found16u)
         {
            BOOST_REGEX_TEST_ERROR("u32regex_replace with UTF-16 string returned incorrect result", UChar32);
         }

         //
         // Now try UTF-8 construction:
         //
         typedef boost::u32_to_u8_iterator<std::vector<UChar32>::const_iterator, unsigned char> u8_conv;
         std::vector<char> expression8, text8, format8, result8, found8;
         expression8.assign(u8_conv(expression.begin()), u8_conv(expression.end()));
         text8.assign(u8_conv(search_text.begin()), u8_conv(search_text.end()));
         format8.assign(u8_conv(format_string.begin()), u8_conv(format_string.end()));
         result8.assign(u8_conv(result_string.begin()), u8_conv(result_string.end()));
         r = boost::make_u32regex(expression8.begin(), expression8.end(), syntax_options);
         boost::u32regex_replace(std::back_inserter(found8), text8.begin(), text8.end(), r, &*format8.begin(), opts);
         if(result8 != found8)
         {
            BOOST_REGEX_TEST_ERROR("u32regex_replace with UTF-8 string returned incorrect result", UChar32);
         }
         //
         // Now with std::string and UTF-8:
         //
         std::string expression8s, text8s, format8s, result8s, found8s;
         expression8s.assign(&*expression8.begin(), expression8.size());
         text8s.assign(&*text8.begin(), text8.size());
         format8s.assign(&*format8.begin(), format8.size()-1);
         result8s.assign(&*result8.begin(), result8.size());
         r = boost::make_u32regex(expression8.begin(), expression8.end(), syntax_options);
         found8s = boost::u32regex_replace(text8s, r, format8s, opts);
         if(result8s != found8s)
         {
            BOOST_REGEX_TEST_ERROR("u32regex_replace with UTF-8 string returned incorrect result", UChar32);
         }
      }
   }
   catch(const boost::bad_expression& e)
   {
      BOOST_REGEX_TEST_ERROR("Expression did not compile when it should have done: " << e.what(), UChar32);
   }
   catch(const std::runtime_error& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::runtime_error: " << r.what(), UChar32);
   }
   catch(const std::exception& r)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected std::exception: " << r.what(), UChar32);
   }
   catch(...)
   {
      BOOST_REGEX_TEST_ERROR("Received an unexpected exception of unknown type", UChar32);
   }
}

#else

#include "test.hpp"

void test_icu(const wchar_t&, const test_regex_search_tag&){}
void test_icu(const wchar_t&, const test_invalid_regex_tag&){}
void test_icu(const wchar_t&, const test_regex_replace_tag&){}

#endif
