#!/usr/bin/python

import sys
import os
import os.path
import deeplearn
import subprocess

if len(sys.argv) < 2:
    print "Error: Specify an image filename"
    sys.exit(1)

image_filename = sys.argv[1];

if not os.path.isfile(image_filename):
    print "Error: File does not exist"
    sys.exit(2)

retval = deeplearn.load("result.nn")
if retval != 0:
    print "Error: Unable to load trained neural network. Error code " + str(retval)
    sys.exit(3)

p = subprocess.Popen(['./catmuzzle', '-f', image_filename],
                     stdout=subprocess.PIPE,
                     stderr=subprocess.PIPE)
out, err = p.communicate()
inputs = [float(i) for i in out.split(",")]

print deeplearn.test(inputs)
#if deeplearn.test(inputs)[0] > 0.5:
#    print "1"
#else:
#    print "0"
