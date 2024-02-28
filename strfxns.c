#include "shell.h"

/**
 * cust_print - Function that prints a string to the screen
 * @str: String to print
 *
 * Return: Number of characters printed
 */
int cust_print(char *str)
{
	while (*str != '\0')
	{
		cust_putchar(*str);
		str++;
	}

	return (0);
}

/**
 * cust_putchar - Prints a character to the screen
 * @c: Character to print
 *
 * Return: Nothing
 */
void cust_putchar(char c)
{
	write(1, &c, 1);
}


/**
 * cust_strlen - Function that calculates the length of a string.
 * @input_str: Pointer to the string
 *
 * Return: The length of the string
 */

int cust_strlen(char *input_str)
{
	int char_count = 0;

	while (*input_str != '\0')
	{
		char_count++;
		input_str++;
	}

	return (char_count);
}

/**
 * cust_strcpy - A custom string copy function
 * @destination: Pointer to the destination string
 * @source: Pointer to the source string
 *
 * Return: Pointer to the destination string
 */

char *cust_strcpy(char *destination, const char *source)
{
	int index = 0;

	while (source[index] != '\0')
	{
		destination[index] = source[index];
		index++;
	}

	destination[index] = '\0';

	return (destination);
}

/**
 * cust_strcmp - A custom string comparison function
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 *
 * Return: 0 if the strings are equal, -1 if the first string is less than the
 *	second, 1 if the first string is greater than the second
*/
int cust_strcmp(const char *s1, const char *s2)
{
	int result = 0, i;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] < s2[i])
		{
			result = -1;
			break;
		}
		else if (s1[i] > s2[i])
		{
			result = 1;
			break;
		}
	}
	return (result);
}

