// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	/* TODO: Implement ftruncate(). */
	// Check if the file descriptor is valid
    if (fd < 0) {
        errno = EBADF;  // Bad file descriptor
        return -1;
    }
	if (length < 0) {
        errno = EINVAL; // Invalid argument
        return -1;
    }

    // // Check if the file is a directory
    // struct stat st;
    // if (fstat(fd, &st) == -1) {
    //     errno = EBADF; // Error while checking file status
    //     return -1;
    // }

    // if (S_ISDIR(st.st_mode)) {
    //     errno = EISDIR;  // Is a directory
    //     return -1;
    // }

    

	int result=syscall(77, fd, length);
	if (result < 0) {
        // An error occurred. Set errno for error details.
        errno=-result;
        return -1;
    }
    return 0;
}
