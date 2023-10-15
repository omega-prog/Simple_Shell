#include "shell.h"
#define l(x) _strlen((x))
#define cch const char

/**
 * custom_putenv - write to environment variables
 * @es: environment variable value argument pair
 * Return: 0 on success and -1 on failure
 */
int custom_putenv(char *es)
{
	char **custom_environ = environ, **new_custom_environ, **custom_environ_ptr;
	int len = 0;

	while (*custom_environ)
	len++, custom_environ++;

	new_custom_environ = _malloc(sizeof(char *) * (len + 4));
	custom_environ_ptr = new_custom_environ;
	custom_environ = environ;
	while (len)
	{
	*_new_custom_environ = _malloc(sizeof(char) * _strlen(*custom_environ) + 4);
	_strcpy(*_new_custom_environ, *_custom_environ);
	_new_custom_environ++, _custom_environ++, len--;
	}
	*_new_custom_environ = _malloc(sizeof(char) * _strlen(es) + 4);
	_strcpy(*_new_custom_environ, es);
	free(es);
	_new_custom_environ++;
	*_new_custom_environ = NULL;
	free_pp(environ);
	environ = new_custom_environ;
	return (0);
}

/**
 * custom_setenv - set environment variables
 * @name: variable name
 * @value: value
 * @overwrite: overwrite status
 * Return: 0 on success and -1 on failure
 */
int custom_setenv(cch *name, cch *value, __attribute__((unused))int overwrite)
{
	char *es, **ep, *var;
	int i = 0;

	if (name == NULL || name[0] == '\0' || value == NULL)
	return (-1);

	if (environ)
	{
	ep = _arrdup(environ);
	while (ep[i])
	{
		var = _strtok(ep[i], "=", 0);
		if (!_strcmp(var, (char *)name))
		{
		free(environ[i]);
		environ[i] = _malloc(_strlen(name) + _strlen(value) + 4);
		_strcpy(environ[i], (char *)name);
		_strcat(environ[i], "=");
		_strcat(environ[i], (char *)value);
		free_pp(ep);
		return (0);
		}
		i++;
	}
	free_pp(ep);
	}
	es = _malloc(_strlen(name) + _strlen(value) + 2);
	if (es == NULL)
	return (-1);
	_strcpy(es, (char *)name), _strcat(es, "="), _strcat(es, (char *)value);
	return ((custom_putenv(es) != 0) ? -1 : 0);
	free(es);
}

/**
 * custom_unsetenv - delete environment variables
 * @name: name of variable
 * Return: 0 on success and -1 on failure
 */
int custom_unsetenv(const char *name)
{
	char **ep, **sp, *var, *value;

	if (name == NULL || name[0] == '\0')
	return (-1);
	ep = _arrdup(environ);
	free_pp(environ);
	environ = _malloc(sizeof(char *));

	for (sp = ep; *sp != NULL;)
	{
	var = _strtok(*sp, "=", 0);
	if (_strcmp(var, (char *)name))
	{
		value = _strtok(NULL, "=", 0);
		custom_setenv(var, value, 1);
	}
		sp++;
	}
	free_pp(ep);
	return (0);
}

/**
 * custom_printenv - print environment variables
 */
void custom_printenv(void)
{
	char **custom_env = environ;

	if (!custom_env)
	return;
	_write(-1, NULL, 0);
	while (*custom_env)
	{
	write(1, *custom_env, _strlen(*custom_env));
	write(1, "\n", 1);
	custom_env++;
	}
	write(1, NULL, 0);
}

/**
 * custom_getenv - get environment variables
 * @name: name of variable
 * Return: pointer to environment variables
 */
char *custom_getenv(const char *name)
{
	int len, i;
	const char *np;
	char **p, *cp;

	if (name == NULL || environ == NULL)
	return (NULL);
	for (np = name; *np && *np != '='; ++np);
	len = np - name;
	for (p = environ; (cp = *p) != NULL; ++p)
	{
	for (np = name, i = len; i && *cp; i--)
		if (*cp++ != *np++)
		break;
	if (i == 0 && *cp++ == '=')
		return (cp);
	}
	return (NULL);
}
