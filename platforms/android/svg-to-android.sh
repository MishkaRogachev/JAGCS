#!/bin/bash

if [[ -z "$1" ]];
then
	echo "No SVG file specified. Exiting."
	exit -1
fi

ispng=$(file $1)
echo $ispng | grep -q SVG

if [[ $? -ne 0 ]];
then
	echo "Invalid SVG file. Exiting."
	exit -2
fi

W=(48 72 96 144 192)
DPINAME=("mdpi" "hdpi" "xhdpi" "xxhdpi" "xxxhdpi")

if [[ -z "$2" ]]; 
then
        BASE="ic_launcher"
else
        BASE="$2"
fi


for ((ii=0;ii<5;ii++));
do
	echo "Processing $1 for ${DPINAME[$ii]}@${W[$ii]} px"
	suffix=${DPINAME[$ii]}
	resroot=`basename $1`
	dirname=res/mipmap-${DPINAME[$ii]}
	mkdir -p "$dirname"
	fname="$dirname"/"$BASE".png
	inkscape -z -f=$1 --export-png="$fname" \
		-h=${W[$ii]}
done
