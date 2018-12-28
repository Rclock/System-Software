#!/bin/sh

for i in $(seq 1 5)
do
	for m in $(seq 1 5)
	do
		echo -ne " "

	done

	for n in $(seq 1 $i)
	do
		echo -ne "$i"
	done
	echo
done
exit 0;
