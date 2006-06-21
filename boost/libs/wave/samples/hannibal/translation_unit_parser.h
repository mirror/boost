//  Hannibal: partial C++ grammar to parse C++ type information
//  Copyright (c) 2005 Danny Havenith
// 
//  Boost.Wave: A Standard compliant C++ preprocessor
//  Copyright (c) 2001-2006 Hartmut Kaiser
// 
//  http://www.boost.org/
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HANNIBAL_TRANSLATION_UNIT_GRAMMAR_H_INCLUDED)
#define HANNIBAL_TRANSLATION_UNIT_GRAMMAR_H_INCLUDED

#include <map>

#include <boost/assert.hpp>
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>

#include <boost/wave/wave_config.hpp>
#include <boost/wave/token_ids.hpp>
#include <boost/wave/util/pattern_parser.hpp>

///////////////////////////////////////////////////////////////////////////////
#define HANNIBAL_TRACE_TRANSLATION_UNIT_GRAMMAR                               \
    bool(BOOST_SPIRIT_DEBUG_FLAGS_CPP & BOOST_SPIRIT_DEBUG_FLAGS_CPP_EXPR_GRAMMAR) \
    /**/

///////////////////////////////////////////////////////////////////////////////
//  Helper macro to register rules for debugging
#if HANNIBAL_DUMP_PARSE_TREE != 0
#define HANNIBAL_REGISTER_RULE(r)                                             \
    BOOST_SPIRIT_DEBUG_TRACE_RULE(r, HANNIBAL_TRACE_TRANSLATION_UNIT_GRAMMAR);\
    self.declare_rule(r, #r)                                                  \
    /**/
#else
#define HANNIBAL_REGISTER_RULE(r)                                             \
    BOOST_SPIRIT_DEBUG_TRACE_RULE(r, HANNIBAL_TRACE_TRANSLATION_UNIT_GRAMMAR) \
    /**/
#endif

///////////////////////////////////////////////////////////////////////////////
struct translation_unit_grammar 
:   public boost::spirit::grammar<translation_unit_grammar>
{
#if HANNIBAL_DUMP_PARSE_TREE != 0
//
// allow an external map with rule-id -> rule-name mappings.
// this map is external so it can be altered by the definition constructor,
// which receives a const grammar object.
//
// Please Note: the lifetime of the rule map should at least extend beyond the 
// call of the definition constructor...
//
    typedef std::map<boost::spirit::parser_id, std::string> rule_map_type;
#endif

    translation_unit_grammar(rule_map_type *rule_map_ptr_ = 0)
#if HANNIBAL_DUMP_PARSE_TREE != 0
    :   rule_map_ptr(rule_map_ptr_)
#endif
    {
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, 
            "translation_unit_grammar", HANNIBAL_TRACE_TRANSLATION_UNIT_GRAMMAR);
    }

    template <typename ScannerT>
    struct definition
    {
        // declare non-terminals
        typedef boost::spirit::rule<ScannerT> rule_type;

        rule_type constant_expression;
        rule_type logical_or_exp, logical_and_exp;
        rule_type inclusive_or_exp, exclusive_or_exp, and_exp;
        rule_type cmp_equality, cmp_relational;
        rule_type shift_exp;
        rule_type add_exp, multiply_exp;
        rule_type unary_exp, primary_exp, constant;

        boost::spirit::subrule<0> const_exp_subrule;
        boost::spirit::subrule<1> shift_exp_clos;

        rule_type simple_type_name, class_keywords;
        rule_type storage_class_specifier, cv_qualifier, function_specifier;
        rule_type access_specifier;
        rule_type sign_specifier;
        rule_type extension_type_decorator;
        rule_type operator_sym;
        rule_type class_key;
        rule_type enumerator;
        rule_type enumerator_list;
        rule_type enumerator_definition;
        rule_type member_declarator;
        rule_type member_declarator_list;
        rule_type member_declaration;
        rule_type constant_initializer;
        rule_type pure_specifier;
        rule_type namespace_body;
        rule_type type_id;
        rule_type unnamed_namespace_definition;
        rule_type extension_namespace_definition;
        rule_type original_namespace_definition;
        rule_type named_namespace_definition;
        rule_type namespace_definition;
        rule_type linkage_specification;
        rule_type explicit_specialization;
        rule_type using_directive;
        rule_type using_declaration;
        rule_type type_parameter;
        rule_type template_parameter;
        rule_type template_parameter_list;
        rule_type template_declaration;
        rule_type explicit_instantiation;
        rule_type qualified_namespace_specifier;
        rule_type namespace_alias_definition;
        rule_type expression_list;
        rule_type initializer_list;
        rule_type initializer_clause;
        rule_type initializer;
        rule_type init_declarator;
        rule_type init_declarator_list;
        rule_type asm_definition;
        rule_type simple_declaration;
        rule_type block_declaration;
        rule_type declaration;
        rule_type declaration_seq;
        rule_type translation_unit;

        rule_type function_definition, function_definition_helper, declarator;
        rule_type direct_declarator, parameters_or_array_spec;
        rule_type abstract_declarator, direct_abstract_declarator;
        rule_type direct_abstract_declarator_helper;
        rule_type parameter_declaration_clause, parameter_declaration_list;
        rule_type parameter_declaration, assignment_expression, decimal_literal;
        rule_type octal_literal, hexadecimal_literal;
        rule_type declarator_id, id_expression, qualified_id, unqualified_id;
        rule_type operator_function_id, conversion_function_id, conversion_type_id;
        rule_type conversion_declarator, function_body;
        rule_type compound_statement, ctor_initializer, ptr_operator;
        rule_type decl_specifier, type_specifier;
        rule_type type_specifier_seq, cv_qualifier_seq, enum_specifier;
        rule_type enum_keyword, simple_type_specifier;
        rule_type class_specifier, member_specification, class_head;
        rule_type type_name, elaborated_type_specifier, template_argument_list;
        rule_type template_argument, nested_name_specifier;
        rule_type class_or_namespace_name, class_name, enum_name, typedef_name;
        rule_type namespace_name, template_id;
        rule_type decl_specifier_seq, no_type_decl_specifier;
        rule_type function_try_block, handler_seq, handler;
        rule_type exception_specification, template_name;
        rule_type original_namespace_name, base_specifier;
        rule_type base_specifier_list, base_clause;
        rule_type odd_language_extension, mem_initializer_id;
        rule_type mem_initializer, mem_initializer_list;

        // 
        // grammar definition. 
        //
        definition(translation_unit_grammar const& self)
        {
            using namespace boost::spirit;
            using namespace boost::wave;
            using boost::wave::util::pattern_p;

            // constant_expression was copied from Wave
            HANNIBAL_REGISTER_RULE(constant_expression);
            constant_expression
                =   logical_or_exp
                >> !(const_exp_subrule =
                        ch_p(T_QUESTION_MARK)
                        >>  logical_or_exp >> ch_p(T_COLON) >> logical_or_exp
                     )
                ;

            HANNIBAL_REGISTER_RULE(logical_or_exp);
            logical_or_exp 
                =   logical_and_exp
                >> *(   pattern_p(T_OROR, MainTokenMask) 
                    >>  logical_and_exp 
                    )
                ;

            HANNIBAL_REGISTER_RULE(logical_and_exp);
            logical_and_exp
                =   inclusive_or_exp
                >> *(   pattern_p(T_ANDAND, MainTokenMask)
                    >>  inclusive_or_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(inclusive_or_exp);
            inclusive_or_exp
                =   exclusive_or_exp
                >> *(   pattern_p(T_OR, MainTokenMask)
                    >>  exclusive_or_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(exclusive_or_exp);
            exclusive_or_exp
                =   and_exp
                >> *(   pattern_p(T_XOR, MainTokenMask)
                    >>  and_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(and_exp);
            and_exp
                =   cmp_equality
                >> *(   pattern_p(T_AND, MainTokenMask)
                    >>  cmp_equality
                    )
                ;

            HANNIBAL_REGISTER_RULE(cmp_equality);
            cmp_equality
                =   cmp_relational
                >> *(   ch_p(T_EQUAL) >>  cmp_relational
                    |   pattern_p(T_NOTEQUAL, MainTokenMask) >> cmp_relational
                    )
                ;

            HANNIBAL_REGISTER_RULE(cmp_relational);
            cmp_relational
                =   shift_exp
                >> *(   ch_p(T_LESSEQUAL) >> shift_exp 
                    |   ch_p(T_GREATEREQUAL) >> shift_exp 
                    |   ch_p(T_LESS) >> shift_exp 
                    |   ch_p(T_GREATER) >> shift_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(shift_exp);
            shift_exp
                =   add_exp
                >> *(shift_exp_clos =
                        ch_p(T_SHIFTLEFT) >> add_exp
                    |   ch_p(T_SHIFTRIGHT) >> add_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(add_exp);
            add_exp
                =   multiply_exp
                >> *(   ch_p(T_PLUS) >> multiply_exp
                    |   ch_p(T_MINUS) >> multiply_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(multiply_exp);
            multiply_exp
                =   unary_exp
                >> *(   ch_p(T_STAR) >> unary_exp
                    |   ch_p(T_DIVIDE) >> unary_exp
                    |   ch_p(T_PERCENT) >> unary_exp
                    )
                ;

            HANNIBAL_REGISTER_RULE(unary_exp);
            unary_exp
                =   primary_exp
                |   ch_p(T_PLUS) >> unary_exp
                |   ch_p(T_MINUS) >> unary_exp
                |   pattern_p(T_COMPL, MainTokenMask) >> unary_exp
                |   pattern_p(T_NOT, MainTokenMask) >> unary_exp
                ;

            HANNIBAL_REGISTER_RULE(primary_exp);
            primary_exp
                =   constant
                |   ch_p(T_LEFTPAREN) >> constant_expression 
                    >>  ch_p(T_RIGHTPAREN)
                ;

            HANNIBAL_REGISTER_RULE(constant);
            constant
                =   ch_p(T_PP_NUMBER) 
                |   ch_p(T_INTLIT) 
                |   ch_p(T_CHARLIT) 
                ;
            // end of Wave rules

            HANNIBAL_REGISTER_RULE(ctor_initializer);
            ctor_initializer
                =   ch_p(T_COLON) >> mem_initializer_list
                ;

            HANNIBAL_REGISTER_RULE(mem_initializer_list);
            mem_initializer_list
                =	  mem_initializer % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(mem_initializer);
            mem_initializer
                =	  mem_initializer_id 
                >>  ch_p(T_LEFTPAREN) >> !expression_list >> ch_p(T_RIGHTPAREN)
                ;

            HANNIBAL_REGISTER_RULE(mem_initializer_id);
            mem_initializer_id
                =	 !ch_p(T_COLON_COLON) >> !nested_name_specifier >> class_name
                |	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(translation_unit);
            translation_unit
                =	 !declaration_seq
                ;

            HANNIBAL_REGISTER_RULE(odd_language_extension);
            odd_language_extension    // read: microsoft extensions
                =	  extension_type_decorator 
                >> !comment_nest_p(ch_p(T_LEFTPAREN), ch_p(T_RIGHTPAREN))
                ;

            HANNIBAL_REGISTER_RULE(declaration_seq);
            declaration_seq
                =	 +declaration
                ;

            HANNIBAL_REGISTER_RULE(declaration);
            declaration
                =	  template_declaration
                |	  explicit_instantiation
                |	  explicit_specialization
                |	  linkage_specification
                |	  namespace_definition
                |	  block_declaration
                |	  function_definition
                ;

            HANNIBAL_REGISTER_RULE(block_declaration);
            block_declaration
                =	  simple_declaration
                |	  asm_definition
                |	  namespace_alias_definition
                |	  using_declaration
                |	  using_directive
                ;

            HANNIBAL_REGISTER_RULE(simple_declaration);
            simple_declaration
                =	 !decl_specifier_seq >> !init_declarator_list 
                    >>  ch_p(T_SEMICOLON)
                ;

            HANNIBAL_REGISTER_RULE(asm_definition);
            asm_definition
                =	  ch_p(T_ASM) 
                    >>  ch_p(T_LEFTPAREN) >> ch_p(T_STRINGLIT) >> ch_p(T_RIGHTPAREN)
                    >>  ch_p(T_SEMICOLON)
                ;

            HANNIBAL_REGISTER_RULE(init_declarator_list);
            init_declarator_list
                =	  init_declarator % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(init_declarator);
            init_declarator
                =	  declarator >> !initializer
                ;

            HANNIBAL_REGISTER_RULE(initializer);
            initializer
                =	  ch_p(T_ASSIGN) >> initializer_clause
                |	  ch_p(T_LEFTPAREN) >> expression_list >> ch_p(T_RIGHTPAREN)
                ;

            HANNIBAL_REGISTER_RULE(initializer_clause);
            initializer_clause
                =	  assignment_expression
                |	  ch_p(T_LEFTBRACE) >> initializer_list 
                    >> !ch_p(T_COMMA) >> ch_p(T_RIGHTBRACE)
                |	  ch_p(T_LEFTBRACE) >> ch_p(T_RIGHTBRACE)
                ;

            HANNIBAL_REGISTER_RULE(initializer_list);
            initializer_list
                =	  initializer_clause % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(expression_list);
            expression_list
                =	  assignment_expression % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(namespace_alias_definition);
            namespace_alias_definition
                =	  ch_p(T_NAMESPACE) >> ch_p(T_IDENTIFIER) >> ch_p(T_ASSIGN)
                    >>  qualified_namespace_specifier 
                    >>  ch_p(T_SEMICOLON)
                ;

            HANNIBAL_REGISTER_RULE(qualified_namespace_specifier);
            qualified_namespace_specifier
                =	 !ch_p(T_COLON_COLON) >> !nested_name_specifier 
                    >>  namespace_name
                ;

            HANNIBAL_REGISTER_RULE(explicit_instantiation);
            explicit_instantiation
                =	  template_declaration
                ;

            HANNIBAL_REGISTER_RULE(template_declaration);
            template_declaration
                =  !ch_p(T_EXPORT) >> ch_p(T_TEMPLATE)
                    >>  ch_p(T_LESS) >> template_parameter_list >> ch_p(T_GREATER)
                    >>  declaration
                ;

            HANNIBAL_REGISTER_RULE(template_parameter_list);
            template_parameter_list
                =	  template_parameter % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(template_parameter);
            template_parameter
                =	  type_parameter
                |	  parameter_declaration
                ;

            HANNIBAL_REGISTER_RULE(type_parameter);
            type_parameter
                =	  ch_p(T_CLASS) >> !ch_p(T_IDENTIFIER) 
                    >> !(ch_p(T_ASSIGN) >> type_id)
                |	  ch_p(T_TYPENAME) >> !ch_p(T_IDENTIFIER) 
                    >> !(ch_p(T_ASSIGN) >> type_id)
                |	  ch_p(T_TEMPLATE) 
                    >>  ch_p(T_LESS) >> template_parameter_list >> ch_p(T_GREATER) 
                    >>  ch_p(T_CLASS) >> !ch_p(T_IDENTIFIER) 
                    >> !(ch_p(T_ASSIGN) >> template_name)
                ;

            HANNIBAL_REGISTER_RULE(template_name);
            template_name
                =	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(using_declaration);
            using_declaration     // optimize?
                =	  ch_p(T_USING) >> !ch_p(T_TYPENAME) >> !ch_p(T_COLON_COLON) 
                    >>  nested_name_specifier >> unqualified_id 
                    >>  ch_p(T_SEMICOLON)
                |	  ch_p(T_USING) >> ch_p(T_COLON_COLON) >> unqualified_id 
                    >>  ch_p(T_SEMICOLON)
                ;

            HANNIBAL_REGISTER_RULE(using_directive);
            using_directive
                =	  ch_p(T_USING) >> ch_p(T_NAMESPACE) >> !ch_p(T_COLON_COLON) 
                    >> !nested_name_specifier >> namespace_name 
                    >>  ch_p(T_SEMICOLON)
                ;

            HANNIBAL_REGISTER_RULE(explicit_specialization);
            explicit_specialization
                =	  ch_p(T_TEMPLATE) >> ch_p(T_LESS) >> ch_p(T_GREATER) 
                    >>  declaration
                ;

            HANNIBAL_REGISTER_RULE(linkage_specification);
            linkage_specification
                =	  ch_p(T_EXTERN) >> ch_p(T_STRINGLIT) 
                    >>  (   ch_p(T_LEFTBRACE) >> !declaration_seq >> ch_p(T_RIGHTBRACE)
                        |	  declaration
                        )
                ;

            HANNIBAL_REGISTER_RULE(namespace_definition);
            namespace_definition
                =	  named_namespace_definition
                |	  unnamed_namespace_definition    // TODO: optimize?
                ;

            HANNIBAL_REGISTER_RULE(named_namespace_definition);
            named_namespace_definition
                =	  original_namespace_definition
           //   |   extension_namespace_definition // optimization: extension namespace is syntactically identical
                ;

            HANNIBAL_REGISTER_RULE(original_namespace_definition);
            original_namespace_definition
                =	  ch_p(T_NAMESPACE) >> ch_p(T_IDENTIFIER)
                    >>  ch_p(T_LEFTBRACE) >> namespace_body >> ch_p(T_RIGHTBRACE)
                ;

            HANNIBAL_REGISTER_RULE(extension_namespace_definition);
            extension_namespace_definition
                =	  ch_p(T_NAMESPACE) >> original_namespace_name 
                    >>  ch_p(T_LEFTBRACE) >> namespace_body >> ch_p(T_RIGHTBRACE)
                ;

            HANNIBAL_REGISTER_RULE(original_namespace_name);
            original_namespace_name
                =	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(unnamed_namespace_definition);
            unnamed_namespace_definition
                =	  ch_p(T_NAMESPACE) 
                    >>  ch_p(T_LEFTBRACE) >> namespace_body >> ch_p(T_RIGHTBRACE)
                ;

            HANNIBAL_REGISTER_RULE(namespace_body);
            namespace_body
                =	 !declaration_seq
                ;

            HANNIBAL_REGISTER_RULE(function_definition);
            function_definition
                =	  function_definition_helper 
                    >> !ctor_initializer >> !function_body  // removed semicolons
                |	  decl_specifier_seq >> declarator >> function_try_block
                |	  declarator >> function_try_block
                ;

            HANNIBAL_REGISTER_RULE(function_definition_helper);
            function_definition_helper
                =	 !decl_specifier_seq >> declarator
                |	  declarator
                ;

            HANNIBAL_REGISTER_RULE(function_try_block);
            function_try_block
                =	  ch_p(T_TRY) 
                    >> !ctor_initializer >> function_body >> handler_seq
                ;

            HANNIBAL_REGISTER_RULE(handler_seq);
            handler_seq
                =	 +handler
                ;

            HANNIBAL_REGISTER_RULE(handler);
            handler // TODO
                =	  ch_p(T_CATCH) 
                    >>  comment_nest_p(ch_p(T_LEFTPAREN), ch_p(T_RIGHTPAREN)) 
                    >>  compound_statement
                ;

            HANNIBAL_REGISTER_RULE(declarator);
            declarator
                =	 *(   ptr_operator 
                    |   odd_language_extension
                    ) 
                    >> direct_declarator
                ;

            HANNIBAL_REGISTER_RULE(direct_declarator);
            direct_declarator
                =	  (   declarator_id
                    |   ch_p(T_LEFTPAREN) >> declarator >> ch_p(T_RIGHTPAREN)
                    )  
                    >> *parameters_or_array_spec
                ;

            HANNIBAL_REGISTER_RULE(parameters_or_array_spec);
            parameters_or_array_spec
                =	  ch_p(T_LEFTPAREN) >> parameter_declaration_clause >> ch_p(T_RIGHTPAREN)
                    >> !cv_qualifier_seq >> !exception_specification
                |	  ch_p(T_LEFTBRACKET) >> !constant_expression >> ch_p(T_RIGHTBRACKET)
                ;

            HANNIBAL_REGISTER_RULE(exception_specification);
            exception_specification     // TODO
                =	  ch_p(T_THROW) 
                    >>  comment_nest_p(ch_p(T_LEFTPAREN), ch_p(T_RIGHTPAREN))
                ;

            HANNIBAL_REGISTER_RULE(abstract_declarator);
            abstract_declarator
                =	 +(   ptr_operator 
                    |   odd_language_extension
                    ) 
                    >> !direct_abstract_declarator
                |	  direct_abstract_declarator
                ;

            HANNIBAL_REGISTER_RULE(direct_abstract_declarator);
            direct_abstract_declarator
                =	  ch_p(T_LEFTPAREN) >> abstract_declarator >> ch_p(T_RIGHTPAREN)
                    >> *direct_abstract_declarator_helper
                ;

            HANNIBAL_REGISTER_RULE(direct_abstract_declarator_helper);
            direct_abstract_declarator_helper
                =	  ch_p(T_LEFTPAREN) >> parameter_declaration_clause >> ch_p(T_RIGHTPAREN)
                    >> !cv_qualifier_seq >> !exception_specification
                |	  ch_p(T_LEFTBRACKET) >> !constant_expression >> ch_p(T_RIGHTBRACKET)
                ;

            HANNIBAL_REGISTER_RULE(parameter_declaration_clause);
            parameter_declaration_clause
                =	  parameter_declaration_list >> ch_p(T_COMMA) 
                    >> ch_p(T_ELLIPSIS)
                |	 !parameter_declaration_list >> !ch_p(T_ELLIPSIS)
                ;

            HANNIBAL_REGISTER_RULE(parameter_declaration_list);
            parameter_declaration_list
                =	  parameter_declaration % ch_p(T_COMMA)
                ;


            HANNIBAL_REGISTER_RULE(parameter_declaration);
            parameter_declaration
                =	  decl_specifier_seq 
                    >> !(declarator | abstract_declarator) 
                    >> !(ch_p(T_ASSIGN) >> assignment_expression)
                ;

            HANNIBAL_REGISTER_RULE(assignment_expression);
            assignment_expression
                =	  constant_expression     // TODO later assignment expressions
                |	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(declarator_id);
            declarator_id
                =	 !ch_p(T_COLON_COLON)
                    >>	(   id_expression
                        |	 !nested_name_specifier >> type_name
                        )
                ;

            HANNIBAL_REGISTER_RULE(id_expression);
            id_expression
                =	  unqualified_id
                |   qualified_id
                ;

            HANNIBAL_REGISTER_RULE(qualified_id);
            qualified_id
                =	  nested_name_specifier >> !ch_p(T_TEMPLATE) >> unqualified_id
                ;

            HANNIBAL_REGISTER_RULE(unqualified_id);
            unqualified_id
                =	  operator_function_id
                |	  conversion_function_id 
                |	  ch_p(T_COMPL) >> class_name
                |	  template_id
                |	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(operator_function_id);
            operator_function_id
                =	  ch_p(T_OPERATOR) >> operator_sym    // this is called 'operator' in the std grammar
                ;
                
            HANNIBAL_REGISTER_RULE(operator_sym);
            operator_sym 
                =	  ch_p(T_DELETE) >> ch_p(T_LEFTBRACKET) >> ch_p(T_RIGHTBRACKET)
                |	  ch_p(T_NEW) >> ch_p(T_LEFTBRACKET) >> ch_p(T_RIGHTBRACKET)
                |	  ch_p(T_LEFTBRACKET) >> ch_p(T_RIGHTBRACKET)
                |	  ch_p(T_LEFTPAREN) >> ch_p(T_RIGHTPAREN)
                |	  pattern_p(OperatorTokenType, TokenTypeMask)
                ;

            HANNIBAL_REGISTER_RULE(conversion_function_id);  
            conversion_function_id
                =   ch_p(T_OPERATOR) >> conversion_type_id
                ;

            HANNIBAL_REGISTER_RULE( conversion_type_id);
            conversion_type_id
                =   type_specifier_seq >> !conversion_declarator
                ;

            HANNIBAL_REGISTER_RULE(type_id);
            type_id
                =	  type_specifier_seq >> !abstract_declarator
                ;


            HANNIBAL_REGISTER_RULE(conversion_declarator);
            conversion_declarator
                = ptr_operator >> !conversion_declarator
                ;

            HANNIBAL_REGISTER_RULE(function_body);
            function_body
                =	compound_statement
                ;

            HANNIBAL_REGISTER_RULE(compound_statement);
            compound_statement
                =	  comment_nest_p(ch_p(T_LEFTBRACE), ch_p(T_RIGHTBRACE))
                ;   // TODO later


            HANNIBAL_REGISTER_RULE(ptr_operator);
            ptr_operator
                =	  ch_p(T_STAR) >> !cv_qualifier_seq
                |	  ch_p(T_AND)
                |  !ch_p(T_COLON_COLON) >> nested_name_specifier 
                    >> ch_p(T_STAR) >> !cv_qualifier_seq
                ;


            HANNIBAL_REGISTER_RULE(decl_specifier);
            decl_specifier
                =	  no_type_decl_specifier
                |   type_specifier
                ;

            HANNIBAL_REGISTER_RULE(no_type_decl_specifier);
            no_type_decl_specifier 
                =	  storage_class_specifier
                |	  function_specifier
                |	  ch_p(T_FRIEND)
                |	  ch_p(T_TYPEDEF)
                |	  cv_qualifier
                |	  odd_language_extension
                ;

            HANNIBAL_REGISTER_RULE(type_specifier_seq);
            type_specifier_seq
                =	 +type_specifier
                ;

            HANNIBAL_REGISTER_RULE(type_specifier);
            type_specifier
                =	  enum_specifier
                |	  class_specifier
                |	  elaborated_type_specifier
                |	  simple_type_specifier
                ;

            HANNIBAL_REGISTER_RULE(cv_qualifier_seq);
            cv_qualifier_seq
                =	  cv_qualifier >> !cv_qualifier_seq
                ;

            HANNIBAL_REGISTER_RULE(cv_qualifier);
            cv_qualifier
                =	  ch_p(T_CONST) 
                |   ch_p(T_VOLATILE)
                ;

            HANNIBAL_REGISTER_RULE(enum_specifier);
            enum_specifier 
                =	  enum_keyword >> !ch_p(T_IDENTIFIER) 
                    >> ch_p(T_LEFTBRACE) >> !enumerator_list >> ch_p(T_RIGHTBRACE)
                ;

            HANNIBAL_REGISTER_RULE(enum_keyword);
            enum_keyword
                =	  ch_p(T_ENUM)
                ;

            HANNIBAL_REGISTER_RULE(enumerator_list);
            enumerator_list
                =	  enumerator_definition % ch_p(T_COMMA) 
                    >> !ch_p(T_COMMA) 
                    // TODO find out if this last COMMA_T is an MS-"extension"?
                    // it seems not to be in the grammar but MSVC 7.0 accepts it.
                ;

            HANNIBAL_REGISTER_RULE(enumerator_definition);
            enumerator_definition
                =	enumerator >> !(ch_p(T_ASSIGN) >> constant_expression)
                ;

            HANNIBAL_REGISTER_RULE(enumerator);
            enumerator
                =	  ch_p(T_IDENTIFIER)
                ;


            HANNIBAL_REGISTER_RULE(simple_type_specifier);
            simple_type_specifier
                =   !ch_p(T_COLON_COLON) >> !nested_name_specifier 
                    >>  ch_p(T_TEMPLATE) >> template_id
                |   sign_specifier >> !simple_type_name 
                |   simple_type_name
                |	 !ch_p(T_COLON_COLON) >> !nested_name_specifier >> type_name
                ;

            HANNIBAL_REGISTER_RULE(class_head);
            class_head 
                =	 !access_specifier >> *odd_language_extension 
                    >>  class_key >> *odd_language_extension 
                    >>  (  !ch_p(T_IDENTIFIER) 
                        |   nested_name_specifier >> !ch_p(T_TEMPLATE) >> ch_p(T_IDENTIFIER)
                        )
                    >> !base_clause
                ;

            HANNIBAL_REGISTER_RULE(sign_specifier);
            sign_specifier
                =	  ch_p(T_SIGNED)
                |   ch_p(T_UNSIGNED)
                ;

            HANNIBAL_REGISTER_RULE(type_name);
            type_name
                =	  class_name
                |	  enum_name
                |	  typedef_name
                ;

            HANNIBAL_REGISTER_RULE(elaborated_type_specifier);
            elaborated_type_specifier
                =	  class_key >> *odd_language_extension >> !ch_p(T_COLON_COLON) 
                    >>  !nested_name_specifier >> ch_p(T_IDENTIFIER)
                |	  ch_p(T_ENUM) >> !ch_p(T_COLON_COLON) 
                    >> !nested_name_specifier >> ch_p(T_IDENTIFIER)
                |	  ch_p(T_TYPENAME) >> !ch_p(T_COLON_COLON) 
                    >>  nested_name_specifier >> ch_p(T_IDENTIFIER) 
                    >> ch_p(T_LESS) >> template_argument_list >> ch_p(T_GREATER)
                |	  ch_p(T_TYPENAME) >> !ch_p(T_COLON_COLON) 
                    >> !nested_name_specifier >> ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(template_argument_list);
            template_argument_list 
                =	  template_argument % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(template_argument);
            template_argument
                =	  longest_d
                    [
                        type_id
                    |   assignment_expression
                    |   template_name
                    ]
                ;

            HANNIBAL_REGISTER_RULE(class_key);
            class_key
                =	  class_keywords
                ;

            HANNIBAL_REGISTER_RULE(class_keywords);
            class_keywords 
                =	  ch_p(T_CLASS)
                |   ch_p(T_STRUCT)
                |   ch_p(T_UNION)
                ;

            HANNIBAL_REGISTER_RULE(nested_name_specifier);
            nested_name_specifier
                =	  class_or_namespace_name >> ch_p(T_COLON_COLON) 
                    >>  ch_p(T_TEMPLATE) >> nested_name_specifier
                |	  class_or_namespace_name >> ch_p(T_COLON_COLON) 
                    >> !nested_name_specifier
                ;

            HANNIBAL_REGISTER_RULE(class_or_namespace_name);
            class_or_namespace_name
                =	  class_name 
                |   namespace_name
                ;

            HANNIBAL_REGISTER_RULE(class_name);
            class_name 
                =	  template_id
                |	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(enum_name);
            enum_name
                =	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(typedef_name);
            typedef_name
                =	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(namespace_name);
            namespace_name    // TODO
                =	  ch_p(T_IDENTIFIER)
                ;

            HANNIBAL_REGISTER_RULE(template_id);
            template_id 
                =   template_name 
                    >> ch_p(T_LESS) >> template_argument_list >> ch_p(T_GREATER)
                ;

            //
            //  This is kind of a HACK. We want to prevent the decl_specifier_seq 
            //  from eating the whole declaration, including the identifier. 
            //  Therefore in the sequence, we only allow one 'unknown' word 
            //  (the type_specifier), the rest of the decl_specifier sequence 
            //  must consist of known keywords or constructs (the 
            //  no_type_decl_specifier).
            //  This means that a declaration like:
            //     MYDLL_EXPORT int f(); 
            //  will not be accepted unless the MYDLL_EXPORT is properly 
            //  expanded by the preprocessor first.
            //     
            //  This should not cause any problems normally, it just means that 
            //  this rule is not very robust in the case where not all symbols 
            //  are known.
            //
            HANNIBAL_REGISTER_RULE(decl_specifier_seq);
            decl_specifier_seq
                =	 *no_type_decl_specifier >> type_specifier >> *no_type_decl_specifier
                ;

            //  The following rule is more according to the standard grammar
            //  decl_specifier_seq // adapted
            //	    =	  decl_specifier >> decl_specifier_seq
            //		  |	  (decl_specifier - (declarator_id >> parameters_or_array_spec )) 
            //	    ;

            HANNIBAL_REGISTER_RULE( storage_class_specifier);
            storage_class_specifier
                =	  ch_p(T_AUTO)
                |   ch_p(T_REGISTER)
                |   ch_p(T_STATIC)
                |   ch_p(T_EXTERN)
                |   ch_p(T_MUTABLE)
                ;

            HANNIBAL_REGISTER_RULE( function_specifier);
            function_specifier
                =	  ch_p(T_INLINE)
                |   ch_p(T_VIRTUAL)
                |   ch_p(T_EXPLICIT)
                ;

            HANNIBAL_REGISTER_RULE(class_specifier);
            class_specifier
                =	  class_head 
                    >> ch_p(T_LEFTBRACE) >> !member_specification >> ch_p(T_RIGHTBRACE)
                ;

            HANNIBAL_REGISTER_RULE(member_specification);
            member_specification
                =	 +(	  access_specifier >> ch_p(T_COLON)
                    |	  member_declaration 
                    )
                ;

      //				member_specification
      //					=	access_specifier >> COLON_T >> !member_specification
      //					|	member_declaration >> !member_specification
      //					;

            HANNIBAL_REGISTER_RULE(member_declaration);
            member_declaration
                =   using_declaration
                |	  template_declaration
                |	 !decl_specifier_seq >> !member_declarator_list 
                    >> ch_p(T_SEMICOLON)
                |	  function_definition >> 
                   !ch_p(T_SEMICOLON)
                |	  qualified_id 
                    >> ch_p(T_SEMICOLON)
                ;

            HANNIBAL_REGISTER_RULE(member_declarator_list);
            member_declarator_list
                =	  member_declarator % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(member_declarator);
            member_declarator
                =	 !ch_p(T_IDENTIFIER) >> ch_p(T_COLON) >> constant_expression
                |	  declarator >> !(pure_specifier | constant_initializer)
                ;

            HANNIBAL_REGISTER_RULE(pure_specifier);
            pure_specifier
                =   ch_p(T_ASSIGN) >> ch_p(T_INTLIT)
                ;

            HANNIBAL_REGISTER_RULE(constant_initializer);
            constant_initializer
                =   ch_p(T_ASSIGN) >> constant_expression
                ;

            HANNIBAL_REGISTER_RULE(access_specifier);
            access_specifier 
                =   ch_p(T_PUBLIC)
                |   ch_p(T_PROTECTED)
                |   ch_p(T_PRIVATE)
                ;

            HANNIBAL_REGISTER_RULE(base_clause);
            base_clause
                =   ch_p(T_COLON) >> base_specifier_list
                ;

            HANNIBAL_REGISTER_RULE(base_specifier_list);
            base_specifier_list
                =	  base_specifier % ch_p(T_COMMA)
                ;

            HANNIBAL_REGISTER_RULE(base_specifier);
            base_specifier
                =	  ch_p(T_VIRTUAL) >> !access_specifier >> !ch_p(T_COLON_COLON) 
                    >> !nested_name_specifier >> class_name
                |	  access_specifier >> !ch_p(T_VIRTUAL) >> !ch_p(T_COLON_COLON)
                    >> !nested_name_specifier >> class_name
                |	 !ch_p(T_COLON_COLON) >> !nested_name_specifier >> class_name
                ;

            HANNIBAL_REGISTER_RULE(extension_type_decorator);
            extension_type_decorator
                =	  ch_p(T_MSEXT_CDECL) 
                |   ch_p(T_MSEXT_DECLSPEC)
                |   ch_p(T_MSEXT_BASED)
                |   ch_p(T_MSEXT_FASTCALL) 
                |   ch_p(T_MSEXT_INLINE)
                ;

            HANNIBAL_REGISTER_RULE(simple_type_name);
            simple_type_name
                =	  ch_p(T_CHAR)
                |   ch_p(T_WCHART)
                |   ch_p(T_BOOL)
                |   ch_p(T_SHORT)
                |   ch_p(T_INT)
                |   ch_p(T_LONG)
                |   ch_p(T_FLOAT)
                |   ch_p(T_DOUBLE)
                |   ch_p(T_VOID)
                |   ch_p(T_MSEXT_INT64)
                |   ch_p(T_MSEXT_INT8)
                |   ch_p(T_MSEXT_INT16)
                |   ch_p(T_MSEXT_INT32)
                ;
        }

        rule_type const& start() const { return translation_unit; }
    };
  
#if HANNIBAL_DUMP_PARSE_TREE != 0
private:
    template<typename Rule>
    void declare_rule(Rule const& rule, std::string const& rule_name) const
    {
        if (rule_map_ptr)
            (*rule_map_ptr)[rule.id()] = rule_name;
    }
    rule_map_type *rule_map_ptr;
#endif 
};

#undef HANNIBAL_REGISTER_RULE
#undef HANNIBAL_TRACE_TRANSLATION_UNIT_GRAMMAR

#endif // HANNIBAL_TRANSLATION_UNIT_GRAMMAR_H_INCLUDED
