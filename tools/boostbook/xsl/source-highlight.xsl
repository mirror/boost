<?xml version="1.0" encoding="utf-8"?>
<!--
   Copyright (c) 2002 Douglas Gregor <doug.gregor -at- gmail.com>
  
   Distributed under the Boost Software License, Version 1.0.
   (See accompanying file LICENSE_1_0.txt or copy at
   http://www.boost.org/LICENSE_1_0.txt)
  -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
  <xsl:param name="boost.syntax.highlight">1</xsl:param>

  <xsl:template name="source-highlight">
    <xsl:param name="text" select="."/>
    <xsl:choose>
      <xsl:when test="$boost.syntax.highlight='1'">
        <xsl:call-template name="highlight-text">
          <xsl:with-param name="text" select="$text"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$text"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:variable name="id-chars" select="'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_'"/>
  <xsl:variable name="keywords"
    select="' asm auto bool break case catch char class const const_cast continue default delete do double dynamic_cast else enum explicit export extern false float for friend goto if inline int long mutable namespace new operator private protected public register reinterpret_cast return short signed sizeof static static_cast struct switch template this throw true try typedef typeid typename union unsigned using virtual void volatile wchar_t while '"/>
    

  <xsl:template name="highlight-identifier">
    <xsl:param name="identifier"/>
    <xsl:choose>
      <xsl:when test="contains($keywords, concat(' ', $identifier, ' '))">
        <xsl:call-template name="highlight-keyword">
          <xsl:with-param name="keyword" select="$identifier"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$identifier"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:template name="highlight-text-impl-ident">
    <xsl:param name="text"/>
    <xsl:param name="pos"/>
    <xsl:choose>
      <xsl:when test="string-length($text) + 1 = $pos">
        <xsl:call-template name="highlight-identifier">
          <xsl:with-param name="identifier" select="substring($text, 1, $pos - 1)"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="contains($id-chars, substring($text, $pos, 1))">
        <xsl:call-template name ="highlight-text-impl-ident">
          <xsl:with-param name="text" select="$text"/>
          <xsl:with-param name="pos" select="$pos + 1"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="highlight-identifier">
          <xsl:with-param name="identifier" select="substring($text, 1, $pos - 1)"/>
        </xsl:call-template>
        <xsl:call-template name ="highlight-text-impl-root">
          <xsl:with-param name="text" select="substring($text, $pos)"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:template name="highlight-text-impl-root">
    <xsl:param name="text"/>
    <xsl:choose>
      <xsl:when test="string-length($text) = 0"/>
      <xsl:when test="contains($id-chars, substring($text, 1, 1))">
        <xsl:call-template name="highlight-text-impl-ident">
          <xsl:with-param name="text" select="$text"/>
          <xsl:with-param name="pos" select="2"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="substring($text, 1, 1)"/>
        <xsl:call-template name="highlight-text-impl-root">
          <xsl:with-param name="text" select="substring($text, 2)"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- Perform C++ keyword highlighting on the given text -->
  <xsl:template name="highlight-text">
    <xsl:param name="text" select="."/>
    <xsl:call-template name="highlight-text-impl-root">
      <xsl:with-param name="text" select="$text"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="*" mode="highlight">
    <xsl:element name="{name(.)}">
      <xsl:for-each select="./@*">
        <xsl:choose>
          <xsl:when test="local-name(.)='last-revision'">
            <xsl:attribute
              name="rev:last-revision"
              namespace="http://www.cs.rpi.edu/~gregod/boost/tools/doc/revision"
>
              <xsl:value-of select="."/>
            </xsl:attribute>
          </xsl:when>
          <xsl:otherwise>
            <xsl:attribute name="{name(.)}">
              <xsl:value-of select="."/>
            </xsl:attribute>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>
      <xsl:apply-templates mode="highlight"/>
    </xsl:element>
  </xsl:template>

  <xsl:template match="text()" mode="highlight">
    <xsl:call-template name="source-highlight">
      <xsl:with-param name="text" select="."/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="classname|methodname|functionname|libraryname|enumname|
                       conceptname|macroname|globalname" mode="highlight">
    <xsl:apply-templates select="." mode="annotation"/>
  </xsl:template>
</xsl:stylesheet>
