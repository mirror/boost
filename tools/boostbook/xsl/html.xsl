<?xml version="1.0" encoding="utf-8"?>
<!--
   Copyright (c) 2002 Douglas Gregor <doug.gregor -at- gmail.com>

   Distributed under the Boost Software License, Version 1.0.
   (See accompanying file LICENSE_1_0.txt or copy at
   http://www.boost.org/LICENSE_1_0.txt)
  -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:rev="http://www.cs.rpi.edu/~gregod/boost/tools/doc/revision"
                xmlns:l="http://docbook.sourceforge.net/xmlns/l10n/1.0"
                version="1.0">

  <!-- Import the HTML chunking stylesheet -->
  <xsl:import
    href="http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl"/>
  <xsl:import
    href="http://docbook.sourceforge.net/release/xsl/current/html/math.xsl"/>

  <!-- Bring in the fast chunking overrides.  There's nothing
       that we need to override, so include instead of importing it. -->
  <xsl:include
    href="http://docbook.sourceforge.net/release/xsl/current/html/chunkfast.xsl"/>
  
  <!-- We have to make sure that our templates override all
       docbook templates.  Therefore, we include our own templates
       instead of importing them.  In order for this to work,
       the stylesheets included here cannot also include each other -->
  <xsl:include href="chunk-common.xsl"/>
  <xsl:include href="docbook-layout.xsl"/>
  <xsl:include href="navbar.xsl"/>
  <xsl:include href="admon.xsl"/>
  <xsl:include href="xref.xsl"/>
  <xsl:include href="relative-href.xsl"/>
  <xsl:include href="callout.xsl"/>
  
  <xsl:param name="html.stylesheet">
    <xsl:choose>
      <xsl:when test = "$boost.defaults = 'Boost'">
        <xsl:value-of select = "concat($boost.root, '/doc/src/boostbook.css')"/>
      </xsl:when>
      <xsl:otherwise>
        boostbook.css
      </xsl:otherwise>
    </xsl:choose>
  </xsl:param>

  <xsl:param name="admon.style"/>
  <xsl:param name="admon.graphics">1</xsl:param>
  <xsl:param name="boostbook.verbose" select="0"/>
  <xsl:param name="navig.graphics" select="1"/>
  <xsl:param name="navig.graphics.extension" select="'.png'"/>
  <xsl:param name="chapter.autolabel" select="1"/>
  <xsl:param name="use.id.as.filename" select="1"/>
  <xsl:param name="refentry.generate.name" select="0"/>
  <xsl:param name="refentry.generate.title" select="1"/>
  <xsl:param name="make.year.ranges" select="1"/>
  <xsl:param name="generate.manifest" select="1"/>
  <xsl:param name="generate.section.toc.level" select="3"/>
  <xsl:param name="doc.standalone">false</xsl:param>
  <xsl:param name="chunker.output.indent">yes</xsl:param>
  <xsl:param name="chunker.output.encoding">US-ASCII</xsl:param>
  <xsl:param name="chunk.quietly" select="not(number($boostbook.verbose))"/>
  <xsl:param name="toc.max.depth">2</xsl:param>
  <xsl:param name="callout.graphics.number.limit">15</xsl:param>
  <xsl:param name = "admon.graphics.path"
            select = "concat($boost.root, '/doc/html/images/')"/>
  <xsl:param name = "navig.graphics.path"
            select = "concat($boost.root, '/doc/html/images/')"/>
  <xsl:param name = "callout.graphics.path"
            select = "concat($boost.root, '/doc/src/images/callouts/')"/>
  <xsl:param name="l10n.gentext.language" select="'en'"/>

  <xsl:param name="generate.toc">
appendix  toc,title
article/appendix  nop
article   toc,title
book      toc,title
chapter   toc,title
part      toc,title
preface   toc,title
qandadiv  toc
qandaset  toc
reference toc,title
sect1     toc
sect2     toc
sect3     toc
sect4     toc
sect5     toc
section   toc
set       toc,title
  </xsl:param>


  <xsl:template name="format.cvs.revision">
    <xsl:param name="text"/>

    <!-- Remove the "$Date: " -->
    <xsl:variable name="text.noprefix"
      select="substring-after($text, '$Date: ')"/>

    <!-- Grab the year -->
    <xsl:variable name="year" select="substring-before($text.noprefix, '/')"/>
    <xsl:variable name="text.noyear"
      select="substring-after($text.noprefix, '/')"/>

    <!-- Grab the month -->
    <xsl:variable name="month" select="substring-before($text.noyear, '/')"/>
    <xsl:variable name="text.nomonth"
      select="substring-after($text.noyear, '/')"/>

    <!-- Grab the year -->
    <xsl:variable name="day" select="substring-before($text.nomonth, ' ')"/>
    <xsl:variable name="text.noday"
      select="substring-after($text.nomonth, ' ')"/>

    <!-- Get the time -->
    <xsl:variable name="time" select="substring-before($text.noday, ' ')"/>

    <xsl:variable name="month.name">
      <xsl:choose>
        <xsl:when test="$month=1">January</xsl:when>
        <xsl:when test="$month=2">February</xsl:when>
        <xsl:when test="$month=3">March</xsl:when>
        <xsl:when test="$month=4">April</xsl:when>
        <xsl:when test="$month=5">May</xsl:when>
        <xsl:when test="$month=6">June</xsl:when>
        <xsl:when test="$month=7">July</xsl:when>
        <xsl:when test="$month=8">August</xsl:when>
        <xsl:when test="$month=9">September</xsl:when>
        <xsl:when test="$month=10">October</xsl:when>
        <xsl:when test="$month=11">November</xsl:when>
        <xsl:when test="$month=12">December</xsl:when>
      </xsl:choose>
    </xsl:variable>

    <xsl:value-of select="concat($month.name, ' ', $day, ', ', $year, ' at ',
                                 $time, ' GMT')"/>
  </xsl:template>


  <xsl:template name="format.svn.revision">
    <xsl:param name="text"/>

    <!-- Remove the "$Date: " -->
    <xsl:variable name="text.noprefix"
      select="substring-after($text, '$Date: ')"/>

    <!-- Grab the year -->
    <xsl:variable name="year" select="substring-before($text.noprefix, '-')"/>
    <xsl:variable name="text.noyear"
      select="substring-after($text.noprefix, '-')"/>

    <!-- Grab the month -->
    <xsl:variable name="month" select="substring-before($text.noyear, '-')"/>
    <xsl:variable name="text.nomonth"
      select="substring-after($text.noyear, '-')"/>

    <!-- Grab the year -->
    <xsl:variable name="day" select="substring-before($text.nomonth, ' ')"/>
    <xsl:variable name="text.noday"
      select="substring-after($text.nomonth, ' ')"/>

    <!-- Get the time -->
    <xsl:variable name="time" select="substring-before($text.noday, ' ')"/>
    <xsl:variable name="text.notime"
      select="substring-after($text.noday, ' ')"/>

    <!-- Get the timezone -->
    <xsl:variable name="timezone" select="substring-before($text.notime, ' ')"/>

    <xsl:variable name="month.name">
      <xsl:choose>
        <xsl:when test="$month=1">January</xsl:when>
        <xsl:when test="$month=2">February</xsl:when>
        <xsl:when test="$month=3">March</xsl:when>
        <xsl:when test="$month=4">April</xsl:when>
        <xsl:when test="$month=5">May</xsl:when>
        <xsl:when test="$month=6">June</xsl:when>
        <xsl:when test="$month=7">July</xsl:when>
        <xsl:when test="$month=8">August</xsl:when>
        <xsl:when test="$month=9">September</xsl:when>
        <xsl:when test="$month=10">October</xsl:when>
        <xsl:when test="$month=11">November</xsl:when>
        <xsl:when test="$month=12">December</xsl:when>
      </xsl:choose>
    </xsl:variable>

    <xsl:value-of select="concat($month.name, ' ', $day, ', ', $year, ' at ',
                                 $time, ' ', $timezone)"/>
  </xsl:template>

  <!-- Footer Copyright -->
  <xsl:template match="copyright" mode="boost.footer">
    <xsl:if test="position() &gt; 1">
      <br/>
    </xsl:if>
    <xsl:call-template name="gentext">
      <xsl:with-param name="key" select="'Copyright'"/>
    </xsl:call-template>
    <xsl:call-template name="gentext.space"/>
    <xsl:call-template name="dingbat">
      <xsl:with-param name="dingbat">copyright</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="gentext.space"/>
    <xsl:call-template name="copyright.years">
      <xsl:with-param name="years" select="year"/>
      <xsl:with-param name="print.ranges" select="$make.year.ranges"/>
      <xsl:with-param name="single.year.ranges"
        select="$make.single.year.ranges"/>
    </xsl:call-template>
    <xsl:call-template name="gentext.space"/>
    <xsl:apply-templates select="holder" mode="titlepage.mode"/>
  </xsl:template>

  <!-- Footer License -->
  <xsl:template match="legalnotice" mode="boost.footer">
    <xsl:apply-templates select="para" mode="titlepage.mode" />
  </xsl:template>

  <xsl:template name="user.footer.content">
    <table width="100%">
      <tr>
        <td align="left">
          <xsl:variable name="revision-nodes"
            select="ancestor-or-self::*
                    [not (attribute::rev:last-revision='')]"/>
          <xsl:if test="count($revision-nodes) &gt; 0">
            <xsl:variable name="revision-node"
              select="$revision-nodes[last()]"/>
            <xsl:variable name="revision-text">
              <xsl:value-of
                select="normalize-space($revision-node/attribute::rev:last-revision)"/>
            </xsl:variable>
            <xsl:if test="string-length($revision-text) &gt; 0">
              <p>
                <small>
                  <xsl:text>Last revised: </xsl:text>
                  <xsl:choose>
                    <xsl:when test="contains($revision-text, '/')">
                      <xsl:call-template name="format.cvs.revision">
                        <xsl:with-param name="text" select="$revision-text"/>
                      </xsl:call-template>
                    </xsl:when>
                    <xsl:otherwise>
                      <xsl:call-template name="format.svn.revision">
                        <xsl:with-param name="text" select="$revision-text"/>
                      </xsl:call-template>
                    </xsl:otherwise>
                  </xsl:choose>
                </small>
              </p>
            </xsl:if>
          </xsl:if>
        </td>
        <td align="right">
          <div class = "copyright-footer">
            <xsl:apply-templates select="ancestor::*/*/copyright"
              mode="boost.footer"/>
            <xsl:apply-templates select="ancestor::*/*/legalnotice"
              mode="boost.footer"/>
          </div>
        </td>
      </tr>
    </table>
  </xsl:template>

  <!-- We don't want refentry's to show up in the TOC because they
       will merely be redundant with the synopsis. -->
  <xsl:template match="refentry" mode="toc"/>

  <!-- override the behaviour of some DocBook elements for better
       rendering facilities -->

  <xsl:template match = "programlisting[ancestor::informaltable]">
     <pre class = "table-{name(.)}"><xsl:apply-templates/></pre>
  </xsl:template>

  <xsl:template match = "refsynopsisdiv">
     <h2 class = "{name(.)}-title">Synopsis</h2>
     <div class = "{name(.)}">
        <xsl:apply-templates/>
     </div>
  </xsl:template>
  
  <!-- Override some unbearably slow docbook templates -->
  
  <xsl:template name="l10n.language">
    <xsl:param name="target" select="."/>
    <xsl:param name="xref-context" select="false()"/>
    <xsl:value-of select="'en'"/>
  </xsl:template>

  <xsl:param name="l10n.xml" select="document('http://docbook.sourceforge.net/release/xsl/current/common/l10n.xml')"/>
  <xsl:param name="local.l10n.xml" select="document('')"/>
  
  <xsl:key name="l10n"
           match="l:i18n/l:l10n/l:context/l:template"
           use="concat(../../@language, '#', ../@name, '#', @name, '#', @style)"/>

  <xsl:template name="gentext.template">
    <xsl:param name="context" select="'default'"/>
    <xsl:param name="name" select="'default'"/>
    <xsl:param name="origname" select="$name"/>
    <xsl:param name="purpose"/>
    <xsl:param name="xrefstyle"/>
    <xsl:param name="referrer"/>
    <xsl:param name="lang">
      <xsl:call-template name="l10n.language"/>
    </xsl:param>
    <xsl:param name="verbose" select="1"/>

    <xsl:variable name="key1" select="concat($lang, '#', $context, '#', $name, '#', $xrefstyle)"/>
    <xsl:variable name="key2" select="concat($lang, '#', $context, '#', $name, '#')"/>

    <xsl:for-each select="$local.l10n.xml">
      <xsl:choose>
        <xsl:when test="key('l10n', $key2)/@text">
          <xsl:value-of select="key('l10n', $key2)/@text"/>
        </xsl:when>
        <xsl:when test="key('l10n', $key1)/@text">
          <xsl:value-of select="key('l10n', $key1)/@text"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:for-each select="$l10n.xml">
            <xsl:choose>
              <xsl:when test="key('l10n', $key2)/@text">
                <xsl:value-of select="key('l10n', $key2)/@text"/>
              </xsl:when>
              <xsl:when test="key('l10n', $key1)/@text">
                <xsl:value-of select="key('l10n', $key1)/@text"/>
              </xsl:when>
              <xsl:when test="contains($name, '/')">
                <xsl:call-template name="gentext.template">
                  <xsl:with-param name="context" select="$context"/>
                  <xsl:with-param name="name" select="substring-after($name, '/')"/>
                  <xsl:with-param name="origname" select="$origname"/>
                  <xsl:with-param name="purpose" select="$purpose"/>
                  <xsl:with-param name="xrefstyle" select="$xrefstyle"/>
                  <xsl:with-param name="referrer" select="$referrer"/>
                  <xsl:with-param name="lang" select="$lang"/>
                  <xsl:with-param name="verbose" select="$verbose"/>
                </xsl:call-template>
              </xsl:when>
              <xsl:when test="$verbose = 0">
                <!-- silence -->
              </xsl:when>
              <xsl:otherwise>
                <xsl:message>
                  <xsl:text>No template for "</xsl:text>
                  <xsl:value-of select="$origname"/>
                  <xsl:text>" (or any of its leaves) exists
in the context named "</xsl:text>
                  <xsl:value-of select="$context"/>
                  <xsl:text>" in the "</xsl:text>
                  <xsl:value-of select="$lang"/>
                  <xsl:text>" localization.</xsl:text>
                </xsl:message>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:for-each>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:for-each>
  </xsl:template>

  <!-- Generate a title attribute for the context node -->
  <xsl:template match="*" mode="html.title.attribute">

    <xsl:variable name="lang">
      <xsl:call-template name="l10n.language"/>
    </xsl:variable>
    
    <xsl:variable name="name" select="local-name(.)"/>
    
    <xsl:variable name="key.title" select="concat($lang, '#', 'title', '#', $name, '#')"/>
    <xsl:variable name="key.title-numbered" select="concat($lang, '#', 'title-numbered', '#', $name, '#')"/>
    <xsl:variable name="key.title-unnumbered" select="concat($lang, '#', 'title-unnumbered', '#', $name, '#')"/>

    <xsl:variable name="is.title.any">
      <xsl:for-each select="$local.l10n.xml">
        <xsl:choose>
          <xsl:when test="key('l10n', $key.title)/@text">
            <xsl:value-of select="1"/>
          </xsl:when>
          <xsl:when test="key('l10n', $key.title-numbered)/@text">
            <xsl:value-of select="1"/>
          </xsl:when>
          <xsl:when test="key('l10n', $key.title-unnumbered)/@text">
            <xsl:value-of select="1"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:for-each select="$l10n.xml">
              <xsl:choose>
                <xsl:when test="key('l10n', $key.title)/@text">
                  <xsl:value-of select="1"/>
                </xsl:when>
                <xsl:when test="key('l10n', $key.title-numbered)/@text">
                  <xsl:value-of select="1"/>
                </xsl:when>
                <xsl:when test="key('l10n', $key.title-unnumbered)/@text">
                  <xsl:value-of select="1"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="0"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:for-each>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>
    </xsl:variable>
    
    <xsl:variable name="has.title.markup">
      <xsl:apply-templates select="." mode="title.markup">
        <xsl:with-param name="verbose" select="0"/>
      </xsl:apply-templates>
    </xsl:variable>

    <xsl:variable name="gentext.title">
      <xsl:if test="$has.title.markup != '???TITLE???' and
                  ($is.title.any != 0)">
        <xsl:apply-templates select="."
                             mode="object.title.markup.textonly"/>
      </xsl:if>
    </xsl:variable>

    <xsl:choose>
      <xsl:when test="string-length($gentext.title) != 0">
        <xsl:attribute name="title">
          <xsl:value-of select="$gentext.title"/>
        </xsl:attribute>
      </xsl:when>
      <!-- Fall back to alt if available -->
      <xsl:when test="alt">
        <xsl:attribute name="title">
          <xsl:value-of select="normalize-space(alt)"/>
        </xsl:attribute>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="html.head">
    <xsl:param name="prev" select="/foo"/>
    <xsl:param name="next" select="/foo"/>
    <xsl:variable name="this" select="."/>
    <xsl:variable name="home" select="/*[1]"/>
    <xsl:variable name="up" select="parent::*"/>

    <head>
      <xsl:call-template name="system.head.content"/>
      <xsl:call-template name="head.content"/>

      <xsl:if test="$home">
        <link rel="home">
          <xsl:attribute name="href">
            <xsl:call-template name="href.target">
              <xsl:with-param name="object" select="$home"/>
            </xsl:call-template>
          </xsl:attribute>
          <xsl:attribute name="title">
            <xsl:apply-templates select="$home"
                                 mode="object.title.markup.textonly"/>
          </xsl:attribute>
        </link>
      </xsl:if>

      <xsl:if test="$up">
        <link rel="up">
          <xsl:attribute name="href">
            <xsl:call-template name="href.target">
              <xsl:with-param name="object" select="$up"/>
            </xsl:call-template>
          </xsl:attribute>
          <xsl:attribute name="title">
            <xsl:apply-templates select="$up" mode="object.title.markup.textonly"/>
          </xsl:attribute>
        </link>
      </xsl:if>

      <xsl:if test="$prev">
        <link rel="prev">
          <xsl:attribute name="href">
            <xsl:call-template name="href.target">
              <xsl:with-param name="object" select="$prev"/>
            </xsl:call-template>
          </xsl:attribute>
          <xsl:attribute name="title">
            <xsl:apply-templates select="$prev" mode="object.title.markup.textonly"/>
          </xsl:attribute>
        </link>
      </xsl:if>

      <xsl:if test="$next">
        <link rel="next">
          <xsl:attribute name="href">
            <xsl:call-template name="href.target">
              <xsl:with-param name="object" select="$next"/>
            </xsl:call-template>
          </xsl:attribute>
          <xsl:attribute name="title">
            <xsl:apply-templates select="$next" mode="object.title.markup.textonly"/>
          </xsl:attribute>
        </link>
      </xsl:if>

      <xsl:if test="$html.extra.head.links != 0">
        <xsl:for-each select="//part
                              |//reference
                              |//preface
                              |//chapter
                              |//article
                              |//refentry
                              |//appendix[not(parent::article)]|appendix
                              |//glossary[not(parent::article)]|glossary
                              |//index[not(parent::article)]|index">
          <link rel="{local-name(.)}">
            <xsl:attribute name="href">
              <xsl:call-template name="href.target">
                <xsl:with-param name="context" select="$this"/>
                <xsl:with-param name="object" select="."/>
              </xsl:call-template>
            </xsl:attribute>
            <xsl:attribute name="title">
              <xsl:apply-templates select="." mode="object.title.markup.textonly"/>
            </xsl:attribute>
          </link>
        </xsl:for-each>

        <xsl:for-each select="section|sect1|refsection|refsect1">
          <link>
            <xsl:attribute name="rel">
              <xsl:choose>
                <xsl:when test="local-name($this) = 'section'
                                or local-name($this) = 'refsection'">
                  <xsl:value-of select="'subsection'"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="'section'"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <xsl:attribute name="href">
              <xsl:call-template name="href.target">
                <xsl:with-param name="context" select="$this"/>
                <xsl:with-param name="object" select="."/>
              </xsl:call-template>
            </xsl:attribute>
            <xsl:attribute name="title">
              <xsl:apply-templates select="." mode="object.title.markup.textonly"/>
            </xsl:attribute>
          </link>
        </xsl:for-each>

        <xsl:for-each select="sect2|sect3|sect4|sect5|refsect2|refsect3">
          <link rel="subsection">
            <xsl:attribute name="href">
              <xsl:call-template name="href.target">
                <xsl:with-param name="context" select="$this"/>
                <xsl:with-param name="object" select="."/>
              </xsl:call-template>
            </xsl:attribute>
            <xsl:attribute name="title">
              <xsl:apply-templates select="." mode="object.title.markup.textonly"/>
            </xsl:attribute>
          </link>
        </xsl:for-each>
      </xsl:if>

      <!-- * if we have a legalnotice and user wants it output as a -->
      <!-- * separate page and $html.head.legalnotice.link.types is -->
      <!-- * non-empty, we generate a link or links for each value in -->
      <!-- * $html.head.legalnotice.link.types -->
      <xsl:if test="not($generate.legalnotice.link = 0)
                    and not($html.head.legalnotice.link.types = '')
                    and //legalnotice">
        <xsl:call-template name="make.legalnotice.head.links"/>
      </xsl:if>

      <xsl:call-template name="user.head.content"/>
    </head>
  </xsl:template>

  <xsl:template name="href.target">
    <xsl:param name="context" select="."/>
    <xsl:param name="object" select="."/>
    <xsl:param name="toc-context" select="."/>
    <xsl:variable name="href.to.uri">
      <xsl:call-template name="href.target.uri">
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="href.from.uri">
      <xsl:choose>
        <xsl:when test="not($toc-context = .)">
          <xsl:call-template name="href.target.uri">
            <xsl:with-param name="object" select="$toc-context"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="href.target.uri">
            <xsl:with-param name="object" select="$context"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:variable name="href.to">
      <xsl:call-template name="trim.common.uri.paths">
        <xsl:with-param name="uriA" select="$href.to.uri"/>
        <xsl:with-param name="uriB" select="$href.from.uri"/>
        <xsl:with-param name="return" select="'A'"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="href.from">
      <xsl:call-template name="trim.common.uri.paths">
        <xsl:with-param name="uriA" select="$href.to.uri"/>
        <xsl:with-param name="uriB" select="$href.from.uri"/>
        <xsl:with-param name="return" select="'B'"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="depth">
      <xsl:call-template name="count.uri.path.depth">
        <xsl:with-param name="filename" select="$href.from"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="href">
      <xsl:call-template name="copy-string">
        <xsl:with-param name="string" select="'../'"/>
        <xsl:with-param name="count" select="$depth"/>
      </xsl:call-template>
      <xsl:value-of select="$href.to"/>
    </xsl:variable>
    <xsl:value-of select="$href"/>
  </xsl:template>
    
  <xsl:template match="footnote" mode="footnote.number">
    <xsl:choose>
      <xsl:when test="string-length(@label) != 0">
        <xsl:value-of select="@label"/>
      </xsl:when>
      <xsl:when test="ancestor::tgroup">
        <xsl:variable name="tfnum">
          <xsl:number level="any" from="table|informaltable" format="1"/>
        </xsl:variable>

        <xsl:choose>
          <xsl:when test="string-length($table.footnote.number.symbols) &gt;= $tfnum">
            <xsl:value-of select="substring($table.footnote.number.symbols, $tfnum, 1)"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:number level="any" from="tgroup"
                        format="{$table.footnote.number.format}"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:otherwise>
        <xsl:variable name="pfoot" select="preceding::footnote[not(@label) and not(ancestor::tgroup)]"/>
        <xsl:variable name="fnum" select="count($pfoot) + 1"/>

        <xsl:choose>
          <xsl:when test="string-length($footnote.number.symbols) &gt;= $fnum">
            <xsl:value-of select="substring($footnote.number.symbols, $fnum, 1)"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:number value="$fnum" format="{$footnote.number.format}"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <!-- ============================================================ -->

<xsl:template name="output.html.stylesheets">
    <xsl:param name="stylesheets" select="''"/>

    <xsl:choose>
        <xsl:when test="contains($stylesheets, ' ')">
            <link rel="stylesheet">
                <xsl:attribute name="href">
                    <xsl:call-template name="href.target.relative">
                        <xsl:with-param name="target" select="substring-before($stylesheets, ' ')"/>
                    </xsl:call-template>
                </xsl:attribute>
                <xsl:if test="$html.stylesheet.type != ''">
                    <xsl:attribute name="type">
                        <xsl:value-of select="$html.stylesheet.type"/>
                    </xsl:attribute>
                </xsl:if>
            </link>
            <xsl:call-template name="output.html.stylesheets">
                <xsl:with-param name="stylesheets" select="substring-after($stylesheets, ' ')"/>
            </xsl:call-template>
        </xsl:when>
        <xsl:when test="$stylesheets != ''">
            <link rel="stylesheet">
                <xsl:attribute name="href">
                    <xsl:call-template name="href.target.relative">
                        <xsl:with-param name="target" select="$stylesheets"/>
                    </xsl:call-template>
                </xsl:attribute>
                <xsl:if test="$html.stylesheet.type != ''">
                    <xsl:attribute name="type">
                        <xsl:value-of select="$html.stylesheet.type"/>
                    </xsl:attribute>
                </xsl:if>
            </link>
        </xsl:when>
    </xsl:choose>
</xsl:template>

</xsl:stylesheet>
