#ifndef BOOST_ARCHIVE_BASIC_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/archive/detail/common_oarchive.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/string.hpp>

namespace boost { 
namespace archive {
        
//////////////////////////////////////////////////////////////////////
// class xml_oarchive - write serialized objects to a xml output stream
template<class Archive>
class basic_xml_oarchive : public detail::common_oarchive<Archive>
{
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
public:
#elif defined(BOOST_MSVC)
    // for some inexplicable reason insertion of "class" generates compile erro
    // on msvc 7.1
    friend detail::interface_oarchive<Archive>;
protected:
#else
    friend class detail::interface_oarchive<Archive>;
protected:
#endif
    // special stuff for xml output
    unsigned int depth;
    bool indent_next;
    bool pending_preamble;
    bool header;
    void indent();
    void init();
    void write_attribute(
        const char *attribute_name, 
        int t,
        const char *conjunction = "=\""
    );
    void write_attribute(
        const char *attribute_name, 
        const char *key
    );
    // helpers used below
    void save_start(const char *name);
    void save_end(const char *name);
    void end_preamble();

#if 0
    // note: we have to go through a little extra funny business
    // to accommodate non-conforming compilers.
    template<class T>
    struct save_primitive_impl {
        static void invoke(Archive & ar, const T & t){
            archive::save_access::save_primitive(ar, t);
        }
    };

    template<class T>
    struct save_non_primitive_impl {
        static void invoke(Archive & ar, const T & t){
            archive::save(ar, t);
        }
    };

    template<class T>
    void save_impl(const T & t){
        mpl::apply_if<
            #ifndef BOOST_NO_STD_WSTRING
                 mpl::or_<
                    mpl::equal_to<
                        ::boost::serialization::implementation_level<T>,
                        // don't forget the damn space between < and :: !
                        mpl::int_< ::boost::serialization::primitive_type>
                    >,
                    is_same<T, std::string>,
                    is_same<T, std::wstring>
                >,
            #else
               is_same<T, std::string>,
            #endif
            mpl::identity<save_primitive_impl<T> >,
            mpl::identity<save_non_primitive_impl<T> >
        >::type::invoke(* this->This(),  t);
    }
#endif

    // Anything not an attribute and not a name-value pair is an
    // error and should be trapped here.
    template<class T>
    void save_override(const T & t, BOOST_PFTO int)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_STATIC_ASSERT(0 == sizeof(T));
    }

   // special treatment for name-value pairs.
    template<class T>
    void save_override(const ::boost::serialization::nvp<T> & t, int)
    {
        this->This()->save_start(t.name());
        archive::save(* this->This(), t.value()); 
        this->This()->save_end(t.name());
    }

    // specific overrides for attributes - not name value pairs so we
    // want to trap them before the above "fall through"
    void save_override(const object_id_type & t, int);
    void save_override(const object_reference_type & t, int);
    void save_override(const version_type & t, int);
    void save_override(const class_id_type & t, int);
    void save_override(const class_id_optional_type & t, int);
    void save_override(const class_id_reference_type & t, int);
    void save_override(const class_name_type & t, int);
    void save_override(const tracking_type & t, int);

    basic_xml_oarchive(unsigned int flags = 0);
    ~basic_xml_oarchive();
};

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_BASIC_XML_OARCHIVE_HPP
