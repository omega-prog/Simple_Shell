#include "shell.h"

/**
 * find_executable_path - find the full path of an executable command
 * @command_name: name of the command
 * Return: a full path if found, or the command_name itself on failure
 */
char *find_executable_path(char *command_name)
{
    char *PATH = _getenv("PATH");
    char *full_path = NULL;
    char *tokenized_path = _strtok(PATH, ":", 0);
    struct stat file_info;

    if (!command_name)
        return NULL;

    if (*command_name == '/' || *command_name == '.')
    {
        full_path = _malloc((_strlen(command_name) + 1) * sizeof(char));
        _strcpy(full_path, command_name);
        return full_path;
    }

    while (tokenized_path)
    {
        full_path = _malloc((_strlen(tokenized_path) + _strlen(command_name) + 1) * sizeof(char));
        _strcpy(full_path, tokenized_path);
        _strcat(full_path, "/");
        _strcat(full_path, command_name);

        if (!stat(full_path, &file_info))
            return full_path;

        free(full_path);
        tokenized_path = _strtok(NULL, ":", 0);
    }

    full_path = _malloc((_strlen(command_name) + 1) * sizeof(char));
    _strcpy(full_path, command_name);
    return full_path;
}
