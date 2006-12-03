REM Copyright 2004-2006 Andreas Huber Doenni
REM Distributed under the Boost Software License, Version 1.0. (See accompany-
REM ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

bjam "-sTOOLS=mingw vc-7_1" "-sMINGW_ROOT_DIRECTORY=C:\ProgramFiles\MinGW3.2.0" "-sINTEL_PATH=C:\Program Files\Intel\Compiler\C++\9.0\IA32" "-sINTEL_BASE_MSVC_TOOLSET=vc-7_1" %1 %2 %3 %4 >log.txt 2>&1