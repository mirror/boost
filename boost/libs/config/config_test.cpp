//  Boost config.hpp configuration test program file  ------------------------------//

//  (C) Copyright Boost.org 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for the most recent version.

#include <boost/config.hpp>
#include <iostream>

using std::cout;

int main()
{

#   ifdef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
        cout << "BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS defined\n";
#   endif

#   ifdef BOOST_NO_INCLASS_MEMBER_INITIALIZER
        cout << "BOOST_NO_INCLASS_MEMBER_INITIALIZER defined\n";
#   endif

#   ifdef BOOST_NO_MEMBER_TEMPLATES
        cout << "BOOST_NO_MEMBER_TEMPLATES defined\n";
#   endif

#   ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
        cout << "BOOST_NO_MEMBER_TEMPLATE_FRIENDS defined\n";
#   endif

#   ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
        cout << "BOOST_NO_OPERATORS_IN_NAMESPACE defined\n";
#   endif

#   ifdef BOOST_NO_STD_ITERATOR
        cout << "BOOST_NO_STD_ITERATOR defined\n";
#   endif

#   ifdef BOOST_NO_STD_ITERATOR_TRAITS
        cout << "BOOST_NO_STD_ITERATOR_TRAITS defined\n";
#   endif

#   ifdef BOOST_NO_STDC_NAMESPACE
        cout << "BOOST_NO_STDC_NAMESPACE defined\n";
#   endif

#   ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        cout << "BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION defined\n";
#   endif

#   ifdef BOOST_NO_USING_TEMPLATE
        cout << "BOOST_NO_USING_TEMPLATE defined\n";
#   endif

#   ifdef BOOST_DECL_EXPORTS
        cout << "BOOST_DECL_EXPORTS defined\n";
#   endif

#   ifdef BOOST_SYSTEM_HAS_STDINT_H
        cout << "BOOST_SYSTEM_HAS_STDINT_H defined\n";
#   endif

#   ifdef __GNUC__
        cout << "__GNUC__ defined as " << __GNUC__ << "\n";
#   endif

#   ifdef __BORLANDC__
        cout << "__BORLANDC__ defined as " << __BORLANDC__ << "\n";
#   endif

#   ifdef __MWERKS__
        cout << "__MWERKS__ defined as " << __MWERKS__ << "\n";
#   endif

#   ifdef __SUNPRO_CC
        cout << "__SUNPRO_CC defined as " << __SUNPRO_CC << "\n";
#   endif

#   ifdef _MSC_VER
        cout << "_MSC_VER defined as " << _MSC_VER << "\n";
#   endif

#   ifdef BOOST_MSVC
        cout << "BOOST_MSVC defined as " << BOOST_MSVC << "\n";
#   endif

#   ifdef BOOST_MSVC6_MEMBER_TEMPLATES
        cout << "BOOST_MSVC6_MEMBER_TEMPLATES defined\n";
#   endif

#   ifdef BOOST_MSVC_STD_ITERATOR
        cout << "BOOST_MSVC_STD_ITERATOR defined\n";
#   endif

#   ifdef __SGI_STL_PORT
        cout << "__SGI_STL_PORT defined\n";
#   endif

#   ifdef __STL_NO_NAMESPACES
        cout << "__STL_NO_NAMESPACES defined\n";
#   endif

#   ifdef __STL_USE_NAMESPACES
        cout << "__STL_USE_NAMESPACES defined\n";
#   endif

#   ifdef __STL_IMPORT_VENDOR_CSTD
        cout << "__STL_IMPORT_VENDOR_CSTD defined\n";
#   endif

    return 0;
}
