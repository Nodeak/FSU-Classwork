# Kaedon Hamm
# COP 3353
# Assignment 6
# Due: 11/17/2017
#! /bin/bash

if [ ! -d "$1" ]
then
   echo "$1: No such directory"
   exit 0
fi

echo -n "Number of directories: "
nonhid=$(find $1 -maxdepth 1 -type d -print | wc -l)
hid=$(find $1 -maxdepth 1 -name ".*" -type d -print | wc -l)
echo `expr $nonhid - $hid - 1`

echo -n "Number of files: "
nonhid=$(find $1 -maxdepth 1 -type f -print | wc -l)
hid=$(find $1 -maxdepth 1 -name ".*" -type f -print | wc -l)
echo `expr $nonhid - $hid`

echo -n "Number of readable items: "
ls -l $1 | cut -c 1-4 | grep "r" | wc -l

echo -n "Number of writable items: "
ls -l $1 | cut -c 1-4 | grep "w" | wc -l

echo -n "Number of executable items: "
ls -l $1 | cut -c 1-4 | grep "x" | wc -l


exit 0
