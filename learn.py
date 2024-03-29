#!/usr/bin/python

import deeplearn

samplesPerAxis = 128
axes = 3

# Reads a number of data samples from a CSV file
noOfSamples = deeplearn.readCsvFile("data.csv", samplesPerAxis*(axes-1), 3, [1], 0)
print str(noOfSamples) + " samples loaded"

# The error threshold (percent) for each layer of the network.
# After going below the threshold the pre-training will move
# on to the next layer
deeplearn.setErrorThresholds([5.0, 7.0, 7.0, 20.0])

# The learning rate in the range 0.0-1.0
deeplearn.setLearningRate(0.5)

# The percentage of dropouts in the range 0-100
deeplearn.setDropoutsPercent(0.001)

# Title of the training error image
deeplearn.setPlotTitle("Catmuzzle Training")

# The number of time steps after which the training error image is redrawn
deeplearn.setHistoryPlotInterval(50000)

print "Training started"

timeStep = 0
while (deeplearn.training() != 0):
    timeStep = timeStep + 1

print "Training Completed"
print "Test data set performance is " + str(deeplearn.getPerformance()) + "%";

deeplearn.export("result.py")
print "Exported trained network"

deeplearn.save("result.nn")
print "Saved trained network"

deeplearn.free();
print "Done"
