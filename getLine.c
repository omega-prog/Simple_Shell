#include "shell.h"

/**
 * customInputBuffer - buffers chained commands
 * @info: custom_info_t struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t customInputBuffer(custom_info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, customSignalIntHandler);
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = customGetLine(info, buf, &len_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* remove trailing newline */
                r--;
            }
            info->lineCountFlag = 1;
            removeComments(*buf);
            buildCustomHistoryList(info, *buf, info->historyCount++);
            /* if (customStrchr(*buf, ';')) is this a command chain? */
            {
                *len = r;
                info->commandBuffer = buf;
            }
        }
    }
    return (r);
}

/**
 * customGetInput - gets a line minus the newline
 * @info: custom_info_t struct
 *
 * Return: bytes read
 */
ssize_t getCustomInput(custom_info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arguments), *p;

    customPutchar(BUFFER_FLUSH);
    r = customInputBuffer(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len) /* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buf position */
        p = buf + i; /* get pointer for return */

        checkCommandChain(info, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (isCommandChain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info->commandBufferType = COMMAND_NORMAL;
        }

        *buf_p = p; /* pass back pointer to current command position */
        return (customStringLength(p)); /* return length of current command */
    }

    *buf_p = buf; /* else not a chain, pass back buffer from customGetLine() */
    return (r); /* return length of buffer from customGetLine() */
}

/**
 * customReadBuffer - reads a buffer
 * @info: custom_info_t struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t customReadBuffer(custom_info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->readFileDescriptor, buf, READ_BUFFER_SIZE);
    if (r >= 0)
        *i = r;
    return r;
}

/**
 * customGetLine - gets the next line of input from STDIN
 * @info: custom_info_t struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int customGetLine(custom_info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUFFER_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = customReadBuffer(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = customStringCharacter(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = customReallocate(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return p ? free(p), -1 : -1;

    if (s)
        customStringConcatenateN(new_p, buf + i, k - i);
    else
        customStringCopyN(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

/**
 * customSignalIntHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void customSignalIntHandler(__attribute__((unused))int sig_num)
{
    customPuts("\n");
    customPuts("$ ");
    customPutchar(BUFFER_FLUSH);
}
