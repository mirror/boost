# Makefile for regex++ library
#
# for SUN workshop 5.0 C++ compiler
#

LIBNAME=regex++

CPP=CC 
CPP_FLAGS=-O -c

AR=CC -O -xar -o
AR_SO=CC -G -o

INTDIR=.
OUTDIR=.

CPP_PROJ= $(CPP_FLAGS) -I../../../ $(CFGX)

LIB32_OBJS= \
	$(INTDIR)/posix_api.o \
	$(INTDIR)/wide_posix_api.o \
	$(INTDIR)/regex_synch.o \
	$(INTDIR)/regex.o \
	$(INTDIR)/fileiter.o \
	$(INTDIR)/cregex.o \
	$(INTDIR)/c_regex_traits_common.o \
	$(INTDIR)/c_regex_traits.o
	$(INTDIR)/cpp_regex_traits.o
	$(INTDIR)/w32_regex_traits.o

all: $(OUTDIR)/lib$(LIBNAME).a
clean:
	rm -f *.o
	rm -rf SunWS_cache

$(OUTDIR)/lib$(LIBNAME).a :: $(LIB32_OBJS)
	$(AR) lib$(LIBNAME).a 	posix_api.o wide_posix_api.o re_strw.o regex_synch.o	regex.o fileiter.o cregex.o c_regex_traits.o c_regex_traits_common.o cpp_regex_traits.o

$(INTDIR)/posix_api.o : ../src/posix_api.cpp
	$(CPP) $(CPP_PROJ) ../src/posix_api.cpp

$(INTDIR)/wide_posix_api.o : ../src/wide_posix_api.cpp
	$(CPP) $(CPP_PROJ) ../src/wide_posix_api.cpp


$(INTDIR)/re_strw.o : ../src/re_strw.cpp
	$(CPP) $(CPP_PROJ) ../src/re_strw.cpp


$(INTDIR)/regex_synch.o : ../src/regex_synch.cpp
	$(CPP) $(CPP_PROJ) ../src/regex_synch.cpp


$(INTDIR)/regex.o : ../src/regex.cpp
	$(CPP) $(CPP_PROJ) ../src/regex.cpp

$(INTDIR)/fileiter.o : ../src/fileiter.cpp
	$(CPP) $(CPP_PROJ) ../src/fileiter.cpp

$(INTDIR)/cregex.o : ../src/cregex.cpp
	$(CPP) $(CPP_PROJ) ../src/cregex.cpp

$(INTDIR)/c_regex_traits.o : ../src/c_regex_traits.cpp
	$(CPP) $(CPP_PROJ) ../src/c_regex_traits.cpp

$(INTDIR)/c_regex_traits_common.o : ../src/c_regex_traits_common.cpp
	$(CPP) $(CPP_PROJ) ../src/c_regex_traits_common.cpp

$(INTDIR)/cpp_regex_traits.o : ../src/cpp_regex_traits.cpp
	$(CPP) $(CPP_PROJ) ../src/cpp_regex_traits.cpp






