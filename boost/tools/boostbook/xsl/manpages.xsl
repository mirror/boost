<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <!-- Import the man pages stylesheet -->
  <xsl:import 
    href="http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl"/>

  <xsl:param name="generate.manifest" select="1"/>
  <xsl:param name="manifest">man.manifest</xsl:param>

  <xsl:template match="literallayout">
    <xsl:text>&#10;.nf&#10;</xsl:text>
    <xsl:apply-templates/>
    <xsl:text>&#10;.fi&#10;</xsl:text>
  </xsl:template>

  <xsl:template match="para|simpara|remark" mode="list">
    <xsl:variable name="foo">
      <xsl:apply-templates/>
    </xsl:variable>
    <xsl:choose>
      <xsl:when test="literallayout">
        <xsl:copy-of select="$foo"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="normalize-space($foo)"/>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>&#10;</xsl:text>
    <xsl:if test="following-sibling::para or following-sibling::simpara or
                  following-sibling::remark">
      <!-- Make sure multiple paragraphs within a list item don't -->
      <!-- merge together.                                        -->
      <xsl:text>&#10;</xsl:text>
    </xsl:if>
  </xsl:template>

  <xsl:template match="refentry" mode="manifest">
    <xsl:variable name="section" select="refmeta/manvolnum"/>
    <xsl:variable name="name" select="refnamediv/refname[1]"/>
    <xsl:value-of select="concat(normalize-space ($name), '.', $section)"/>
    <xsl:text>&#10;</xsl:text>
  </xsl:template>

  <xsl:template match="/">
    <xsl:choose>
      <xsl:when test="//refentry">
        <xsl:apply-templates select="//refentry"/>
        <xsl:if test="$generate.manifest=1">
          <xsl:call-template name="write.text.chunk">
            <xsl:with-param name="filename" select="$manifest"/>
            <xsl:with-param name="content">
              <xsl:apply-templates select="//refentry" mode="manifest"/>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:otherwise>
        <xsl:message>No refentry elements!</xsl:message>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
