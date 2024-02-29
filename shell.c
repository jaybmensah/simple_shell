#include "shell.h"

/**
 * main - Entry point
 * @ac: Number of arguments
 * @av: Array of arguments
 *
 * Return: 0
*/

int main(int ac __attribute__((unused)), char __attribute__((unused)) *av[])
{
	char *user_input = NULL, **command_tokens;
	size_t ui_size, cmd_ctr = 0;
	ssize_t ui_read;
	char *shell_name = av[0];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			cust_write(STDOUT_FILENO, "$ ");
		fflush(stdout);
		ui_read = getline(&user_input, &ui_size, stdin);
		++cmd_ctr;
		if (ui_read == -1)
		{
			free(user_input);
			user_input = NULL;
			if (isatty(STDIN_FILENO))
				cust_write(STDOUT_FILENO, "\n");
			exit(EXIT_SUCCESS);
		}
		user_input[ui_read - 1] = '\0';
		if (user_input[0] == '\0')
			continue;
		command_tokens = splitting_command(user_input, " \t\n\r\f\v");
		if (command_tokens == NULL)
			continue;
		if (strcmp(command_tokens[0], "exit") == 0)
		{
			free_memory(command_tokens);
			free(user_input);
			user_input = NULL;
			exit(EXIT_SUCCESS);
		}
		handle_command(user_input, command_tokens, shell_name);
		free(user_input);
		free_memory(command_tokens);
		user_input = NULL;
		command_tokens = NULL;
	}
	return (EXIT_SUCCESS);
}
