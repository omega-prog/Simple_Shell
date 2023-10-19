#include "shell.h"

/**
 * isCustomCommand - determines if a file is an executable command
 * @info: the custom_info_t struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCustomCommand(custom_info_t *info, char *file_path)
{
    struct stat st;

    (void)info;
    if (!file_path || stat(file_path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicateChars - duplicates characters
 * @source: the source string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicateChars(char *source, int start, int stop)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (source[i] != ':')
            buffer[k++] = source[i];
    buffer[k] = 0;
    return buf;
}

/**
 * findCustomPath - finds this cmd in the PATH string
 * @info: the custom_info_t struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findCustomPath(custom_info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((customStringLength(cmd) > 2) && customStartsWith(cmd, "./"))
    {
        if (isCustomCommand(info, cmd))
            return cmd;
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = duplicateChars(pathstr, curr_pos, i);
            if (!*path)
                customStringConcatenate(path, cmd);
            else
            {
                customStringConcatenate(path, "/");
                customStringConcatenate(path, cmd);
            }
            if (isCustomCommand(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}
