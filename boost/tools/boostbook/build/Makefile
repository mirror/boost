include Makefile.def 
include Makefile.rules

default: html

all: html man pdf 

.dummy:

docbook: .dummy
	$(XSL) --stringparam boost.root $(BOOST_ROOT) $(BOOSTBOOK_XSL_PATH)/docbook.xsl $(BOOST_ROOT)/doc/src/boost.xml > boost.docbook
	@mkdir -p $(BOOST_ROOT)/doc

fo: docbook
	$(XSL) $(DOCBOOK_FO_PARAMS) $(DOCBOOK_XSL_PATH)/fo/docbook.xsl boost.docbook > boost.fo

man: docbook
	$(XSL) $(DOCBOOK_XSL_PATH)/manpages/docbook.xsl boost.docbook
	@rm -rf $(BOOST_ROOT)/doc/man
	@mkdir -p $(BOOST_ROOT)/doc/man
	@mkdir -p $(BOOST_ROOT)/doc/man/man3
	@mv *.3 $(BOOST_ROOT)/doc/man/man3
	(cd $(BOOST_ROOT) && tar czvf doc/boost-doc-man.tar.gz doc/man) 

html: docbook
	@rm -f $(BOOST_ROOT)/doc/html/*.html
	$(XSL) -o $(BOOST_ROOT)/doc/html/ $(BOOSTBOOK_XSL_PATH)/html.xsl boost.docbook

pdf: fo
	JAVA_HOME=$(JAVA_HOME) $(FOP) boost.fo $(BOOST_ROOT)/doc/boost.pdf	

testsuite: .dummy
	$(XSL) --stringparam boost.root $(BOOST_ROOT) $(BOOSTBOOK_XSL_PATH)/testing/Jamfile.xsl boost.xml

check: .dummy
	$(CHECK_DTD) $(BOOST_ROOT)/doc/src/boost.xml

check-docbook: docbook
	$(CHECK_DTD) boost.docbook

