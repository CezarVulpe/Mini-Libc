// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	/* TODO: Implement lseek(). */
	// Check for valid file descriptor
    if (fd < 0) {
        errno = EBADF;
        return -1;
    }

    // Check for valid 'whence' values
    if (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END) {
        errno = EINVAL;
        return -1;
    }

    // Check for valid offset
    if ((whence == SEEK_SET && offset < 0) || offset < -1) {
        errno = EINVAL;
        return -1;
    }

	off_t result = syscall(8, fd, offset, whence);

    if (result == -1) {
        // An error occurred. Set errno for error details.
		if(result == -EBADF) errno = EBADF;
		else if( result == -EINVAL) errno = EINVAL;
		else if( result == -ESPIPE)  errno = ESPIPE;
		else errno = EINVAL;
    }

    return result;
}
