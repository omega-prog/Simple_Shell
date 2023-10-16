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
int custom_putenv(char *es);
int custom_setenv(cch *name, cch *value, __attribute__((unused))int overwrite);
int custom_unsetenv(const char *name);
void custom_printenv(void);
char *custom_getenv(const char *name);
void custom_print_error(char *prog, int *cmdr, char *msg);
char *find_executable_path(char *command_name);
int display_command_history(void);
int save_command_history(char *command);
int read_user_input(char **input, size_t *input_len, char ***commands, int file_descriptor);
void free_string_array(char **array);
void remove_extra_spaces(char **str, char *original);
void *allocate_memory(unsigned int size);
void *reallocate_memory(void *ptr, unsigned int size);
int add_command_node(command_node **head, char *cmd, char *op);
command_node *build_command_list(char *cmds);
int print_command_nodes(command_node *head);
void free_command_list(command_node *head);
command_node *add_command_node_at_index(command_node **head, char *cmd, char *operator, int pos);

