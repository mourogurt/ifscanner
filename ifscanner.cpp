#include "ifscanner.h"

void producer_func(Protocol* pack)
{
	size_t numbytes;
	char buf[IP_MAXPACKET];
	Buffer* tmpbuf;
	while (!pack->exit_thread)
	{
		numbytes=recvfrom(pack->sock, buf, IP_MAXPACKET, 0, NULL, NULL);
		tmpbuf = new Buffer;
		tmpbuf->buff = new char[numbytes];
		memcpy(tmpbuf->buff,buf,numbytes);
		tmpbuf->buffsize = numbytes;
		pack->bufs.push(tmpbuf);
	}
	pack->notelog->write_log(std::string("complete: producer_func()"));
}

void consumer_func (Protocol* pack)
{
	Buffer* bufobj;
	Buffer *outpack;
	int err;
	while (!pack->exit_thread)
	{
		bufobj=pack->bufs.pop();
		outpack = nullptr;
		err = pack->proc.func(bufobj->buff,bufobj->buffsize,pack->indata,outpack);
		if (err!=0)
			pack->errlog->write_log((std::string("error: proc.func() ")+std::to_string(err)));
		if (outpack!=nullptr)
			pack->outdata.push(outpack);
		delete [] bufobj->buff;
		delete bufobj;
	}
	pack->notelog->write_log(std::string("complete: consumer_func()"));
}


InterfaceScanner::InterfaceScanner(std::string ifname,bool promisc = 0)
{
	memcpy(ifopts.ifr_name, ifname.c_str(), ifname.length());
	prom_mode = promisc;
	set_max_log(5);
	notelog.write_log(std::string("complete: InterfaceScanner()"));
}

int InterfaceScanner::add_protocol(int typeprotin)
{
	Protocol* tmppack = new Protocol;
	tmppack->type_prot = typeprotin;
	tmppack->sock = socket(PF_INET, SOCK_RAW,typeprotin);
	if (tmppack->sock == -1)
	{
		errlog.write_log((std::string("error: socket() ")+std::to_string(tmppack->sock)));
		return -1;
	}
	tmppack->head_on = 1;
	if (setsockopt(tmppack->sock, IPPROTO_IP, IP_HDRINCL, &tmppack->head_on, sizeof(tmppack->head_on)) == -1) {
		errlog.write_log((std::string("error: setsockopt()")+std::to_string(IP_HDRINCL)));
		return -1;
	}
	ioctl(tmppack->sock, SIOCGIFFLAGS, &ifopts);
	if (prom_mode == 1)
	{
		ifopts.ifr_flags |= IFF_PROMISC;
		ioctl(tmppack->sock, SIOCSIFFLAGS, &ifopts);
	}
	tmppack->notelog = &notelog;
	tmppack->errlog = &errlog;
	tmppack->indata = nullptr;
	tmppack->bufs.set_max_size(50);
	tmppack->exit_thread = 1;
	tmppack->outdata.set_max_size(0);
	prtcls.push_back(tmppack);
	notelog.write_log(std::string("complete: add_protocol()"));
	return prtcls.size() -1;
}

int InterfaceScanner::remove_protocol(size_t num)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: remove_protocol()")+std::to_string(num)));
		return -1;
	}
	stop_protocol(num);
	prtcls.at(num)->bufs.clean();
	Protocol* dltprtcl = prtcls.at(num);
	prtcls.erase(prtcls.begin() + num);
	delete dltprtcl;
	notelog.write_log(std::string("complete: remove_protocol()"));
	return 0;
}

int InterfaceScanner::set_callback(size_t num,functor infunc)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: set_callback()")+std::to_string(num)));
		return -1;
	}
	prtcls.at(num)->proc = infunc;
	notelog.write_log(std::string("complete: set_callback()"));
	return 0;
}

int InterfaceScanner::set_max_buf(size_t num,size_t maxelem)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: set_max_buf()")+std::to_string(num)));
		return -1;
	}
	prtcls.at(num)->bufs.set_max_size(maxelem);
	notelog.write_log(std::string("complete: set_max_buf()"));
	return 0;
}

void InterfaceScanner::set_max_log(size_t maxelem)
{
	notelog.set_max_log(maxelem);
}

void InterfaceScanner::set_max_err_log(size_t maxelem)
{
	errlog.set_max_log(maxelem);
}

int InterfaceScanner::set_input_data(size_t num,Buffer* indata)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: set_input_data()")+std::to_string(num)));
		return -1;
	}
	prtcls.at(num)->indata = indata;
	notelog.write_log(std::string("complete: set_input_data()"));
	return 0;
}

int InterfaceScanner::launch_protocol(size_t num)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: launch_protocol()")+std::to_string(num)));
		return -1;
	}
	prtcls.at(num)->exit_thread = 0;
	#ifdef USE_BOOST_THREAD
	prtcls.at(num)->producer = boost::thread(producer_func,prtcls.at(num));
	prtcls.at(num)->consumer = boost::thread(consumer_func,prtcls.at(num));
	#else
	prtcls.at(num)->producer = std::thread(producer_func,prtcls.at(num));
	prtcls.at(num)->consumer = std::thread(consumer_func,prtcls.at(num));
	#endif
	notelog.write_log(std::string("complete: launch_protocol()"));
	return 0;
}

void InterfaceScanner::launch_all()
{
	for (size_t i = 0; i < prtcls.size(); i++)
		launch_protocol(i);
	notelog.write_log(std::string("complete: launch_all()"));
}

int InterfaceScanner::stop_protocol(size_t num)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: stop_protocol()")+std::to_string(num)));
		return -1;
	}
	if (prtcls.at(num)->exit_thread == 0)
	{
		prtcls.at(num)->exit_thread = 1;
		if (prtcls.at(num)->producer.joinable())
			prtcls.at(num)->producer.join();
		if (prtcls.at(num)->consumer.joinable())
			prtcls.at(num)->consumer.join();
	}
	notelog.write_log(std::string("complete: stop_protocol()"));
	return 0;
}

void InterfaceScanner::stop_all()
{
	for (size_t i = 0; i < prtcls.size(); i++)
		stop_protocol(i);
	notelog.write_log(std::string("complete: stop_all()"));
}

std::vector<std::string> InterfaceScanner::get_log()
{
	return notelog.get_log();
}

std::vector<std::string> InterfaceScanner::get_error_log()
{
	return errlog.get_log();
}

int InterfaceScanner::get_out_data(size_t num,std::vector<Buffer*> &outdata)
{
	if (num >= prtcls.size())
	{
		errlog.write_log((std::string("error: get_out_data()")+std::to_string(num)));
		return -1;
	}
	Buffer* buf;
	while (prtcls.at(num)->outdata.size() > 0)
	{
		buf = prtcls.at(num)->outdata.pop();
		outdata.push_back(buf);
	}
	prtcls.at(num)->outdata.clean();
	notelog.write_log(std::string("complete: set_input_data()"));
	return 0;
}

InterfaceScanner::~InterfaceScanner()
{
	for (int i = prtcls.size() -1; i >= 0; i--)
	{
		stop_protocol(i);
		prtcls.at(i)->bufs.clean();
		delete [] prtcls.at(i);
		prtcls.pop_back();
	}
}