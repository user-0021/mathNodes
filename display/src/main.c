#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int freq = nodeSystemAddPipe("Freq",NODE_CONST,NODE_UINT_32,1,&default_freq);
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

	char line[4096];
	strcpy(line,"xAxsis");
	for(i = 0;i < INPUT_COUNT;i++){
		char numString[100];
		sprintf(numString,",yAxsis-%d",i+1);
		strcat(line,numString);
	}
	nodeSystemDebugLog(line);

	while(!nodeSystemLoop()){

		//read xAxsis
		if(nodeSystemRead(xAxsis,&rdata,0) == 1){
			//if xAxsis updated
			sprintf(line,"%lf",(double)rdata);
			for(i = 0;i < INPUT_COUNT;i++){
				char numString[100];
				if(nodeSystemRead(xAxsis,&rdata,0) < 0){
					rdata = 0;
				}
				sprintf(numString,",%lf",(double)rdata);
				strcat(line,numString);
			}
			nodeSystemDebugLog(line);
		}

		//update freq
		int ret = nodeSystemRead(freq,&hz,0);
		if(ret == 1){
			if(hz == 0)
				hz = default_freq;

			req.tv_nsec = 1000 * 1000 * 1000 / hz;
			req.tv_sec = req.tv_nsec/(1000*1000*1000);
			req.tv_nsec = req.tv_nsec % (1000*1000*1000);
		}

		nanosleep(&req,NULL);
	}
}