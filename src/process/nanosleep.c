#include <unistd.h>
#include <time.h>
#include <errno.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	long int result = (void *)syscall(35, req, rem);
    if (result < 0) {
        errno = -result;
        return -1;
    }

    return (void *) result;

}