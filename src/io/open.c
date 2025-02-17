// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	mode_t mode = 0;
	va_list args;
    if ((flags!=0) & (O_CREAT!=0)) {
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }
	int result;
	result = syscall(2, filename, flags, mode);
	if (result < 0) {
    
        errno = -result;
        return -1;
    }
    return result;
}
