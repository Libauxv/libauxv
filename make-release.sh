#!/bin/bash

ENAME=$0

usage()
{
cat << EOF
Usage: $ENAME OPTION
  -x Clean git repository before preparing release
EOF
}

while getopts "x" opt; do
	case "$opt" in
	x )
		git clean -ffdx
		;;
	? )
		usage
		exit 1
		;;
	esac
done

logfile=release.$(date +%y-%m-%d-%T).log
echo "Logging to ${logfile}"

# TODO: Handle tagging?

if [ ! -e ./configure ]; then
	echo "Configure missing. Did you bootstrap?"
fi

# Ensure these all have a similar and sane timestamp to
# prevent autotools from trying to rebuild portions wrongly
touch configure.ac aclocal.m4 configure Makefile.am Makefile.in

config_opts=""
if ./configure --help | grep -- --enable-maintainer-mode > /dev/null; then
	config_opts+=" --enable-maintainer-mode";
fi

echo "Running configure with options '${config_opts}'"
if ! ./configure $config_opts >> ${logfile} 2>&1; then
	echo "Configuration failed. Aborting"
	exit 1
fi

if [ ! -e Makefile ]; then
	echo "Makefile missing. Aborting"
	exit 1
fi

# TODO - The underlying cause of this extra make should
# be fixed.
#
# Due to the use of recursive makefiles, in test/ the
# target auxv_test_shared.o has no knowledge of how
# to build targets generated in a parallel makefile
# of src/.
#
# The ordering of the subdir's ensures 'make' builds
# in such a way that this issue remains hidden, except
# when running 'make dist' on a clean repo.
#
make >> ${logfile} 2>&1


echo "Running make distcheck"
make distcheck >> ${logfile} 2>&1

# Extract out the name of the tarball from the log.
# There is probably a saner method to do this.

tarballs=$(awk '
/^=+$/ && doprint == 1                 { exit 0 }
doprint == 1                           { print $0 }
$0 ~ /archives ready for distribution/ { doprint = 1 }
' ${logfile})

if [ "x${tarballs}" == "x" ]; then
	echo "Failed to build and verify tarballs"
	exit 1
fi

echo "Found tarballs: ${tarballs}"

# Generate some popular checksums for the tarball
for tarball in ${tarballs}; do
	for sum in sha256 md5; do
		echo "Generating ${tarball}.${sum}"
		${sum}sum ${tarball} > ${tarball}.${sum}
	done
done

# TODO: Support signing these releases

exit 0
