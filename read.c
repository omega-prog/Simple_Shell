#include "shell.h"

/**
 * read_user_input - reads input from the command line
 * @input: pointer to input string
 * @input_len: pointer to input length
 * @commands: pointer to array of arguments
 * @file_descriptor: file descriptor
 *
 * Return: length of input
 */
int read_user_input(char **input, size_t *input_len, char ***commands, int file_descriptor)
{
    int length;

    if (isatty(0) && !file_descriptor)
        write(1, "$ ", 2);

    length = _getline(input, input_len, file_descriptor);

    if (length == -1)
    {
        free(*input);
        write(1, "\n", 1);
        exit(0);
    }

    (*input)[length - 1] = '\0';
    parse_arguments(*input, ";", commands, 0);

    return (length - 1);
}
