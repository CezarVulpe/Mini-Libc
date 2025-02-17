#define time_t unsigned long

struct timespec {
    time_t tv_sec;
    long int tv_nsec;
};

unsigned int sleep(unsigned int seconds);
int nanosleep(const struct timespec *req, struct timespec *rem);
