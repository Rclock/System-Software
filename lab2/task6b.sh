#!/bin/sh

for i in $(seq 1 5)
do
	for m in $(seq 1 $i)
	do

		echo -ne "*"

	done

	echo 
done

for p in $(seq 1 4)
do
	for n in $(seq $p 4)
	do
		echo -ne "*"
	done
	echo
done 
exit 0;

