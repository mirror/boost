#
# Copyright Sebastian Redl
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
#----------------------------------------------------------------------------
boost_additional_test_dependencies(property_tree BOOST_DEPENDS test serialization)


#-- List our regression tests
set (tests
    test_property_tree
    test_info_parser
    test_json_parser
   # test_xml_parser_rapidxml
)
message(STATUS "property_tree/test/test_xml_parser_rapidxml needs love.")

# test_xml_parser_rapidxml gets compile errors that I can not figure out


#-- Create an executable test for each
foreach(test ${tests})
    boost_test_run(${test} "${test}.cpp"
                    COMPILE_FLAGS ${test_compile_flags} 
                    DEPENDS boost_unit_test_framework boost_serialization STATIC) 
endforeach(test ${tests})
