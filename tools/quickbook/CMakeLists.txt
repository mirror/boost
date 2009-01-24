boost_tool_project(Quickbook
  DESCRIPTION "A WikiWiki style documentation tool geared towards C++ documentation"
  AUTHORS "Joel de Guzman <joel -at- boost-consulting.com>"
          "Eric Niebler <eric -at- boost-consulting.com>")

if (BUILD_QUICKBOOK)
  if (MSVC)
    add_definitions(/wd4511 /wd4512 /wd4701 /wd4702 /wd4244 /wd4267 /wd4800)
  endif (MSVC)
  
  boost_add_executable(quickbook
    detail/quickbook.cpp
    detail/actions.cpp
    detail/actions_class.cpp
    detail/utils.cpp
    detail/post_process.cpp
    detail/collector.cpp
    detail/template_stack.cpp
    DEPENDS boost_program_options boost_filesystem
    )  
endif (BUILD_QUICKBOOK)