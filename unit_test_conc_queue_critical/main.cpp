#include <iostream>
#include <cstring>
#include "concurent_queue.h"

const int MAX_INPUT = 3000000;
const int MAX_OUT = 100000;

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
		memcpy(buf->buff,&i,buf->buffsize);
		testqueue.push(buf);
	}
	int *ind;
	for (int i = 0; i < MAX_OUT; i++)
	{
		buf = testqueue.pop();
		ind = (int*) buf->buff;
		testmas[i] = *ind;
		delete [] buf->buff;
		delete buf;
	}
	for (int i = 0; i < MAX_OUT; i++)
		if (testmas[i] != i + (MAX_INPUT-MAX_OUT)) std::cout<<"Test failed at: "<<i<<"\tResult: "<<testmas[i]<<std::endl;
	testqueue.clean();
	std::cout<<"Finished\n";
	return 0;
}
