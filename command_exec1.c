#include "shell.h"

/**
 * print_error - print an error message
 * @shell_name: name of the shell
 * @command: name of the command
 * @status: exit status of the command
 *
 * Return: void
*/
void print_error(char *shell_name, char *command, int status)
{
	char status_str[BUFFER_SIZE];

	int_to_str(status_str, status);
	cust_write(STDERR_FILENO, shell_name);
	cust_write(STDERR_FILENO, ": ");
	cust_write(STDERR_FILENO, status_str);
	cust_write(STDERR_FILENO, ": ");
	cust_write(STDERR_FILENO, command);
	cust_write(STDERR_FILENO, ": ");
	cust_write(STDERR_FILENO, (status < 0) ?
	"terminated by signal" : "exited with status");
	cust_write(STDERR_FILENO, " ");
	cust_write(STDERR_FILENO, status_str);
	cust_write(STDERR_FILENO, "\n");
}
