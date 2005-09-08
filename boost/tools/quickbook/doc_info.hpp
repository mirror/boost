/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_DOC_INFO_HPP)
#define BOOST_SPIRIT_QUICKBOOK_DOC_INFO_HPP

#include "./phrase.hpp"
#include <boost/spirit/core.hpp>
#include <boost/spirit/actor.hpp>
#include <boost/spirit/utility/loops.hpp>

namespace quickbook
{
    using namespace boost::spirit;

    template <typename Actions>
    struct doc_info_grammar
    : public grammar<doc_info_grammar<Actions> >
    {
        doc_info_grammar(Actions& actions)
            : actions(actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(doc_info_grammar const& self)
                : unused(false), common(self.actions, unused)
            {
                doc_info =
                        space
                    >>  '['
                    >>  (   str_p("book")
                        |   "article"
                        |   "library"
                        |   "chapter"
                        |   "part"
                        )                           [assign_a(self.actions.doc_type)]
                    >> hard_space
                    >>  (  *(anychar_p -
                            (ch_p('[') | ']' | eol_p)
                            )
                        )                           [assign_a(self.actions.doc_title)]
                    >> *( doc_version
                        | doc_id
                        | doc_dirname
                        | doc_copyright
                        | doc_purpose               [self.actions.extract_doc_purpose]
                        | doc_category
                        | doc_authors
                        | doc_license               [self.actions.extract_doc_license]
                        | doc_last_revision
                        | doc_source_mode
                        )
                    >> ']' >> +eol_p
                    ;

                doc_version =
                        space
                    >> "[version" >> hard_space
                    >> (*(anychar_p - ']'))         [assign_a(self.actions.doc_version)]
                    >> ']' >> +eol_p
                    ;

                doc_id =
                        space
                    >> "[id" >> hard_space
                    >> (*(anychar_p - ']'))         [assign_a(self.actions.doc_id)]
                    >> ']' >> +eol_p
                    ;

                doc_dirname =
                        space
                    >> "[dirname" >> hard_space
                    >> (*(anychar_p - ']'))         [assign_a(self.actions.doc_dirname)]
                    >> ']' >> +eol_p
                    ;

                doc_copyright =
                        space
                    >> "[copyright" >> hard_space
                    >> +( repeat_p(4)[digit_p]      [push_back_a(self.actions.doc_copyright_years)]
                          >> space
                        )
                    >> space
                    >> (*(anychar_p - ']'))         [assign_a(self.actions.doc_copyright_holder)]
                    >> ']' >> +eol_p
                    ;

                doc_purpose =
                        space
                    >> "[purpose" >> hard_space
                    >> phrase
                    >> ']' >> +eol_p
                    ;

                doc_category =
                        space
                    >> "[category" >> hard_space
                    >> (*(anychar_p - ']'))         [assign_a(self.actions.doc_category)]
                    >> ']' >> +eol_p
                    ;

                doc_author =
                        space
                    >>  '[' >> space
                    >>  (*(anychar_p - ','))        [assign_a(name.second)] // surname
                    >>  ',' >> space
                    >>  (*(anychar_p - ']'))        [assign_a(name.first)] // firstname
                    >>  ']'
                    ;

                doc_authors =
                        space
                    >> "[authors" >> hard_space
                    >> doc_author                   [push_back_a(self.actions.doc_authors, name)]
                    >> *(   ','
                            >>  doc_author          [push_back_a(self.actions.doc_authors, name)]
                        )
                    >> ']' >> +eol_p
                    ;

                doc_license =
                        space
                    >> "[license" >> hard_space
                    >> phrase
                    >> ']' >> +eol_p
                    ;

                doc_last_revision =
                        space
                    >> "[last-revision" >> hard_space
                    >> (*(anychar_p - ']'))         [assign_a(self.actions.doc_last_revision)]
                    >> ']' >> +eol_p
                    ;

                doc_source_mode =
                        space
                    >> "[source-mode" >> hard_space
                    >> (
                           str_p("c++") 
                        |  "python"
                        )                           [assign_a(self.actions.source_mode)]
                    >> space >> ']' >> +eol_p
                    ;

                comment =
                    "[/" >> *(anychar_p - ']') >> ']'
                    ;

                space =
                    *(space_p | comment)
                    ;

                hard_space =
                    (eps_p - (alnum_p | '_')) >> space  // must not be followed by
                    ;                                   // alpha-numeric or underscore

                phrase =
                   *(   common
                    |   comment
                    |   (anychar_p - ']')               [self.actions.plain_char]
                    )
                    ;
            }

            bool unused;
            std::pair<std::string, std::string> name;
            rule<Scanner>   doc_info, doc_title, doc_version, doc_id, doc_dirname,
                            doc_copyright, doc_purpose,doc_category, doc_authors,
                            doc_author, comment, space, hard_space, doc_license,
                            doc_last_revision, doc_source_mode, phrase;
            phrase_grammar<Actions> common;

            rule<Scanner> const&
            start() const { return doc_info; }
        };

        Actions& actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_DOC_INFO_HPP

