#include "concurent_queue.h"
#include <iostream>
#include <string>
#include <cstring>

const int MAX_SIZE = 3000000;

int testmas [MAX_SIZE];

int main(int argc, char **argv)
{
	ConcurentQueue testqueue(1);
	testqueue.set_max_size(0);
	Buffer* buf;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		buf = new Buffer;
		buf->buff = new char [sizeof(i)];
		buf->buffsize = sizeof(i);
		memcpy(buf->buff,&i,buf->buffsize);
		testqueue.push(buf);
	}
	int *ind;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		buf = testqueue.pop();
		ind = (int*)buf->buff;
		testmas[*ind]++;
		delete [] buf->buff;
		delete buf;
	}
	for (int i = 0; i < MAX_SIZE; i++)
		if (testmas[i] != 1) std::cout<<"Test failed at: "<<i<<"\tResult: "<<testmas[i]<<std::endl;
	std::cout<<"Finished\n";
	return 0;
}