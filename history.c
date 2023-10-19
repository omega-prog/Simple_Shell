#include "shell.h"

/**
 * getCustomHistoryFile - gets the history file
 * @info: custom_info_t struct
 *
 * Return: allocated string containing history file
 */
char *getCustomHistoryFile(custom_info_t *info)
{
	char *buf, *dir;

	dir = customGetEnv(info, "HOME=");
	if (!dir)
	return (NULL);
	buf = (char *)malloc(sizeof(char) * (customStringLength(dir)
				+ customStringLength(HISTORY_FILE) + 2));
	if (!buf)
	return (NULL);
	buf[0] = 0;
	customStringCopy(buf, dir);
	customStringConcatenate(buf, "/");
	customStringConcatenate(buf, HISTORY_FILE);
	return (buf);
}

/**
 * writeCustomHistory - creates a file, or appends to an existing file
 * @info: custom_info_t struct
 *
 * Return: 1 on success, else -1
 */
int writeCustomHistory(custom_info_t *info)
{
	ssize_t fd;
	char *filename = getCustomHistoryFile(info);
	custom_list_t *node = NULL;

	if (!filename)
	return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
	return (-1);
	for (node = info->history; node; node = node->next)
	{
	customPutsFd(node->string, fd);
	customPutFd('\n', fd);
	}
	customPutFd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readCustomHistory - reads history from file
 * @info: custom_info_t struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readCustomHistory(custom_info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getCustomHistoryFile(info);

	if (!filename)
	return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
	return (0);
	if (!fstat(fd, &st))
	fsize = st.st_size;
	if (fsize < 2)
	return (0);
	buf = (char *)malloc(sizeof(char) * (fsize + 1));
	if (!buf)
	return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
	return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
	if (buf[i] == '\n')
	{
	buf[i] = 0;
	buildCustomHistoryList(info, buf + last, linecount++);
	last = i + 1;
	}
	if (last != i)
	buildCustomHistoryList(info, buf + last, linecount++);
	free(buf);
	info->historyCount = linecount;
	while (info->historyCount-- >= HISTORY_MAX)
	    deleteCustomNodeAtIndex(&(info->history), 0);
	renumberCustomHistory(info);
	return (info->historyCount);
}

/**
 * buildCustomHistoryList - adds an entry to a history linked list
 * @info: custom_info_t struct
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildCustomHistoryList(custom_info_t *info, char *buffer, int lineCount)
{
	custom_list_t *node = NULL;

	if (info->history)
	node = info->history;
	addCustomNodeEnd(&node, buffer, lineCount);

	if (!info->history)
	info->history = node;
	return (0);
}

/**
 * renumberCustomHistory - renumbers the history linked list after changes
 * @info: custom_info_t struct
 *
 * Return: the new histcount
 */
int renumberCustomHistory(custom_info_t *info)
{
	custom_list_t *node = info->history;
	int i = 0;

	while (node)
	{
	node->number = i++;
	node = node->next;
	}
	return (info->historyCount = i);
}
