#include "../minishell.h"

/**
 * ft_substrdup -   Allocates (using malloc) and returns a substring of the given string str,
 *                  starting at index start and extending up to, but not including, index end.
 * @str: The source string from which to extract the substring.
 * @start: The starting index of the substring within str.
 * @end: The ending index of the substring within str.
 * Return:  A pointer to the newly allocated substring, which must be freed using free when no longer needed.
 *          NULL if memory allocation fails, or if any of the provided arguments are invalid
 *          (e.g., start is greater than end, or either index is out of bounds).
*/

char	*ft_substrdup(const char *str, int start, int end)
{
	char	*ptr;
	int	len;
	int	i;

	len = ft_strlen(str);
    if (!(start >= 0 && end <= len && start <= end))
        return (NULL);
    else
        len = end - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = str[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int ft_iswhitespace(char c)
{

}
int ft_isquote(char c)
{

}

int ft_isdquote(char c)
{

}

int ft_ispipe(char c)
{

}

int ft_isoutfile(char c)
{

}
int ft_isinfile(char c)
{

}
int ft_isoutfile_appendmode(char *str)
{

}
int ft_herdoc(char *str)
{
    
}