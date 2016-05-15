#include "semaphore.h"


semaphore::semaphore(int value = 1) :count{ value }, wakeups{ 0 }
{
}


semaphore::~semaphore()
{
}
