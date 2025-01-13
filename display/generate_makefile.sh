#!/bin/bash

#check argment count
if [[ $# < 2 ]]; then
	echo "too few argment"
	echo "format is <input unit> <output unit> <input count>"
	exit 1
elif [[ $# > 2 ]]; then
	echo "too many argment"
	echo "format is <input unit> <output unit> <input count>"
	exit 1
fi

#unit array
unitArry=("INT8" "INT16" "INT32" "INT64" "UINT8" "UINT16" "UINT32" "UINT64" "FLOAT" "DOUBLE")

## First Argment
isMatching=false
#check first argment(input unit)
for u in ${unitArry[@]}; do
  if [[ $1 == $u ]]; then 
	isMatching=true
  fi
done

#judgement
if [[ $isMatching == false ]]; then
	echo "first argment is invalid value."
	echo "first argment is input unit arrow words are"

	for u in ${unitArry[@]}; do
		echo $u
	done
	exit 1
fi


## Second Argment
isMatching=false
#check third argment(input count)
if [[ "$2" =~ ^[0-9]+$ ]]; then
  isMatching=true
fi

#judgement
if [[ $isMatching == false ]]; then
	echo "third argment is invalid value."
	echo "third argment is input counts allow only number."
	exit 1
fi

##generate
#check dir
if [ -d ./obj ]; then
	:
else
	mkdir obj
fi

echo -e \
"#build executable file\n"\
"build:out\n"\
"\n"\
"#make objs\n"\
"obj/main.o: src/main.c\n"\
"	gcc -o obj/main.o src/main.c -I include -I ../nodeSystem -c -D NODE_IN_$1 -D INPUT_COUNT=$2 \n"\
"\n"\
"obj/nodeSystem.o: ../nodeSystem/nodeSystem.c\n"\
"	gcc -o obj/nodeSystem.o ../nodeSystem/nodeSystem.c -I include -I ../nodeSystem -c\n"\
"\n"\
"out: obj/main.o obj/nodeSystem.o\n"\
"	gcc -o output-csv_${2}-input-${1} obj/main.o obj/nodeSystem.o\n"\
"\n"\
"all: clean out\n"\
"\n"\
"clean:\n"\
"	\$(RM) output-csv_${2}-input-${1} obj/main.o obj/nodeSystem.o\n" > Makefile
