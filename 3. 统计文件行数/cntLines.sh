#!/bin/bash
# description: to count lines in a file

cnt=0

echo "please input file name:"
read file

if [[ -e $file ]]; then
	if [[ -r $file ]]; then
		while read line
			do
				echo $line
				let cnt+=1
			done < $file
		echo "There are $cnt lines."
	else
		echo "unreadable file"
	fi
else
	echo "file not found"
fi
