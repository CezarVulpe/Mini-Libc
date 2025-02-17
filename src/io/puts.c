#include <unistd.h>
#include <string.h>

int puts(const char *str) {
    size_t len = strlen(str);
    ssize_t written = write(1, str, len); // 1 is the file descriptor for standard output

    if (written < 0) {
        // An error occurred
        return -1;
    }

    // Write a newline character
    char newline = '\n';
    ssize_t newline_written = write(1, &newline, 1);

    if (newline_written < 0) {
        // An error occurred
        return -1;
    }

    // Successfully wrote the string and newline character
    return written + newline_written;
}





