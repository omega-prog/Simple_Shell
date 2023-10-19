#include "shell.h"

/**
 * clearCustomInfo - initializes custom_info_t struct
 * @info: struct address
 */
void clearCustomInfo(custom_info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * setCustomInfo - initializes custom_info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setCustomInfo(custom_info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = customStringDuplicate(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * freeCustomInfo - frees custom_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeCustomInfo(custom_info_t *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        customPutChar(BUF_FLUSH);
    }
}
