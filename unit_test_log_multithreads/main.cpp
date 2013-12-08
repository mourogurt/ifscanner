#include <iostream>
#include <thread>
#include <cstring>
#include "iflog.h"

const int MAX_THREADS = 3000;
const int MAX_WRITE = 1000;

int testmas [MAX_WRITE];

Log testlog;
int thread_complite;

void write_log()
{
	for (int i = 0; i < MAX_WRITE; i++)
		testlog.write_log(std::to_string(i));
	thread_complite++;
}


int main(int argc, char **argv)
{
	testlog.set_max_log(MAX_THREADS*MAX_WRITE+1);
	std::thread masthread[MAX_THREADS];
	for (int i = 0; i <MAX_THREADS; i++)
		masthread[i] = std::thread(write_log);
	while (thread_complite != MAX_THREADS)
	{
	}
	for (int i = 0; i < MAX_THREADS; i++)
		masthread[i].join();
	std::vector<std::string> inlog = testlog.get_log();
	for (size_t i = 0; i < inlog.size(); i++)
		testmas[atoi(inlog[i].c_str())]++;
	for (int i = 0; i <MAX_WRITE; i++)
		if (testmas[i] != MAX_THREADS) std::cout<<"Test failed at: "<<i<<"\tResult: "<<testmas[i]<<std::endl;
	std::cout<<"Finished\n";
	return 0;
}
