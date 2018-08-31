#!/bin/bash

echo "hello daemon process"
source /etc/profile

ALL="all"
CLEAN="clean"

BIN=bin
LIBS=libs/armeabi-v7a

function mk_dir
{
     if [ ! -d "$1" ];then
         mkdir $1
     fi
}
function rm_dir
{
    if [ ! -d "$1" ];then
    echo "$1 is not a dir"
    else
	rm -rf $1
    fi
}

function all
{
    mk_dir $BIN
    ndk-build 
    cp $LIBS/daemonProc  $BIN
}

function clean
{
    ndk-build clean
 
    rm_dir $BIN    
    rm_dir obj
    rm_dir libs 
}
case "$1"z in
	"$ALL"z)
	all;;
	"$CLEAN"z)
	clean;;

	z)
        all;;
esac
exit 0 
