<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
  <xsl:include href="annotation.xsl"/>
  <xsl:include href="template.xsl"/>
  <xsl:include href="function.xsl"/>
  <xsl:include href="type.xsl"/>
  <xsl:include href="source-highlight.xsl"/>
  <xsl:include href="utility.xsl"/>
  <xsl:include href="lookup.xsl"/>
  <xsl:include href="library.xsl"/>
  <xsl:include href="index.xsl"/>
  <xsl:include href="error.xsl"/>
  <xsl:include href="testing/testsuite.xsl"/>

  <xsl:template name="namespace-synopsis">
    <xsl:param name="indentation" select="0"/>
    <!-- Open namespace-->
    <xsl:call-template name="indent">
      <xsl:with-param name="indentation" select="$indentation"/>
    </xsl:call-template>
    <xsl:call-template name="source-highlight">
      <xsl:with-param name="text" select="concat('namespace ',@name)"/>
    </xsl:call-template>
    <xsl:text> {</xsl:text>
    
    <!-- Emit namespace types -->
    <xsl:apply-templates select="class|class-specialization|
                                 struct|struct-specialization|
                                 union|union-specialization|
                                 typedef|enum" mode="synopsis">
      <xsl:with-param name="indentation" select="$indentation + 2"/>
    </xsl:apply-templates>
    
    <!-- Emit namespace functions -->
    <xsl:apply-templates 
      select="free-function-group|function|overloaded-function" 
      mode="synopsis">
      <xsl:with-param name="indentation" select="$indentation + 2"/>
    </xsl:apply-templates>
    
    <!-- Emit namespaces -->
    <xsl:apply-templates select="namespace" mode="synopsis">
      <xsl:with-param name="indentation" select="$indentation + 2"/>
    </xsl:apply-templates>
    
    <!-- Close namespace -->
    <xsl:text>&#10;</xsl:text>
    <xsl:call-template name="indent">
      <xsl:with-param name="indentation" select="$indentation"/>
    </xsl:call-template>
    <xsl:text>}</xsl:text>
  </xsl:template>

  <!-- Emit namespace synopsis -->
  <xsl:template match="namespace" mode="synopsis">
    <xsl:param name="indentation" select="0"/>

    <xsl:choose>
      <xsl:when test="count(ancestor::namespace)=0">
        <xsl:call-template name="synopsis">
          <xsl:with-param name="text">
            <xsl:call-template name="namespace-synopsis">
              <xsl:with-param name="indentation" select="$indentation"/>
            </xsl:call-template>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>&#10;</xsl:text>
        <xsl:call-template name="namespace-synopsis">
          <xsl:with-param name="indentation" select="$indentation"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- Emit namespace reference -->
  <xsl:template match="namespace" mode="reference">
    <xsl:apply-templates select="class|class-specialization|
                                 struct|struct-specialization|
                                 union|union-specialization|
                                 namespace|typedef|enum|
                                 free-function-group"
      mode="reference">
      <xsl:with-param name="indentation" select="0"/>
    </xsl:apply-templates>
    <xsl:apply-templates select="enum|function|overloaded-function"
      mode="namespace-reference"/>
  </xsl:template>

  <!-- Eat extra documentation when in the synopsis or reference sections -->
  <xsl:template match="para|section" mode="synopsis"/>
  <xsl:template match="para|section" mode="reference"/>
</xsl:stylesheet>
