#!/bin/bash

chmod 0777 add/generate_makefile.sh
chmod 0777 sub/generate_makefile.sh
chmod 0777 mul/generate_makefile.sh
chmod 0777 div/generate_makefile.sh
chmod 0777 display/generate_makefile.sh

#unit array
unitArry=("INT8" "INT16" "INT32" "INT64" "UINT8" "UINT16" "UINT32" "UINT64" "FLOAT" "DOUBLE")
#number array
numArry=("1" "2" "3" "4" "5")

##generate add nodes

cd add

for u in ${unitArry[@]}; do
	for i in ${numArry[@]}; do
		./generate_makefile.sh $u $u $i
		make all
	done
done

cd ../

##generate sub nodes

cd sub

for u in ${unitArry[@]}; do
	for i in ${numArry[@]}; do
		./generate_makefile.sh $u $u $i
		make all
	done
done

cd ../

##generate mul nodes

cd mul

for u in ${unitArry[@]}; do
	for i in ${numArry[@]}; do
		./generate_makefile.sh $u $u $i
		make all
	done
done

cd ../

##generate div nodes

cd div

for u in ${unitArry[@]}; do
	./generate_makefile.sh $u $u
	make all
done

cd ../

##generate integral nodes

cd integral

for u in ${unitArry[@]}; do
	./generate_makefile.sh $u $u
	make all
done

cd ../

##generate const nodes

cd const

for u in ${unitArry[@]}; do
	./generate_makefile.sh $u
	make all
done

cd ../

##generate counter nodes

cd counter

for u in ${unitArry[@]}; do
	./generate_makefile.sh $u
	make all
done

cd ../

##generate display nodes

cd display

for u in ${unitArry[@]}; do
	for i in ${numArry[@]}; do
		./generate_makefile.sh $u $i
		make all
	done
done

cd ../