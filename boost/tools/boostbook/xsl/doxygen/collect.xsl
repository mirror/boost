<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" version="1.0" indent="yes" standalone="yes" />
  
  <xsl:template match="/">
    <doxygen version="{doxygen/@version}">
      <!-- Load all doxgen generated xml files -->
      <xsl:for-each select="doxygen/compound">
        <xsl:copy-of select="document( concat(
                             @refid, '.xml' ) )/doxygen/*" />
      </xsl:for-each>
    </doxygen>
  </xsl:template>
</xsl:stylesheet>
