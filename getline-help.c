#include "shell.h"

/**
 * needs_realloc - checks if reallocating is needed
 * @cur_syz: current size of the buffer
 * @cur_len: current length of the string in the buffer
 * @bytes_read: number of bytes read in the last chunk
 *
 * Return: 1 if reallocation is needed, 0 otherwise
 */
int needs_realloc(size_t cur_syz, size_t cur_len, ssize_t bytes_read)
{
	return ((cur_syz - cur_len) < (size_t)bytes_read);
}

/**
 * concatenate_chunk - concatenates the read chunk to the line
 * @line: line to concatenate to
 * @line_size: size of the line
 * @bytes_read: number of bytes read in the last chunk
 *
 * Return: 0 on success, -1 on failure
 */
ssize_t concatenate_chunk(FILE *fp, char **line, size_t line_size, ssize_t bytes_read)
{
	ssize_t chunk_bytes;
	char chunk[1024]; // Assuming a reasonable size for the chunk

	if ((*line) == NULL)
	{
		(*line) = malloc(line_size);
		if ((*line) == NULL)
			return (-1);
	}
	chunk_bytes = fread(chunk, 1, bytes_read, fp);

	if (line_size < (size_t)bytes_read)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}

	chunk_bytes = read_from_file(fp, chunk, sizeof(chunk));

	if (chunk_bytes == -1)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}

	strncat(*line, chunk, chunk_bytes);
	return chunk_bytes;
}

/**
 * last_character_is_newline - checks if the last character
 * in the line is a newline
 * @line: line to check
 * @bytes_read: number of bytes read in the last chunk
 *
 * Return: 1 if the last character is a newline, 0 otherwise
 */
int last_character_is_newline(const char *line, ssize_t bytes_read)
{
	return ((bytes_read > 0) && (line[bytes_read - 1] == '\n'));
}

/**
 * validate_arguments - validates the arguments for my_getline function
 * @line: pointer to the line buffer
 * @line_size: pointer to the size of the line buffer
 * @fp: file pointer
 *
 * Return: 0 on success, -1 on failure
 */
int validate_arguments(char **line, size_t *line_size, FILE *fp)
{
	if (line == NULL || line_size == NULL || fp == NULL)
	{
		return (-1);  /* Error: Invalid arguments */
	}
	return (0); /* Success */
}
