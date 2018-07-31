#!/usr/bin/python3

import random
import sys

#def random_line(afile):
#    line = next(afile)
#    for num, aline in enumerate(afile):
#      if random.randrange(num + 2): continue
#      line = aline
#    return line

infilename = sys.argv[1]
ofilename = sys.argv[2]


infile = open(infilename, "r")
ofile = open(ofilename, "w")

data = infile.read()

lines = data.splitlines()

i = 0
while i < int(sys.argv[3]):
    #ofile.write(random_line(infile))
    ofile.write(random.choice(lines))
    ofile.write("\n")
    i = i + 1

