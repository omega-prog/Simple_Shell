#include "shell.h"

/**
 * save_command_history - save a command to the history file
 * @command: command to be stored in the history list
 * Return: 0 on success and 1 on failure
 */
int save_command_history(char *command)
{
    char *filename, *home_directory = _getenv("HOME");
    char *temp = NULL;
    ssize_t bytes_written;
    int len = _strlen(command);

    filename = _malloc(_strlen(home_directory) + _strlen("/.shell.history") + 4);
    _strcpy(filename, home_directory);
    _strcat(filename, "/.shell.history");

    int fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0640);
    free(filename);

    if (fd < 0)
        return 1;

    if (len)
    {
        temp = _malloc(len + 4);
        _strcpy(temp, command);
        _strcat(temp, "\n");
        bytes_written = write(fd, temp, len + 1);

        if (bytes_written < 0)
        {
            close(fd);
            free(temp);
            return 1;
        }

        free(temp);
    }

    close(fd);
    return 0;
}

/**
 * display_command_history - display the command history
 * Return: 0 on success and 1 on failure
 */
int display_command_history(void)
{
    char *filename, *home_directory = _getenv("HOME");
    char *history_line = _malloc(4);
    int fd, bytes_read = 1;
    int counter = 0;
    char *index_str = NULL;

    filename = _malloc(_strlen(home_directory) + _strlen("/.shell.history") + 4);
    _strcpy(filename, home_directory);
    _strcat(filename, "/.shell.history");

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return 1;

    while (bytes_read > 0)
    {
        counter++;
        bytes_read = read(fd, history_line, 1);

        if (bytes_read > 0)
        {
            _write(-1, NULL, 0);
            _write(1, "   ", 3);
            index_str = itoa(counter);
            _write(1, index_str, _strlen(index_str));
            _write(1, "  ", 2);
            _write(1, NULL, 0);
            free(index_str);
        }

        _write(-1, NULL, 0);

        while (bytes_read > 0 && *history_line != '\n')
        {
            _write(1, history_line, _strlen(history_line));
            bytes_read = read(fd, history_line, 1);
        }

        if (bytes_read > 0 && *history_line == '\n')
            _write(1, "\n", 1);

        _write(1, NULL, 0);
    }

    free(filename);
    free(history_line);
    close(fd);
    return 1;
}

