#include "includes/minishell.h"


int main(int argc, char **argv, char *envp[])
{
    char *cmd_line;
    char *prompt = "ohmyminishell~$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    while (TRUE)
    {
        cmd_line = readline(prompt);
        printf(cmd_line);
    }
    return (0);
}