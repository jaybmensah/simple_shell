#include "shell.h"

/**
 * splitting_command - split a command into an array of strings
 * @input: command to be split
 * @delims: delimiters to be used
 *
 * Return: an array of strings
*/
char **splitting_command(char *input, const char *delims)
{
	char **command_tokens = NULL, *replicated_input, *tokens;
	ssize_t tok_num = 0, lup_cntr;

	if (input == NULL || *input == '\0')
		return (NULL);

	replicated_input = strdup(input);
	tokens = strtok(replicated_input, delims);

	tok_num = 0;
	while (tokens != NULL)
	{
		++tok_num;
		tokens = strtok(NULL, delims);
	}
	free(replicated_input);

	if (tok_num > 0)
	{
		command_tokens = malloc(sizeof(char *) * (tok_num + 1));
		if (command_tokens == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		tokens = strtok(input, delims);
		lup_cntr = 0;
		while (tokens != NULL)
		{
			command_tokens[lup_cntr] = strdup(tokens);
			tokens = strtok(NULL, delims);
			lup_cntr++;
		}
		command_tokens[lup_cntr] = NULL;

		return (command_tokens);
	}
	return (NULL);
}

/**
 * free_memory - free the memory allocated for the command
 * @command_tokens: array of strings to be freed
 *
 * Return: none
*/
void free_memory(char **command_tokens)
{
	size_t i;

	for (i = 0; command_tokens[i] != NULL; i++)
	{
		free(command_tokens[i]);
		command_tokens[i] = NULL;
	}
	free(command_tokens);
}

/**
 * cmds_path - get the path of the commands file
 * @pathName: name of the file
 *
 * Return: void
*/
void cmds_path(char **pathName)
{
	char *token = NULL, *tmp_path = NULL, *pathDir, *replicate_str;

	if (pathName == NULL || *pathName == NULL)
		return;

	pathDir = getenv("PATH");
	replicate_str = strdup(pathDir);
	token = strtok(replicate_str, ":");

	while (token != NULL)
	{
		if ((*pathName)[0] == '/' || (*pathName)[0] == '.')
		{
			/* If *pathName is an absolute or relative path, use it directly */
			tmp_path = strdup(*pathName);
		}
		else
		{
			tmp_path = malloc(strlen(*pathName) + strlen(token) + 2);
			if (tmp_path == NULL)
			{
				fprintf(stderr, "malloc failed\n");
				free(replicate_str);
				return;
			}
			sprintf(tmp_path, "%s/%s", token, *pathName);
		}

		if (access(tmp_path, X_OK) == 0)
		{
			free(*pathName);
			*pathName = strdup(tmp_path);
			free(tmp_path);
			free(replicate_str);
			return;
		}
		free(tmp_path);
		token = strtok(NULL, ":");
	}
	free(replicate_str);
}

