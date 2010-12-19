/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "grammar_impl.hpp"
#include "actions_class.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_chset.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct doc_info_grammar_local
    {
        cl::rule<scanner>
                        doc_title, doc_version, doc_id, doc_dirname,
                        doc_copyright, doc_purpose, doc_category, doc_authors,
                        doc_author, space, hard_space, doc_license,
                        doc_last_revision, doc_source_mode, doc_biblioid, doc_lang,
                        phrase, quickbook_version, char_, comment, dummy_block;
        cl::symbols<> doc_types;
    };

    void quickbook_grammar::impl::init_doc_info()
    {
        doc_info_grammar_local& local = store_.create();

        typedef cl::uint_parser<int, 10, 1, 2>  uint2_t;

        local.doc_types =
            "book", "article", "library", "chapter", "part"
          , "appendix", "preface", "qandadiv", "qandaset"
          , "reference", "set"
        ;
        
        doc_info_details =
            local.space
            >> '[' >> local.space
            >> (local.doc_types >> cl::eps_p)
                                            [cl::assign_a(actions.doc_type)]
            >> local.hard_space
            >>  (  *(~cl::eps_p(cl::ch_p('[') | ']' | cl::eol_p) >> local.char_)
                )                           [actions.extract_doc_title]
            >>  !(
                    local.space >> '[' >>
                        local.quickbook_version
                    >> local.space >> ']'
                )
            >>
                *(
                    local.space >> '[' >>
                    (
                      local.doc_version
                    | local.doc_id
                    | local.doc_dirname
                    | local.doc_copyright   [cl::push_back_a(actions.doc_copyrights, actions.copyright)]
                    | local.doc_purpose
                    | local.doc_category
                    | local.doc_authors
                    | local.doc_license
                    | local.doc_last_revision
                    | local.doc_source_mode
                    | local.doc_biblioid
                    | local.doc_lang
                    )
                    >> local.space >> ']' >> +cl::eol_p
                )
            >> local.space >> ']' >> +cl::eol_p
            ;

        local.quickbook_version =
                "quickbook" >> local.hard_space
            >>  (   cl::uint_p              [cl::assign_a(qbk_major_version)]
                    >> '.' 
                    >>  uint2_t()           [cl::assign_a(qbk_minor_version)]
                )
            ;

        local.doc_version =
                "version" >> local.hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_version]
            ;

        // TODO: Restrictions on doc_id?
        local.doc_id =
                "id" >> local.hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_id]
            ;

        // TODO: Restrictions on doc_dirname?
        local.doc_dirname =
                "dirname" >> local.hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_dirname]
            ;

        local.doc_copyright =
                "copyright"
            >> local.hard_space             [cl::clear_a(actions.copyright.first)]
            >> +( cl::repeat_p(4)[cl::digit_p]
                                            [cl::push_back_a(actions.copyright.first)]
                  >> local.space
                )
            >> local.space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_copyright_second]
            ;

        local.doc_purpose =
                "purpose" >> local.hard_space
            >> local.phrase                 [actions.extract_doc_purpose]
            ;

        local.doc_category =
                "category" >> local.hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_category]
                                            [cl::push_back_a(actions.doc_categories, actions.doc_category)]
            ;

        local.doc_author =
                '[' >> local.space
            >>  (*(~cl::eps_p(',') >> local.char_))
                                            [actions.extract_name_second]
            >>  ',' >> local.space
            >>  (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_name_first]
            >>  ']'
            ;

        local.doc_authors =
                "authors"
            >>  local.hard_space
            >>  local.doc_author            [cl::push_back_a(actions.doc_authors, actions.name)]
            >>  local.space
            >>  *(  !(cl::ch_p(',') >> local.space)
                >>  local.doc_author        [cl::push_back_a(actions.doc_authors, actions.name)]
                >>  local.space
                )
            ;

        local.doc_license =
                "license" >> local.hard_space
            >> local.phrase                 [actions.extract_doc_license]
            ;

        local.doc_last_revision =
                "last-revision" >> local.hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_last_revision]
            ;

        local.doc_source_mode =
                "source-mode" >> local.hard_space
            >>  (
                   cl::str_p("c++") 
                |  "python"
                |  "teletype"
                )                           [cl::assign_a(actions.source_mode)]
            ;

        local.doc_biblioid =
                "biblioid"
            >>  local.hard_space
            >>  (+cl::alnum_p)              [cl::assign_a(actions.doc_biblioid.first)]
            >>  local.hard_space
            >>  (+(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_biblioid]
                                            [cl::push_back_a(actions.doc_biblioid_items, actions.doc_biblioid)]
            ;

        local.doc_lang =
                "lang" >> local.hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_lang]
            ;

        local.space =
            *(cl::space_p | local.comment)
            ;

        local.hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> local.space  // must not be preceded by
            ;                                   // alpha-numeric or underscore

        local.comment =
            "[/" >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.dummy_block =
            '[' >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.phrase =
           *(   common
            |   (cl::anychar_p - ']')       [actions.plain_char]
            )
            ;

        local.char_ =
                cl::str_p("\\n")            [actions.break_]
            |   "\\ "                       // ignore an escaped space
            |   '\\' >> cl::punct_p         [actions.raw_char]
            |   "\\u" >> cl::repeat_p(4)
                    [cl::chset<>("0-9a-fA-F")]
                                            [actions.escape_unicode]
            |   "\\U" >> cl::repeat_p(8)
                    [cl::chset<>("0-9a-fA-F")]
                                            [actions.escape_unicode]
            |   (
                    ("'''" >> !cl::eol_p)   [actions.escape_pre]
                >>  *(cl::anychar_p - "'''")[actions.raw_char]
                >>  cl::str_p("'''")        [actions.escape_post]
                )
            |   cl::anychar_p               [actions.plain_char]
            ;
    }
}
