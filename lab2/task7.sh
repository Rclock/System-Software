#!/bin/sh


number=$1
factorial=1
count=$1

while [ $count -gt 0 ]; do

	factorial=`expr $factorial \* $number`
	number=`expr $number - 1`

	let count--;


done


echo "Factorial is: $factorial "


exit 0;
