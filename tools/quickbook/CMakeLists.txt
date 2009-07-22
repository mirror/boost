#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
boost_tool_project(Quickbook
  DESCRIPTION "A WikiWiki style documentation tool geared towards C++ documentation"
  AUTHORS "Joel de Guzman <joel -at- boost-consulting.com>"
          "Eric Niebler <eric -at- boost-consulting.com>")

if (BUILD_QUICKBOOK)
  if (MSVC)
    add_definitions(/wd4511 /wd4512 /wd4701 /wd4702 /wd4244 /wd4267 /wd4800)
  endif (MSVC)
  
#
# TDS: this needs fixing...  these are the modules that quickbook is
# dependent on.  if boost is modularized, you need these, but
# they don't hurt if quickbook isn't modularized.
#
include_directories(
  ${CMAKE_SOURCE_DIR}/libs/any/include
  ${CMAKE_SOURCE_DIR}/libs/bind/include
  ${CMAKE_SOURCE_DIR}/libs/concept/include
  ${CMAKE_SOURCE_DIR}/libs/concept_check/include
  ${CMAKE_SOURCE_DIR}/libs/config/include
  ${CMAKE_SOURCE_DIR}/libs/detail/include
  ${CMAKE_SOURCE_DIR}/libs/exception/include
  ${CMAKE_SOURCE_DIR}/libs/filesystem/include
  ${CMAKE_SOURCE_DIR}/libs/foreach/include
  ${CMAKE_SOURCE_DIR}/libs/function/include
  ${CMAKE_SOURCE_DIR}/libs/integer/include
  ${CMAKE_SOURCE_DIR}/libs/iostreams/include
  ${CMAKE_SOURCE_DIR}/libs/iterator/include
  ${CMAKE_SOURCE_DIR}/libs/mpl/include
  ${CMAKE_SOURCE_DIR}/libs/preprocessor/include
  ${CMAKE_SOURCE_DIR}/libs/program_options/include
  ${CMAKE_SOURCE_DIR}/libs/range/include
  ${CMAKE_SOURCE_DIR}/libs/spirit/include
  ${CMAKE_SOURCE_DIR}/libs/smart_ptr/include
  ${CMAKE_SOURCE_DIR}/libs/static_assert/include
  ${CMAKE_SOURCE_DIR}/libs/system/include
  ${CMAKE_SOURCE_DIR}/libs/tuple/include
  ${CMAKE_SOURCE_DIR}/libs/optional/include
  ${CMAKE_SOURCE_DIR}/libs/type_traits/include
  ${CMAKE_SOURCE_DIR}/libs/utility/include
  )

  boost_add_executable(quickbook
    detail/quickbook.cpp
    detail/actions.cpp
    detail/actions_class.cpp
    detail/utils.cpp
    detail/post_process.cpp
    detail/collector.cpp
    detail/input_path.cpp
    detail/template_stack.cpp
    detail/markups.cpp
    DEPENDS boost_program_options boost_filesystem
    )  
endif (BUILD_QUICKBOOK)
