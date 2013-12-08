#include "ifscanner.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

int out_func (char* buf,unsigned int num, Buffer *indata, Buffer *outdata)
{
	struct in_addr saddr,daddr;
	struct iphdr *iph = (struct iphdr *)buf;  //Устанавливаем указатель заколовка ip пакета на начало буффера
	struct tcphdr *tcph = (struct tcphdr *) (buf + sizeof(struct iphdr));
	saddr.s_addr=iph->saddr; //Устанавливаем адресс источника
	daddr.s_addr=iph->daddr; //Устанавливаем адресс получателя
	std::cout<<"Size: "<<num<<std::endl;
	std::cout<<"From: "<<inet_ntoa(saddr)<<"\tTO: "<<inet_ntoa(daddr)<<std::endl;
	std::cout<<"ID: "<<iph->id<<"\tTTL: "<<(int)iph->ttl<<std::endl;
	std::cout<<"Source Port: "<<ntohs(tcph->th_sport)<<"\tDest Port: "<<ntohs(tcph->th_dport)<<std::endl;
	std::cout<<"Sequence: "<<tcph->th_seq<<"\tAck: "<<tcph->th_ack<<std::endl;
	return 0;
}

int main(int argc,char **argv) 
{
	functor fc1;
	int prot1;
	fc1.func = out_func;
	InterfaceScanner ifsc1("eth0",1);
	prot1 = ifsc1.add_protocol(IPPROTO_TCP);
	ifsc1.set_callback(prot1,fc1);
	ifsc1.set_max_buf(prot1,10000);
	ifsc1.launch_protocol(prot1);
	bool ext = 0;
	std::vector<std::string> log;
	log = ifsc1.get_error_log();
	for (size_t i = 0; i < log.size(); i++)
		std::cout<<log.at(i)<<std::endl;
	log = ifsc1.get_log();
	for (size_t i = 0; i < log.size(); i++)
		std::cout<<log.at(i)<<std::endl;
	while (!ext)
	{
		std::cin>>ext;
	}
	ifsc1.remove_protocol(prot1);
	return 0;
}