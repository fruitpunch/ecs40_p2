#!/bin/bash
args=("$@")

#check the number of arguements entered to be 3 or else print error
if [ $# -ne 3 ]; then
    echo usage: cpdir.sh source_directory1 source_directory2 dest_directory
    exit 1
fi

#to make sure that the two source directory exist or print error
if [ ! -e "${args[0]}" ] || [ ! -e "${args[1]}" ]; then
    if [ ! -e "${args[0]}" ]; then
	echo ${args[0]} does not exist
    fi
    if [ ! -e "${args[1]}" ]; then
	echo ${args[1]} does not exist
    fi
    exit 1
fi

#if destination directory does not exist, make the directory
if [ ! -e "${args[2]}" ]; then
    mkdir ${args[2]}
fi

#copy all file in source_directory1 to dest_directory
for fileOne in ${args[0]}/*
do
    if [ ! -d "$fileOne" ]; then
	cp $fileOne ${args[2]}
    fi
done

#copy file in source_directory2 to dest_directory
for fileTwo in ${args[1]}/*
do
    a=1
#scan through source_directory1 to compare name and time
    for fileOneAgain in ${args[0]}/*
    do
       if [ ! -d "$fileTwo" ]; then
#if file name from source2 is same as source1 AND source2 is OLDER than source1, variable a will set to 0
	   if [[ ${fileTwo#${args[1]}} = ${fileOneAgain#${args[0]}} ]] && [ ! $fileTwo -nt $fileOneAgain ]; then
		#echo same and older detected
		a=0
	   fi
       fi
     done
#if variable a=1, all condition matches and file will be copied to dest_directory or else skipped.
     if [[ a -eq 1 ]]; then
	cp $fileTwo ${args[2]}
	#echo $fileTwo copied
     fi
done

#ls ${args[2]}