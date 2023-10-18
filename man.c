#include "man.h"

/**
 * display_help - Display help information for shell commands
 * @argument: Command or topic to get help for
 *
 * Return: None
 */
void display_help(char *argument)
{
    int fd = 1;

    _write(-1, NULL, 0);

    if (!argument)
        _write(1, ghelp, _strlen(ghelp));
    else if (!_strcmp(argument, "help"))
        _write(1, help_h, _strlen(help_h));
    else if (!_strcmp(argument, "set"))
        _write(1, set_h, _strlen(set_h));
    else if (!_strcmp(argument, "unset"))
        _write(1, unset_h, _strlen(unset_h));
    else if (!_strcmp(argument, "history"))
        _write(1, history_h, _strlen(history_h));
    else if (!_strcmp(argument, "env"))
        _write(1, env_h, _strlen(env_h));
    else if (!_strcmp(argument, "cd"))
        _write(1, cd_h, _strlen(cd_h));
    else if (!_strcmp(argument, "alias"))
        _write(1, alias_h, _strlen(alias_h));
    else if (!_strcmp(argument, "exit"))
        _write(1, exit_h, _strlen(exit_h));
    else if (!_strcmp(argument, "setenv"))
        _write(1, set_h, _strlen(set_h));
    else if (!_strcmp(argument, "unsetenv"))
        _write(1, unset_h, _strlen(unset_h));
    else
    {
        _write(2, "No help found for ", 18), fd = 2;
        _write(2, argument, _strlen(argument));
        _write(2, "\n", 1);
    }
    _write(fd, NULL, 0);
}
