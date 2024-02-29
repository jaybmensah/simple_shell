#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stddef.h>

#define BUFFER_SIZE 32
#define INITIAL_BUFFER_SIZE 1024

extern char **environ;
/* command_processing */
char **splitting_command(char *input, const char *delims);
void free_memory(char **command_tokens);
void cmds_path(char **pathName);

/* io_operations */
void cust_write(int fd, const char *str);
void int_to_str(char *str, int num);

/* command_execution */
void handle_command(char *user_input __attribute__((unused)),
char **command_tokens, char *shell_name);
int check_access(char **command_tokens, char *shell_name);
void find_path(char **command, char *shell_name);
void execute_command(char **command_tokens);
void handle_status(pid_t childprocess, char *shell_name, char *command);
void print_error(char *shell_name, char *command, int status);

/* string_fxns */
int cust_print(char *str);
void cust_putchar(char c);
int cust_strlen(char *input_str);
char *cust_strcpy(char *destination, const char *source);
int cust_strcmp(const char *s1, const char *s2);

/* my_getline */
ssize_t my_getline(char **line, size_t *line_size, FILE *fp);
int read_from_file(FILE *fp, char *chunk, size_t chunk_size);
int allocate_initial_line(char **line, size_t *line_size);
int reallocate_line(char **line, size_t *line_size);
int handle_read_error(const char *message);

/* getline-help */
int needs_realloc(size_t cur_syz, size_t cur_len, ssize_t bytes_read);
int concatenate_chunk(char **line, size_t line_size, ssize_t bytes_read);
int last_character_is_newline(const char *line, ssize_t bytes_read);
int validate_arguments(char **line, size_t *line_size, FILE *fp);
ssize_t read_chunk(FILE *fp, char *line, size_t line_size);

#endif /* SHELL_H */
