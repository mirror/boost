/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_DOC_INFO_HPP)
#define BOOST_SPIRIT_QUICKBOOK_DOC_INFO_HPP

#include "./phrase.hpp"
#include "./quickbook.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_symbols.hpp>

namespace quickbook
{
    using namespace boost::spirit::classic;

    struct doc_info_grammar
    : public grammar<doc_info_grammar>
    {
        doc_info_grammar(quickbook::actions& actions)
            : actions(actions) {}

        template <typename Scanner>
        struct definition
        {
            typedef uint_parser<int, 10, 1, 2>  uint2_t;

            definition(doc_info_grammar const& self)
                : unused(false), common(self.actions, unused)
            {
                quickbook::actions& actions = self.actions;

                doc_types =
                    "book", "article", "library", "chapter", "part"
                  , "appendix", "preface", "qandadiv", "qandaset"
                  , "reference", "set"
                ;
                
                doc_info =
                    space
                    >> '[' >> space
                    >> (doc_types >> eps_p)         [assign_a(actions.doc_type)]
                    >> hard_space
                    >>  (  *(~eps_p(ch_p('[') | ']' | eol_p) >> char_)
                        )                           [actions.extract_doc_title]
                    >>  !(
                            space >> '[' >>
                                quickbook_version
                            >> space >> ']'
                        )
                    >>
                        *(
                            space >> '[' >>
                            (
                              doc_version
                            | doc_id
                            | doc_dirname
                            | doc_copyright         [push_back_a(actions.doc_copyrights, actions.copyright)]
                            | doc_purpose
                            | doc_category
                            | doc_authors
                            | doc_license
                            | doc_last_revision
                            | doc_source_mode
                            )
                            >> space >> ']' >> +eol_p
                        )
                    >> space >> ']' >> +eol_p
                    ;

                quickbook_version =
                        "quickbook" >> hard_space
                    >>  (   uint_p                  [assign_a(qbk_major_version)]
                            >> '.' 
                            >>  uint2_t()           [assign_a(qbk_minor_version)]
                        )
                    ;

                doc_version =
                        "version" >> hard_space
                    >> (*(~eps_p(']') >> char_))    [actions.extract_doc_version]
                    ;

                // TODO: Restrictions on doc_id?
                doc_id =
                        "id" >> hard_space
                    >> (*(~eps_p(']') >> char_))    [actions.extract_doc_id]
                    ;

                // TODO: Restrictions on doc_dirname?
                doc_dirname =
                        "dirname" >> hard_space
                    >> (*(~eps_p(']') >> char_))    [actions.extract_doc_dirname]
                    ;

                doc_copyright =
                        "copyright" >> hard_space   [clear_a(actions.copyright.first)]
                    >> +( repeat_p(4)[digit_p]      [push_back_a(actions.copyright.first)]
                          >> space
                        )
                    >> space
                    >> (*(~eps_p(']') >> char_))    [actions.extract_copyright_second]
                    ;

                doc_purpose =
                        "purpose" >> hard_space
                    >> phrase                       [actions.extract_doc_purpose]
                    ;

                doc_category =
                        "category" >> hard_space
                    >> (*(~eps_p(']') >> char_))    [actions.extract_doc_category]
                                                    [push_back_a(actions.doc_categories, actions.doc_category)]
                    ;

                doc_author =
                        '[' >> space
                    >>  (*(~eps_p(',') >> char_))   [actions.extract_name_second] // surname
                    >>  ',' >> space
                    >>  (*(~eps_p(']') >> char_))   [actions.extract_name_first] // firstname
                    >>  ']'
                    ;

                doc_authors =
                        "authors"
                    >>  hard_space
                    >>  doc_author                  [push_back_a(actions.doc_authors, actions.name)]
                    >>  space
                    >>  *(  !(ch_p(',') >> space)
                        >>  doc_author              [push_back_a(actions.doc_authors, actions.name)]
                        >>  space
                        )
                    ;

                doc_license =
                        "license" >> hard_space
                    >> phrase                       [actions.extract_doc_license]
                    ;

                doc_last_revision =
                        "last-revision" >> hard_space
                    >> (*(~eps_p(']') >> char_))    [actions.extract_doc_last_revision]
                    ;

                doc_source_mode =
                        "source-mode" >> hard_space
                    >>  (
                           str_p("c++") 
                        |  "python"
                        |  "teletype"
                        )                           [assign_a(actions.source_mode)]
                    ;

                comment =
                    "[/" >> *(anychar_p - ']') >> ']'
                    ;

                space =
                    *(space_p | comment)
                    ;

                hard_space =
                    (eps_p - (alnum_p | '_')) >> space  // must not be preceded by
                    ;                                   // alpha-numeric or underscore

                phrase =
                   *(   common
                    |   comment
                    |   (anychar_p - ']')           [actions.plain_char]
                    )
                    ;

                char_ =
                        str_p("\\n")                [actions.break_]
                    |   "\\ "                       // ignore an escaped space
                    |   '\\' >> punct_p             [actions.raw_char]
                    |   "\\u" >> repeat_p(4) [chset<>("0-9a-fA-F")]
                                                    [actions.escape_unicode]
                    |   "\\U" >> repeat_p(8) [chset<>("0-9a-fA-F")]
                                                    [actions.escape_unicode]
                    |   (
                            ("'''" >> !eol_p)       [actions.escape_pre]
                        >>  *(anychar_p - "'''")    [actions.raw_char]
                        >>  str_p("'''")            [actions.escape_post]
                        )
                    |   anychar_p                   [actions.plain_char]
                    ;
            }

            bool unused;
            std::string category;
            rule<Scanner>   doc_info, doc_title, doc_version, doc_id, doc_dirname,
                            doc_copyright, doc_purpose, doc_category, doc_authors,
                            doc_author, comment, space, hard_space, doc_license,
                            doc_last_revision, doc_source_mode, phrase, quickbook_version,
                            char_;
            phrase_grammar common;
            symbols<> doc_types;

            rule<Scanner> const&
            start() const { return doc_info; }
        };

        quickbook::actions& actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_DOC_INFO_HPP

