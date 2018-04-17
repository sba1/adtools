#! /usr/bin/python
#
# Extract from the comment the text that was marked with a stdout marker:
# The format looks something like this:
#
# ```stdout
# Text to be extracted
# ```
#
from __future__ import print_function

import re
import sys

text = sys.stdin.read()

result = re.findall(r'^(.*)```stdout\n([\s\S]*)```', text, re.MULTILINE)

for r in result:
    prefix = r[0]
    contents = r[1]

    # Extract the proper lines, i.e., without the prefix and without the last line
    lines = [l[len(prefix):] for l in contents.split('\n')[:-1]]
    print('\n'.join(lines))
