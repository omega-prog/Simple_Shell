#include "shell.h"

/**
 * tokenize_and_parse - tokenize and parse input into arguments
 * @input: input string
 * @delimiter: delimiter
 * @parsed_args: parsed arguments vector
 * @mode: parsing mode (0 for character delimiter, 1 for string delimiter)
 *
 * Return: none
 */
void tokenize_and_parse(char *input, const char *delimiter,
		char ***parsed_args, int mode)
{
	char *tokenized = NULL, **temp_args, *trimmed_arg;
	int arg_index = 0, i;

	*parsed_args = NULL;
	tokenized = tokenizeString(input, delimiter, mode);

	while (tokenized != NULL)
	{
	temp_args = allocate_memory((get_string_array_length(*parsed_args) + 2) * sizeof(char *));

	if (!*parsed_args)
		*parsed_args = temp_args;
	else
	{
		i = 0;
	while ((*parsed_args)[i])
	{
		temp_args[i] = duplicateString((*parsed_args)[i]);
		i++;
	}
	free_string_array(*parsed_args);
	*parsed_args = temp_args;
	}
	(*parsed_args)[arg_index] = NULL;
	trimmed_arg = tokenized;

	if ((tokenized[0] == '"' && tokenized[getStringLength(tokenized) - 1] == '"') ||
		(tokenized[0] == '\'' && tokenized[getStringLength(tokenized) - 1] == '\''))
	{
		trimmed_arg = duplicateString(tokenized + 1);
		trimmed_arg[getStringLength(trimmed_arg) - 1] = '\0';
	}

	trim_spaces(&((*parsed_args)[arg_index]), trimmed_arg);
	(*parsed_args)[arg_index + 1] = NULL;
	if (trimmed_arg != tokenized)
		free(trimmed_arg);
	tokenized = tokenizeString(NULL, delimiter, mode);
	arg_index++;
	}
}

