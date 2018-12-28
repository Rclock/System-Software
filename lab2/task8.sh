#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "The number of parameters is not equal to one. Goodbye. "
	exit 1;
fi




number=$1
sum=0
while [ "$number" -ge 1 ]; do
    remainder=`expr $number % 10`
    sum=`expr $sum + $remainder`
    number=`expr $number / 10`
done

echo "The sum is: $sum"
exit 0; 
