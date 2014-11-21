#ifndef HTTPLOCKER_H
#define HTTPLOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

/*封装信号量类*/

class sem
{
public:
	sem()
	{
		if (0 != sem_init(&m_sem, 0, 0))
		{
			throw std::exception();
		}
	}

	~sem()
	{
		sem_destroy(&m_sem);
	}

	bool wait()
	{
		return 0 == sem_wait(&m_sem);
	}

	bool post()
	{
		return 0 == sem_post(&m_sem);
	}

private:
	sem_t m_sem;
};

/*封装互斥锁的类*/

class locker
{
public:
	locker()
	{
		if (0 != pthread_mutex_init(&m_mutex, NULL))
		{
			throw std::exception();
		}
	}
	
	~locker()
	{
		pthread_mutex_destroy(&m_mutex);
	}

	bool lock()
	{
		return 0 == pthread_mutex_lock(&m_mutex);
	}
	
	bool unlock()
	{
		return 0 == pthread_mutex_unlock(&m_mutex);
	}

private:
	pthread_mutex_t m_mutex;
};

/*封装条件变量的类*/

class cond
{
public:
	cond()
	{
		if (0 != pthread_mutex_init(&m_mutex, NULL))
		{
			throw std::exception();
		}

		if (0 != pthread_cond_init(&m_cond, NULL))
		{
			pthread_mutex_destroy(&m_mutex);
			throw std::exception();
		}
	}
	
	~cond()
	{
		pthread_mutex_destroy(&m_mutex);
		pthread_cond_destroy(&m_cond);
	}

	bool wait()
	{
		int ret = 0;
		pthread_mutex_lock(&m_mutex);
		ret = pthread_cond_wait(&m_cond, &m_mutex);
		pthread_mutex_unlock(&m_mutex);
		return 0 == ret;
	}

	bool signal()
	{
		return 0 == pthread_cond_signal(&m_cond);
	}

private:
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;
};

#endif

