@echo off

if "%3" == ""  goto usage

c:\home\sx\bin\sx -x lower -x empty %2 >%3.xml
c:\home\msxsl\msxsl.exe %3.xml ..\..\..\..\..\docbook-xsl-1.50.0\html\my\%1 -o %3
del %3.xml
c:\home\tidy\tidy.exe -config tidy_config -m %3
python tidy_attr.py %3
exit

:usage
echo Usage example: 
echo    msxsl_build.bat docbook_msxsl.xsl src\body.sgml index.html
