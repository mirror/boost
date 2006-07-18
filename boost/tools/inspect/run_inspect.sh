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
opt=""
opt="${opt} -crlf"
opt="${opt} -link"
opt="${opt} -long_name"
opt="${opt} -tab"
opt="${opt} -minmax"
./dist/bin/inspect -text ${opt} > inspect-X.out
opt=""
opt="${opt} -license"
opt="${opt} -copyright"
./dist/bin/inspect -text ${opt} > inspect-LC.out

#~ Send email(s) with results.
mail_date=`date --iso-8601 --utc`
/usr/sbin/sendmail "${mail_to}" <<EMAIL
From: ${mail_from}
To: ${mail_to}
Reply-To: ${mail_to}
References: <44BD6089.3010709@gmail.com>
In-Reply-To: <44BD6089.3010709@gmail.com>
Subject: Boost inspection notification (${mail_date}/${cvs_branch}) *X*

`cat inspect-X.out`
EMAIL
/usr/sbin/sendmail "${mail_to}" <<EMAIL
From: ${mail_from}
To: ${mail_to}
Reply-To: ${mail_to}
References: <44BD6089.3010709@gmail.com>
In-Reply-To: <44BD6089.3010709@gmail.com>
Subject: Boost inspection notification (${mail_date}/${cvs_branch}) *LC*

`cat inspect-LC.out`
EMAIL
