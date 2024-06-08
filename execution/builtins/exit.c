#include "../../minishell.h"

void exit_shell(char *arg)
{
    if (arg == NULL)
    {
        exit(0);
    }

    if (!is_number(arg))
    {
        print_error("numeric argument required", arg);
        exit(255);
    }

    int status = atoi(arg);
    exit(status);
}