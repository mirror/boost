#!/bin/sh

rm html.tar.gz
tar -czf html.tar.gz html

scp html.tar.gz eric_niebler@shell.sf.net:/home/groups/b/bo/boost-sandbox/htdocs/libs/proto/doc
ssh eric_niebler@shell.sf.net 'cd /home/groups/b/bo/boost-sandbox/htdocs/libs/proto/doc; rm -rf html; tar -xzf html.tar.gz'

