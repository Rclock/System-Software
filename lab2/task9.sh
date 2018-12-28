#!/bin/sh
#task9.sh

echo "Please specify a directory to find a file in"
read directoryname


if eval cd "$directoryname"; then
    echo $PWD
	echo "Directory found."
else 
	echo "Directory not found, goodbye."
	exit 1;
fi




echo "Please enter a file to find in this directory."
read fname

if [ -f "$fname" ]; then
	echo "File found."
else
	count=1;
	while [ "$count" -lt 3 ]; do
		echo "Enter the file name again. "
		read fname

		if [ -f "$fname" ]; then
			echo "File found."
			break;
		fi
		let count++;
	done
	if [ ! -f "$fname" ]; then
		echo "File never found goodbye"
		exit 2;
	fi
fi

if [ ! -f "$fname" ]; then
	echo "error. File is not readable"
	exit 3; 

fi

echo "Enter a word to search for in the file"
read searchword 


if grep -q "$searchword" "$fname"; then
	echo "$searchword FOUND"
else 
	echo "$searchword NOT FOUND"
	exit 4;
fi


exit 0;
