///////////////////////////////////////////////////////////////////////////////
/// \file cpp_regex_traits.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_TRAITS_CPP_REGEX_TRAITS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_TRAITS_CPP_REGEX_TRAITS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <string>
#include <locale>
#include <sstream>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/integer.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/utility/literals.hpp>

namespace boost { namespace xpressive
{

namespace detail
{

    // define an unsigned integral typedef of the same size as std::ctype_base::mask
    typedef boost::uint_t<sizeof(std::ctype_base::mask) * CHAR_BIT>::least umask_t;
    BOOST_MPL_ASSERT_RELATION(sizeof(std::ctype_base::mask), ==, sizeof(umask_t));

    // Calculate what the size of the umaskex_t type should be to fix the 3 extra bitmasks
    //   11 char categories in ctype_base
    // +  3 extra categories for xpressive
    // = 14 total bits needed
    int const umaskex_bits = (14 > (sizeof(umask_t) * CHAR_BIT)) ? 14 : sizeof(umask_t) * CHAR_BIT;

    // define an unsigned integral type larger than umask_t (+3 for the 3 extra bitmasks below)
    typedef boost::uint_t<umaskex_bits>::fast umaskex_t;
    BOOST_MPL_ASSERT_RELATION(sizeof(umask_t), <=, sizeof(umaskex_t));

    // cast a ctype mask to a umaskex_t
    template<std::ctype_base::mask MaskT>
    struct mask_cast
    {
        BOOST_STATIC_CONSTANT(umaskex_t, value = static_cast<umask_t>(MaskT));
    };

    #ifdef __CYGWIN__
    // Work around a gcc warning on cygwin
    template<>
    struct mask_cast<std::ctype_base::print>
    {
        BOOST_MPL_ASSERT_RELATION('\227', ==, std::ctype_base::print);
        BOOST_STATIC_CONSTANT(umaskex_t, value = 0227);
    };
    #endif

    #ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
    template<std::ctype_base::mask MaskT>
    umaskex_t const mask_cast<MaskT>::value;
    #endif

    // an unsigned integer with the highest bit set
    umaskex_t const highest_bit = 1 << (sizeof(umaskex_t) * CHAR_BIT - 1);

    ///////////////////////////////////////////////////////////////////////////////
    // unused_mask
    //   find a bit in an int that isn't set
    template<umaskex_t In, umaskex_t Out = highest_bit, bool Done = (0 == (Out & In))>
    struct unused_mask
    {
        BOOST_MPL_ASSERT_RELATION(1, !=, Out);
        BOOST_STATIC_CONSTANT(umaskex_t, value = (unused_mask<In, (Out >> 1)>::value));
    };

    template<umaskex_t In, umaskex_t Out>
    struct unused_mask<In, Out, true>
    {
        BOOST_STATIC_CONSTANT(umaskex_t, value = Out);
    };

    #ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
    template<umaskex_t In, umaskex_t Out, bool Done>
    umaskex_t const unused_mask<In, Out, Done>::value;
    #endif

    // Bitwise-or all the ctype masks together
    umaskex_t const all_ctype_masks =
        mask_cast<std::ctype_base::alnum>::value | mask_cast<std::ctype_base::alpha>::value
      | mask_cast<std::ctype_base::cntrl>::value | mask_cast<std::ctype_base::digit>::value
      | mask_cast<std::ctype_base::graph>::value | mask_cast<std::ctype_base::lower>::value
      | mask_cast<std::ctype_base::print>::value | mask_cast<std::ctype_base::punct>::value
      | mask_cast<std::ctype_base::space>::value | mask_cast<std::ctype_base::upper>::value
      | mask_cast<std::ctype_base::xdigit>::value;

    // define a new mask for "underscore" ("word" == alnum | underscore)
    umaskex_t const std_ctype_underscore = unused_mask<all_ctype_masks>::value;

    // define a new mask for "blank"
    umaskex_t const std_ctype_blank = unused_mask<all_ctype_masks | std_ctype_underscore>::value;

    // define a new mask for "newline"
    umaskex_t const std_ctype_newline = unused_mask<all_ctype_masks | std_ctype_underscore | std_ctype_blank>::value;

    ///////////////////////////////////////////////////////////////////////////////
    // cpp_regex_traits_base
    //   BUGBUG this should be replaced with a regex facet that lets you query for
    //   an array of underscore characters and an array of line separator characters.
    template<typename CharT, std::size_t SizeOfCharT = sizeof(CharT)>
    struct cpp_regex_traits_base
    {
    protected:
        template<typename TraitsT>
        void imbue(TraitsT const &tr)
        {
        }
    };

    template<typename CharT>
    struct cpp_regex_traits_base<CharT, 1>
    {
    protected:
        template<typename TraitsT>
        void imbue(TraitsT const &tr)
        {
            int i = 0;
            CharT allchars[UCHAR_MAX + 1];
            for(i = 0; i <= UCHAR_MAX; ++i)
            {
                allchars[i] = static_cast<CharT>(i);
            }

            std::ctype<CharT> const &ct = BOOST_USE_FACET(std::ctype<CharT>, tr.getloc());
            std::ctype_base::mask tmp[UCHAR_MAX + 1];
            ct.is(allchars, allchars + UCHAR_MAX + 1, tmp);
            for(i = 0; i <= UCHAR_MAX; ++i)
            {
                this->masks_[i] = static_cast<umask_t>(tmp[i]);
            }

            this->masks_[static_cast<unsigned char>('_')] |= detail::std_ctype_underscore;
            this->masks_[static_cast<unsigned char>(' ')] |= detail::std_ctype_blank;
            this->masks_[static_cast<unsigned char>('\t')] |= detail::std_ctype_blank;
            this->masks_[static_cast<unsigned char>('\n')] |= detail::std_ctype_newline;
            this->masks_[static_cast<unsigned char>('\r')] |= detail::std_ctype_newline;
            this->masks_[static_cast<unsigned char>('\f')] |= detail::std_ctype_newline;
        }
 
        umaskex_t masks_[UCHAR_MAX + 1];
    };

    #ifndef BOOST_XPRESSIVE_NO_WREGEX
    template<std::size_t SizeOfCharT>
    struct cpp_regex_traits_base<wchar_t, SizeOfCharT>
    {
    protected:
        template<typename TraitsT>
        static void imbue(TraitsT const &)
        {
        }
    };
    #endif

    template<typename CharT>
    struct version_tag
    {
        typedef regex_traits_version_1_tag type;
    };

    template<>
    struct version_tag<char>
    {
        typedef regex_traits_version_1_case_fold_tag type;
    };

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// cpp_regex_traits
//
/// \brief Encapsaulates a std::locale for use by the 
/// basic_regex\<\> class template.
template<typename CharT>
struct cpp_regex_traits
  : detail::cpp_regex_traits_base<CharT>
{
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::locale locale_type;
    typedef detail::umaskex_t char_class_type;
    typedef typename detail::version_tag<CharT>::type version_tag;
    typedef detail::cpp_regex_traits_base<CharT> base_type;

    /// Initialize a cpp_regex_traits object to use the specified std::locale,
    /// or the global std::locale if none is specified.
    ///
    cpp_regex_traits(locale_type const &loc = locale_type())
      : base_type()
      , loc_()
    {
        this->imbue(loc);
    }

    /// Checks two cpp_regex_traits objects for equality
    ///
    /// \return this->getloc() == that.getloc().
    bool operator ==(cpp_regex_traits<char_type> const &that) const
    {
        return this->loc_ == that.loc_;
    }

    /// Checks two cpp_regex_traits objects for inequality
    ///
    /// \return this->getloc() != that.getloc().
    bool operator !=(cpp_regex_traits<char_type> const &that) const
    {
        return this->loc_ != that.loc_;
    }

    /// Convert a char to a CharT
    ///
    /// \param ch The source character.
    /// \return std::use_facet<std::ctype<char_type> >(this->getloc()).widen(ch).
    char_type widen(char ch) const
    {
        return this->ctype_->widen(ch);
    }

    /// Returns a hash value for a CharT in the range [0, UCHAR_MAX]
    ///
    /// \param ch The source character.
    /// \return a value between 0 and UCHAR_MAX, inclusive.
    static unsigned char hash(char_type ch)
    {
        return static_cast<unsigned char>(std::char_traits<CharT>::to_int_type(ch));
    }

    /// No-op
    ///
    /// \param ch The source character.
    /// \return ch
    static char_type translate(char_type ch)
    {
        return ch;
    }

    /// Converts a character to lower-case using the internally-stored std::locale.
    ///
    /// \param ch The source character.
    /// \return std::tolower(ch, this->getloc()).
    char_type translate_nocase(char_type ch) const
    {
        return this->ctype_->tolower(ch);
    }

    /// Returns a string_type containing all the characters that compare equal
    /// disregrarding case to the one passed in. This function can only be called
    /// if is_convertible<version_tag*, regex_traits_version_1_case_fold_tag*>::value
    /// is true.
    ///
    /// \param ch The source character.
    /// \return string_type containing all chars which are equal to ch when disregarding
    ///     case
    //typedef array<char_type, 2> fold_case_type;
    string_type fold_case(char_type ch) const
    {
        BOOST_MPL_ASSERT((is_same<char_type, char>));
        char_type ntcs[] = {
            this->ctype_->tolower(ch)
          , this->ctype_->toupper(ch)
          , 0
        };
        if(ntcs[1] == ntcs[0])
            ntcs[1] = 0;
        return string_type(ntcs);
    }

    /// Checks to see if a character is within a character range.
    ///
    /// \param first The bottom of the range, inclusive.
    /// \param last The top of the range, inclusive.
    /// \param ch The source character.
    /// \return first <= ch && ch <= last.
    static bool in_range(char_type first, char_type last, char_type ch)
    {
        return first <= ch && ch <= last;
    }

    /// Checks to see if a character is within a character range, irregardless of case.
    ///
    /// \param first The bottom of the range, inclusive.
    /// \param last The top of the range, inclusive.
    /// \param ch The source character.
    /// \return in_range(first, last, ch) || in_range(first, last, tolower(ch, this->getloc())) ||
    ///     in_range(first, last, toupper(ch, this->getloc()))
    /// \attention The default implementation doesn't do proper Unicode
    ///     case folding, but this is the best we can do with the standard
    ///     ctype facet.
    bool in_range_nocase(char_type first, char_type last, char_type ch) const
    {
        // NOTE: this default implementation doesn't do proper Unicode
        // case folding, but this is the best we can do with the standard
        // std::ctype facet.
        return this->in_range(first, last, ch)
            || this->in_range(first, last, this->ctype_->toupper(ch))
            || this->in_range(first, last, this->ctype_->tolower(ch));
    }

    /// INTERNAL ONLY
    //string_type transform(char_type const *begin, char_type const *end) const
    //{
    //    return this->collate_->transform(begin, end);
    //}

    /// Returns a sort key for the character sequence designated by the iterator range [F1, F2)
    /// such that if the character sequence [G1, G2) sorts before the character sequence [H1, H2)
    /// then v.transform(G1, G2) < v.transform(H1, H2).
    ///
    /// \attention Not used in xpressive 1.0
    template<typename FwdIterT>
    string_type transform(FwdIterT begin, FwdIterT end) const
    {
        //string_type str(begin, end);
        //return this->transform(str.data(), str.data() + str.size());

        BOOST_ASSERT(false);
        return string_type();
    }

    /// Returns a sort key for the character sequence designated by the iterator range [F1, F2)
    /// such that if the character sequence [G1, G2) sorts before the character sequence [H1, H2)
    /// when character case is not considered then
    /// v.transform_primary(G1, G2) < v.transform_primary(H1, H2).
    /// 
    /// \attention Not used in xpressive 1.0
    template<typename FwdIterT>
    string_type transform_primary(FwdIterT begin, FwdIterT end) const
    {
        BOOST_ASSERT(false); // TODO implement me
        return string_type();
    }

    /// Returns a sequence of characters that represents the collating element
    /// consisting of the character sequence designated by the iterator range [F1, F2).
    /// Returns an empty string if the character sequence is not a valid collating element.
    ///
    /// \attention Not used in xpressive 1.0
    template<typename FwdIterT>
    string_type lookup_collatename(FwdIterT begin, FwdIterT end) const
    {
        BOOST_ASSERT(false); // TODO implement me
        return string_type();
    }

    /// For the character class name represented by the specified character sequence,
    /// return the corresponding bitmask representation.
    ///
    /// \param begin A forward iterator to the start of the character sequence representing
    ///     the name of the character class.
    /// \param end The end of the character sequence.
    /// \param icase Specifies whether the returned bitmask should represent the case-insensitive
    ///     version of the character class.
    /// \return A bitmask representing the character class.
    template<typename FwdIterT>
    char_class_type lookup_classname(FwdIterT begin, FwdIterT end, bool icase) const
    {
        static detail::umaskex_t const icase_masks =
            detail::mask_cast<std::ctype_base::lower>::value | detail::mask_cast<std::ctype_base::upper>::value;

        BOOST_ASSERT(begin != end);
        char_class_type char_class = this->lookup_classname_impl_(begin, end);
        if(0 == char_class)
        {
            // convert the string to lowercase
            string_type classname(begin, end);
            for(typename string_type::size_type i = 0, len = classname.size(); i < len; ++i)
            {
                classname[i] = this->translate_nocase(classname[i]);
            }
            char_class = this->lookup_classname_impl_(classname.begin(), classname.end());
        }
        // erase case-sensitivity if icase==true
        if(icase && 0 != (char_class & icase_masks))
        {
            char_class |= icase_masks;
        }
        return char_class;
    }

    /// Tests a character against a character class bitmask.
    ///
    /// \param ch The character to test.
    /// \param mask The character class bitmask against which to test.
    /// \pre mask is a bitmask returned by lookup_classname, or is several such masks bit-or'ed
    ///     together.
    /// \return true if the character is a member of any of the specified character classes, false
    ///     otherwise.
    bool isctype(char_type ch, char_class_type mask) const
    {
        return this->isctype_impl_(ch, mask, mpl::sizeof_<char_type>());
    }

    /// Convert a digit character into the integer it represents.
    ///
    /// \param ch The digit character.
    /// \param radix The radix to use for the conversion.
    /// \pre radix is one of 8, 10, or 16.
    /// \return -1 if ch is not a digit character, the integer value of the character otherwise. 
    ///     The conversion is performed by imbueing a std::stringstream with this->getloc();
    ///     setting the radix to one of oct, hex or dec; inserting ch into the stream; and
    ///     extracting an int.
    int value(char_type ch, int radix) const
    {
        BOOST_ASSERT(8 == radix || 10 == radix || 16 == radix);
        int val = -1;
        std::basic_stringstream<char_type> str;
        str.imbue(this->getloc());
        str << (8 == radix ? std::oct : (16 == radix ? std::hex : std::dec));
        str << ch;
        str >> val; // if this fails, it leaves val unchanged (-1)
        return val;
    }

    /// Imbues *this with loc
    ///
    /// \param loc A std::locale.
    /// \return the previous std::locale used by *this.
    locale_type imbue(locale_type loc)
    {
        locale_type old_loc = this->loc_;
        this->loc_ = loc;
        this->ctype_ = &BOOST_USE_FACET(std::ctype<char_type>, this->loc_);
        //this->collate_ = &BOOST_USE_FACET(std::collate<char_type>, this->loc_);
        this->base_type::imbue(*this);
        return old_loc;
    }

    /// Returns the current std::locale used by *this.
    ///
    locale_type getloc() const
    {
        return this->loc_;
    }

private:

    ///////////////////////////////////////////////////////////////////////////////
    // isctype_impl_
    /// INTERNAL ONLY
    bool isctype_impl_(char_type ch, char_class_type mask, mpl::size_t<1>) const
    {
        return 0 != (this->masks_[static_cast<unsigned char>(ch)] & mask);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // isctype_impl_
    /// INTERNAL ONLY
    bool isctype_impl_(char_type ch, char_class_type mask, std::size_t) const
    {
        if(this->ctype_->is(static_cast<std::ctype_base::mask>((detail::umask_t)mask), ch))
        {
            return true;
        }

        switch(ch)
        {
        case L'\t': return 0 != (mask & detail::std_ctype_blank);
        case L'_': return 0 != (mask & detail::std_ctype_underscore);
        case L'\n': case L'\r': case L'\f': case 0x2028u: case 0x2029u: case 0x85u:
            return 0 != (mask & detail::std_ctype_newline);
        default:;
        }

        return false;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // char_class_pair
    /// INTERNAL ONLY
    struct char_class_pair
    {
        char_type const *const class_name_;
        char_class_type const class_type_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // char_class
    /// INTERNAL ONLY
    static char_class_pair const &char_class(std::size_t j)
    {
        using namespace detail;
        static char_class_pair const s_char_class_map[] =
        {
            { BOOST_XPR_CSTR_(char_type, "alnum"),  mask_cast<std::ctype_base::alnum>::value }
          , { BOOST_XPR_CSTR_(char_type, "alpha"),  mask_cast<std::ctype_base::alpha>::value }
          , { BOOST_XPR_CSTR_(char_type, "blank"),  std_ctype_blank }
          , { BOOST_XPR_CSTR_(char_type, "cntrl"),  mask_cast<std::ctype_base::cntrl>::value }
          , { BOOST_XPR_CSTR_(char_type, "d"),      mask_cast<std::ctype_base::digit>::value }
          , { BOOST_XPR_CSTR_(char_type, "digit"),  mask_cast<std::ctype_base::digit>::value }
          , { BOOST_XPR_CSTR_(char_type, "graph"),  mask_cast<std::ctype_base::graph>::value }
          , { BOOST_XPR_CSTR_(char_type, "lower"),  mask_cast<std::ctype_base::lower>::value }
          , { BOOST_XPR_CSTR_(char_type, "newline"),std_ctype_newline }
          , { BOOST_XPR_CSTR_(char_type, "print"),  mask_cast<std::ctype_base::print>::value }
          , { BOOST_XPR_CSTR_(char_type, "punct"),  mask_cast<std::ctype_base::punct>::value }
          , { BOOST_XPR_CSTR_(char_type, "s"),      mask_cast<std::ctype_base::space>::value }
          , { BOOST_XPR_CSTR_(char_type, "space"),  mask_cast<std::ctype_base::space>::value }
          , { BOOST_XPR_CSTR_(char_type, "upper"),  mask_cast<std::ctype_base::upper>::value }
          , { BOOST_XPR_CSTR_(char_type, "w"),      mask_cast<std::ctype_base::alnum>::value | std_ctype_underscore }
          , { BOOST_XPR_CSTR_(char_type, "xdigit"), mask_cast<std::ctype_base::xdigit>::value }
          , { 0, 0 }
        };
        return s_char_class_map[j];
    }

    ///////////////////////////////////////////////////////////////////////////////
    // lookup_classname_impl
    /// INTERNAL ONLY
    template<typename FwdIterT>
    static char_class_type lookup_classname_impl_(FwdIterT begin, FwdIterT end)
    {
        // find the classname
        for(std::size_t j = 0; 0 != cpp_regex_traits::char_class(j).class_name_; ++j)
        {
            if(compare_(cpp_regex_traits::char_class(j).class_name_, begin, end))
            {
                return cpp_regex_traits::char_class(j).class_type_;
            }
        }
        return 0;
    }

    /// INTERNAL ONLY
    template<typename FwdIterT>
    static bool compare_(char_type const *name, FwdIterT begin, FwdIterT end)
    {
        for(; *name && begin != end; ++name, ++begin)
        {
            if(*name != *begin)
            {
                return false;
            }
        }
        return !*name && begin == end;
    }

    locale_type loc_;
    std::ctype<char_type> const *ctype_;
    //std::collate<char_type> const *collate_;
};

///////////////////////////////////////////////////////////////////////////////
// cpp_regex_traits<>::hash specializations
template<>
inline unsigned char cpp_regex_traits<unsigned char>::hash(unsigned char ch)
{
    return ch;
}

template<>
inline unsigned char cpp_regex_traits<char>::hash(char ch)
{
    return static_cast<unsigned char>(ch);
}

template<>
inline unsigned char cpp_regex_traits<signed char>::hash(signed char ch)
{
    return static_cast<unsigned char>(ch);
}

#ifndef BOOST_XPRESSIVE_NO_WREGEX
template<>
inline unsigned char cpp_regex_traits<wchar_t>::hash(wchar_t ch)
{
    return static_cast<unsigned char>(ch);
}
#endif

}}

#endif
