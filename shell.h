#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdlib.h>
#include <ctype.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>


int convertStringToInt(const char *str);
int customGetline(char **lnptr, size_t *size, int fd);

#define BUFFER_t 1024
