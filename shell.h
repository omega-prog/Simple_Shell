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
char *numberToString(int n);
char *concatenateStrings(char *dest, char *src);
int alternateStringComparison(char *fstring, const char *sub);
int customStringComparison(char *fstring, const char *sub);
int compareStrings(char *s1, char *s2);
char *copyString(char *dest, const char *src);
char *duplicateString(char *str);
int getStringLength(const char *str);
char *tokenizeString(char *str, const char *delimiter, int whichf);
int writeToDescriptor(int fd, char *inp, int len);
int printAliasByKey(alias *head, char *key);
int handleAliases(char **arg, alias **aliashead);
int addNewAlias(alias **head, char *key, char *value);
int change_current_directory(char *path);
