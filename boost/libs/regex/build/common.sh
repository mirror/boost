#
# locate all the header dependencies:
for file in ../../../boost/regex/*.hpp ; do
	if [ -f $file ]; then
		header="$header $file"
	fi
done

for file in ../../../boost/regex/detail/*.hpp; do
	if [ -f $file ]; then
		header="$header $file"
	fi
done

for file in ../../../boost/regex/detail/*.hxx; do
	if [ -f $file ]; then
		header="$header $file"
	fi
done

#
# locate all the source files:
for file in ../src/*.cpp; do
	if [ -f $file ]; then
		src="$src $file"
	fi
done

