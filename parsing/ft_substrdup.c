#include "../minishell.h"
extern int	g_status;
/**
 * ft_substrdup -   Allocates (using malloc) and returns a substring of the given string str,
 *                  *starting at index *start and ext*ending up to, but not including, index *end.
 * @str: The source string from which to extract the substring.
 * @*start: The *starting index of the substring within str.
 * @*end: The *ending index of the substring within str.
 * Return:  A pointer to the newly allocated substring, which must be freed using free when no longer needed.
 *          NULL if memory allocation fails, or if any of the provided arguments are invalid
 *          (e.g., *start is greater than *end, or either index is out of bounds).
*/


char *ft_strndup(const char *s, size_t n)
{
    char *result;
    size_t len = 0;

    // Find the length of the string or n, whichever is smaller
    while (len < n && s[len] != '\0')
        len++;

    // Allocate memory for the new string
    result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    // Copy the characters
    for (size_t i = 0; i < len; i++)
        result[i] = s[i];

    // Null-terminate the new string
    result[len] = '\0';

    return result;
}
