// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	/* TODO: Implement fstat(). */
	long ret = syscall(__NR_fstat, fd, st);

    if (ret < 0) {
        // An error occurred. Set errno for error details.
        errno = -ret;
        return -1;
    }
	
	return 0;
}
