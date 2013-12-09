#include "ifscanner.h"
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

int out_func_tcp (char* buf,unsigned int num, Buffer *indata, Buffer *outdata)
{
	struct in_addr saddr,daddr;
	struct iphdr *iph = (struct iphdr *)buf;
	struct tcphdr *tcph = (struct tcphdr *) (buf + sizeof(struct iphdr));
	saddr.s_addr=iph->saddr;
	daddr.s_addr=iph->daddr;
	std::cout<<"TCP\nSize: "<<num<<std::endl;
	std::cout<<"From: "<<inet_ntoa(saddr)<<"\tTO: "<<inet_ntoa(daddr)<<std::endl;
	std::cout<<"ID: "<<iph->id<<"\tTTL: "<<(int)iph->ttl<<std::endl;
	std::cout<<"Source Port: "<<ntohs(tcph->th_sport)<<"\tDest Port: "<<ntohs(tcph->th_dport)<<std::endl;
	std::cout<<"Sequence: "<<tcph->th_seq<<"\tAck: "<<tcph->th_ack<<std::endl;
	return 0;
}

int out_func_udp (char* buf,unsigned int num, Buffer *indata, Buffer *outdata)
{
	struct in_addr saddr,daddr;
	struct iphdr *iph = (struct iphdr *)buf;
	struct udphdr *udph = (struct udphdr *) (buf + sizeof(struct iphdr));
	saddr.s_addr=iph->saddr;
	daddr.s_addr=iph->daddr;
	std::cout<<"UDP\nSize: "<<num<<std::endl;
	std::cout<<"From: "<<inet_ntoa(saddr)<<"\tTO: "<<inet_ntoa(daddr)<<std::endl;
	std::cout<<"ID: "<<iph->id<<"\tTTL: "<<(int)iph->ttl<<std::endl;
	std::cout<<"Source port: "<<ntohs(udph->uh_sport)<<"\tDest Port: "<<ntohs(udph->uh_dport)<<std::endl;
	return 0;
}

int main(int argc,char **argv) 
{
	functor fc1,fc2;
	int prot1,prot2;
	fc1.func = out_func_tcp;
	fc2.func = out_func_udp;
	InterfaceScanner ifsc1("eth0",1);
	prot1 = ifsc1.add_protocol(IPPROTO_TCP);
	prot2 = ifsc1.add_protocol(IPPROTO_UDP);
	ifsc1.set_callback(prot1,fc1);
	ifsc1.set_callback(prot2,fc2);
	ifsc1.set_max_buf(prot1,10000);
	ifsc1.set_max_buf(prot2,10000);
	ifsc1.launch_all();
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
	ifsc1.clean_all();
	return 0;
}