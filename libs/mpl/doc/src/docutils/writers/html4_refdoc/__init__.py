
# Copyright Aleksey Gurtovoy 2004-2008
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

from docutils.writers import html4_frames
from docutils.writers import html4css1
from docutils import nodes

import re
import string


class Writer(html4_frames.Writer):
        
    def __init__(self):
        self.__super = html4_frames.Writer
        self.__super.__init__(self)
        self.translator = refdoc_translator


class refdoc_translator(html4_frames.frame_pages_translator):

    tocframe_width = 25
    
    def __init__(self, document, index_page, page_files_dir, extension):
        self.docframe += ' refmanual'
        self.__super = html4_frames.frame_pages_translator
        self.__super.__init__(self, document, index_page, page_files_dir, extension)
        self.page_translator = hacked_html_translator
        self.re_include = re.compile(r'(\s*#include\s+<)(.*?\.hpp)?(>\s*)?')
        self.re_identifier = re.compile(r'(.*?\W*)(\w+)(\W.*?)?')
        self.re_modtime = re.compile(r'\s*modtime:\s*(.*)')
        self.in_literal_block = 0
        self.in_reference = 0


    def visit_title(self, node):
        old_len = len(self.active_visitor().body)
        self.__super.visit_title(self, node)
        
        self = self.active_visitor()
        if len(self.body) - old_len > 1 and not node.has_key('refid'):
            name = nodes.make_id(node.astext())
            self.body[-1] = self.starttag(
                  {}, 'a', '', name=name, href='#%s' % name, CLASS='subsection-title'
                )

    def depart_title(self, node):
        self.__super.depart_title(self, node)


    def visit_reference(self, node):
        self.in_reference = 1
        if len(node) == 1 and isinstance(node[0], nodes.literal) and node[0].has_key('class'):
            if node.has_key('class') and node['class'].find(node[0]['class']) == -1:
                node['class'] += ' %s' % node[0]['class']
            else:
                node['class'] = node[0]['class']
            
        self.__super.visit_reference(self, node)


    def depart_reference(self, node):
        self.__super.depart_reference(self, node)
        self.in_reference = 0


    def visit_literal(self, node):
        if self.in_reference:
            self.__super.visit_literal(self, node)
     
        base = self
        self = self.active_visitor()

        self.body.append(self.starttag(node, 'tt', '', CLASS='literal'))
        text = node.astext()

        if base.re_include.search(text):
            text = base.re_include.sub(lambda m: base._handle_include_sub(self, m), text)
            self.body.append('<span class="pre">%s</span>' % text)
        else:
            for token in self.words_and_spaces.findall(text):
                if token.strip():
                    if base.re_identifier.search(token):
                        token = base.re_identifier.sub(lambda m: base._handle_id_sub(self, m), token)
                    else:
                        token = self.encode(token)

                    self.body.append('<span class="pre">%s</span>' % token)
                elif token in ('\n', ' '):
                    # Allow breaks at whitespace:
                    self.body.append(token)
                else:
                    # Protect runs of multiple spaces; the last space can wrap:
                    self.body.append('&nbsp;' * (len(token) - 1) + ' ')

        self.body.append('</tt>')
        # Content already processed:
        raise nodes.SkipNode


    def visit_literal_block(self, node):
        self.__super.visit_literal_block(self, node)
        self.in_literal_block = True

    def depart_literal_block(self, node):
        self.__super.depart_literal_block(self, node)
        self.in_literal_block = False


    def visit_Text(self, node):
        if not self.in_literal_block:
            self.__super.visit_Text(self, node)
        else:
            base = self
            self = self.active_visitor()
            
            text = node.astext()            
            if base.re_include.search(text):
                text = base.re_include.sub(lambda m: base._handle_include_sub(self, m), text)
            elif base.re_identifier.search(text):
                text = base.re_identifier.sub(lambda m: base._handle_id_sub(self, m), text)
            else:
                text = self.encode(text)
            
            self.body.append(text)


    def depart_Text(self, node):
        pass


    def visit_substitution_reference(self, node):
        # debug help
        print 'Unresolved substitution_reference:', node.astext()
        raise nodes.SkipNode

    def _handle_depart_page(self, translator, node):
        pass


    def _handle_include_sub(base, self, match):
        if not match.group(2) or not match.group():
            return self.encode(match.group(0))

        header = match.group(2)
        result = self.encode(match.group(1))
        result += '<a href="%s" class="header">%s</a>' \
                        % ( '../../../../%s' % header
                          , self.encode(header)
                          )
        
        result += self.encode(match.group(3))
        return result

    
    def _handle_id_sub(base, self, match):
        identifier = match.group(2)        
        if not base.document.has_name( identifier.lower() ):
            return self.encode(match.group(0))
        
        result = self.encode(match.group(1))
        result += '<a href="%s" class="identifier">%s</a>' \
                        % ( base._chunk_ref( base._active_chunk_id(), base.document.nameids[identifier.lower()] )
                          , self.encode(identifier)
                          )
        
        if match.group(3):
            result += self.encode(match.group(3))

        return result


class hacked_html_translator(nodes.NodeVisitor):
        
    def __init__(self, document):
        self.__super = nodes.NodeVisitor
        self.__super.__init__(self, document)
        self.base = html4css1.HTMLTranslator(document)
        self.body = self.base.body
        self.head = self.base.head
        self.astext = self.base.astext
        self.starttag = self.base.starttag
        self.words_and_spaces = self.base.words_and_spaces
        self.encode = self.base.encode
        self.recursion_level = 0

    def visit_section(self, node):
        if self.base.section_level == 1:
            self.base.section_level = 2
            
        self.base.body_prefix = self.body_prefix
        self.base.visit_section(node)
        
    def depart_section(self, node):
        self.base.depart_section(node)
        if self.base.section_level == 2:
            self.base.section_level = 1
 

    def visit_generated(self, node):
        if node.get('class', '') == 'sectnum':
            node[0].data = string.strip(node[0].data, u'\u00a0')
            
        self.base.visit_generated(node)

    def depart_generated(self, node):
        self.base.depart_generated(node)


def _setup_forwarding(visitor):
    for name in nodes.node_class_names:
        if not getattr(visitor, 'visit_' + name, None):
        
            def forward_visit(self, node, name=name):
                self.recursion_level += 1
                #print '%svisit_%s' % ( '+' * self.recursion_level, name )
                getattr(self.base, 'visit_' + name)(node)

            def forward_depart(self, node, name=name):
                #print '%sdepart_%s' % ( '-' * self.recursion_level, name )
                self.recursion_level -= 1
                getattr(self.base, 'depart_' + name)(node)
            
            setattr(visitor, 'visit_' + name, forward_visit)
            setattr(visitor, 'depart_' + name, forward_depart)

_setup_forwarding(hacked_html_translator)
