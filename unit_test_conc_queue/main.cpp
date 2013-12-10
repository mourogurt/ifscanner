#include "concurent_queue.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <cstring>

const int MAX_THREADS = 3000;
const int MAX_WRITES = 1000;

ConcurentQueue testqueue;

std::atomic<int> testmas[MAX_WRITES];

std::atomic<int> push_thread;
std::atomic<int> pop_thread;

void push_queue ()
{
	Buffer* buf;
	for (int i = 0; i < MAX_WRITES; i++)
	{
		buf = new Buffer;
		buf->buff = new char [sizeof(i)];
		buf->buffsize = sizeof(i);
		memcpy(buf->buff,&i,buf->buffsize);
		testqueue.push(buf);
	}
	push_thread++;
}

void pop_queue ()
{
	Buffer* buf;
	int *ind;
	for (int i = 0; i < MAX_WRITES; i++)
	{
		buf = testqueue.pop();
		ind = (int*)buf->buff;
		testmas[*ind]++;
		delete [] buf->buff;
		delete buf;
	}
	pop_thread++;
}

int main(int argc, char **argv)
{
	std::thread maspushthread[MAX_THREADS];
	std::thread maspopthread[MAX_THREADS];
	for (int i = 0; i < MAX_THREADS; i++)
	{
		maspushthread[i] = std::thread(push_queue);
		maspopthread[i] = std::thread(pop_queue);
	}
	while ((push_thread!=MAX_THREADS) && (pop_thread!=MAX_THREADS))
	{
	}
	for (int i = 0; i < MAX_THREADS; i++)
	{
		maspushthread[i].join();
		maspopthread[i].join();
	}
	for (int i = 0; i < MAX_WRITES; i++)
		if (testmas[i] != MAX_THREADS) std::cout<<"Test failed at: "<<i<<"\tResult: "<<testmas[i]<<std::endl;
	testqueue.clean();
	std::cout<<"Finished\n";
	return 0;
}