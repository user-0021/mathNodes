#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NODE_IN_INT8
	#define NODE_IN_UNIT NODE_UNIT_INT8
	typedef int8_t node_in_unit;
#elif  NODE_IN_INT16
	#define NODE_IN_UNIT NODE_UNIT_INT16
	typedef int16_t node_in_unit;
#elif  NODE_IN_INT32
	#define NODE_IN_UNIT NODE_UNIT_INT32
	typedef int32_t node_in_unit;
#elif  NODE_IN_INT64
	#define NODE_IN_UNIT NODE_UNIT_INT64
	typedef int64_t node_in_unit;
#elif NODE_IN_UINT8
	#define NODE_IN_UNIT NODE_UNIT_UINT8
	typedef uint8_t node_in_unit;
#elif  NODE_IN_UINT16
	#define NODE_IN_UNIT NODE_UNIT_UINT16
	typedef uint16_t node_in_unit;
#elif  NODE_IN_UINT32
	#define NODE_IN_UNIT NODE_UNIT_UINT32
	typedef uint32_t node_in_unit;
#elif  NODE_IN_UINT64
	#define NODE_IN_UNIT NODE_UNIT_UINT64
	typedef uint64_t node_in_unit;
#elif  NODE_IN_FLOAT
	#define NODE_IN_UNIT NODE_UNIT_FLOAT
	typedef float node_in_unit;
#elif  NODE_IN_DOUBLE
	#define NODE_IN_UNIT NODE_UNIT_DOUBLE
	typedef double node_in_unit;
#endif


int main(){
	//add pipe
	int xAxsis = nodeSystemAddPipe("xAxsis",NODE_PIPE_IN,NODE_IN_UNIT,1,NULL);
	int* inputPipes = malloc(INPUT_COUNT*sizeof(int));
	int i;
	for(i = 0;i < INPUT_COUNT;i++){
		char numString[100];
		sprintf(numString,"yAxsis-%d",i+1);
		inputPipes[i] = nodeSystemAddPipe(numString,NODE_PIPE_IN,NODE_IN_UNIT,1,NULL);
	}

	//system wake up
	nodeStstemSetDebugMode(NODE_DEBUG_CSV);
	nodeSystemInit();
	nodeSystemBegine();

	node_in_unit rdata;

	char line[4096];
	strcpy(line,"xAxsis");
	for(i = 0;i < INPUT_COUNT;i++){
		char numString[100];
		sprintf(numString,",yAxsis-%d",i+1);
		strcat(line,numString);
	}
	nodeSystemDebugLog(line);


	nodeSystemWait();
	while(!nodeSystemLoop()){

		//read xAxsis
		if(nodeSystemRead(xAxsis,&rdata) < 0){
			rdata = 0;
		}
		sprintf(line,"%lf",(double)rdata);

		//read yAxsis
		for(i = 0;i < INPUT_COUNT;i++){
			char numString[100];
			if(nodeSystemRead(inputPipes[i],&rdata) < 0){
				rdata = 0;
			}
			sprintf(numString,",%lf",(double)rdata);
			strcat(line,numString);
		}
		nodeSystemDebugLog(line);

		nodeSystemWait();
	}
}