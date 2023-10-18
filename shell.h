#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdlib.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/**
 * struct cmdnode - a node for one command in a command list
 * @cmd: command string
 * @op: operation between the current command and the next command
 * @estat: exit status (shows if the command has been executed or not)
 * @next: a pointer to the next operand
 */

typedef struct cmdnode
{
    char *cmd;
    char *op;
    int estat;
    struct cmdnode *next;
} cmdnode;

/**
 * struct alias - a node for one alias
 * @key: the alias
 * @value: value of the alias
 * @next: a pointer to the next alias
 */

typedef struct alias
{
    char *key;
    char *value;
    struct alias *next;
} alias;

void moveCommand(cmdnode **, int);
int executeCommand(char **, int, alias **);

char *getFilePath(char *);
void parseArguments(char *, const char *, char ***, int);
int getInput(char **, size_t *, char ***, int);
void trimSpaces(char **, char *);

int *handleBinary(char **, alias **);

void freePointerArray(char **);
int arrayLength(char **);
void *customMalloc(unsigned int);
void *customRealloc(void *, unsigned int);

char **arrayDuplicate(char **);
void printDebug(char **);

int customGetLine(char **, size_t *, int);
int customStringCompareDelim(char *, const char *);
char *customStrtok(char *, const char *, int);
int customStringCompare(char *, const char *);

int findTokenOccurrences(char *, char *);
int findAndReplace(char **, char *, char *);

int customStrlen(const char *);
char *customStrcat(char *, char *);
char *customStrdup(char *);
int customStringCompare(char *, char *);
char *customStrcpy(char *, char *);

int customPutenv(char *);
int customSetenv(const char *, const char *, int);
int customUnsetenv(const char *);
char *customGetenv(const char *);
void printEnvironment(void);

int customChdir(char *);
int runScript(char *);
int executeCommand(char **);

int expandString(char **, int);

int addAlias(alias **, char *, char *);
int printLongAlias(alias *);
int printAlias(alias *, char *);
int handleAlias(char **, alias **);
int freeAlias(alias *);

void expandAlias(char **, alias *);

int removeAlias(alias **, char *);

int addCommandNode(cmdnode **, char *, char *);
cmdnode *buildCommandList(char *);
int printCommandNodes(cmdnode *);
void freeCommandList(cmdnode *);
cmdnode *addCommandNodeAtIndex(cmdnode **, char *, char *, int);

int powerOf(int base, int power);
int numberLength(int num);
char *intToString(int);
int customAtoi(char *);

void printHelp(char *arg);

int printCommandHistory(void);
int writeCommandHistory(char *);

int customWrite(int, char *, int);

void printErrorMessage(char *, int *, char *);

extern char **environ;

#endif
