#!/bin/bash

##fenerate add nodes

chmod 0777 add/generate_makefile.sh

#unit array
unitArry=("INT8" "INT16" "INT32" "INT64" "UINT8" "UINT16" "UINT32" "UINT64" "FLOAT" "DOUBLE")
#number array
numArry=("1" "2" "3" "4" "5")

cd add

for u in ${unitArry[@]}; do
	for i in ${numArry[@]}; do
		./generate_makefile.sh $u $u $i
		make
	done
done

cd ../