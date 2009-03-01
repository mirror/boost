PROJECT_ROOT="../../../.."
#uncomment next line with correct path to boost_docs or pass BOOST_SRC_DIR to make environment.
#BOOST_SRC_DIR=~/svn/boost_docs/
BOOSTBOOK_TOOL_DIR=$(BOOST_SRC_DIR)/tools/boostbook

XML_SRCS=\
	examples.xml \
	faq.xml \
	introduction.xml \
	porting.xml \
	rationale.xml \
	signals.xml \
	tests.xml \
	thread_safety.xml \
	tutorial.xml \
	reference/connection.xml \
	reference/deconstruct.xml \
	reference/dummy_mutex.xml \
	reference/last_value.xml \
	reference/mutex.xml \
	reference/optional_last_value.xml \
	reference/reference.xml \
	reference/shared_connection_block.xml \
	reference/signal_base.xml \
	reference/signal_header.xml \
	reference/signal_type.xml \
	reference/slot_base.xml \
	reference/slot.xml \
	reference/trackable.xml \
#	reference/visit_each.xml

.PHONY: all
all: doc

.PHONY: clean
clean:
	$(RM) -r html/*
	$(RM) *.docbook

.PHONY: doc
doc: html

.PHONY: html
html: signals.docbook
	(export XML_CATALOG_FILES="./catalog.xml /etc/xml/catalog";\
		xsltproc --xinclude --stringparam project.root $(PROJECT_ROOT) \
		--stringparam chapters.select.box.show false \
		--stringparam google.search.box.show false \
		--stringparam generate.manifest 0 \
		-o html/ $(BOOSTBOOK_TOOL_DIR)/xsl/html.xsl $<)

signals.docbook: $(XML_SRCS)
	(export XML_CATALOG_FILES="./catalog.xml /etc/xml/catalog";\
		xsltproc --xinclude --stringparam project.root $(PROJECT_ROOT) -o $@ $(BOOSTBOOK_TOOL_DIR)/xsl/docbook.xsl signals.xml)
