#!/bin/bash
#
# Generate markdown ChangeLog files based on git history.

tmp=$(mktemp)
touch ${tmp}

# Commits prior to this one contain mangled commit history.
# Reformatting these requires some extra handholding
LASTCOMMIT="1502aec05a4152a91fcff56a7bbcc9744e711225"

prev_tag="${LASTCOMMIT}"
echo "# ChangeLog"
for tag in $(git tag -l release_[0-9]* | sort -V); do
	# Prepend tags to the output because we want the ChangeLog in the
	# reverse order, e.g. 2.0.0, 1.0.1 and 1.0.0.
	{
		date=$(git show --date=short --format='tformat:%cd' -s ${tag} | tail -n 1)
		echo -e "\n## ${tag} - ${date}\n"
		git --no-pager log --no-merges --format='format: - %s%n' \
		    ${prev_tag:+${prev_tag}..}${tag} | cat - ${tmp}
	} > ${tmp}.1
	mv ${tmp}.1 ${tmp}
	prev_tag=${tag}
done

# Send the output to stdout.
cat ${tmp}
cat ChangeLog.old.md

rm ${tmp}
