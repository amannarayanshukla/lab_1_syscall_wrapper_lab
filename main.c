#include <stdio.h>
#define O_RDONLY 0
#define O_CREAT 64


// extern means that the function is defined somewhere else
// long return type in x86_64 since the return value is place in RAX register
// which is 64 bit
extern long my_write(int fd, const void *buf, long count);
extern long my_read(int fd, void *buf, long count);
// flags can have the following values: O_RDONLY = 0, O_WRONLY=1, O_RDWR=2, O_CREAT=64
// mode is the permission mode of the file it can be 0 or 0777 or 0644 etc.
// 4 points = Read (r): Look at the file.
// 2 points = Write (w): Edit or delete the file.
// 1 point = Execute (x): Run the file as a program (or enter a folder).
//
extern long my_open(const char *pathname, int flags, int mode);
extern long my_close(int fd);
extern void my_exit(int status);

int main(void) {
    //we are creating a buffer to read from
    // this is created on the stack
    char buffer[100];

    // open a file for reading
    long fd = my_open("test.txt", O_RDONLY, 0);

    if (fd < 0) {
        my_write(1, "Error opening file\n", 18);
        my_exit(1);
    }

    while (1) {
        long bytes_read = my_read(fd, buffer, 100);
        if (bytes_read == 0) {
            break;
        }

        my_write(1, buffer, bytes_read);
    }
    my_close(fd);


    // when file descriptor is 1, it is the standard output
    // count is the number of bytes to write
    // buf is the buffer to write from
    my_write(1, "Write something\n", 16);




    // read from standard input
    // returns the number of bytes read into buffer, afer that it stops reading i.e. after 100 bytes or EOF
    // if there is an error, it returns -1
    long bytes_received = my_read(0, buffer, 100);

    my_write(1, "You wrote: \n", 12);
    my_write(1, buffer, bytes_received);

    // the number is the exit code, message from dying program to the OS.
    // 0 means success 1-255 means error
    my_exit(0);

    // this is never reached, however it is required by the C standard,
    // it is just to avoid compiler warnings
    // it can be removed though if we do extern void my_exit(int status) __attribute__((noreturn));
    return 0;
}