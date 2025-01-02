#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const uint32_t default_freq = 100;

#ifdef NODE_IN_INT8
	#define NODE_IN_UNIT NODE_INT_8
	typedef int8_t node_in_unit;
#elif  NODE_IN_INT16
	#define NODE_IN_UNIT NODE_INT_16
	typedef int16_t node_in_unit;
#elif  NODE_IN_INT32
	#define NODE_IN_UNIT NODE_INT_32
	typedef int32_t node_in_unit;
#elif  NODE_IN_INT64
	#define NODE_IN_UNIT NODE_INT_64
	typedef int64_t node_in_unit;
#elif NODE_IN_UINT8
	#define NODE_IN_UNIT NODE_UINT_8
	typedef uint8_t node_in_unit;
#elif  NODE_IN_UINT16
	#define uNODE_IN_UNIT NODE_UINT_16
	typedef uint16_t node_in_unit;
#elif  NODE_IN_UINT32
	#define NODE_IN_UNIT NODE_UINT_32
	typedef uint32_t node_in_unit;
#elif  NODE_IN_UINT64
	#define NODE_IN_UNIT NODE_UINT_64
	typedef uint64_t node_in_unit;
#elif  NODE_IN_FLOAT
	#define NODE_IN_UNIT NODE_FLOAT
	typedef float node_in_unit;
#elif  NODE_IN_DOUBLE
	#define NODE_IN_UNIT NODE_DOUBLE
	typedef double node_in_unit;
#endif


int main(){
	//add pipe
	int xAxsis = nodeSystemAddPipe("xAxsis",NODE_IN,NODE_IN_UNIT,1,NULL);
	int* inputPipes = malloc(INPUT_COUNT*sizeof(int));
	int i;
	for(i = 0;i < INPUT_COUNT;i++){
		char numString[100];
		sprintf(numString,"yAxsis-%d",i+1);
		inputPipes[i] = nodeSystemAddPipe(numString,NODE_IN,NODE_IN_UNIT,1,NULL);
	}

	//system wake up
	nodeStstemSetDebugMode(NODE_DEBUG_CSV);
	nodeSystemInit();
	nodeSystemBegine();

	node_in_unit rdata;

	//timer
	uint32_t hz;
	struct timespec req = {};
	

	while(!nodeSystemLoop()){
		sleep(3);
	}
}