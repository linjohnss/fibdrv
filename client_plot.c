#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"

int main(int argc, char *argv[])
{
    char buf[1];
    int offset = 100; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }
    if (argv[1][0] == '0') {  // running time
        for (int i = 0; i <= offset; i++) {
            lseek(fd, i, SEEK_SET);
            struct timespec t1, t2;
            clock_gettime(CLOCK_MONOTONIC, &t1);
            read(fd, buf, 1);
            clock_gettime(CLOCK_MONOTONIC, &t2);
            long long user_time = (long long) (t2.tv_sec * 1e9 + t2.tv_nsec) -
                                  (t1.tv_sec * 1e9 + t1.tv_nsec);
            long long sz = write(fd, buf, 0);
            printf("%d %lld %lld\n", i, sz, user_time);
        }
    } else if (argv[1][0] == '1') {  // runnung time compare
        for (int i = 0; i <= offset; i++) {
            long long time_interative, time_fast_doubling;
            lseek(fd, i, SEEK_SET);
            time_interative = write(fd, buf, 1);
            time_fast_doubling = write(fd, buf, 2);
            printf("%d %lld %lld\n", i, time_interative, time_fast_doubling);
        }
    }
    close(fd);
    return 0;
}
