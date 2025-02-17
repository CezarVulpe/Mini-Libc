// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	/* TODO: Implement stat(). */
	long ret = syscall(4, path, buf);

    if (ret < 0) {
        // An error occurred. Set errno for error details.
        errno = -ret;
        return -1;
    }
	return 0;
}
