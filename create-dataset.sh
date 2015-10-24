#!/bin/bash

DATASET=data.csv

if [ ! -f catmuzzle ]; then
	make
fi

if [ -f $DATASET ]; then
	rm $DATASET
fi

for f in img/positive/*.png
do
	echo "Positive $f"
	./catmuzzle -f $f --positive >> $DATASET
done

for f in img/negative/*.png
do
	echo "Negative $f"
	./catmuzzle -f $f --negative >> $DATASET
done

exit 0
