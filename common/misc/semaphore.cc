#include "semaphore.h"

#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <limits.h>

Semaphore::Semaphore(int count)
   : _count(count)
   , _numWaiting(0)
   , _futx(0)
{
}

Semaphore::~Semaphore()
{
}

void Semaphore::wait()
{
   _lock.acquire();

   while (_count <= 0)
   {
      _numWaiting ++;
      _futx = 0;

      _lock.release();

      syscall(SYS_futex, (void*) &_futx, FUTEX_WAIT, 0, NULL, NULL, 0);

      _lock.acquire();

      _numWaiting --;
   }

   _count --;
   _lock.release();
}

void Semaphore::signal()
{
   _lock.acquire();

   _count ++;
   if (_numWaiting > 0)
   {
      _futx = 1;
      syscall(SYS_futex, (void*) &_futx, FUTEX_WAKE, 1, NULL, NULL, 0);
   }

   _lock.release();
}

void Semaphore::broadcast()
{
   _lock.acquire();

   _count ++;
   if (_numWaiting > 0)
   {
      _futx = 1;
      syscall(SYS_futex, (void*) &_futx, FUTEX_WAKE, INT_MAX, NULL, NULL, 0);
   }

   _lock.release();
}
