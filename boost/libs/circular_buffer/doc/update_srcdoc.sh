#!/bin/sh
################################################################################
# Shell script which updates the Circular Buffer library documentation with    #
# the latest source code documentation (which is in the source files).         #
#                                                                              #
# Copyright (c) 2007 Jan Gaspar                                                #
#                                                                              #
# Use, modification, and distribution is subject to the Boost Software         #
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at      #
# http://www.boost.org/LICENSE_1_0.txt)                                        #
################################################################################

DOCFILE="$1.html"

if [ -f $DOCFILE ]; then

  echo Starting Doxygen ...
  doxygen

  echo Converting Doxygen generated source code documentation into XHTML ...
  xsltproc --stringparam container $1 --stringparam xmldir srcdoc -o srcdoc/srcdoc.xhtml $1.xslt srcdoc/index.xml

  echo Preprocessing $DOCFILE ...
  sed 's/<a\s*id="[^"]*"/<a /g' $DOCFILE | sed 's/<a\s*\(name="[^"]*"\)\s*\(id="[^"]*"\)/<a \1/g' > srcdoc/$DOCFILE

  echo Converting preprocessed $DOCFILE into XHTML ...
  xsltproc --html -o srcdoc/$1.xhtml html2xhtml.xslt srcdoc/$DOCFILE

  echo Generating $DOCFILE with updated source code documentation ...
  xsltproc --stringparam srcdoc srcdoc/srcdoc.xhtml -o $DOCFILE update_srcdoc.xslt srcdoc/$1.xhtml

  echo Correcting and pretty-printing $DOCFILE with HTML Tidy ...
  tidy -ashtml -config Tidy.conf $DOCFILE

  echo Removing temporary directory ...
  rm -rf srcdoc

  echo Done.

else

  echo Usage: update_srcdoc.sh container

fi
