#include <iostream>
#include <cstring>
#include "concurent_queue.h"

const int MAX_INPUT = 100000;
const int MAX_OUT = 3000000;

int testmas [MAX_OUT];

int main(int argc, char **argv)
{
    ConcurentQueue testqueue(1);
	testqueue.set_max_size(MAX_OUT);
	Buffer* buf;
	for (int i = 0; i < MAX_INPUT; i++)
	{
		buf = new Buffer;
		buf->buff = new char [sizeof(i)];
		buf->buffsize = sizeof(i);
		memcpy(buf->buff,&i,sizeof(i));
		testqueue.push(buf);
	}
	for (int i = 0; i < MAX_OUT; i++)
	{
		buf = testqueue.pop();
		testmas[i] = buf->buffsize;
		delete [] buf->buff;
		delete buf;
	}
	for (int i = MAX_INPUT; i < MAX_OUT; i++)
		if (testmas[i] != 1) std::cout<<"Test failed at: "<<i<<"\tResult: "<<testmas[i]<<std::endl;
	std::cout<<"Finished\n";
	return 0;
}