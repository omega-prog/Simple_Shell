#include "shell.h"

/**
 * customGetLine - get line of string from file
 * @lnptr: variable to store string
 * @size: number of strings stored
 * @fd: file to read from
 *
 * Return: the length of lnptr or -1 on failure
 */

int customGetLine(char **lnptr, size_t *size, int fd)
{
    char buffer[BUFFER_SIZE + 1];
    int r = BUFFER_SIZE, len = 0, mode = isatty(0);
    char *tmp;

    *lnptr = (char *)customMalloc(4);
    **lnptr = '\0';
    while (r == BUFFER_SIZE)
    {
        if (*lnptr && len > 0)
            if ((*lnptr)[len - 1] == '\n' && mode)
                break;
        r = read(fd, buffer, BUFFER_SIZE);
        if (r < 0 && errno == EINTR)
        {
            **lnptr = '\n',    *(*lnptr + 1) = '\n', len = 2;
            return (len);
        }
        if (r < 0)
            exit(-1);
        if (r == 0 && mode)
            return (-1);
        tmp = customRealloc(*lnptr, len + r + 4);
        *size = len + r + 4, *lnptr = tmp;
        buffer[r] = '\0', customStrcat(*lnptr, buffer), len += r;
        if (!mode)
            findAndReplace(lnptr, "\n", ";");
    }
    if (!mode)
    {
        tmp = customRealloc(*lnptr, customStrlen(*lnptr) + 3);
        *lnptr = tmp;
        (*lnptr)[len] = '\n', (*lnptr)[len + 1] = '\0';
    }
    return (len);
}
