#!/usr/bin/python

#
# Generate html, TeX, and PDF versions of all the source files
#
import os
import sys

from syscmd import syscmd
from sources import sources

if 0:
    for s in sources:
        syscmd('boosthtml %s' % s)
else:        
    extensions = ('html', 'tex', 'pdf')

    if len(sys.argv) > 1:
        extensions = sys.argv[1:]

    all = [ '%s.%s' % (os.path.splitext(s)[0],ext)
          for ext in extensions
          for s in sources 
        ]

    print 'make -k %s' % ' '.join(all)
    syscmd('make -k %s' % ' '.join(all))


