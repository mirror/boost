# GNUmakefile for postprocessing PDF files
#
# © 2000 IBM Corporation.
# Licensed under the GNU GPL.

########################################################################
# Make sure that the following macros are correct for your setup
########################################################################
# ... System utilities
RMRF	= /bin/rm -rf
MV	= /bin/mv
EGREP	= /bin/egrep
ECHO	= /bin/echo
PERL	= /usr/bin/perl
CAT	= /bin/cat
TOUCH 	= /bin/touch
ZIP	= /usr/bin/zip

# ... TeX & postprocessors
PPOWER4	      = ppower4
PDFLATEX      = pdflatex
METAPOST      = mpost
FIG2DEV	      = fig2dev
BIBTEX	      = bibtex
FOLIAGECUTTER = foliageCutter --verbose
RST2LATEX	  = rst2latex --documentclass book --documentoptions 10pt,twoside,pdftex # --use-latex-toc
RST2HTML	  = rst2html

TEX = latex
export TEX
########################################################################
# End of user servicable parts; don't fiddle with the remainder of this
# makefile unless you know what you do.
#
# You have been warned ;=)
########################################################################

# ... Variables
TEXFILES = $(strip $(wildcard *.tex))
RSTFILES = $(strip $(wildcard *.rst))
-include GNUmakefile.local
TEXSTEMS = $(strip $(patsubst %.tex,%,${TEXFILES}))
RSTSTEMS = $(strip $(patsubst %.rst,%,${RSTFILES}))
CUTFOILS = $(strip $(patsubst %,%---toc.tex,${TEXSTEMS}))
PDFFILES = $(strip $(patsubst %.tex,%.pdf,${TEXFILES}))
PRINTS = $(patsubst %.pdf,%-print.pdf,${PDFFILES})
PRINTZIP = prints.zip
SLIDEZIP = slides.zip

# ... Depend
DEPENDFILES = .depend .depend-rst
GENFILE	    = .generated

# ... List of extensions and files generated
texcrap = *.mpx *.log *.aux *.blg *-print.brf *-print.tex *.out

mpxcrap = mpxerr.tex mpxerr.pdf

generated = *.out *.[0-9] *.[0-9][0-9] *.bbl *.brf \
	    *.mp *.mmp *.pdf *.ps TMP-*.pdf *.ftoc\
	    ${PRINTZIP} ${SLIDEZIP} ${GENFILE} ${DEPENDFILES} \
	    ${texcrap} ${mpxcrap} ${CUTFOILS} $(strip $(wildcard *---*.tex))


# ... canned command to run PDFLaTeX
define run-pdflatex
@${ECHO} ""
@${ECHO} "---- Running PDFLaTeX on $<" && ${PDFLATEX} $<
@${ECHO} "---- Running PDFLaTeX on $< again" && ${PDFLATEX} $<
-@(${EGREP} -qi 'Rerun to get' $*.log && \
		${ECHO} "---- Rerunning PDFLaTeX on $* to get cross-refs right" && \
		${PDFLATEX} $<) || \
		${ECHO} "---- No cross-refs correcting PDFLaTeX rerun required for $*"
-@(${EGREP} -qi $*.ftoc $*.log && \
		${ECHO} "---- Rerunning PDFLaTeX on $* for FTOC" && \
		${PDFLATEX} $<) || \
		${ECHO} "---- No FTOC PDFLaTeX run required for $*"
-@(${EGREP} -qi 'Warning: Citation' $*.log && \
		${ECHO} "---- Running BIBTeX on $*" && \
		${BIBTEX} $* && \
		${ECHO} "---- Running PDFLaTeX on $<" && \
		${PDFLATEX} $<) || \
		${ECHO} "---- No BIBTeX run required for $*"
-@(${EGREP} -qi 'Warning: .+undefined references' $*.log && \
		${ECHO} "---- Running PDFLaTeX on $<" && \
		${PDFLATEX} $<) || \
		${ECHO} "---- No further PDFLaTex run required for $<"
@${ECHO} "Generated:     $@ {$<}" >> ${GENFILE}
@${RMRF} ${texcrap}
endef

# ... canned command to run PDFLaTeX for printable versions
define run-pdflatex-for-print
@${ECHO} ""
@${ECHO} "---- Running PDFLaTeX on $*-print.tex" && ${PDFLATEX} $*-print.tex
@${ECHO} "---- Running PDFLaTeX on $< again" && ${PDFLATEX} $<
-@(${EGREP} -qi 'Warning: Citation' $*-print.log && \
		${ECHO} "---- Running BIBTeX on $*-print" && \
		${BIBTEX} $*-print && \
		${ECHO} "---- Running PDFLaTeX on $*-print.tex" && \
		${PDFLATEX} $*-print.tex) || \
		${ECHO} "---- No BIBTeX run required for $*"
-@(${EGREP} -qi 'Warning: .+undefined references' $*-print.log && \
		${ECHO} "---- Running PDFLaTeX on $*-print" && \
		${PDFLATEX} $*-print.tex) || \
		${ECHO} "---- No further PDFLaTex run required for $*-print"
@${ECHO} "Generated:     $@ {$<}" >> ${GENFILE}
@${RMRF} ${texcrap}
endef

# DWA begin modifications
# ... Rule: How to generate TeX from ReST
%.tex: %.txt
	@${ECHO} "---- Running rst2latex on $<"
	${RST2LATEX} $< $@
	@${ECHO} "Generated: $@ {$<}" >> ${GENFILE}

# ... Rule: How to generate TeX from ReST
%.tex: %.rst
	@${ECHO} "---- Running rst2latex on $<"
	${RST2LATEX} $< $@
	@${ECHO} "Generated: $@ {$<}" >> ${GENFILE}

# ... Rule: How to generate HTML from ReST
%.html: %.txt
	@${ECHO} "---- Running rst2html on $<"
	${RST2HTML} $< $@
	@${ECHO} "Generated: $@ {$<}" >> ${GENFILE}

# ... Rule: How to generate HTML from ReST
%.html: %.rst
	@${ECHO} "---- Running rst2html on $<"
	${RST2HTML} $< $@
	@${ECHO} "Generated: $@ {$<}" >> ${GENFILE}
# DWA end modifications

# ... Rule: How to generate PDF from TeX
%.pdf: %.tex
	$(run-pdflatex)
	@${MV} $@ TMP-$@
	@${ECHO} "---- Running PPower4 on $*"
	${PPOWER4} -v TMP-$@ $@
	@${RMRF} TMP-$@
	@${ECHO} "Postprocessed: $*.pdf {$*.pdf}" >> ${GENFILE}

# ... Rule: How to generate printable PDF from TeX
%-print.pdf: %.tex
	${PERL} -pe 's/^\\documentclass\[(.*?)\]/\\documentclass\[$$1,prints\]/;' < $< > $*-print.tex
	$(run-pdflatex-for-print)
	@${ECHO} "Generated:     $*-print.pdf {$*.pdf}" >> ${GENFILE}

# ... Rule: How to generate cut foils from TeX master
%---toc.tex: %.tex
	${FOLIAGECUTTER} --prefix=$* $<

# ... Rule: How to generate MetaPost from FIG
%.mp: %.fig
	@${ECHO} "---- Running Fig2Dev (mp) on $<"
	${FIG2DEV} -L mp $< $@
	@${ECHO} "Generated:     $@ {$<}" >> ${GENFILE}

# ... Rule: How to generate MultiMetaPost from FIG
%.mmp: %.fig
	@${ECHO} "---- Running Fig2Dev (mmp) on $<"
	${FIG2DEV} -L mmp $< $@
	@${ECHO} "Generated:     $@ {$<}" >> ${GENFILE}

# ... Rule: How to generate includable PS from FIG via MetaPost
%.mps: %.fig
	@${ECHO} "---- Running Fig2Dev (mps) on $<"
	${FIG2DEV} -L mp $< $*.mps.mp
	@${RMRF} $*.mps.[0-9]
	${METAPOST} $*.mps.mp
	@${MV} $*.mps.0 $@
	@${ECHO} "Generated:     $@ {$<}" >> ${GENFILE}

# ... Rule: How to generate includable PS files from MultiMetaPost
%.0: %.mmp
	@${ECHO} "---- Running MetaPost on $<"
	@${RMRF} $*.[0-9] $*.[0-9][0-9]
	${METAPOST} $<
	@${ECHO} "Generated:     $*.0{...} {$<}" >> ${GENFILE}

cleanup-crap:
	@${RMRF} ${mpxcrap}

# ... Target: all
all: cleanup-crap ${DEPENDFILES} ${PDFFILES} ${PRINTS} ${PRINTZIP} ${SLIDEZIP}
	@${ECHO} ""
	@${TOUCH} ${GENFILE}
	@${CAT} ${GENFILE}
	@${RMRF} ${GENFILE}

# ... Target: ZIP files
zip zips: ${PRINTZIP} ${SLIDEZIP}

# ... Target: ZIP file containing printable versions of slides
${PRINTZIP}: .depend ${PDFFILES}
	@${RMRF} ${PRINTZIP}
	${ZIP} -r ${PRINTZIP} ${PRINTS}
	@${ECHO} "Generated:     ${PRINTZIP}" >> ${GENFILE}

# ... Target: ZIP file containing screen versions of slides
 ${SLIDEZIP}: .depend ${PDFFILES}
	@${RMRF} ${SLIDEZIP}
	${ZIP} -r ${SLIDEZIP} ${PDFFILES}
	@${ECHO} "Generated:     ${SLIDEZIP}" >> ${GENFILE}

# ... Target: clean up
clean:
	${RMRF} ${generated}

# ... Target: create dependencies
depend: .depend-rst

# ... Target: dependency file (parse TEXFILES for multiinclude and includegraphics)
.depend: GNUmakefile ${TEXFILES}
	${RMRF} $@
	@for t in ${TEXSTEMS} ; do \
		${ECHO} "Scanning $$t.tex"; \
		${PERL} -e 'my $$target = shift @ARGV;' -e 'while (<>) { /\\multiinclude(\[.*?\])?{(.*?)}/ && print "$$target: $$2.0\n";}' $$t.pdf < $$t.tex >> $@; \
		${PERL} -e 'my $$target = shift @ARGV;' -e 'while (<>) { /\\includegraphics(\[.*?\])?{(.*?)\.(.*?)}/ && print "$$target: $$2.$$3\n";}' $$t.pdf < $$t.tex >> $@; \
	done

.depend-rst: GNUmakefile ${RSTFILES}
	${RMRF} $@
	@for t in ${RSTSTEMS} ; do \
		${ECHO} "Scanning $$t.rst"; \
		${PERL} -e 'my $$target = shift @ARGV;' -e 'while (<>) { /^\.\. (include|image)::\s+(.*)/ && print "$$target: $$2\n";}' $$t.html < $$t.rst >> $@; \
		${PERL} -e 'my $$target = shift @ARGV;' -e 'while (<>) { /^\.\. (include|image)::\s+(.*)/ && print "$$target: $$2\n";}' $$t.tex < $$t.rst >> $@; \
	done


# ... include dependency files
# -include .depend
-include .depend-rst
