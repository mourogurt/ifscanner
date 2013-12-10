#ifndef _IF_CONCURENT_QUEUE
#define _IF_CONCURENT_QUEUE
#include "ifstruct.h"
#include <thread>
#include <mutex>
#include <condition_variable>

class ConcurentQueue
{
public:
	ConcurentQueue();
	ConcurentQueue(bool);
	void push (Buffer*);
	Buffer* pop();
	size_t size();
	void set_max_size(size_t);
	void set_priority(bool);
	void clean();
private:
	size_t queue_size;
	size_t max_size;
	bool critical_queue;
	Spisok* first;
	Spisok* back;
	std::mutex lock_mutex;
	std::condition_variable wait_cond;
};

#endif