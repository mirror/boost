. profile
TOOLS=
export BOOST_ROOT=c:\\BoostMainCVS
echo $BOOST_ROOT
export SPIRIT_ROOT=c:/spirit161
echo $SPIRIT_ROOT

TOOLS=gcc
makepath
runtest gcc

TOOLS=borland_5.51
makepath
whence bcc32
runtest borland-5.5.1
TOOLS=borland_5.60
makepath
whence bcc32
runtest borland-5.6.4

TOOLS=VC7.1
makepath
runtest VC7.1

TOOLS=msvc6
makepath
runtest msvc
runtest msvc-stlport
