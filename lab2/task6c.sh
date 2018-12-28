#!/bin/sh

echo "Enter a number between 5 and 9"
read number


if [ "$number" -lt 5 ] || [ "$number" -gt 9 ]; then
	echo "Enter the number again, 5 to 9 only."
	read number
    
else
	echo

fi

for i in $(seq 1 $number)
do

	for j in $(seq 1 `expr $number - $i`)
	do
		echo -ne " "
	done


	for m in $(seq 1 $i)
	do
	       	echo -ne "$i "
	done

	echo

done



exit 0;
