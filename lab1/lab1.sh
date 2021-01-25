#!/bin/bash

source=$1
type=${source##*.}
tmp=$(mktemp -d temp_build.XXX)
cd $tmp

echo "Temp folder: $tmp"
echo "$type"
function CloseScript()
{
	echo "$1"
	cd ../
	rm -r $tmp
	exit
}

# Обработка сигналов ошибки и выхода
trap 'CloseScript "Build error... Exit..."' ERR
trap 'CloseScript "Script was closed..."' HUP INT TERM STOP

out=$(grep -o 'Output:.*' ../$1 -s | cut -f2- -d:)
if [ -z "$out" ]
then
	echo "Output name not founded"
	out="output"
fi

case "$type" in
	"cpp")
		g++ -g -Wall -o ../$out ../$1
		;;
	[cC])
		gcc -Wall -pedantic -O2 -o ../$out ../$1 -lpthread
		;;
	"tex")
		cp ../$1 $1
		latex --jobname=$out $1
		cp $out.dvi ../$out.dvi
		;;
	*)
		CloseScript "Bad type"
		exit
		;;
esac
CloseScript "Success"