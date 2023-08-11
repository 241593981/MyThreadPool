#pragma once
#include <queue>
#include <pthread.h>

using callback = void(*)(void* arg);

template <typename T>
struct Task
{
	Task<T>()
	{
		function = nullptr;
		arg = nullptr;
	}

	Task<T>(callback f, void* arg)
	{
		this->arg = (T*)arg;
		this->function = f;
	}

	callback function;
	T* arg;
};

template <typename T>
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();
	
	void addTask(Task<T> task);
	void addTask(callback f, void* arg);
	Task<T> takeTask();
	inline size_t taskNumber()
	{
		return m_taskQ.size();
	}


private:
	pthread_mutex_t m_mutex;
	std::queue<Task<T>> m_taskQ;
};

