#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
# DPG: tools need modular dependencies just like libraries have
# them. For now, we just include the appropriate directories.

include_directories(
  ${CMAKE_SOURCE_DIR}/libs/algorithm/include
  ${CMAKE_SOURCE_DIR}/libs/any/include
  ${CMAKE_SOURCE_DIR}/libs/bind/include
  ${CMAKE_SOURCE_DIR}/libs/concept/include
  ${CMAKE_SOURCE_DIR}/libs/concept_check/include
  ${CMAKE_SOURCE_DIR}/libs/config/include
  ${CMAKE_SOURCE_DIR}/libs/date_time/include
  ${CMAKE_SOURCE_DIR}/libs/detail/include
  ${CMAKE_SOURCE_DIR}/libs/exception/include
  ${CMAKE_SOURCE_DIR}/libs/filesystem/include
  ${CMAKE_SOURCE_DIR}/libs/function/include
  ${CMAKE_SOURCE_DIR}/libs/integer/include
  ${CMAKE_SOURCE_DIR}/libs/intrusive/include
  ${CMAKE_SOURCE_DIR}/libs/io/include
  ${CMAKE_SOURCE_DIR}/libs/iterator/include
  ${CMAKE_SOURCE_DIR}/libs/mpl/include
  ${CMAKE_SOURCE_DIR}/libs/multi_index/include
  ${CMAKE_SOURCE_DIR}/libs/optional/include
  ${CMAKE_SOURCE_DIR}/libs/preprocessor/include
  ${CMAKE_SOURCE_DIR}/libs/program_options/include
  ${CMAKE_SOURCE_DIR}/libs/pool/include
  ${CMAKE_SOURCE_DIR}/libs/range/include
  ${CMAKE_SOURCE_DIR}/libs/serialization/include
  ${CMAKE_SOURCE_DIR}/libs/smart_ptr/include
  ${CMAKE_SOURCE_DIR}/libs/spirit/include
  ${CMAKE_SOURCE_DIR}/libs/static_assert/include
  ${CMAKE_SOURCE_DIR}/libs/system/include
  ${CMAKE_SOURCE_DIR}/libs/thread/include
  ${CMAKE_SOURCE_DIR}/libs/timer/include
  ${CMAKE_SOURCE_DIR}/libs/tuple/include
  ${CMAKE_SOURCE_DIR}/libs/type_traits/include
  ${CMAKE_SOURCE_DIR}/libs/utility/include
  ${CMAKE_SOURCE_DIR}/libs/wave/include
)

boost_add_executable(wave cpp.cpp 
  DEPENDS boost_wave boost_program_options boost_filesystem boost_serialization
  MULTI_THREADED
  )
