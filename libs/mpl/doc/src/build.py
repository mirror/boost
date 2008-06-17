# Copyright (c) Aleksey Gurtovoy 2008
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

import shutil
import os


def build():

   def cleanup():
       if os.path.exists( 'refmanual.gen' ):
           os.unlink( 'refmanual.gen' )

       if os.path.exists( 'build' ):
           shutil.rmtree( 'build' )

   def generate_html():
       os.system( 'python refmanual.py' )
       os.mkdir( 'build' )
       os.system( 'rst2htmlrefdoc.py -g -d -t --no-frames --traceback refmanual.gen build/refmanual.html' )

   os.chdir( 'refmanual' )
   cleanup()
   generate_html()


build()
