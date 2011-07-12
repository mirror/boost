#!/bin/bash
rm -fr html && doxygen && cp index.template.html html/index.html
