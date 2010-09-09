/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "phrase_grammar.hpp"
#include "actions_class.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_chset.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    template <typename Scanner>
    struct doc_info_grammar::definition
    {
        definition(doc_info_grammar const&);

        typedef cl::uint_parser<int, 10, 1, 2>  uint2_t;

        bool unused;
        std::string category;
        cl::rule<Scanner>
                        doc_info, doc_title, doc_version, doc_id, doc_dirname,
                        doc_copyright, doc_purpose, doc_category, doc_authors,
                        doc_author, comment, space, hard_space, doc_license,
                        doc_last_revision, doc_source_mode, doc_biblioid,
                        phrase, quickbook_version, char_;
        phrase_grammar common;
        cl::symbols<> doc_types;

        cl::rule<Scanner> const&
        start() const { return doc_info; }
    };

    template <typename Scanner>
    doc_info_grammar::definition<Scanner>::definition(doc_info_grammar const& self)
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
            >> (doc_types >> cl::eps_p)     [cl::assign_a(actions.doc_type)]
            >> hard_space
            >>  (  *(~cl::eps_p(cl::ch_p('[') | ']' | cl::eol_p) >> char_)
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
                    | doc_copyright         [cl::push_back_a(actions.doc_copyrights, actions.copyright)]
                    | doc_purpose
                    | doc_category
                    | doc_authors
                    | doc_license
                    | doc_last_revision
                    | doc_source_mode
                    | doc_biblioid
                    )
                    >> space >> ']' >> +cl::eol_p
                )
            >> space >> ']' >> +cl::eol_p
            ;

        quickbook_version =
                "quickbook" >> hard_space
            >>  (   cl::uint_p              [cl::assign_a(qbk_major_version)]
                    >> '.' 
                    >>  uint2_t()           [cl::assign_a(qbk_minor_version)]
                )
            ;

        doc_version =
                "version" >> hard_space
            >> (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_doc_version]
            ;

        // TODO: Restrictions on doc_id?
        doc_id =
                "id" >> hard_space
            >> (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_doc_id]
            ;

        // TODO: Restrictions on doc_dirname?
        doc_dirname =
                "dirname" >> hard_space
            >> (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_doc_dirname]
            ;

        doc_copyright =
                "copyright" >> hard_space   [cl::clear_a(actions.copyright.first)]
            >> +( cl::repeat_p(4)[cl::digit_p]
                                            [cl::push_back_a(actions.copyright.first)]
                  >> space
                )
            >> space
            >> (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_copyright_second]
            ;

        doc_purpose =
                "purpose" >> hard_space
            >> phrase                       [actions.extract_doc_purpose]
            ;

        doc_category =
                "category" >> hard_space
            >> (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_doc_category]
                                            [cl::push_back_a(actions.doc_categories, actions.doc_category)]
            ;

        doc_author =
                '[' >> space
            >>  (*(~cl::eps_p(',') >> char_))
                                            [actions.extract_name_second]
            >>  ',' >> space
            >>  (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_name_first]
            >>  ']'
            ;

        doc_authors =
                "authors"
            >>  hard_space
            >>  doc_author                  [cl::push_back_a(actions.doc_authors, actions.name)]
            >>  space
            >>  *(  !(cl::ch_p(',') >> space)
                >>  doc_author              [cl::push_back_a(actions.doc_authors, actions.name)]
                >>  space
                )
            ;

        doc_license =
                "license" >> hard_space
            >> phrase                       [actions.extract_doc_license]
            ;

        doc_last_revision =
                "last-revision" >> hard_space
            >> (*(~cl::eps_p(']') >> char_))
                                            [actions.extract_doc_last_revision]
            ;

        doc_source_mode =
                "source-mode" >> hard_space
            >>  (
                   cl::str_p("c++") 
                |  "python"
                |  "teletype"
                )                           [cl::assign_a(actions.source_mode)]
            ;

		doc_biblioid =
				"biblioid"
			>>	hard_space
			>>	(+cl::alnum_p)				[cl::assign_a(actions.doc_biblioid.first)]
			>>	hard_space
			>>	(+(~cl::eps_p(']') >> char_))
											[actions.extract_doc_biblioid]
											[cl::push_back_a(actions.doc_biblioid_items, actions.doc_biblioid)]
			;

        comment =
            "[/" >> *(cl::anychar_p - ']') >> ']'
            ;

        space =
            *(cl::space_p | comment)
            ;

        hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> space  // must not be preceded by
            ;                                   // alpha-numeric or underscore

        phrase =
           *(   common
            |   comment
            |   (cl::anychar_p - ']')       [actions.plain_char]
            )
            ;

        char_ =
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

    cl::parse_info<iterator> call_parse(
        iterator& first, iterator last, doc_info_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }
}
