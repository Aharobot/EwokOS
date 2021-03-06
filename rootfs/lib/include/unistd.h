#ifndef UNISTD_H
#define UNISTD_H

#include <types.h>
#include <cmain.h>

int chdir(const char* dir);

char* getcwd(char* buf, uint32_t size);

int fork();

int getpid();

int exec(const char* cmd);

void exit(int code);

void wait(int pid);

void yield();

int getuid();

/*i/o functions*/
int open(const char* fname, int mode);

int write(int fd, const void* buf, uint32_t mode);

int read(int fd, void* buf, uint32_t mode);

void close(int fd);

#endif
