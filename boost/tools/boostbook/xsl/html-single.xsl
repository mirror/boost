<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:rev="http://www.cs.rpi.edu/~gregod/boost/tools/doc/revision"
                version="1.0">

  <!-- Import the HTML stylesheet -->
  <xsl:import 
    href="http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl"/>

  <xsl:param name="chapter.autolabel" select="0"/>
  <xsl:param name="refentry.generate.name" select="0"/>
  <xsl:param name="refentry.generate.title" select="1"/>
  <xsl:param name="make.year.ranges" select="1"/>

  <xsl:template match="variablelist">
    <p><xsl:apply-templates mode="boost.variablelist"/></p>
  </xsl:template>

  <xsl:template match="varlistentry" mode="boost.variablelist">
    <xsl:if test="position() &gt; 1">
      <br/>
    </xsl:if>
    <b><xsl:apply-templates select="term"/></b>:
    <xsl:apply-templates select="listitem/*|listitem/text()"/>
  </xsl:template>

</xsl:stylesheet>
