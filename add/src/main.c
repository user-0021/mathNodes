#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(){
	int freq = nodeSystemAddPipe("Freq",NODE_CONST,NODE_UINT_32,1);
	int in_1 = nodeSystemAddPipe("IN-1",NODE_IN,NODE_INT_8,1);
	int in_2 = nodeSystemAddPipe("IN-2",NODE_IN,NODE_INT_8,1);
	int out  = nodeSystemAddPipe("OUT",NODE_OUT,NODE_INT_8,1);

	nodeSystemInit();

	nodeSystemBegine();

	nodeSystemDebugLog("SystemBegin");

	int8_t rdata[2] = {};
    int8_t wdata;

	//timer
	uint32_t hz = 60;
	struct timespec req = {};
	req.tv_nsec = 1000 * 1000 * 1000 / hz;
	req.tv_sec = req.tv_nsec/(1000*1000*1000);
	req.tv_nsec = req.tv_nsec % (1000*1000*1000);
	

	while(!nodeSystemLoop()){
		uint8_t wdata = 0;
		int ret = nodeSystemRead(in_1,rdata,0);
		ret += nodeSystemRead(in_2,rdata+1,0);
		if(ret > 0){
			wdata = rdata[0] + rdata[1] + 1;
		    nodeSystemWrite(out,&wdata,0);
		}

		ret = nodeSystemRead(freq,&hz,0);
		if(ret == 1){
			if(hz == 0)
				hz = 60;

			req.tv_nsec = 1000 * 1000 * 1000 / hz;
			req.tv_sec = req.tv_nsec/(1000*1000*1000);
			req.tv_nsec = req.tv_nsec % (1000*1000*1000);
		}

		nanosleep(&req,NULL);
	}
}