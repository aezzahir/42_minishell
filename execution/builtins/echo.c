#include "../../minishell.h"


void echo(char *args[])
{
    bool newline = true;
    int i = 1;

    if (args[i] && args[i][0] == '-')
    {
        int j;
        while (args[i] && args[i][0] == '-')
        {
            j = 1;
            while (args[i][j] == 'n')
                j++;
            if (args[i][j] != '\0')
                break;
            newline = false;
            i++;
        }
    }

    while (args[i] != NULL)
    {
        if (i > 1)
            ft_putstr_fd(" ", 1);
        ft_putstr_fd(args[i], 1);
        i++;
    }

    if (newline)
        write(1, "\n", 1);
}
