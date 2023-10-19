#include "shell.h"

/**
 * clearCustomInfo - initializes custom_info_t struct
 * @info: struct address
 */
void clearCustomInfo(custom_info_t *info)
{
    info->arguments = NULL;
    info->argumentVector = NULL;
    info->commandPath = NULL;
    info->argumentCount = 0;
}

/**
 * setCustomInfo - initializes custom_info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setCustomInfo(custom_info_t *info, char **av)
{
    int i = 0;

    info->filename = av[0];
    if (info->arguments)
    {
        info->argumentVector = customStringToWords(info->arguments, " \t");
        if (!info->argumentVector)
        {
            info->argumentVector = malloc(sizeof(char *) * 2);
            if (info->argumentVector)
            {
                info->argumentVector[0] = customStringDuplicate(info->arg);
                info->argumentVector[1] = NULL;
            }
        }
        for (i = 0; info->argumentVector && info->argumentVector[i]; i++)
            ;
        info->argumentCount = i;

        replaceCustomAlias(info);
        replaceCustomVariables(info);
    }
}

/**
 * freeCustomInfo - frees custom_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeCustomInfo(custom_info_t *info, int all)
{
    customFree(info->argumentVector);
    info->argumentVector = NULL;
    info->commandPath = NULL;
    if (all)
    {
        if (!info->commandBuffer)
            customFree(info->arguments);
        if (info->environment)
            freeCustomList(&(info->environment));
        if (info->history)
            freeCustomList(&(info->history));
        if (info->alias)
            freeCustomList(&(info->alias));
        customFree(info->custom_environment);
        info->custom_environment = NULL;
        customFreeMemory((void **)info->commandBuffer);
        if (info->readFileDescriptor > 2)
            close(info->readFileDescriptor);
        customPutchar(BUF_FLUSH);
    }
}
