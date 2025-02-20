#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

#ifdef NODE_OUT_INT8
	#define NODE_OUT_UNIT NODE_UNIT_INT8
	typedef int8_t node_out_unit;
#elif  NODE_OUT_INT16
	#define NODE_OUT_UNIT NODE_UNIT_INT16
	typedef int16_t node_out_unit;
#elif  NODE_OUT_INT32
	#define NODE_OUT_UNIT NODE_UNIT_INT32
	typedef int32_t node_out_unit;
#elif  NODE_OUT_INT64
	#define NODE_OUT_UNIT NODE_UNIT_INT64
	typedef int64_t node_out_unit;
#elif NODE_OUT_UINT8
	#define NODE_OUT_UNIT NODE_UNIT_UINT8
	typedef uint8_t node_out_unit;
#elif  NODE_OUT_UINT16
	#define NODE_OUT_UNIT NODE_UNIT_UINT16
	typedef uint16_t node_out_unit;
#elif  NODE_OUT_UINT32
	#define NODE_OUT_UNIT NODE_UNIT_UINT32
	typedef uint32_t node_out_unit;
#elif  NODE_OUT_UINT64
	#define NODE_OUT_UNIT NODE_UNIT_UINT64
	typedef uint64_t node_out_unit;
#elif  NODE_OUT_FLOAT
	#define NODE_OUT_UNIT NODE_UNIT_FLOAT
	typedef float node_out_unit;
#elif  NODE_OUT_DOUBLE
	#define NODE_OUT_UNIT NODE_UNIT_DOUBLE
	typedef double node_out_unit;
#endif


int main(){
	//add pipe
	int out  = nodeSystemAddPipe("OUT" ,NODE_PIPE_OUT  ,NODE_OUT_UNIT,1,NULL);
	int* inputPipes = malloc(INPUT_COUNT*sizeof(int));
	int i;
	for(i = 0;i < INPUT_COUNT;i++){
		char numString[100];
		sprintf(numString,"%d",i+1);
		inputPipes[i] = nodeSystemAddPipe(numString,NODE_PIPE_IN   ,NODE_IN_UNIT,1,NULL);
	}

	//system wake up
	nodeSystemInit();
	nodeSystemBegine();
	nodeSystemDebugLog("SystemBegin");

	node_in_unit rdata;
    node_out_unit wdata;
	
	nodeSystemWait();
	while(!nodeSystemLoop()){
		//read input
		int ret = 0;
		wdata = 0;
		for(i = 0;i < INPUT_COUNT;i++){
			ret |= nodeSystemRead(inputPipes[i],&rdata);
			wdata += rdata;		
		}
		
		//write add result
		if(ret > 0){
		    nodeSystemWrite(out,&wdata);
		}

		nodeSystemWait();
	}
}