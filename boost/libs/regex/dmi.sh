#! /bin/sh

if test "$#" != "1"; then
exit 1
fi

cd "$1"

if eval make; then
exit 0
fi

exit 1

