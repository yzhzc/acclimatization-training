#pragma once
#include<mutex>


template<class Lock>
class LockGuard
{
public:
	LockGuard(Lock& lock)
		:_lk(lock)
	{
		_lk.lock();
	}
	~LockGuard()
	{
		_lk.unlock();
	}

	LockGuard(LockGuard<Lock>&) = delete;
	LockGuard<Lock>& operator=(LockGuard<Lock>&) = delete;
private:
	Lock& _lk;
};