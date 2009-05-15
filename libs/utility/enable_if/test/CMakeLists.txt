foreach(T
    constructors
    dummy_arg_disambiguation
    lazy
    lazy_test
    member_templates
    namespace_disambiguation
    no_disambiguation
    partial_specializations
    )
  boost_test_run(${T} DEPENDS boost_test_exec_monitor)
endforeach()


