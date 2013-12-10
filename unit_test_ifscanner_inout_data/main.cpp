#include "ifscanner.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
const int MAX_SIZE = 2048;
const char TEST_VALUE[5] = "test";

Buffer testmas[MAX_SIZE];
int kolrazin;
int kolrazout;
int kolraz;


int testfoo (Buffer* pack, Buffer* indata, Buffer* outdata)
{
	testmas[kolraz].buff = new char [pack->buffsize];
	memcpy (testmas[kolraz].buff,pack->buff,pack->buffsize);
	testmas[kolraz].buffsize = pack->buffsize;
	bool ext = 0;
	for (int i = 0; i < indata->buffsize; i++)
		if (indata->buff[i] != TEST_VALUE[i]) { ext = 1; break; }
	if (ext == 0) kolrazin++;
		else std::cout<<"Test input failed at: "<<kolraz<<"\tResult: "<<indata->buff<<std::endl;
	kolraz++;
	outdata ->buff = new char[pack->buffsize];
	outdata->buffsize = pack->buffsize;
	memcpy (outdata->buff,pack->buff,pack->buffsize);
	
	return 0;
}

int main(int argc, char **argv)
{
	Buffer indata;
	char* str = new char[5];
	str[0] = 't';
	str[1] = 'e';
	str[2] = 's';
	str[3] = 't';
	str[4] = '\0';
	indata.buff = str;
	indata.buffsize = 5;
	InterfaceScanner testscan("eth0",1);
	int prot1 = testscan.add_protocol(IPPROTO_TCP);
	testscan.set_input_data(prot1,indata);
	testscan.set_max_buf(prot1,10000);
	testscan.set_callback(prot1,testfoo);
	testscan.launch_protocol(prot1);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	testscan.stop_protocol(prot1);
	std::vector<Buffer*> bufsout;
	testscan.get_out_data(prot1,bufsout);
	for (size_t i = 0; i < bufsout.size(); i++)
	{
		bool ext = 0;
		for (size_t j = 0; j < bufsout.at(i)->buffsize; j++)
			if (testmas[i].buff[j]!=bufsout.at(i)->buff[j]) { ext = 1; break; }
		if ((ext == 0) && (testmas[i].buffsize==bufsout.at(i)->buffsize))
			kolrazout++;
		else std::cout<<"Test output failed at: "<<i<<"\tResult: "<<bufsout.at(i)->buff<<std::endl;
		delete [] bufsout.at(i)->buff;
		delete [] testmas[i].buff;
		delete bufsout.at(i);
	}
	testscan.clean_all();
	delete [] str;
	std::cout<<"Finished\n";
    if ((kolraz!=kolrazin) || (kolraz!=kolrazout)) return 1; else return 0;
}
