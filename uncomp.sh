#!/bin/bash
args=("$@")

for var in ${args[@]}
do
#check if it exist
    if [ -f $var ]; then
#check if the name matches
	if [[ $var = *.gz ]] || [[ $var = *.tar ]] || [[ $var = *.Z ]] || [[ $var = *.zip ]]; then
	    tar -xzvf $var
	else
	    echo $var has no compression extention.
	fi
    else
	echo $var does not exist
	
    fi
done
