#!/bin/sh

#~ Copyright Rene Rivera 2006.
#~ Distributed under the Boost Software License, Version 1.0.
#~ (See accompanying file LICENSE_1_0.txt or copy at
#~ http://www.boost.org/LICENSE_1_0.txt)

set -e

#~ Configuration options.
mail_from="Rene Rivera <grafikrobot@gmail.com>"
mail_to="Boost <boost@lists.boost.org>"
cvs_branch="$1"
cvs_user=":ext:${USER}"
cvs_co="cvs -q -z9 -d${cvs_user}@boost.cvs.sourceforge.net:/cvsroot/boost co -P -r ${cvs_branch}"
cvs_dir="${HOME}/devroots"

#~ Build bjam.
cd ${cvs_dir}
${cvs_co} -d boost_jam_src boost/tools/jam/src
cd boost_jam_src
LOCATE_TARGET=bin sh ./build.sh

#~ Build inspect.
cd ${cvs_dir}
${cvs_co} -d boost_${cvs_branch} boost
cd boost_${cvs_branch}/tools/inspect/build
${cvs_dir}/boost_jam_src/bin/bjam --v2

#~ Run the inspection.
cd ${cvs_dir}
cd boost_${cvs_branch}
./dist/bin/inspect -text -license -copyright -crlf -link -long_name -tab -minmax > inspect-out.txt

#~ Send email with results.
mail_date=`date --iso-8601 --utc`
/usr/sbin/sendmail "${mail_to}" <<EMAIL
From: ${mail_from}
To: ${mail_to}
Reply-To: ${mail_to}
Subject: Boost inspection notification (${mail_date}/${cvs_branch})

`cat inspect-out.txt`
EMAIL
