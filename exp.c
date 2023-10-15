#include "shell.h"

/**
 * expand_special_signs - expand special command signs
 * @str: pointer to the string to be used
 * @exit_status: last exit status
 */
void expand_special_signs(char **str, int exit_status)
{
    char *pid_str = itoa(getpid());
    char *status_str = itoa(exit_status);

    if (**str != '\n')
    {
        find_and_replace(str, "$$", pid_str);
        find_and_replace(str, "$?", status_str);
    }

    free(pid_str);
    free(status_str);
}

/**
 * expand_environment_variables - expand environment variables in a string
 * @str: pointer to the string
 */
void expand_environment_variables(char **str)
{
    int i = 0;
    char *variable, *temp, *replacement;

    while (*(*str + i))
    {
        if (*(*str + i) == '$' && *(*str + i + 1))
        {
            if (*(*str + i + 1) != '$' && *(*str + i + 1) != '?')
            {
                variable = _malloc(2);
                temp = NULL;
                i = 0;
                variable[0] = 'k';
                variable[1] = '\0';

                while (*(*str + i) != ' ' && *(*str + i))
                {
                    variable = _realloc(variable, _strlen(variable) + 2);
                    variable[i] = *(*str + i);
                    variable[i + 1] = '\0';

                    if (!(*str + i + 1))
                        break;

                    i++;
                }

                temp = _malloc(_strlen(variable));
                _strcpy(temp, variable + 1);
                replacement = getenv(temp);

                if (replacement)
                {
                    find_and_replace(str, variable, replacement);
                }
                else
                {
                    find_and_replace(str, variable, "");
                }

                free(variable);
                free(temp);
                variable = (char *)_malloc(2);
                variable[0] = ' ';
                variable[1] = '\0';
                temp = NULL;
                free(variable);
            }
        }
        i++;
    }
}

/**
 * remove_shell_comments - remove comments in a string (text after '#')
 * @str: pointer to the string
 */
void remove_shell_comments(char **str)
{
    char *_str = *str;

    while (*_str)
    {
        if (*_str == '#')
        {
            *_str = '\0';
            break;
        }
        _str++;
    }
}

/**
 * expand_shell_variables - expand shell variables in a string
 * @str: pointer to the string containing variables
 * @child_status: the last exit status of the child process
 * Return: 0 on success and -1 on error
 */
int expand_shell_variables(char **str, int child_status)
{
    expand_special_signs(str, child_status);
    expand_environment_variables(str);
    remove_shell_comments(str);
    return 0;
}

/**
 * expand_aliases - expand aliases inside a string
 * @str: pointer to the string to be manipulated
 * @head: pointer to the first alias node
 */
void expand_aliases(char **str, alias *head)
{
    while (head)
    {
        find_and_replace(str, head->key, head->value);
        head = head->next;
    }
}
