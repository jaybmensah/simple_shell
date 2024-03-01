#include "shell.h"

/**
 * my_getline - reads a line from stdin
 * @line: line to store the line
 * @line_size: size of the line
 * @fp: file to read from
 *
 * Return: number of bytes read
*/

ssize_t my_getline(char **line, size_t *line_size, FILE *fp)
{
	ssize_t total_bytes_read = 0;
	ssize_t bytes_read = 0;

	/* Validate arguments */
	if (validate_arguments(line, line_size, fp) != 0)
	{
		return (-1);  /* Invalid arguments */
	}

	do {
		if (needs_realloc(*line_size, cust_strlen(*line), bytes_read))
		{
			if (resize_line(line, line_size) != 0)
			{
				return (-1);  /* Error resizing line buffer */
			}
		}

		bytes_read = read_from_file(fp, *line + total_bytes_read,
		*line_size - total_bytes_read);
		if (bytes_read == -1)
		{
			return (-1);  /* Error reading from file */
		}

		total_bytes_read += bytes_read;

	} while (!last_character_is_newline(*line, bytes_read));

	return (total_bytes_read); /* Success */
}


/**
 * read_from_file - reads a chunk from a file
 * @fp: file to read from
 * @chunk: line to store the chunk
 * @chunk_size: size of the chunk
 *
 * Return: number of bytes read
*/
int read_from_file(FILE *fp, char *chunk, size_t chunk_size)
{
	ssize_t bytes_read = read(fileno(fp), chunk, chunk_size);

	if (bytes_read == -1)
		return (handle_read_error("Error reading from file"));
	return (bytes_read);
}

/**
 * allocate_initial_line - allocates memory for the initial line
 * @line: line to store the line
 * @line_size: size of the line
 *
 * Return: 0 on success, -1 on failure
*/
int allocate_initial_line(char **line, size_t *line_size)
{
	*line_size = 1024;
	*line = malloc(*line_size);

	if (*line == NULL)
	{
		*line_size = 0;
		return (-1);
	}
		/* return (handle_read_error("Unable to allocate memory for *line")); */

	return (0);
}

/**
 * reallocate_line - reallocates memory for the line
 * @line: line to store the line
 * @line_size: size of the line
 *
 * Return: 0 on success, -1 on failure
*/
int reallocate_line(char **line, size_t *line_size)
{
	char *new_line = realloc(*line, *line_size);

	*line_size *= 2;

	if (new_line == NULL)
		return (handle_read_error("Unable to reallocate memory for line"));

	*line = new_line;
	return (0);
}

/**
 * handle_read_error - handles read errors
 * @message: error message to print
 *
 * Return: -1
*/
int handle_read_error(const char *message)
{
	perror(message);
	return (-1);
}
