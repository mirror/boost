<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <!-- Import the FO stylesheet -->
  <xsl:import 
    href="http://docbook.sourceforge.net/release/xsl/current/fo/docbook.xsl"/>

  <xsl:param name="chapter.autolabel" select="0"/>
  <xsl:param name="refentry.generate.name" select="0"/>
  <xsl:param name="refentry.generate.title" select="1"/>
  <xsl:param name="fop.extensions" select="1"/>
  <xsl:param name="make.year.ranges" select="1"/>
  <xsl:param name="ulink.show" select="0"/>
</xsl:stylesheet>
