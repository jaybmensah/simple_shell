#include "shell.h"

/* extern char **environ; */
/**
 * handle_command - handles the command entered by the user
 * @user_input: the command entered by the user
 * @command_tokens: the command entered by the user
 * @shell_name: the name of the shell
 *
 * Return: none
*/
void handle_command(char *user_input __attribute__((unused)),
char **command_tokens, char *shell_name)
{
	pid_t childprocess;
	/* int status; */
	find_path(&command_tokens[0], shell_name);

	/* printf("Resolved path in handle_command: %s\n",*/
	/* command_tokens[0]); */ /*Debugging*/

	if (!check_access(command_tokens, shell_name))
		return;

	childprocess = fork();

	if (childprocess == -1)
	{
		perror("fork");
		return;
	}

	if (childprocess == 0)
	{
		execute_command(command_tokens);
	}
	else
	{
		handle_status(childprocess, shell_name, command_tokens[0]);
	}
}

/**
 * check_access - check the access permission of the command
 * @command_tokens: array of command tokens
 * @shell_name: name of the shell
 *
 * Return: true if the command is accessible, false otherwise
*/
int check_access(char **command_tokens, char *shell_name)
{
	if (access(command_tokens[0], X_OK) == -1)
	{
		fprintf(stderr, "%s: %s: command not found\n", shell_name,
		command_tokens[0]);
		/* free_memory(command_tokens); */
		return (0);
	}
	return (1);
}

/**
 * find_path - find the path of the command
 * @command: pointer to the command token
 * @shell_name: name of the shell
 *
 * Return: void
*/
void find_path(char **command, char *shell_name)
{
	cmds_path(command);

	/* printf("Resolved path in find_path: %s\n", *command); */ /* Debugging */

	if (command != NULL && access(*command, X_OK) == -1)
	{
		fprintf(stderr, "%s: %s: command not found\n", shell_name,
		*command);
		/* free_memory(command); */
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_command - execute the command in a child process
 * @command_tokens: array of command tokens
 *
 * Return: void
*/
void execute_command(char **command_tokens)
{
	if (execve(command_tokens[0], command_tokens, environ) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/**
 * handle_status - handle the exit status of the child process
 * @childprocess: pid of the child process
 * @shell_name: name of the shell
 * @command: name of the command
 *
 * Return: void
*/
void handle_status(pid_t childprocess, char *shell_name, char *command)
{
	int status;

	if (waitpid(childprocess, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}

	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);

		if (exit_status != 0)
			print_error(shell_name, command, exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		int term_signal = WTERMSIG(status);

		print_error(shell_name, command, -term_signal);
	}
}
