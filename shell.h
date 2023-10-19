#ifndef _CUSTOM_SHELL_H_
#define _CUSTOM_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* for convert_number() */
#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * struct custom_list_string - singly linked list
 * @number: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct custom_list_string
{
int number;
char *string;
struct custom_list_string *next;
} custom_list_t;

/**
 * struct custom_pass_info - contains pseudo-arguments to pass into a function,
 *		allowing uniform prototype for function pointer struct
 * @arguments: a string generated from getline containing arguments
 * @argumentVector: an array of strings generated from arguments
 * @commandPath: a string path for the current command
 * @argumentCount: the argument count
 * @lineCount: the error count
 * @errorNumber: the error code for exit()s
 * @lineCountFlag: if on count this line of input
 * @filename: the program filename
 * @environment: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @custom_environment: custom modified copy of environ from LL env
 * @environmentChanged: on if custom_environment was changed
 * @executionStatus: the return status of the last executed command
 * @commandBuffer: address of pointer to command buffer, on if chaining
 * @commandBufferType: command type ||, &&, ;
 * @readFileDescriptor: the file descriptor from which to read line input
 * @historyCount: the history line number count
 */
typedef struct custom_pass_info
{
char *arguments;
char **argumentVector;
char *commandPath;
int argumentCount;
unsigned int lineCount;
int errorNumber;
int lineCountFlag;
char *filename;
custom_list_t *environment;
custom_list_t *history;
custom_list_t *alias;
char **custom_environment;
int environmentChanged;
int executionStatus;
char **commandBuffer;
/* pointer to command ; chain buffer,for memory management */
int commandBufferType; /* command type ||, &&, ; */
int readFileDescriptor;
int historyCount;
} custom_info_t;

#define CUSTOM_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct custom_builtin - contains a built-in string and related function
 * @commandType: the built-in command flag
 * @function: the function
 */
typedef struct custom_builtin
{
char *commandType;
int (*function)(custom_info_t *);
} custom_builtin_table;

/* custom_shloop.c */
int customShellLoop(custom_info_t *, char **);
int findCustomBuiltIn(custom_info_t *);
void findCommand(custom_info_t *);
void forkCommand(custom_info_t *);

/* custom_parser.c */
int isCustomCommand(custom_info_t *, char *);
char *duplicateChars(char *, int, int);
char *findCustomPath(custom_info_t *, char *, char *);

/* custom_shell_loop.c */
int customShellLoops(char **);

/* custom_errors.c */
void customErrorPuts(char *);
int customErrorPutchar(char);
int customPutFd(char c, int fd);
int customPutsFd(char *str, int fd);

/* custom_string.c */
int customStringLength(char *);
int customStringCompare(char *, char *);
char *customStartsWith(const char *, const char *);
char *customStringConcatenate(char *, char *);

/* custom_string1.c */
char *customStringCopy(char *, char *);
char *customStringDuplicate(const char *);
void customPuts(char *);
int customPutchar(char);

/* custom_exits.c */
char *customStringCopyN(char *, char *, int);
char *customStringConcatenateN(char *, char *, int);
char *customStringCharacter(char *, char);

/* custom_tokenizer.c */
char **customStringToWords(char *, char *);
char **customStringToWords2(char *, char);

/* custom_realloc.c */
char *customMemorySet(char *, char, unsigned int);
void customFree(char **);
void *customReallocate(void *, unsigned int, unsigned int);

/* custom_memory.c */
int customFreeMemory(void **);

/* custom_atoi.c */
int checkIfInteractive(custom_info_t *);
int isDelimiterCharacter(char, char *);
int isAlphabetical(int);
int customAtoi(char *);

/* custom_errors1.c */
int customErrorAtoi(char *);
void printCustomError(custom_info_t *, char *);
int printDecimal(int, int);
char *convertInteger(long int, int, int);
void removeComments(char *);

/* custom_builtin.c */
int customExit(custom_info_t *);
int customChangeDirectory(custom_info_t *);
int customHelp(custom_info_t *);

/* custom_alias.c */
int customHistory(custom_info_t *);
int customAlias(custom_info_t *);

/* custom_getline.c */
ssize_t getCustomInput(custom_info_t *);
int customGetLine(custom_info_t *, char **, size_t *);
void customSignalIntHandler(int);

/* custom_getinfo.c */
void clearCustomInfo(custom_info_t *);
void setCustomInfo(custom_info_t *, char **);
void freeCustomInfo(custom_info_t *, int);

/* custom_environ.c */
char *customGetEnv(custom_info_t *, const char *);
int customEnvironment(custom_info_t *);
int customSetEnv(custom_info_t *);
int customUnsetEnv(custom_info_t *);
int populateEnvironmentList(custom_info_t *);

/* custom_getenv.c */
char **getCustomEnvironment(custom_info_t *);
int customUnsetEnvironment(custom_info_t *, char *);
int customSetEnvironment(custom_info_t *, char *, char *);

/* custom_history.c */
char *getCustomHistoryFile(custom_info_t *info);
int writeCustomHistory(custom_info_t *info);
int readCustomHistory(custom_info_t *info);
int buildCustomHistoryList(custom_info_t *info, char *buffer, int lineCount);
int renumberCustomHistory(custom_info_t *info);

/* custom_lists.c */
custom_list_t *addCustomNode(custom_list_t **, const char *, int);
custom_list_t *addCustomNodeEnd(custom_list_t **, const char *, int);
size_t printCustomListString(const custom_list_t *);
int deleteCustomNodeAtIndex(custom_list_t **, unsigned int);
void freeCustomList(custom_list_t **);

/* custom_lists1.c */
size_t listLength(const custom_list_t *);
char **listToStrings(custom_list_t *);
size_t printCustomList(const custom_list_t *);
custom_list_t *nodeStartsWith(custom_list_t *, char *, char);
ssize_t getCustomNodeIndex(custom_list_t *, custom_list_t *);

/* custom_vars.c */
int isCommandChain(custom_info_t *, char *, size_t *);
void checkCommandChain(custom_info_t *, char *, size_t *, size_t, size_t);
int replaceCustomAlias(custom_info_t *);
int replaceCustomVariables(custom_info_t *);
int replaceCustomString(char **, char *);

#endif
