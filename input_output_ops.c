#include "shell.h"

/**
 * cust_write - Custom write function
 * @str: String to write
 * @fd: File descriptor
 *
 * Return: none
*/
void cust_write(int fd, const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
		len++;

	write(fd, str, len);
}

/**
 * int_to_str - Convert an integer to a string
 * @str: String to write
 * @num: Integer to convert
 *
 * Return: none
*/
void int_to_str(char *str, int num)
{
	int i = 0, sign = 0, start = 0, end;

	if (num < 0)
	{
		sign = 1;
		num = -num;
	}

	do {
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num > 0);

	if (sign)
		str[i++] = '-';

	str[i] = '\0';

	if (sign)
		start = 1;

	end = i - 1;
	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

