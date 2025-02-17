// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	
	long int result = (void *)syscall(9, addr, length, prot, flags, fd, offset);

    if (result < 0) {
        errno = -result;
        return -1;
    }

    return (void *) result;
}


void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */

	long int result = syscall(25, old_address, old_size, new_size, flags);

    if (result < 0) {
        errno = -result;
        return -1;
    }

    return (void *)result;
}

int munmap(void *addr, size_t length)
{
	int result = syscall(11, addr, length);

    if (result < 0) {
        // An error occurred. Set errno for error details.
        errno = -result;  // You can choose an appropriate error code here
        return -1;
    }

    return result;
}